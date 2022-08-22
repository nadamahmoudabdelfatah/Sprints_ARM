
#include "tm4c123gh6pm_registers.h"
#include "Dio.h"
#include "Port.h"
#include"IntCtrl.h"
#include "Timer.h"
#include "tm4c123gh6pm_registers.h"

#define SYSTICK_PRIORITY_MASK  0x1FFFFFFF
#define SYSTICK_INTERRUPT_PRIORITY  3
#define SYSTICK_PRIORITY_BITS_POS   29

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762

static void (*g_SysTick_Call_Back_Ptr)(void) = NULL_PTR;

/************************************************************************************
* Service Name: SysTick_Handler
* Description: SysTick Timer ISR
************************************************************************************/
void SysTick_Handler(void)
{
    /* Check if the Timer0_setCallBack is already called */
    if(g_SysTick_Call_Back_Ptr != NULL_PTR)
    {
        (*g_SysTick_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    /* No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */
}

void SysTick_SetCallBack(void(*Ptr2Func)(void))
{
    g_SysTick_Call_Back_Ptr = Ptr2Func;
}
/* GPIO PORTF External Interrupt - ISR */
void GPIOPortF_Handler(void)
{
   // GPIO_PORTF_DATA_REG  |= (1<<2);       /* Blue LED ON*/
   Dio_WriteChannel(F3,1);
    GPIO_PORTF_ICR_REG   |= (1<<4);       /* Clear Trigger flag for PF4 (Interupt Flag) */
}

/* Enable PF4 (SW1) and activate external interrupt with falling edge */
void SW1_Init(void)
{
    GPIO_PORTF_AMSEL_REG &= ~(1<<4);      /* Disable Analog on PF4 */
    GPIO_PORTF_PCTL_REG  &= 0xFFF0FFFF;   /* Clear PMCx bits for PF4 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   &= ~(1<<4);      /* Configure PF4 as input pin */
    GPIO_PORTF_AFSEL_REG &= ~(1<<4);      /* Disable alternative function on PF4 */
    GPIO_PORTF_PUR_REG   |= (1<<4);       /* Enable pull-up on PF4 */
    GPIO_PORTF_DEN_REG   |= (1<<4);       /* Enable Digital I/O on PF4 */
    GPIO_PORTF_IS_REG    &= ~(1<<4);      /* PF4 detect edges */
    GPIO_PORTF_IBE_REG   &= ~(1<<4);      /* PF4 will detect a certain edge */
    GPIO_PORTF_IEV_REG   &= ~(1<<4);      /* PF4 will detect a falling edge */
    GPIO_PORTF_ICR_REG   |= (1<<4);       /* Clear Trigger flag for PF4 (Interupt Flag) */
    GPIO_PORTF_IM_REG    |= (1<<4);       /* Enable Interrupt on PF4 pin */
    /* Set GPIO PORTF priotiy as 2 by set Bit number 22, 23 and 24 with value 2 */
  //  NVIC_PRI7_REG = (NVIC_PRI7_REG & GPIO_PORTF_PRIORITY_MASK) | (GPIO_PORTF_INTERRUPT_PRIORITY<<GPIO_PORTF_PRIORITY_BITS_POS); 
    NVIC_EN0_REG         |= 0x40000000;   /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
}

void Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}

/* Enable PF1, PF2 and PF3 (RED, Blue and Green LEDs) */
void Leds_Init(void)
{
    GPIO_PORTF_AMSEL_REG &= 0xF1;         /* Disable Analog on PF1, PF2 and PF3 */
    GPIO_PORTF_PCTL_REG  &= 0xFFFF000F;   /* Clear PMCx bits for PF1, PF2 and PF3 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   |= 0x0E;         /* Configure PF1, PF2 and PF3 as output pin */
    GPIO_PORTF_AFSEL_REG &= 0xF1;         /* Disable alternative function on PF1, PF2 and PF3 */
    GPIO_PORTF_DEN_REG   |= 0x0E;         /* Enable Digital I/O on PF1, PF2 and PF3 */
    GPIO_PORTF_DATA_REG  &= 0xF1;         /* Clear bit 0, 1 and 2 in Data regsiter to turn off the leds */
}
static uint8 time_on = 1;
static uint8 time_off = 3;
void Toggle_Led(void)
{
    static uint8 ticks_total = 0;
    static uint8 tick_count = 0;
    ticks_total = time_on + time_off;
    tick_count++;
    if(tick_count == time_on)
    {
        Dio_WriteChannel(F3,STD_OFF);
    }
    else if(tick_count == ticks_total)
    {
        Dio_WriteChannel(F3,STD_ON);
    }
    if(tick_count == ticks_total)
    {
        tick_count = 0;
    }
}
int main(void)
{
    /* Enable clock for PORTF and allow time for clock to start*/  
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= 0x00000020;
    delay = SYSCTL_REGCGC2_REG;
    
    /* Initailize the LEDs as GPIO Pins */
  /* Initialize Port Driver */
    Port_Init(&Port_Configuration);
    SW1_Init();
    IntCtrl_init(&Container);
    IntCtrl_SetExtInterrupt(&Ext_Container);
    SysTick_Init();
    while(1)
    {
        SysTick_SetCallBack(Toggle_Led);
        //GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02; /* Turn on the Red LED and disbale the others */
        //Delay_MS(1000);
        //GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04; /* Turn on the Blue LED and disbale the others */
        //Delay_MS(1000);
        //GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x08; /* Turn on the Green LED and disbale the others */
        //Delay_MS(1000); 
    }
}