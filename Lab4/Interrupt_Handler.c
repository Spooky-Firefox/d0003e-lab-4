#include "Interrupt_Handler.h"
#include "Controller.h"
#include "avr/io.h"
#define NOP asm("nop")

void read_port_e(struct Interrupt_Handler *self, int _){
	uint8_t pin_change = PINE^self->last_pin_e;
    if (pin_change & (1<<PE2)){ // joy left
        if (PINE & (1<<PE2)){
            ASYNC(self->cntr, joy_left_off, NULL);
        } else {
            ASYNC(self->cntr, joy_left_on, NULL);
        }
    }
    if (pin_change & (1<<PE3)){
        if (PINE & (1<<PE3)){ // joy right
            ASYNC(self->cntr, joy_right_off, NULL);
        } else {
            ASYNC(self->cntr, joy_right_on, NULL);
        }
    }
    self->last_pin_e = PINE;
    
}
void read_port_b(struct Interrupt_Handler *self, int _){
    uint8_t pin_change = PINB^self->last_pin_b;
    if (pin_change & (1<<PB4)){
        if (PINE & (1<<PB4)){ // joy middle
            ASYNC(self->cntr, joy_up_off, NULL);
        } else {
            ASYNC(self->cntr, joy_up_on, NULL);
        }
    }
    if (pin_change & (1<<PB6)){ //joy_up
        if (PINE & (1<<PB6)){
            ASYNC(self->cntr, joy_up_off, NULL);
        } else {
            ASYNC(self->cntr, joy_up_on, NULL);
        }
    }
    if (pin_change & (1<<PB7)){// joy_down
        if (PINE & (1<<PB7)){ 
            ASYNC(self->cntr, joy_down_off, NULL);
        } else {
            ASYNC(self->cntr, joy_up_on, NULL);
        }
    }
    self->last_pin_b = PINB;
}

void init_joystick(struct Interrupt_Handler *self, struct Controller *cntr){
    self->cntr = cntr;
    // set all joystick ports to be input with pullup
    // PB4, PB6,PB7 and PE2, PE3
    PORTB = PORTB | (1<<PB4) | (1<<PB6) | (1<<PB7);
    PORTE = PORTE | (1<<PE2) | (1<<PE3);

    // enable pin change interrupt for 15..8 and 7..0
    EIMSK = EIMSK | (1<<PCIE1) | (1<<PCIE0);

    //enable interrupt for joystick pins
    // PB4, interrupt 12
    // PB6, interrupt 14
    // PB7, interrupt 15
    // PE2, interrupt 2
    // PE3, interrupt 3
    PCMSK1 = PCMSK1 | (1<< PCINT12) | (1<< PCINT14) | (1<< PCINT15);
    PCMSK0 = PCMSK0 | (1<< PCINT2)  | (1<< PCINT3);

    INSTALL(self,read_port_e,IRQ_PCINT0);
    INSTALL(self,read_port_b,IRQ_PCINT1);
}
