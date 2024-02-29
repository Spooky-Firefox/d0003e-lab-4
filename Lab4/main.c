/*
 * Lab4.c
 *
 * Created: 2024-02-21 11:19:15
 * Author : oller
 */ 

#include <avr/io.h>
#include "TinyTimber.h"
#include "Controller.h"
#include "Gui.h"
#include "Generator.h"
#include "Interrupt_Handler.h"

struct Gui gui = initGui();
struct Generator gen1 = initGenerator();
struct Generator gen2 = initGenerator(); 
struct Controller cntr = initController(&gui, &gen1, &gen2);
struct Interrupt_Handler int_handler = initInterrupt_Handler(&cntr);

int main(void)
{	
	init_joystick(&int_handler, NULL); // enables interrupt and installs handler
	setupLCD(&gui, NULL);
	tinytimber(&cntr,init_all, NULL);
}

