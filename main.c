#define GPIO_PORTF_DATA_REG       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_REG        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_REG      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_REG        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_PDR_REG        (*((volatile unsigned long *)0x40025514))
#define GPIO_PORTF_DEN_REG        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_REG       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_REG         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_REG      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_REG       (*((volatile unsigned long *)0x4002552C))

void led_init(void)
{
    GPIO_PORTF_DIR_REG|=(1<<2);
    GPIO_PORTF_AFSEL_REG &=~(1<<2);
    GPIO_PORTF_DEN_REG|=(1<<2);
    GPIO_PORTF_AMSEL_REG&=~(1<<2);
    GPIO_PORTF_PCTL_REG  &= ((0xFFFFFFFF) & (~((0x00000000F) <<(2*4))));
    GPIO_PORTF_DATA_REG &=~(1<<2); 
    GPIO_PORTF_DATA_REG &=~(1<<1); 
    GPIO_PORTF_DATA_REG &=~(1<<3); 
    GPIO_PORTF_DATA_REG &=~(1<<0); 
}
int main()
{
    led_init();
    while(1)
    {
        GPIO_PORTF_DATA_REG&=~(1<<2);
    }
}