#include <kipr/botball.h>
#define r_motor 1
#define l_motor 0
#define motor_speed 700
#define position_thresh 4000
#define et_distance 600
#define front_sensor 0
#define front_sensor_thresh 1500
#define distance 850

void turn_right();
void straight(int dist);
void search();
void spider_sense();

int main()
{
    
    int position; int sensor; int logic;
    clear_motor_position_counter(r_motor);
    logic = 0;
    while(logic==0){
    	position = get_motor_position_counter(r_motor);
        
    	sensor = 0;
        if (analog(front_sensor) > front_sensor_thresh){
   			sensor = 1;
		}
        
        logic = 0;
        if ((sensor == 1)&(position > position_thresh)){
            logic = 1;
        }
        mav(r_motor,motor_speed);
        mav(l_motor,motor_speed);
        
        
    }
    straight(1000);
    turn_right();
    straight(4000);
    search();
    turn_right();
    spider_sense();
    return 0;
}

void turn_right(){
        clear_motor_position_counter(r_motor);
        while (get_motor_position_counter(r_motor)<805){
        	mav(r_motor,motor_speed);
        	mav(l_motor,-motor_speed);
        }
}

void straight(int dist){
        clear_motor_position_counter(r_motor);
        while (get_motor_position_counter(r_motor)<dist){
        	mav(r_motor,motor_speed);
        	mav(l_motor,motor_speed);
        }
}

void search(){
     while(analog(front_sensor) > front_sensor_thresh){
         mav(r_motor,motor_speed);
         mav(l_motor,motor_speed);
    
        }
}
    
void spider_sense(){
     while(1){
    	if(analog(1)<1420){
        	(get_motor_position_counter(l_motor));
 			mav(r_motor,motor_speed);
    		mav(l_motor,motor_speed);
        	msleep(0);
      }
    	else{
        	(get_motor_position_counter(l_motor));
 			mav(r_motor,motor_speed);
    		mav(l_motor,motor_speed);
    
        }
     }
}


