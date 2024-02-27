#include <stdint.h>
#include "TinyTimber.h"
#include "Generator.h"



static int freq_to_delay(uint8_t freq){

}
int get_freq(struct Generator *self, int _){
   return self->freq; 
}

void set_freq(struct Generator *self, int value){
   self->freq = value;
   //TODO calculate new delay
}

void cyclic_func(struct Generator *self, int _){
   //TODO toggle pin
   self->next_cyclic = AFTER(self->delay,self,cyclic_func,NULL);
}

void enable(struct Generator *self, int enable){
   if(enable){
      //TODO start cyclic function
   } else {
      //TODO stop cyclic function
      //set pin low
   }
}
