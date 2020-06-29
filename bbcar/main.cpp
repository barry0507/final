#include "mbed.h"

#include "bbcar.h"
//RawSerial xbee(D12, D11);
Serial xbee(D12, D11);
Serial uart(D1,D0);
Ticker servo_ticker;
//Serial pc(USBTX, USBRX);
//RawSerial pc(USBTX, USBRX);
PwmOut pin8(D8), pin9(D9);
DigitalInOut pin10(D10);
BBCar car(pin8, pin9, servo_ticker);
DigitalIn pin3(D3);
Timer t;
int a;
float logger[200];
int main() {
    xbee.printf("hello\r\n");
    // please contruct you own calibration table with each servo
    parallax_ping  ping1(pin10);
    double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};

    double speed_table0[] = {-16.667, -16.269, -15.072, -11.882, -5.822, 0.000, 5.822, 11.882, 15.072, 16.269, 16.667};

    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};

    double speed_table1[] = {-16.428, -15.950, -14.833, -11.803, -6.141, 0.000, 6.141, 11.803, 14.833, 15.950, 16.428};


    // first and fourth argument : length of table

    car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);


    /**************************************************************************************/
    car.goStraight(100);
    xbee.printf("keep staright\r\n");
    //pc.baud(9600);
    while(1){
        
        if((float)ping1 > 22){ a=0;}
        else{
            car.stop();
            //wait(5);
            car.turn(80,0.01); 
            wait(1.28);
            car.stop();
            break;
         }
         wait(.01);
    }
    car.goStraight(100);
    xbee.printf("mission1\r\n");
    /*while(1){
       printf("Ping = %lf\r\n",float(ping1));
       wait(0.01);
    }*/
    /***************************first left******************/
    while(1){
        if((float)ping1 > 22 ){ a=1;} ///stop and turn
        else{
            car.stop();
            car.turn(80,-0.02); 
            wait(1.28);
            car.stop();
            break;
         }
         wait(.01);
    }
    car.goStraight(-100);
    wait(2); 
    car.stop();
    char s[21];
    xbee.printf("smile take a picture\r\n");
    sprintf(s,"image_classification");
    uart.puts(s);
    wait(5);
    /********************mission1 out the space*/
     /// (not sure)
    
    /***************************************picture*/

    car.turn(80,-0.02);
    wait(1.3);
    car.stop();
    car.goStraight(100);
    while(1){
        
        if((float)ping1 > 25){ a=3;}   ///parking lot
        else{
            car.stop();
            //wait(5);
            car.turn(80,0.01); 
            wait(1.3);
            car.stop();
            break;
         }
         wait(.01);
     }
    car.goStraight(-100); ///park into it
    xbee.printf("back back back\r\n");
    wait(3.6);
    car.stop();
    wait(1);
    car.goStraight(100);///drive out
    xbee.printf("bye mission1\r\n");
    while(1){
        
        if((float)ping1 > 26 ){ a=2;}
        else{
            car.stop();
            //wait(5);
            car.turn(80,-0.01); 
            wait(1.3);
            car.stop();
            break;
         }
        wait(.01);
    } 
    car.goStraight(100);
    wait(0.6);  
    car.stop();
    car.turn(80,-0.01); 
    wait(1.28);
    car.stop();        
    ///U-turn
    car.goStraight(100);
        while(1){
        
        if((float)ping1 > 22 ){ a=2;}
        else{
            car.stop();
            //wait(5);
            car.turn(80,-0.01); 
            wait(1.3);
            car.stop();
            break;
         }
         wait(.01);
    } 
    wait(3);
    car.goStraight(100);
    xbee.printf("let's mission2\r\n");
    /*******go out to the mission2*/
    wait(1.5);
    car.stop();
    car.turn(80,-0.01); 
    wait(1.23);
    car.stop();
    
    car.goStraight(100);
    xbee.printf("scanning\r\n");
    float sum_log=0;
    while(1){
        
        if((float)ping1 > 25){ a=3;}   
        else{
            car.stop();
            wait(1);
            xbee.printf("rotate head\r\n");
            car.turn(60,-0.02); 
            for(int i=0;i<100;i++){
                logger[i]=float(ping1);
                wait(0.01);
                sum_log+=logger[i];
                xbee.printf("ping:%f\r\n",logger[i]);
            }
            //equals wait(1.3);
            car.stop();
            break;
         }
         wait(.01);
    }    

    if(sum_log/130 >logger[64])
        xbee.printf("I suppose it is a triangle.\r\n");
    else if(sum_log/1130 == logger[64])
        xbee.printf("I suppose it is a square.\r\n");
    else if(sum_log/1130 < logger[64])
        xbee.printf("I suppose it is a crown.\r\n");    
    else 
        xbee.printf("I suppose it is a triangle.\r\n");
    xbee.printf("mission complete\r\n");
    car.turn(80,0.01);
    wait(1.3);
    car.goStraight(-100);
    wait(2); 
    car.stop();
    car.turn(80,0.01); 
    wait(1.28);
    car.stop();
    car.goStraight(100);
    while(1){
        
        if((float)ping1 > 22 ){ a=1;} ///stop and turn
        else{
            car.stop();
            //wait(5);
            car.turn(80,-0.01); 
            wait(1.34);
            car.stop();
            break;

         }
         wait(.01);
    }
    car.goStraight(100);

}    
