# Plan: dựng khung API cho firmware/common

## A. Quy ước chung

| Mục | Quy ước |
|---|---|
| Thư mục | bsw/<Mod>/include + bsw/<Mod>/src, giống mcal/*. ecum/include + ecum/src. Header SchM dùng chung đặt trong stubs/, header boot đặt trong boot_shared/. Xoá .gitkeep khi thư mục đã có file. |
| File .h (đầy đủ) | Include guard, các macro version (Vendor ID, Module ID theo BSW Module List), Service ID và mã lỗi DET lấy từ SWS, các kiểu dữ liệu ở chương 8.2 của SWS, prototype kèm doxygen (@brief, SWS ID, Service ID, SRS ID). |
| File .c (thân hàm trống) | Mỗi hàm chỉ có (void)param; và /* TODO(<SRS_ID>): SWS_xxx */. Hàm có kiểu trả về thì thêm một dòng return E_NOT_OK; (hoặc BUFREQ_E_NOT_OK) để không bị warning -Wreturn-type. |
| Chữ ký hàm | Luôn theo SWS R24-11. Chữ ký trong classic-platform đã khớp SWS thì giữ nguyên prototype. Mình không copy thân hàm của repo vì repo là GPL và bạn yêu cầu không viết phần implement. |
| Commit | Mỗi module một commit, làm ngay trên feature/platform-mcal-config. Mẫu: feat(<scope>): add <Mod> API skeleton per SWS R24-11, thân commit ghi Refs: <SRS IDs>. Không thêm dòng Co-Authored-By (theo memory của bạn). |

Ký hiệu trong bảng: ✅ repo khớp SWS, giữ prototype · ✏️ repo khác SWS, sửa theo SWS · ➕ repo không có, thêm theo SWS.

### Phần 1: stubs/ (commit chore(stubs): add SchM headers for BSW main functions)

SWS quy định các hàm MainFunction được khai báo qua SchM_<Mod>.h. Phần này tạo SchM_CanIf.h, SchM_CanTp.h, SchM_PduR.h, SchM_CanSM.h, SchM_ComM.h, SchM_Dcm.h, SchM_Dem.h. Mỗi file chứa prototype MainFunction (xem bảng các phần sau) và macro exclusive area để trống.

### Phần 2: Det (feat(det)): Det.h, Det.c

| API | SWS ID | SvcID | Chữ ký R24-11 | Repo | SRS |
|---|---|---|---|---|---|
| Det_Init | SWS_Det_00008 | 0x00 | void (const Det_ConfigType* ConfigPtr) | ✏️ repo là (void) | DET_SRS_002 |
| Det_ReportError | SWS_Det_00009 | 0x01 | Std_ReturnType (uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId) | ✅ | DET_SRS_001/002 |
| Det_Start | SWS_Det_00010 | 0x02 | void (void) | ✅ | — |
| Det_GetVersionInfo | SWS_Det_00011 | 0x03 | void (Std_VersionInfoType* versioninfo) | ✅ | — |
| Det_ReportRuntimeError | SWS_Det_01001 | 0x04 | Std_ReturnType (uint16, uint8, uint8, uint8 ErrorId) | ➕ | DET_SRS_003/004 |
| Det_ReportTransientFault | SWS_Det_01003 | 0x05 | Std_ReturnType (uint16, uint8, uint8, uint8 FaultId) | ➕ | — |

Loại bỏ: Det_AddCbk, Det_RemoveCbk, Det_DeInit. Đây là extension của ArcCore, R24-11 không có.

### Phần 3: EcuM + scheduler (feat(ecum)): EcuM.h, EcuM_Externals.h, Os_Sched.h, EcuM.c, EcuM_Callout.c, Os_Sched.c

classic-platform EcuM cần OS nên phần này viết mới theo doc. RTD đang #include "EcuM.h" và "EcuM_Externals.h".

