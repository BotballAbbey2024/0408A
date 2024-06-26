#include <kipr/wombat.h>

int rspeed = 93; // make this slightly faster // after a few runs to warm up, set this to 95% // then set to 92
int lspeed = 100;

int right = 1;
int left = 2;
int rightSens = 0;
int leftSens = 1;
int black = 3600;
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
    void driveRev(int time);
    //countTime();
    
    enable_servos();
    
    // TESTING CODE
    //drive(20000);
    
    /*
    driveRev(1000);
    drive(1000);
    turn(1100, 1);
    turn(500, 0);
    
    msleep(50000);
    */
    //drive(20000); // warmup
    /*
    motor(right, -rspeed);
    motor(left, -lspeed);
    msleep(1000);
    ao();
    
    followBlack(3000);
  
    msleep(1000);
	*/
    
    // TESTING CODE
    
    
    
    
    
    
    driveToBlack();
    drive(3400);
    turn(1000, 1);
    
    driveRev(3000);
    
    
    drive(1000);
    turn(1000, 0);
    
    driveToBlack();
    drive(500);
    sweepForBlack();
	
    followBlack(2200); // need to tune //2200 prime
    turn(700, 1);
    driveToBlack();
    drive(2000);
    driveRev(1250);
    
    turn(1450, 1);
    driveRev(4000);
    
    //BACKED UP ON SOLAR PANEL
    
    sweepForBlack();
    stop();
    
    followBlack(2869); // need to tune between 2900 and 3200 // 2800 prime
    
    turn(1200, 1);
    drive(3000);
    driveRev(3000);
    turn(1200, 0);
    sweepForBlack();
    
    followBlack(1300);
    
    // TURNING TO FACE THE 5th ROCK
    
    turn(1000, 1);
    drive(300);
    turn(1100, 1);
    drive(3100);

    // TURNING TO FACE THE ROCK HEAP 2nd TIME AROUND
    
    turn(700, 1);
    driveToBlack();
    drive(2500);
    driveRev(1300);
    
    turn(1450, 1);
    driveRev(5000);
    //BACKED UP ON SOLAR PANEL FOR THE SECOND TIME: READY TO RETURN TO HOME
    
    drive(500);
    sweepForBlack();
    followBlack(3000);
    turn(1000, 1);
    drive(1400); //drive down to the final point line
    turn(1100, 0);
    driveToBlack();
    drive(500);
    sweepForBlack();
    followBlack(1300); // fix to avoid running into pillar next to base // 1400 prime
    turn(1000, 1);
    
    //go forward 1300 total
    drive(400);
    stop(500);
    drive(400);
    stop(500);
    drive(400);
    stop(500);
    
    
    driveRev(200);
    turn(200, 1);
    stop(500);
    turn(200, 0);
    
    /* e h=&e%e:
    turn(1200, 1);
    driveRev(7000);
    */
    
    stop();
    
    ao();
  
    disable_servos();
    
    

    return 0;
}

void countTime(){
    
}

void followBlack(int time){
    int counter = 0;
    while(counter<time){
        counter++;
        if(analog(0)>black && analog(1)>black){
    		motor(right, rspeed);
            motor(left, lspeed);
    	} else if(analog(0)>black){
            printf("right\n");
            motor(right, 50);
            motor(left, lspeed);
        } else if(analog(1)>black){
            printf("left\n");
            motor(left, 50);
            motor(right, rspeed);
        }
    }
    ao();
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
    ao();
}

void driveRev(int time){
    motor(right, -rspeed);
    motor(left, -lspeed);
    msleep(time);
    ao();
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
    ao();
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
        if(sweep>1200){
            break;
        }
        
    }
    stop();
    
}
