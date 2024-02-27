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

struct Controller cntr = initController();
struct Gui gui = initGui();
struct Generator gen1 = initGenerator();
struct Generator gen2 = initGenerator(); 
struct Interrupt_Handler int_handler = initInterrupt_Handler();

int main(void)
{	
	init_joystick(&int_handler, &cntr); // enables interrupt and installs handler
	setupLCD(&gui, NULL);
	
	cntr.generator_0 = &gen1;
	cntr.generator_1 = &gen2;
	cntr.gui = &gui;

	tinytimber(&cntr,init_all, NULL);


}

