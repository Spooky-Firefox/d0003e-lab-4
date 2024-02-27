# Labb 4 Realtidssystem
Labb 4 för kursen d0003e realtidssystem.
I uppgiften implementeras en reaktivt system

## GUI klassen
Denna klass tar hand om det grafiska gränsnittet till användaren.
Klassen tar även hand om interrupt som skapas av joysticken.
Klassen kallar på `set_freq()` och `enable()` på klasserna `square_gen`

## Square gen klassen
Denna klass generar en fyrkantig våg på den givna pinnen med den givna frekvensen.

## Klass diagram
<!--
hur klass diagramed görs
https://mermaid.js.org/syntax/classDiagram.html
-->
```mermaid
classDiagram

    class Controller {
        - up_msg : Msg
        - down-msg : Msg

        + gui : Gui *

        - current_generator : Generator *
        + generator_1 : Generator *
        + generator_2 : Generator *

        + init_all() void

        + joy_up_on() void
        + joy_down_on() void
        + joy_left_on() void
        + joy_right_on() void
        + joy_up_off() void
        + joy_down_off() void
        + joy_left_off() void
        + joy_right_off() void
        - display_current_generator(int value);
        - switch_left()
        - switch_right()
    }
    
    class Gui{
        + setupLCD() void
        + set_s1(bool state) void
        + set_s2(bool state) void
        + write_left(int num) void
        + write_right(int num) void
    }

    class Generator {
        - enable : bool
        - freq : int
        - delay : int
        - pin : int
        + init(pin) void
        + get_freq(int freq)
        + inc_freq()
        + dec_freq()
        + enable(bool enable)
        - freq_to_half_period()
        - set_pin(bool)
        - cyclic_func()
    }

    class Pin_Out_Maneger {
        - shadow_e4 : bool
        - shadow_e6 : bool
        + status_pin_e4() bool
        + status_pin_e6() bool
        + set_pin_e4(state) void
        + set_pin_e6(state) void
    }

    class Joystick_Interrupt_Handler {
        - last_pin_b uint8_T
        - last_pin_e uint8_T
        - controller_ref : Controller*
        - PCINT0_handler() void
        - PCINT1_handler() void
    }
```

# Implementation

## Gui klassen

### ``setupLCD``
Sätter de register som behövs för att kunna använda LCD

### ``set_s1`` och ``set_s2``
Sätter s1 och s2 segmenten beroende på den inskickade tillstånd

### ```write_left`` och ``write_left``
Skriven det skickade talet till position 0,1 eller 4,5 beroende om det är ``write_left`` eller ``write_right``

## Generator klassen

### ``init``
Sätter upp pin för output och initialselar andra variabler

### ``set_freq``
Sätter ``freq`` och beräknar delay med ``freq_to_half_period``

### ``enable``
Om generatorn kallas med **på** och den är **på** görs ingenting.
Om generatorn kallas med **av** och den är **på** sätts status till av samt pin dras till låg.
Om generatorn kallas med **på** och den är **av** sätts status till på och ``cyclic_funk`` kallas.
Om generatorn kallas med **av** och den är **av** görs ingenting.

### ``cyclic_func``
När ``cyclic_func`` kallas och generatorn är av så returnerar functioned.
om generatorn är på så byts stadiet på pin och ``after`` kallas med sig själv med en
tids som beräknades tidigare med ``freq_to_half_period``

## Joystick_Interrupt_Handler klassen

### ``init_joystick``
Funktionen tar och sätter de register för att tillåta interrupts på joystickens pins.
Samt så installeras objektet som en interrupt hanterare på IRQ_PCINT0 och IRQ_PCINT1.
| joystick function | Pin   | interrupt |
| - | - | - |
| mitten klick      | PB4   | nr 12     |
| uppåt             | PB6   | nr 14     | 
| nedåt             | PB7   | nr 15     | 
| vänster           | PE2   | nr 2      | 
| höger             | PE3   | nr 3      |

### ``PCINT0_handler`` och ``PCINT1_handler``
Dessa funktioner är kopplade till IRQ_PCINT0 och IRQ_PCINT1
och deras funktion är att kalla ``Controller`` olika metoder som hanterar joystick input
(Tex ``joy_up_on()``).
Separering av objects funktion bryts lite då även fördröjning skickas med för att undvika att utöka ``Controller`` klassens kod för mycket.
