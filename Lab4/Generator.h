#pragma once


#include <stdint.h>
#include "TinyTimber.h"

struct Generator
{
    Object obj; // inherit from object from tiny timber
    uint8_t freq;
    int delay;
    int* pin_reg;
    Msg next_cyclic;
    uint8_t pin_mask;
};
#define initGenerator() {initObject(),0,0,NULL,NULL,NULL}

int get_freq(struct Generator *self, int _);
void set_freq(struct Generator *self, int value);
void enable(struct Generator *self, int enable);



