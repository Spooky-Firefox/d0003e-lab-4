#include "Interrupt_Handler.h"
#include "Controller.h"
#include "avr/io.h"

#define DELAY MSEC(1000)

// called when a pin in PINE changed
void PCINT0_handler(struct Interrupt_Handler *self, int _){
    // read the pins
    uint8_t pin_val = PINE;
    // determine which pins changed
	uint8_t pin_change = pin_val^self->last_pin_e;

    // did the pin for joy left change?
    if (pin_change & (1<<PE2)){ 
        // is joy left on or off
        if (pin_val & (1<<PE2)){
            ASYNC(self->cntr, joy_left_off, NULL);
        } else {
            // debouncing is not needed since multiple presses do the same as one press
            ASYNC(self->cntr, joy_left_on, NULL);
        }
    }
    // did the pin for joy right change?
    if (pin_change & (1<<PE3)){
        // is joy right on or off
        if (pin_val & (1<<PE3)){
            ASYNC(self->cntr, joy_right_off, NULL);
        } else {
            // debouncing is not needed since multiple presses do the same as one press
            ASYNC(self->cntr, joy_right_on, NULL);
        }
    }
    self->last_pin_e = pin_val;
    
}
// called when a pin in PINB changed
void PCINT1_handler(struct Interrupt_Handler *self, int _){
    // read the pins
	uint8_t pin_val = PINB;
    // determine which pins changed
    uint8_t pin_change = pin_val^self->last_pin_b;

    // dit the pin for joy middle change
    if (pin_change & (1<<PB4)){
        // is joy middle on or off
        if (pin_val & (1<<PB4)){
            ASYNC(self->cntr, joy_middle_off, NULL);
        } else {
            ASYNC(self->cntr, joy_middle_on, NULL);
        }
    }
    // dit the pin for joy up change
    if (pin_change & (1<<PB6)){
        // is joy up on or off
        if (pin_val & (1<<PB6)){
            ASYNC(self->cntr, joy_up_off, NULL);
        } else {
            // replace with AFTER(MSEC(50),cntr, joy_up_on, DELAY) if debouncing is desired
            ASYNC(self->cntr, joy_up_on, DELAY);
        }
    }
    // dit the pin for joy down change
    if (pin_change & (1<<PB7)){
        // is joy down on or off
        if (pin_val & (1<<PB7)){
            ASYNC(self->cntr, joy_down_off, NULL);
        } else {
            // replace with AFTER(MSEC(50),cntr, joy_down_on, DELAY) if debouncing is desired
            ASYNC(self->cntr, joy_down_on, DELAY);
        }
    }
    self->last_pin_b = pin_val;
}

void init_joystick(struct Interrupt_Handler *self, int _){
    // set all joystick ports to be input with pullup
    // PB4, PB6,PB7 and PE2, PE3
    PORTB = PORTB | (1<<PB4) | (1<<PB6) | (1<<PB7);
    PORTE = PORTE | (1<<PE2) | (1<<PE3);

    // enable pin change interrupt for 15..8 and 7..0
    EIMSK = EIMSK | (1<<PCIE1) | (1<<PCIE0);

    //enable interrupt for joystick pins
    // PB4, interrupt 12,   joy_middle
    // PB6, interrupt 14,   joy_up
    // PB7, interrupt 15,   joy_down
    // PE2, interrupt 2,    joy left
    // PE3, interrupt 3,    joy right
    PCMSK1 = PCMSK1 | (1<< PCINT12) | (1<< PCINT14) | (1<< PCINT15);
    PCMSK0 = PCMSK0 | (1<< PCINT2)  | (1<< PCINT3);

    INSTALL(self,PCINT0_handler,IRQ_PCINT0);
    INSTALL(self,PCINT1_handler,IRQ_PCINT1);
}
