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

    //
    uint8_t *current_freq;
    uint8_t freq_0;
    uint8_t freq_1;

    // gui
    struct Gui *gui;

    //generators
    struct Generator *current_generator;
    struct Generator *generator_0;
    struct Generator *generator_1;

};

#define initController(gui,gen0,gen1) { initObject(), NULL,NULL, NULL, 0, 0, gui, gen0, gen0, gen1}
// initialise variables and sets curent generator
void init_all(struct Controller *self, int _);

// increases current generator within its bounds, enables the generator when increased from zero
// calls itself with a delay of 100ms and saves its next call msg
// - ``int delay_next`` is the time until its call to self
void joy_up_on(struct Controller *self, int delay_next);
// aborts the upcoming joy_up_on call
void joy_up_off(struct Controller *self, int _);

// decrees current generator within its bounds, disables the generator decreased to zero
// calls itself with a delay of 100ms and saves its next call msg
// - ``int delay_next`` is the time until its call to self
void joy_down_on(struct Controller *self, int delay_next);
// aborts the upcoming joy_down_on call
void joy_down_off(struct Controller *self, int _);

// sets curent generator to generator 0
void joy_left_on(struct Controller *self, int _);
// does nothing
void joy_left_off(struct Controller *self, int _);

// sets curent generator to generator 1
void joy_right_on(struct Controller *self, int _);
// does nothing
void joy_right_off(struct Controller *self, int _);

// saves or loads current generators saved value
void joy_middle_on(struct Controller *self, int _);
// does nothing
void joy_middle_off(struct Controller *self, int _);
