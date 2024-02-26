#include "Controller.h"

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

void joy_up_on(struct Controller *self, int _){
	int freq = SYNC(self->current_generator,get_freq,NULL);
	if (freq < 99){
        // ASYNC(self->current_generator,inc_freq,NULL);
        // write freq +1 
    } else if (freq == 0){
        // async enable
        // async inc
        // write freq +1
    }
    // AFTER(bl, obj, meth, arg)
    self->up_msg = AFTER(MSEC(500), self, joy_up_on, NULL);
}

void joy_up_off(struct Controller *self, int _){
    ABORT(self->up_msg);
}

void joy_down_on(struct Controller *self, int _){
    int freq = SYNC(self->current_generator,get_freq,NULL);
    if (freq > 1) {
        // async deq freq
        // write freq-1
    } else if (freq == 1) {
        // async disable
        // async deq freq
        // write freq-1
    }
    self->down_msg = AFTER(MSEC(500), self, joy_down_on, NULL);
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

void joy_right_on(struct Controller *self, int _){ 
    toggle_right(self,NULL);
}
void joy_right_off(struct Controller *self, int _){ 
    // do nothing
}

void init_all(struct Controller *self, int _){
    self->current_generator = self->generator_0;
    ASYNC(self->gui,set_s1, 1);
	ASYNC(self->gui,write_left,0);
	ASYNC(self->gui,write_right,0);
}
