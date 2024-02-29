#include "Controller.h"

#define REAPEAT_DEALY MSEC(75)

void toggle_left(struct Controller *self, int _){
	self->current_generator = self->generator_0;
	ASYNC(self->gui,set_s1, 1); // self.gui.set_s1(1)
	ASYNC(self->gui,set_s2, 0);
}

void toggle_right(struct Controller *self, int _){
	self->current_generator = self->generator_1;
	ASYNC(self->gui,set_s1, 0);
	ASYNC(self->gui,set_s2, 1);
}

void joy_up_on(struct Controller *self, int delay_next){
	int freq = SYNC(self->current_generator,get_freq,NULL);
    if (freq < 99){
        ASYNC(self->current_generator,set_freq,freq+1);
        display_current(self,freq+1);
        // AFTER(bl, obj, meth, arg)
        self->up_msg = AFTER(delay_next, self, joy_up_on, REAPEAT_DEALY);
    }
    // ABORT(self->up_msg); // stop next up counter if exist
}

void joy_up_off(struct Controller *self, int _){
    ABORT(self->up_msg);
}

void joy_down_on(struct Controller *self, int delay_next){
    int freq = SYNC(self->current_generator,get_freq,NULL);
    if (freq){
        ASYNC(self->current_generator,set_freq,freq-1);
        display_current(self,freq-1);
        self->down_msg = AFTER(delay_next, self, joy_down_on, REAPEAT_DEALY); // make new down counter
    }
    // ABORT(self->down_msg); // stop next down counter if exist
}

void joy_down_off(struct Controller *self, int _){
    ABORT(self->down_msg);
}

void joy_left_on(struct Controller *self, int _){
    toggle_left(self,NULL);
}
void joy_left_off(struct Controller *self, int _){
    // do nothing
}

void display_current(struct Controller *self, int val){
    if(self->current_generator == self->generator_0) {
        ASYNC(self->gui,write_left,val);
    } else {
        ASYNC(self->gui,write_right,val);
    };
}

void joy_right_on(struct Controller *self, int _){ 
    toggle_right(self,NULL);
}
void joy_right_off(struct Controller *self, int _){ 
    // do nothing
}

void init_all(struct Controller *self, int _){
    ASYNC(self->gui,set_s1, 1);
	ASYNC(self->gui,write_left,0);
	ASYNC(self->gui,write_right,0);
}
