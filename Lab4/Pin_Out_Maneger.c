#include <avr/io.h>
#include "Pin_Out_Maneger.h"

void init_all_pin(struct Pin_Out_Manager *self, int _){
    DDRE = DDRE | (1<<PE4) | (1<<PE6);
}

void set_pin_on(struct Pin_Out_Manager *self, int pin_num){
    PORTE = PORTE | (1<<(uint8_t)pin_num);
}

void set_pin_off(struct Pin_Out_Manager *self, int pin_num){
    PORTE = PORTE & ~(1<<(uint8_t)pin_num);
}

int get_pin(struct Pin_Out_Manager *self, int pin_num){
    int tmp = (int)((PORTE>>pin_num))&0x01;
    return tmp;
}
