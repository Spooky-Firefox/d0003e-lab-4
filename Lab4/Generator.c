#include <stdint.h>
#include "TinyTimber.h"
#include "Generator.h"

void cyclic_func(struct Generator *self, int _){
   //TODO toggle pin
   if (SYNC(self->pin_man, get_pin, self->pin_number)) {
      ASYNC(self->pin_man, set_pin_off, self->pin_number);
   } else{
      ASYNC(self->pin_man, set_pin_on, self->pin_number);
   }
   self->next_cyclic = AFTER(self->delay,self,cyclic_func,NULL);
}

int get_freq(struct Generator *self, int _){
   return self->freq; 
}

void set_freq(struct Generator *self, int value){
   self->freq = value;
   if(self->next_cyclic) ABORT(self->next_cyclic); // stop current cyclic if there is one
   if(self->freq){ // if freq is not zero star cyclic else pull pin low
      self->delay = MSEC(500/value);
      ASYNC(self,cyclic_func,NULL);
   } else{
      //TODO disable pin
      ASYNC(self->pin_man, set_pin_off, self->pin_number);
   }
   
}
