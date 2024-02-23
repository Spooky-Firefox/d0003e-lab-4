#include "TinyTimber.h"
#include "avr/io.h"

#define initGui() initObject()

struct Gui{
    Object obj;
};

// write two digits to the left position
void write_left(struct Gui *self, int num);

// write two digits to the right position
void write_right(struct Gui *self, int num);

// set the state of s1 segment
void set_s1(struct Gui *self, int state);

// set the state of s1 segment
void set_s2(struct Gui *self, int state);

void setupLCD(struct Gui *self, int _);
