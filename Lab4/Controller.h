#pragma once

#include <stdint.h>
#include "TinyTimber.h"
#include "Gui.h"
#include "Generator.h"
#include "Interrupt_Handler.h"

struct Controller{
    Object obj;

    // for joystick handling
    Msg up_msg;
    Msg down_msg;

    // gui
    struct Gui *gui;

    //generators
    struct Generator *current_generator;
    struct Generator *generator_0;
    struct Generator *generator_1;

};

#define initController() { initObject(), NULL,NULL, NULL, NULL, NULL, NULL}

void init_all(struct Controller *self, int _);

void joy_up_on(struct Controller *self, int _);
void joy_up_off(struct Controller *self, int _);

void joy_down_on(struct Controller *self, int _);
void joy_down_off(struct Controller *self, int _);

void joy_left_on(struct Controller *self, int _);
void joy_left_off(struct Controller *self, int _);

void joy_right_on(struct Controller *self, int _);
void joy_right_off(struct Controller *self, int _);
