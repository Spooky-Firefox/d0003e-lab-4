#pragma once


#include <stdint.h>
#include "TinyTimber.h"
#include "Pin_Out_Maneger.h"

struct Generator
{
    Object obj; // inherit from object from tiny timber
    uint8_t freq;
    int delay;
    struct Pin_Out_Manager* pin_man;
    Msg next_cyclic;
    int pin_number;
};
#define initGenerator(pin_out_manager,pin_num) {initObject(), 0, 0, pin_out_manager, NULL, pin_num}

// void cyclic_func(struct Generator *self, int _);
int get_freq(struct Generator *self, int _);
void set_freq(struct Generator *self, int value);