| API | SWS ID | SvcID | Chữ ký | Nguồn | SRS |
|---|---|---|---|---|---|
| EcuM_Init | SWS_EcuM_02811 | 0x01 | void (void) | ➕ | ECUM_SRS_001/003 |
| EcuM_GetVersionInfo | SWS_EcuM_02813 | 0x00 | void (Std_VersionInfoType*) | ➕ | — |
| EcuM_SetWakeupEvent | SWS_EcuM_02826 | 0x0c | void (EcuM_WakeupSourceType sources) | ➕ (RTD gọi) | — |
| EcuM_CheckWakeup | SWS_EcuM_91007 | 0x49 | void (EcuM_WakeupSourceType wakeupSource) | ➕ (RTD gọi) | — |
| EcuM_AL_DriverInitZero | SWS_EcuM_02905 | 0x31 | void (void) (callout) | ➕ | ECUM_SRS_001 |
| EcuM_AL_DriverInitOne | SWS_EcuM_02907 | 0x33 | void (void) (callout) | ➕ | ECUM_SRS_001 |
| EcuM_AL_Reset | SWS_EcuM_04065 | 0x4C | void (EcuM_ResetType reset) | ➕ | ECUM_SRS_004 |
| EcuM_ErrorHook | SWS_EcuM_02904 | 0x30 | void (uint16 reason) | ➕ | — |
| Os_Sched_Run / Os_Sched_Tick1ms / Os_Task_1ms / Os_Task_10ms | — (Project) | — | void (void) | ➕ | ECUM_SRS_002 |

Loại bỏ: StartupTwo, Shutdown, các API sleep/wakeup alarm (không có OS, không có sleep; xem SRS 3.11.2).

### Phần 4: CanIf (feat(canif)): CanIf.h, CanIf_Types.h, CanIf_Can.h, CanIf.c

RTD include CanIf_Can.h và kiểm tra macro CANIF_CAN_AR_RELEASE_* trong file này.

| API | SWS ID | SvcID | Chữ ký R24-11 | Repo | SRS |
|---|---|---|---|---|---|
| CanIf_Init | SWS_CANIF_00001 | 0x01 | void (const CanIf_ConfigType* ConfigPtr) | ✅ | CANIF_SRS_001 |
| CanIf_SetControllerMode | SWS_CANIF_00003 | 0x03 | Std_ReturnType (uint8 ControllerId, Can_ControllerStateType ControllerMode) | ✏️ CanIf_ControllerModeType → Can_ControllerStateType | CANIF_SRS_008 |
| CanIf_GetControllerMode | SWS_CANIF_00229 | 0x04 | Std_ReturnType (uint8, Can_ControllerStateType* ControllerModePtr) | ✏️ đổi kiểu | — |
| CanIf_Transmit | SWS_CANIF_00005 | 0x49 | Std_ReturnType (PduIdType TxPduId, const PduInfoType* PduInfoPtr) | ✅ | CANIF_SRS_002/003 |
| CanIf_SetPduMode | SWS_CANIF_00008 | 0x09 | Std_ReturnType (uint8 ControllerId, CanIf_PduModeType PduModeRequest) | ✏️ CanIf_PduSetModeType → CanIf_PduModeType | CANIF_SRS_004 |
| CanIf_GetPduMode | SWS_CANIF_00009 | 0x0a | Std_ReturnType (uint8, CanIf_PduModeType* PduModePtr) | ✏️ đổi kiểu | — |
| CanIf_GetVersionInfo | SWS_CANIF_00158 | 0x0b | void (Std_VersionInfoType*) | ✏️ macro → hàm | — |
| CanIf_TxConfirmation | SWS_CANIF_00007 | 0x13 | void (PduIdType CanTxPduId) | ✅ | CANIF_SRS_007 |
| CanIf_RxIndication | SWS_CANIF_00006 | 0x14 | void (const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr) | ✅ (bỏ biến thể 3.x) | CANIF_SRS_005/006 |
| CanIf_ControllerBusOff | SWS_CANIF_00218 | 0x16 | void (uint8 ControllerId) | ✅ | CANIF_SRS_010 |
| CanIf_ControllerModeIndication | SWS_CANIF_00699 | 0x17 | void (uint8, Can_ControllerStateType ControllerMode) | ✏️ đổi kiểu | CANIF_SRS_009 |
| CanIf_ControllerErrorStatePassive | SWS_CANIF_91008 | 0x4f | void (uint8, uint16 RxErrorCounter, uint16 TxErrorCounter) | ➕ (RTD gọi khi bật error IRQ) | — |
| CanIf_ErrorNotification | SWS_CANIF_91009 | 0x50 | void (uint8, Can_ErrorType Can_ErrorType) | ➕ (như trên) | — |

