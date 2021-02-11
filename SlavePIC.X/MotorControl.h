#ifndef XC_CONTROLLERTEST_H
#define	XC_CONTROLLERTEST_H 

/*controller tuning values*/
#define CRUISESPEED 8   //normal running speed of the mouse (in radians)
#define TURNSPEED 2
#define ACCELRATE 0.05  //increase the multiplier to cruise speed this much
#define DECELRATE 0.03  //multiplier to cruise speed
#define BRAKINGDIST 60  //distance from target to start braking (in mm)
#define MINSPEED 0.4    //minimum speed to decelerate to before STOPTHRESHOLD
#define STOPTHRESHOLD 1 //dist to get within before fully stopping

#define ONEEIGHTYTURN 129.591
#define NINTYTURN 64.7955


int controllerTest(int, char);
int forwardMove(int);
int rotationMove(int, char);

#endif	/* XC_HEADER_TEMPLATE_H */
