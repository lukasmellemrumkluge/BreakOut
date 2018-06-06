
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdio.h>
#define ESC 0x1B

typedef struct {
    int hours;
    int minutes;
    int seconds;
    int centiseconds;
} funTime_t;

volatile funTime_t t;

void startTimer(int f) {
    int reloadValue = 64*1000000/f;
    RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
    TIM2->CR1 = 0x01; // Configure timer 2
    TIM2->ARR = reloadValue; // Set reload value
    TIM2->PSC = 0x00; // Set prescale value
    TIM2->DIER |= 0x0001; // Enable timer 2 interrupts
    NVIC_SetPriority(TIM2_IRQn, 1); // Set interrupt priority
    NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
}

void stopTimer(void) {
    TIM2->CR1 = 0x00;
}

void TIM2_IRQHandler(void) {
    t.centiseconds++;
    if (t.centiseconds/100 > 0) {
        t.seconds++;
        t.centiseconds %= 100;
    }
    if (t.seconds/60 > 0) {
        t.minutes++;
        t.seconds %= 60;
    }
    if (t.minutes/60 > 0) {
        t.hours++;
        t.minutes %= 60;
    }
    TIM2->SR &= ~0x0001; // Clear interrupt bit
}

int main(void) {
    int previousSeconds = 0;
    init_usb_uart( 9600 );
    startTimer(100);
    while(1) {
        if (t.seconds != previousSeconds) {
            printf("%d:%d:%d:%d",t.hours,t.minutes,t.seconds,t.centiseconds);
            previousSeconds = t.seconds;
        }
    }
    while(1){}
}
