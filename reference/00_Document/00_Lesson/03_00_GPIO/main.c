int main()
{

	*(unsigned int*)(0x40065000u + 0x130) |= (1U<<30U);

	*(unsigned int*)(0x4004C000u + 0x0) |= (1U<<8U);

	*(unsigned int*)(0x400FF0C0u + 0x14) |= 1U;
	
	while(1)
	{
		for(int i = 0; i < 600000; i++);
		
		*(unsigned int*)(0x400FF0C0u + 0x0) ^= 1U;
		
	}
}
