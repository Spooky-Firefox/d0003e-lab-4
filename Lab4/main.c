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
#include "Pin_Out_Maneger.h"

struct Gui gui = initGui();
struct Pin_Out_Manager pin_man = initPin_Out_Maneger();
struct Generator gen1 = initGenerator(&pin_man,PE4);
struct Generator gen2 = initGenerator(&pin_man,PE6); 
struct Controller cntr = initController(&gui, &gen1, &gen2);
struct Interrupt_Handler int_handler = initInterrupt_Handler(&cntr);

int main(void)
{	
	init_joystick(&int_handler, NULL); // enables interrupt and installs handler
	setupLCD(&gui, NULL);
	init_all_pin(&pin_man, NULL);
	//PORTE = PORTE | (1<<PE4);
	//while (1){};
	tinytimber(&cntr,init_all, NULL);
}