Loại bỏ: các API Trcv/Wakeup/PN (SWS_CANIF_00287 ghi N/A), DynamicTxId, ReadRx/TxNotifStatus, TriggerTransmit (RTD đang TRIGGER_TRANSMIT_USED = OFF), DeInit, SetBaudrate, timestamp, mirroring.

### Phần 5: PduR (feat(pdur)): PduR.h, PduR_Types.h, PduR_CanTp.h, PduR_Dcm.h, PduR.c, PduR_CanTp.c, PduR_Dcm.c

| API | SWS ID | SvcID | Chữ ký R24-11 | Repo | SRS |
|---|---|---|---|---|---|
| PduR_Init | SWS_PduR_00334 | 0xf0 | void (const PduR_PBConfigType* ConfigPtr) | ✅ | PDUR_SRS_001 |
| PduR_GetVersionInfo | SWS_PduR_00338 | 0xf1 | void (Std_VersionInfoType*) | ✅ | — |
| PduR_GetConfigurationId | SWS_PduR_00341 | 0xf2 | PduR_PBConfigIdType (void) | ✅ | — |
| PduR_DcmTransmit | SWS_PduR_00406 | 0x49 | Std_ReturnType (PduIdType TxPduId, const PduInfoType* PduInfoPtr) | ✅ | PDUR_SRS_004 |
| PduR_CanTpStartOfReception | SWS_PduR_00507 | 0x46 | BufReq_ReturnType (PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr) | ✏️ thiếu info | PDUR_SRS_002 |
| PduR_CanTpCopyRxData | SWS_PduR_00512 | 0x44 | BufReq_ReturnType (PduIdType, const PduInfoType* info, PduLengthType* bufferSizePtr) | ✏️ thiếu const | PDUR_SRS_003 |
| PduR_CanTpRxIndication | SWS_PduR_00375 | 0x45 | void (PduIdType id, Std_ReturnType result) | ✏️ NotifResultType → Std_ReturnType | PDUR_SRS_003 |
| PduR_CanTpCopyTxData | SWS_PduR_00518 | 0x43 | BufReq_ReturnType (PduIdType, const PduInfoType* info, const RetryInfoType* retry, PduLengthType* availableDataPtr) | ✏️ thiếu const | PDUR_SRS_005 |
| PduR_CanTpTxConfirmation | SWS_PduR_00381 | 0x48 | void (PduIdType id, Std_ReturnType result) | ✏️ NotifResultType → Std_ReturnType | PDUR_SRS_005 |

Loại bỏ: Enable/DisableRouting, Cancel*, glue cho CanIf và các bus khác (IF routing N/A, SWS_PduR_00625/00627/00621).

### Phần 6: CanTp (feat(cantp)): CanTp.h, CanTp_Types.h, CanTp.c

| API | SWS ID | SvcID | Chữ ký R24-11 | Repo | SRS |
|---|---|---|---|---|---|
| CanTp_Init | SWS_CanTp_00208 | 0x01 | void (const CanTp_ConfigType* CfgPtr) | ✅ | CANTP_SRS_001 |
| CanTp_GetVersionInfo | SWS_CanTp_00210 | 0x07 | void (Std_VersionInfoType*) | ✏️ macro → hàm | — |
| CanTp_Shutdown | SWS_CanTp_00211 | 0x02 | void (void) | ✅ | — |
| CanTp_Transmit | SWS_CanTp_00212 | 0x49 | Std_ReturnType (PduIdType TxPduId, const PduInfoType* PduInfoPtr) | ✅ | CANTP_SRS_002/003 |
| CanTp_MainFunction | SWS_CanTp_00213 | 0x06 | void (void) (khai báo trong SchM_CanTp.h) | ✅ | CANTP_SRS_006/007 |
| CanTp_RxIndication | SWS_CanTp_00214 | 0x42 | void (PduIdType RxPduId, const PduInfoType* PduInfoPtr) | ✏️ thiếu const | CANTP_SRS_004/005/008/009 |
| CanTp_TxConfirmation | SWS_CanTp_00215 | 0x40 | void (PduIdType TxPduId, Std_ReturnType result) | ✏️ thiếu result | CANTP_SRS_003/007 |

