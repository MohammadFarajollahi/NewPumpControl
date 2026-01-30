#ifndef __DELEY_INCLUDED__
#define __DELEY_INCLUDED__
#define CRYSTAL 48000000 
#define DELEY_MS_QTY    (CRYSTAL/10000)
#define DELEY_US_QTY    (CRYSTAL/10)
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//delay in ms
void delay_ms(uint16_t delay)
{
uint32_t   t=(uint32_t) delay;
t *=8000;
while(t--);	
}
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//delay in us
void delay_us(unsigned int delay){
uint32_t   t=(uint32_t) delay;
t *=8;
while(t--);	                       
}

#endif

