
#include <kipr/wombat.h>
int rspeed = 97; // make this slightly faster
int lspeed = 100;
int right = 0;
int left = 1;
int rightSens = 0;
int leftSens = 1;
int black = 3500;
int elevator = 3;
/*
3500+ black
1-right motor
2-left motor

0-right side
1-left side

=========== methods =======================
turn method
0: turn right
1: turn left




*/



int main()
{	
    void sweepForBlack();
    void driveToBlack();
    void drive(int time);
    void followBlack(int time);
    void countTime();
    void stop();
    void turn(int t, int dir);
    void open_claw();
    void close_claw();
    void raise(int t);
    void lower(int t);
    void driveRev(int time);
    
    // The elevator will be in its highest position in the beginning.
 
	//TESTING CODE
	
    
    //TESTING CODE
    
    
    enable_servos();
    
    //open_claw();
    open_claw();
    close_claw();
    
    //msleep(75000);
    
    driveToBlack();
    drive(1000);
    driveToBlack();
    drive(800);
    turn(1325, 0);
    open_claw();
    motor(right, 30);
    motor(left, 30);
    msleep(4500);
    close_claw();
    //GRABBING BLOCKS
    msleep(500);
    driveRev(800);
    turn(1300, 1);
    sweepForBlack();
    motor(elevator, 100);
    followBlack(3800);
    ao();
    turn(500, 0);
    lower(8250);
    drive(1200);
    msleep(2000);
    open_claw();
    msleep(500);
    drive(900);
    turn(2700, 0);
    drive(6000);
    drive(1000);
    
    
    ao();
  
    disable_servos();
    
    

    return 0;
}

void countTime(){
    
}

void raise(int t)
{
    motor(elevator, -100);
    msleep(t);
    motor(elevator, 0);
}

void lower(int t)
{
    motor(elevator, 100);
    msleep(t);
    motor(elevator, 0);
}

void open_claw()
{
    //opening position: 1000
    set_servo_position(0, 1200);
    msleep(500);
   
}

void close_claw(){
    //closing position: 350
    set_servo_position(0, 400);
    msleep(500);
}

void followBlack(int time){
    int counter = 0;
    while(counter<time){
        counter++;
        if(analog(0)>black && analog(1)>black){
    		motor(right, rspeed);
            motor(left, lspeed);
    	} else if(analog(1)>black){
            printf("right\n");
            motor(right, 50);
            motor(left, lspeed);
        } else if(analog(0)>black){
            printf("left\n");
            motor(left, 50);
            motor(right, rspeed);
        } else {
            motor(right, rspeed);
            motor(left, lspeed);
        }
    }
}

void turn(int t, int dir){
    if(dir == 0){
        motor(right, -100);
        motor(left, 100);
        msleep(t);
    } else if (dir == 1){
        motor(right, 100);
        motor(left, -100);
        msleep(t);
    }
    ao();
}

void drive(int time){
    motor(right, rspeed);
    motor(left, lspeed);
    msleep(time);
    motor(right, 0);
    motor(left, 0);
    
}

void driveRev(int time){
    motor(right, -rspeed);
    motor(left, -lspeed);
    msleep(time);
    motor(right, 0);
    motor(left, 0);
    
}

void driveToBlack(){
    while(analog(0)<black){
        motor(right, rspeed);
        motor(left, lspeed);
    }
    ao();
}

void stop(){
    motor(right, 0);
    motor(left, 0);
}

void sweepForBlack(){
    int sweep = 100;
    while(analog(0)<black && analog(1)<black){
        motor(right, -rspeed);
        motor(left, lspeed);
        msleep(sweep);
        if(analog(0)>black || analog(1)>black) break;
        motor(right, rspeed);
        motor(left, -lspeed);
        msleep(sweep*2);
        if(analog(0)>black || analog(1)>black) break;
        motor(right, -rspeed);
        motor(left, lspeed);
        msleep(sweep);
        if(analog(0)>black || analog(1)>black) break;
        sweep+=200;
        
    }
    stop();
    
}
