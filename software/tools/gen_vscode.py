"""Generate the VS Code C/C++ configuration from the S32DS projects.

IntelliSense uses the same include paths and defines as the S32DS build
(Debug_FLASH of firmware/application/.cproject and firmware/bootloader/.cproject),
so a .c/.h file is resolved the same way as in S32 Design Studio. Every path is
written relative to ${workspaceFolder}, so the files work on any clone.

A configuration is written for each folder that can be opened in VS Code:
  <repo>/                    -> "Application", "Bootloader"
  <repo>/firmware/application -> "Application"
  <repo>/firmware/bootloader  -> "Bootloader"
  <repo>/firmware/common      -> "Application", "Bootloader"
and the multi-root workspace <repo>/mock-ecu-s32k144.code-workspace opens the
projects side by side, each folder with its own configuration.

usage: python software/tools/gen_vscode.py      (re-run after changing a .cproject)
"""
import json
import os
import posixpath
import xml.etree.ElementTree as ET

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
PROJECTS = {'Application': 'firmware/application', 'Bootloader': 'firmware/bootloader'}
LOCATIONS = {
    '.': ['Application', 'Bootloader'],
    'firmware/application': ['Application'],
    'firmware/bootloader': ['Bootloader'],
    'firmware/common': ['Application', 'Bootloader'],
}
BUILD_CONFIG = 'Debug_FLASH'

# Toolchain install dir: the only machine specific value, kept as one variable.
S32DS_ROOT = 'C:/NXP/S32DS.3.6.10'
COMPILER = '${S32DS_ROOT}/S32DS/build_tools/gcc_v11.4/gcc-11.4-arm32-eabi/bin/arm-none-eabi-gcc.exe'
COMPILER_ARGS = ['-mcpu=cortex-m4', '-mthumb', '-mfloat-abi=hard', '-mfpu=fpv4-sp-d16', '-std=c99']

FILES_EXCLUDE = {'**/Debug_FLASH': True, '**/Release_FLASH': True, '**/.metadata': True}
INTELLISENSE_EXCLUDE = dict(FILES_EXCLUDE, **{'**/reference/**': True, '**/mcal/Spi/**': True})


def read_cproject(project):
    """Return (include dirs relative to the repo, defines) of the C compiler of BUILD_CONFIG."""
    proj = PROJECTS[project]
    root = ET.parse(os.path.join(REPO, proj, '.cproject')).getroot()
    for cc in root.iter('cconfiguration'):
        cfg = cc.find("storageModule[@moduleId='cdtBuildSystem']/configuration")
        if cfg is None or cfg.get('name') != BUILD_CONFIG:
            continue
        for tool in cfg.iter('tool'):
            if not tool.get('superClass', '').endswith('.c.compiler'):
                continue
            incs, defs = [], []
            for opt in tool.findall('option'):
                sc = opt.get('superClass', '')
                vals = [v.get('value') for v in opt.findall('listOptionValue')]
                if sc == 'gnu.c.compiler.option.include.paths':
                    for v in vals:
                        v = v.strip('"').replace('${ProjDirPath}', proj)
                        incs.append(posixpath.normpath(v))
                elif sc == 'gnu.c.compiler.option.preprocessor.def.symbols':
                    defs = vals
            return incs, defs
    raise SystemExit('no %s C compiler options in %s/.cproject' % (BUILD_CONFIG, proj))


def ws_path(location, repo_rel):
    rel = posixpath.relpath(repo_rel, location if location != '.' else '.')
    return '${workspaceFolder}' if rel == '.' else '${workspaceFolder}/' + rel


def configuration(location, project):
    incs, defs = read_cproject(project)
    sources = [PROJECTS[project] + '/src', PROJECTS[project] + '/cfg', 'firmware/common']
    return {
        'name': project,
        'includePath': [ws_path(location, p) for p in incs],
        'defines': defs,
        'compilerPath': COMPILER,
        'compilerArgs': COMPILER_ARGS,
        'cStandard': 'c99',
        'intelliSenseMode': 'gcc-arm',
        'browse': {
            'path': [ws_path(location, p) for p in sources + incs],
            'limitSymbolsToIncludedHeaders': True,
        },
    }


def settings():
    return {
        'files.associations': {
            '*.h': 'c',
            '*.xdm': 'xml',
            '*.epc': 'xml',
            '*.cproject': 'xml',
            '.cproject': 'xml',
            '.project': 'xml',
            '*.launch': 'xml',
            '*.args': 'plaintext',
        },
        'files.exclude': FILES_EXCLUDE,
        'search.exclude': dict(FILES_EXCLUDE, **{'**/reference/**': True}),
        'C_Cpp.files.exclude': INTELLISENSE_EXCLUDE,
        'C_Cpp.default.cStandard': 'c99',
        'C_Cpp.errorSquiggles': 'enabled',
        'files.eol': '\n',
    }


def write_json(path, data):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w', encoding='utf8', newline='\n') as f:
        json.dump(data, f, indent=4)
        f.write('\n')
    print('wrote', os.path.relpath(path, REPO).replace(os.sep, '/'))


for loc, projects in LOCATIONS.items():
    base = os.path.join(REPO, loc, '.vscode')
    write_json(os.path.join(base, 'c_cpp_properties.json'), {
        'env': {'S32DS_ROOT': S32DS_ROOT},
        'configurations': [configuration(loc, p) for p in projects],
        'version': 4,
    })
    write_json(os.path.join(base, 'settings.json'), settings())

write_json(os.path.join(REPO, '.vscode', 'extensions.json'),
           {'recommendations': ['ms-vscode.cpptools', 'ms-vscode.cpptools-extension-pack']})

write_json(os.path.join(REPO, 'mock-ecu-s32k144.code-workspace'), {
    'folders': [
        {'name': 'application (S32DS)', 'path': 'firmware/application'},
        {'name': 'bootloader (S32DS)', 'path': 'firmware/bootloader'},
        {'name': 'common', 'path': 'firmware/common'},
        {'name': 'mcal_config (EB Tresos)', 'path': 'firmware/mcal_config'},
        {'name': 'repo', 'path': '.'},
    ],
    'settings': settings(),
    'extensions': {'recommendations': ['ms-vscode.cpptools']},
})