Loại bỏ: Cancel/ChangeParameter/ReadParameter. Đây là API tuỳ chọn và Dcm không dùng ở v1.0.

### Phần 7: Dem (feat(dem)): Dem.h, Dem_Types.h, Dem.c

Mcu_PBcfg.c của RTD đang include Dem.h và gọi Dem_SetEventStatus.

| API | SWS ID | SvcID | Chữ ký R24-11 | Repo | SRS |
|---|---|---|---|---|---|
| Dem_PreInit | SWS_Dem_00179 | 0x01 | void (void) | ✏️ repo có ConfigPtr | DEM_SRS_001 |
| Dem_Init | SWS_Dem_00181 | 0x02 | void (const Dem_ConfigType* ConfigPtr) | ✏️ repo là (void) | — |
| Dem_Shutdown | SWS_Dem_00182 | 0x03 | void (void) | ✅ | — |
| Dem_GetVersionInfo | SWS_Dem_00177 | 0x00 | void (Std_VersionInfoType*) | ✏️ macro → hàm | — |
| Dem_MainFunction | SWS_Dem_00266 | 0x55 | void (void) (khai báo trong SchM_Dem.h) | ✅ | — |
| Dem_SetEventStatus | SWS_Dem_00183 | 0x04 | Std_ReturnType (Dem_EventIdType EventId, Dem_EventStatusType EventStatus) | ✅ | DEM_SRS_002/003/006 |
| Dem_ResetEventStatus | SWS_Dem_00185 | 0x05 | Std_ReturnType (Dem_EventIdType) | ✅ | — |
| Dem_RestartOperationCycle | SWS_Dem_00194 | 0x08 | Std_ReturnType (uint8 OperationCycleId) | ➕ | DEM_SRS_007, ECUM_SRS_003 |
| Dem_GetEventUdsStatus | SWS_Dem_91008 | 0xb6 | Std_ReturnType (Dem_EventIdType, Dem_UdsStatusByteType* UDSStatusByte) | ➕ | DEM_SRS_004 |
| Dem_GetDTCOfEvent | SWS_Dem_00198 | 0x0d | Std_ReturnType (Dem_EventIdType, Dem_DTCFormatType, uint32* DTCOfEvent) | ✅ | — |
| Dem_SelectDTC | SWS_Dem_91016 | 0xb7 | Std_ReturnType (uint8 ClientId, uint32 DTC, Dem_DTCFormatType, Dem_DTCOriginType) | ➕ | DCM_SRS_012 |
| Dem_ClearDTC | SWS_Dem_00665 | 0x23 | Std_ReturnType (uint8 ClientId) | ✏️ repo theo kiểu 4.0.3 | DEM_SRS_005 |
| Dem_DisableDTCSetting | SWS_Dem_00242 | 0x24 | Std_ReturnType (uint8 ClientId) | ✏️ | DEM_SRS_006 |
| Dem_EnableDTCSetting | SWS_Dem_00243 | 0x25 | Std_ReturnType (uint8 ClientId) | ✏️ | DCM_SRS_013 |
| Dem_SetDTCFilter | SWS_Dem_00208 | 0x13 | Std_ReturnType (uint8 ClientId, uint8 DTCStatusMask, Dem_DTCFormatType, Dem_DTCOriginType, boolean FilterWithSeverity, Dem_DTCSeverityType, boolean FilterForFaultDetectionCounter) | ✏️ | DCM_SRS_012 |
| Dem_GetNumberOfFilteredDTC | SWS_Dem_00214 | 0x17 | Std_ReturnType (uint8 ClientId, uint16*) | ✏️ | DCM_SRS_012 |
| Dem_GetNextFilteredDTC | SWS_Dem_00215 | 0x18 | Std_ReturnType (uint8 ClientId, uint32* DTC, uint8* DTCStatus) | ✏️ | DCM_SRS_012 |
| Dem_GetDTCStatusAvailabilityMask | SWS_Dem_00213 | 0x16 | Std_ReturnType (uint8 ClientId, Dem_UdsStatusByteType*, Dem_DTCOriginType) | ✏️ | DCM_SRS_012 |
| Dem_GetTranslationType | SWS_Dem_00230 | 0x3c | Dem_DTCTranslationFormatType (uint8 ClientId) | ✏️ | DCM_SRS_012 |

