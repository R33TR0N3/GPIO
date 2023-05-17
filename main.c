#include <LPC21xx.H>

#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000

#define BUT0_bm 0x10
#define BUT1_bm 0x40
#define BUT2_bm 0x20
#define BUT3_bm 0x80

void LedInit()
{
	
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm ;
	IO1SET = LED0_bm ;
}

void KeyboardInit()
{
	IO0DIR = IO0DIR & (~(BUT0_bm | BUT1_bm | BUT2_bm | BUT3_bm)) ;
}

void Delay(int iMilisecondCounter) 
{
	
	int iCounter ;
	
	for (iCounter = 11997 * iMilisecondCounter; iCounter > 0; iCounter--) ; //11997 daje 1ms
}

void LedOn(unsigned char ucLedIndeks)
{
	
	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm ;
	switch(ucLedIndeks)
	{
		case 0 :
			IO1SET = LED0_bm ;
			break ;
		case 1 :
			IO1SET = LED1_bm ;
			break ;
		case 2 :
			IO1SET = LED2_bm ;
			break ;
		case 3 :
			IO1SET = LED3_bm ;
			break ;
	}
}

enum KeyboardState {RELEASED,BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3} ;
enum KeyboardState eKeyboardState()
{
	if((~IO0PIN & BUT0_bm) == BUT0_bm)
	{
		return BUTTON_0 ;
	}
	else if((~IO0PIN & BUT1_bm) == BUT1_bm)
	{
		return BUTTON_1 ;
	}
	else if((~IO0PIN & BUT2_bm) == BUT2_bm)
	{
		return BUTTON_2 ;
	}
	else if((~IO0PIN & BUT3_bm) == BUT3_bm)
	{
		return BUTTON_3 ;
	}
	return RELEASED ;
}

enum eDirection {RIGHT,LEFT} ;
void LedStep(eDirection)
{
	static unsigned int siLedPosition;
	unsigned int uiSetDirection = eDirection ;
	
	if(uiSetDirection == RIGHT)
	{
		siLedPosition-- ;
	}
	else if(uiSetDirection == LEFT)
	{
		siLedPosition++ ;
	}
	LedOn(siLedPosition % 4) ;
}

void LedStepLeft(void)
{
	LedStep(LEFT) ;
}

void LedStepRight(void)
{
	LedStep(RIGHT) ;
}

int main()
{
	
	KeyboardInit() ;
	LedInit() ;
	
	while(1)
	{
		Delay(100) ;
		switch(eKeyboardState())
		{
			case BUTTON_1 :
				LedStepLeft() ;
				break ;
			case BUTTON_2 :
				LedStepRight() ;
				break ;
			default: ;
		}
	}
}