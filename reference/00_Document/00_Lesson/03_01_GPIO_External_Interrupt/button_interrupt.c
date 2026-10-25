/*
*			PTC12  ~ Button - SW2
*			Pull down --> Press is High logic
*					  --> Release is Low logic
*/
#define PCC_PORTC 			(*(volatile unsigned int*)(0x40065000u + 0x12C))
#define PORTC_PCR_PIN12 	(*(volatile unsigned int*)(0x4004B000u + 0x30))
#define GPIOC_PDDR 			(*(volatile unsigned int*)(0x400FF080u + 0x12))	
#define GPIOC_PDIR			(*(volatile const unsigned int*)(0x400FF080u + 0x10))

#define PCC_PORTD 			(*(volatile unsigned int*)(0x40065000u + 0x130))   
#define PORTD_PCR_PIN16		(*(volatile unsigned int*)(0x4004C000 +16*4)) 					
#define GPIOD_PDDR			(*(volatile unsigned int*)(0x400FF0C0 + 0x14))
#define GPIOD_PDOR			(*(volatile unsigned int*)(0x400FF0C0 + 0))
	
#define NVIC_ISER_1			(*(volatile unsigned int*)(0xE000E100u + 4*1))

int main()
{
	/*Step 1: Interrupt Set Enable Register */
	NVIC_ISER_1 |= (1<<29);
	
	/*------------------------*/
	/*    config button       */
	/*------------------------*/
	/* Step 1: Enable clock for Port C */
	PCC_PORTC |= (1<<30);
	
	/* Step 2: Configure Pin 12 of Port C is GPIO */
	PORTC_PCR_PIN12 |= (1<<8);
	
	/* Step 3: set rising-edge interrupt */
	PORTC_PCR_PIN12 |= (9<<16);
	
	/* Step 3: Configure Pin 12 of Port C is input */
	GPIOC_PDDR &= ~(1<<12);
	
	/*------------------------*/
	/*    config led green      */
	/*------------------------*/
		/* Step 1: Enable clock for Port D */
	PCC_PORTD |= (1<<30);
	
	/* Step 2: Configure Pin 15 of Port D is GPIO */
	PORTD_PCR_PIN16 |= (1<<8);
	
	/* Step 3: Configure Pin 16 of Port D is output */
	GPIOD_PDDR |= (1<<16);
	
	while(1)
	{

		
	}
}

void PORTC_IRQHandler(void)
{
	if(PORTC_PCR_PIN12 & (1<<24)){
		PORTC_PCR_PIN12 |= (1<<24);
		GPIOD_PDOR ^= (1<<16);
	}
	
}