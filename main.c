#include <kipr/botball.h>
#define TRUE 1
#define FALSE 0

#define lmotor 0
#define rmotor 1
#define fsensor 0

#define full_speed 2000
#define half_speed 1000
#define pause_after_move 500

#define turn90 720

#define dist1 200
#define dist2 12500
#define dist3 2650

#define bias -250
#define dist_thresh 1000
#define fsensor_thresh 2000
#define drive_straight_speed_kick 50
#define drive_straight_pause 10
#define stop_line_extend 550
#define follow_delta 500
#define follow_pause 100

void drive_straight(int dist, int speed);
void straight(int dist, int speed);
void stop_at_line(int speed);    
void follow_line(int dist, int speed);
void turn_right();
void turn_left();

int main()
{
    //wait_for_light(1);
    //shut_down_in(119);
    
    straight(dist1, full_speed); //exit starting box
    turn_right(); //turn right toward utility area
    stop_at_line(full_speed); //drive to utility area
    turn_left(); //turn left toward center line
    stop_at_line(full_speed); //drive to center line
    turn_left(); //turn left onto line
    
    follow_line(dist2, full_speed);
    turn_left();
    straight(dist3,full_speed);
    turn_left();
    follow_line(dist3, full_speed);
    
    //Test code
    //drive_straight(10000, full_speed);
    //follow_line(2000, full_speed);
    /*
    turn_left();
    turn_right();
    turn_right();
    turn_left();
    */
    return 0;
}


void drive_straight(int dist, int speed){
	int lmotor_dist;
	int rmotor_dist;
	int lmotor_dist_start;
	int rmotor_dist_start;
    
    int lmotor_speed;
    int rmotor_speed;
    
    int dist_err;
    
    lmotor_dist_start = gmpc(lmotor);
    rmotor_dist_start = gmpc(rmotor);
    lmotor_dist = gmpc(lmotor) - lmotor_dist_start; 
    rmotor_dist = gmpc(rmotor) - rmotor_dist_start; 
    
    lmotor_speed = speed;
    rmotor_speed = speed;
    while(lmotor_dist < dist){
    	lmotor_dist = gmpc(lmotor) - lmotor_dist_start;
    	rmotor_dist = gmpc(rmotor) - rmotor_dist_start;
        dist_err = lmotor_dist - rmotor_dist;
        lmotor_speed = lmotor_speed + dist_err*2;
        lmotor_speed = lmotor_speed - dist_err*2;
        mav(lmotor, lmotor_speed);
        mav(rmotor, rmotor_speed);
        msleep(drive_straight_pause);
        //printf("check\n");
    }
    ao();
    msleep(pause_after_move);
}

void turn_left(){
        clear_motor_position_counter(rmotor);
        while (get_motor_position_counter(rmotor)<(turn90 + 30)){
        	mav(rmotor,half_speed);
        	mav(lmotor,-half_speed);
        }
    	ao();
    	msleep(pause_after_move);
}

void turn_right(){
        clear_motor_position_counter(rmotor);
        while (-get_motor_position_counter(rmotor)<(turn90 - 30)){
        	mav(rmotor,-half_speed);
        	mav(lmotor,half_speed);
        }
    	ao();
    	msleep(pause_after_move);
}

void straight(int dist, int speed){
    clear_motor_position_counter(rmotor);
    while (get_motor_position_counter(rmotor)<dist){
        mav(rmotor, speed + bias);
        mav(lmotor, speed - bias);
    }
    ao();
    msleep(pause_after_move);
}
    
void stop_at_line(int speed){    
    int go; 
    int dist;
    cmpc(lmotor);
    go = TRUE;
    while(go){
        dist = gmpc(lmotor);
        
        go = TRUE;
        if((analog(fsensor) > fsensor_thresh)&&(dist > dist_thresh)){
            //if sensor sees black and distance is far enough stop
            go = FALSE;
        }
        mav(rmotor, speed + bias);
        mav(lmotor, speed - bias);
    }
    clear_motor_position_counter(rmotor);
    while (get_motor_position_counter(rmotor)<stop_line_extend){
        mav(rmotor, speed + bias);
        mav(lmotor, speed - bias);
    }
    ao();
    msleep(pause_after_move);
}    
    
void follow_line(int dist, int speed){
    cmpc(lmotor);
    while(gmpc(lmotor) < dist){
        if(analog(fsensor) > fsensor_thresh){ //if sensor sees black
            mav(rmotor, speed + follow_delta);
            mav(lmotor, speed - follow_delta);
            msleep(follow_pause);
        }
        else{
            mav(rmotor, speed - follow_delta);
            mav(lmotor, speed + follow_delta);
            msleep(follow_pause);
        }
    }
    ao();
    msleep(pause_after_move);
}





