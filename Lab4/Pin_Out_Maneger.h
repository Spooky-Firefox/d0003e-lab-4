#pragma once
#include <stdint.h>
#include "TinyTimber.h"


struct Pin_Out_Manager
{
    Object obj;
};
#define initPin_Out_Maneger() {initObject()}

void init_all_pin(struct Pin_Out_Manager *self, int _);

void set_pin_on(struct Pin_Out_Manager *self, int pin_num);

void set_pin_off(struct Pin_Out_Manager *self, int pin_num);

int get_pin(struct Pin_Out_Manager *self, int pin_num);
