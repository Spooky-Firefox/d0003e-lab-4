#pragma once

#include <stdint.h>
#include "TinyTimber.h"


struct Interrupt_Handler{
    Object obj;
	
    struct Controller *cntr;
    //joystick pins are PB4, PB6,PB7 and PE2, PE3
    volatile uint8_t last_pin_b;
    volatile uint8_t last_pin_e;
};

#define initInterrupt_Handler() {initObject(),NULL,0xF1,0x8F}

// setts upp the interrupt_handler object, enables interrupts and installs itself on IRQ_PCINT0 and IRQ_PCINT1
void init_joystick(struct Interrupt_Handler *self, struct Controller *cntr);