Loại bỏ: Freeze frame, extended data, OBD, IUMPR, Dlt, NvM (SWS_Dem_00388 ghi N/A), Dem_ReportErrorStatus (không còn trong R24-11).

### Phần 8: CanSM (feat(cansm)): CanSM.h, CanSM_CanIf.h, CanSM.c

| API | SWS ID | SvcID | Chữ ký R24-11 | Repo | SRS |
|---|---|---|---|---|---|
| CanSM_Init | SWS_CanSM_00023 | 0x00 | void (const CanSM_ConfigType* ConfigPtr) | ✅ | CANSM_SRS_001 |
| CanSM_DeInit | SWS_CanSM_91001 | 0x14 | void (void) | ➕ | — |
| CanSM_GetVersionInfo | SWS_CanSM_00024 | 0x01 | void (Std_VersionInfoType*) | ✏️ macro → hàm | — |
| CanSM_RequestComMode | SWS_CanSM_00062 | 0x02 | Std_ReturnType (NetworkHandleType network, ComM_ModeType ComM_Mode) | ✅ | CANSM_SRS_002 |
| CanSM_GetCurrentComMode | SWS_CanSM_00063 | 0x03 | Std_ReturnType (NetworkHandleType, ComM_ModeType* ComM_ModePtr) | ✅ | — |
| CanSM_MainFunction | SWS_CanSM_00065 | 0x05 | void (void) (khai báo trong SchM_CanSM.h) | ✅ | CANSM_SRS_005 |
| CanSM_ControllerBusOff | SWS_CanSM_00064 | 0x04 | void (uint8 ControllerId) | ✅ | CANSM_SRS_003/004 |
| CanSM_ControllerModeIndication | SWS_CanSM_00396 | 0x07 | void (uint8, Can_ControllerStateType ControllerMode) | ✏️ đổi kiểu | — |

Loại bỏ: Trcv/PN/Wakeup, SetBaudrate, SetEcuPassive, TxTimeoutException (SWS_CanSM_00653 ghi N/A).

### Phần 9: ComM (feat(comm)): ComM.h, ComM_Types.h, ComM_Dcm.h, ComM_BswM.h, ComM.c

| API | SWS ID | SvcID | Chữ ký R24-11 | Repo | SRS |
|---|---|---|---|---|---|
| ComM_Init | SWS_ComM_00146 | 0x01 | void (const ComM_ConfigType* ConfigPtr) | ✅ | COMM_SRS_001 |
| ComM_DeInit | SWS_ComM_00147 | 0x02 | void (void) | ✅ | — |
| ComM_GetStatus | SWS_ComM_00242 | 0x03 | Std_ReturnType (ComM_InitStatusType* Status) | ✅ | COMM_SRS_001 |
| ComM_RequestComMode | SWS_ComM_00110 | 0x05 | Std_ReturnType (ComM_UserHandleType User, ComM_ModeType ComMode) | ✅ | COMM_SRS_002 |
| ComM_GetRequestedComMode | SWS_ComM_00079 | 0x07 | Std_ReturnType (ComM_UserHandleType, ComM_ModeType*) | ✅ | — |
| ComM_GetCurrentComMode | SWS_ComM_00083 | 0x08 | Std_ReturnType (ComM_UserHandleType, ComM_ModeType*) | ✅ | — |
| ComM_GetVersionInfo | SWS_ComM_00370 | 0x10 | void (Std_VersionInfoType*) | ✏️ macro → hàm | — |
| ComM_DCM_ActiveDiagnostic | SWS_ComM_00873 | 0x1f | void (NetworkHandleType Channel) | ✅ | COMM_SRS_003 |
| ComM_DCM_InactiveDiagnostic | SWS_ComM_00874 | 0x20 | void (NetworkHandleType Channel) | ✅ | COMM_SRS_003 |
| ComM_BusSM_ModeIndication | SWS_ComM_00675 | 0x33 | void (NetworkHandleType, ComM_ModeType ComMode) | ✏️ repo truyền con trỏ | COMM_SRS_002 |
| ComM_CommunicationAllowed | SWS_ComM_00871 | 0x35 | void (NetworkHandleType, boolean Allowed) | ✅ | — |
| ComM_MainFunction_CAN0 | SWS_ComM_00429 | 0x60 | void (void) (khai báo trong SchM_ComM.h) | ✏️ thay macro bằng hàm có tên cố định | COMM_SRS_004 |

