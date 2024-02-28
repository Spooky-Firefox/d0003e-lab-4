# Labb 4 Realtidssystem
Labb 4 för kursen d0003e realtidssystem.
I uppgiften implementeras en reaktivt system

## GUI klassen
Denna klass tar hand om det grafiska gränsnittet till användaren som att skriva till LCD och sätta segment

## Controller klassen
Syftet för denna kalls ärr att fungera som en controller av de andra klasserna,
den för kallelser av ``Joystick_Interrupt_Handler`` och bestämmer mad som ska göras.
Som exempel är det dens jobb att öka freq, skriva ut den nya freq när ``joy_up_on`` kallas.

## Joystick_Interrupt_Handler klassen
Klassen tar hand om när en interrupt sker och skickar vad som hända till Controller klassen med att asynkront kalla på tex ``joy_up_on`` 

## Generator klassen
Denna klass generar en fyrkantig våg på den givna pinnen med den givna frekvensen.

## Pin Out Maneger
Output tass hand av denna klass, detta behövs för att undvika race condition vid skrivning till pinsen.  

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

        + gui : Gui*

        - current_generator : Generator*
        + generator_1 : Generator*
        + generator_2 : Generator*

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
        + pin_manger : Pin_Out_Maneger*
        + pin : int

        + get_freq() int
        + set_freq(int freq)
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

### ``write_left`` och ``write_left``
Skriven det skickade talet till position 0,1 eller 4,5 beroende om det är ``write_left`` eller ``write_right``

## Generator klassen

### ``init``
Sätter upp pin för output och initialselar andra variabler

### ``set_freq``
Sätter ``freq``
avbryter nästa ``cyclic func`` om det finns en.
Om freq är 0 så sätts dras pin låg annars beräknas en ny delay och en ny cyclic function startar.


### ``cyclic_func``
När ``cyclic_func`` kallas och generatorn är av så returnerar functioned.
om generatorn är på så byts stadiet på pin och ``after`` kallas med sig själv med en
tids som beräknades tidigare med ``freq_to_half_period``

## Joystick_Interrupt_Handler klassen

### ``init_joystick``
Funktionen tar och sätter de register för att tillåta interrupts på joystickens pins.
Samt så installeras objektet som en interrupt hanterare på IRQ_PCINT0 och IRQ_PCINT1.
| joystick function | Pin   | interrupt |
| ----------------- | ----- | --------- |
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

## Controller klassen

### ``init_all``
Initialization av delar av programmet sker i denna funktion,
så som att sätta s1 segmentet till på och sätta current_generator variabeln till den första generatorn.
Även 00 skrivs till de båda nummer positionerna.

### ``joy_up_on``, ``joy_up_off``, ``joy_down_on`` och ``joy_down_on``
Dessa funktioner tar hand om att öka och sänka den nuvarande generatorns frekvens.
När tex ``joy_up_on`` kallas ökas den nuvarande generatorn och des nya värdet skickas till Gui.
Därefter kallas ``joy_up_on`` med dess nya baseline är nuvarande baseline + invärdet (omhändertaget av AFTER),
invärdet som skickas till den nya ``joy_up_on`` är 75ms.
När ``Joystick_Interrupt_Handler`` kallar på ``joy_up_on`` så kommer nästa ``joy_up_on`` om 1000ms,
därefter kommer resten av ``joy_up_on`` komma med en avstånd på 75ms.

När off kallas tas den uppkommande ``joy_up_on`` bort med hjälp av ``ABORT``.

### ``joy_left_on`` och ``joy_right_on``
dessa funktioner ändrar current_generator och kallar på gui för att ändra vilket segment som indikerar aktiv generator.

### ``joy_left_off`` och ``joy_right_off``
Gör ingenting men finns för att kunna utöka funktionaliteten vid senare skede

### ``display_current_generator``
Denna hjälpfunktion tittar på vilken current_generator är och väljer om 