Loại bỏ: Nm_, PNC, Inhibition/Limit, EcuM_WakeUpIndication (SWS_ComM_00869/00890 ghi N/A).

### Phần 10: Dcm (feat(dcm)): Dcm.h, Dcm_Types.h, Dcm_ComM.h, Dcm_Externals.h, Dcm.c

| API | SWS ID | SvcID | Chữ ký R24-11 | Repo | SRS |
|---|---|---|---|---|---|
| Dcm_Init | SWS_Dcm_00037 | 0x01 | void (const Dcm_ConfigType* ConfigPtr) | ✅ | — |
| Dcm_GetVersionInfo | SWS_Dcm_00065 | 0x24 | void (Std_VersionInfoType*) | ✏️ macro → hàm | — |
| Dcm_GetSecurityLevel | SWS_Dcm_00338 | 0x0d | Std_ReturnType (Dcm_SecLevelType* SecLevel) | ✅ | DCM_SRS_003 |
| Dcm_GetSesCtrlType | SWS_Dcm_00339 | 0x06 | Std_ReturnType (Dcm_SesCtrlType* SesCtrlType) | ✅ | DCM_SRS_002 |
| Dcm_ResetToDefaultSession | SWS_Dcm_00520 | 0x2a | Std_ReturnType (void) | ✅ | DCM_SRS_008 |
| Dcm_MainFunction | SWS_Dcm_00053 | 0x25 | void (void) (khai báo trong SchM_Dcm.h) | ✅ | DCM_SRS_008/009 |
| Dcm_StartOfReception | SWS_Dcm_00094 | 0x46 | BufReq_ReturnType (PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr) | ✏️ thiếu info | DCM_SRS_016 |
| Dcm_CopyRxData | SWS_Dcm_00556 | 0x44 | BufReq_ReturnType (PduIdType, const PduInfoType* info, PduLengthType*) | ✏️ thiếu const | DCM_SRS_016 |
| Dcm_TpRxIndication | SWS_Dcm_00093 | 0x45 | void (PduIdType id, Std_ReturnType result) | ✏️ NotifResultType | DCM_SRS_016 |
| Dcm_CopyTxData | SWS_Dcm_00092 | 0x43 | BufReq_ReturnType (PduIdType, const PduInfoType*, const RetryInfoType*, PduLengthType* availableDataPtr) | ✏️ thiếu const | DCM_SRS_016 |
| Dcm_TpTxConfirmation | SWS_Dcm_00351 | 0x48 | void (PduIdType id, Std_ReturnType result) | ✏️ NotifResultType | DCM_SRS_006 |
| Dcm_ComM_NoComModeEntered | SWS_Dcm_00356 | 0x21 | void (uint8 NetworkId) | ✅ | — |
| Dcm_ComM_SilentComModeEntered | SWS_Dcm_00358 | 0x22 | void (uint8 NetworkId) | ✅ | — |
| Dcm_ComM_FullComModeEntered | SWS_Dcm_00360 | 0x23 | void (uint8 NetworkId) | ✅ | — |

Các callout dưới đây chỉ khai báo trong Dcm_Externals.h. Thân hàm thuộc App hoặc BL, không nằm trong common.

| Callout | SWS ID | SvcID | Chữ ký R24-11 | Repo | SRS |
|---|---|---|---|---|---|
| Dcm_SetProgConditions | SWS_Dcm_00543 | 0x61 | Std_ReturnType (Dcm_OpStatusType OpStatus, const Dcm_ProgConditionsType*) | ✏️ thiếu OpStatus và const | DCM_SRS_014, BL_SRS_004 |
| Dcm_GetProgConditions | SWS_Dcm_00544 | 0x62 | Dcm_EcuStartModeType (Dcm_ProgConditionsType*) | ✅ | SWS_Dcm_00536 |
| Dcm_ProcessRequestDownload | SWS_Dcm_00754 | 0x30 | Std_ReturnType (OpStatus, uint8 DataFormatIdentifier, uint8 MemoryIdentifier, uint32 MemoryAddress, uint32 MemorySize, uint32* BlockLength, Dcm_NegativeResponseCodeType* ErrorCode) | ✏️ thiếu MemoryIdentifier | BL_SRS_006 |
| Dcm_WriteMemory | SWS_Dcm_00540 | 0x27 | Dcm_ReturnWriteMemoryType (OpStatus, uint8 MemoryIdentifier, uint32, uint32, const uint8* MemoryData, Dcm_NegativeResponseCodeType* ErrorCode) | ✏️ thiếu const và ErrorCode | BL_SRS_007 |
| Dcm_ProcessRequestTransferExit | SWS_Dcm_00755 | 0x32 | Std_ReturnType (OpStatus, const uint8* reqRecord, uint32 reqSize, uint8* respRecord, uint32* respSize, ErrorCode*) | ✏️ khác tham số | BL_SRS_008 |

Loại bỏ: ROE, ReadMemory/Upload, Dcm_Arc_*, Rte_Switch_*, Dcm_GetActiveProtocol (không còn trong R24-11). Callout seed/key và DID là interface riêng của từng cấu hình nên để App/BL làm (X-08, B-04).

### Phần 11: boot_shared (feat(bl)): Boot_Shared.h

Header không có SWS, chỉ chứa định nghĩa của dự án: địa chỉ boot record 0x2000_6FF0, magic 0x424F4F54 và giá trị đảo bit của nó, struct metadata ở 0x0007_F000, các vùng App/BL theo mục 1.10. Nguồn: BL_SRS_001/002/004.

## B. Bạn cần chốt 4 điểm

1. "Copy các API đã triển khai đúng": mình hiểu là giữ nguyên prototype của repo khi nó khớp SWS, còn thân hàm vẫn để trống. Nếu ý bạn là copy cả implementation của các hàm khớp SWS thì báo mình.
2. Giao diện Dcm↔Dem: doc (OP-DEM-01) chọn giữ kiểu 4.0.3 không có ClientId, nhưng bạn yêu cầu đúng SWS. Mình đề xuất theo R24-11 (có ClientId) như bảng Phần 7.
3. Macro AR version = 4.7.0: RTD có lệnh #error khi version của Det.h, CanIf_Can.h, Dem.h… không khớp 4.7. Mình đề xuất đặt AR version 4.7.0 cho tương thích, còn chữ ký API vẫn theo R24-11. Cách khác là bật DISABLE_MCAL_INTERMODULE_ASR_CHECK.
4. File <Mod>_Cfg.h: header của module sẽ include file này, nhưng file nằm ở application/cfg và bootloader/cfg và được tạo ở các commit cấu hình (C-03, T-04…). Mình đề xuất không tạo trong đợt này. Hiện hai project S32DS chưa build common nên không bị lỗi build. Header SchM_*.h cho các module RTD (Can, Gpt, Mcu…) cũng để lại cho bước tích hợp build.

Bạn chấp nhận plan (kèm câu trả lời cho 4 điểm trên) thì mình bắt đầu từ Phần 1 và commit từng phần một.
