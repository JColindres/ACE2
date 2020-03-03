#include "alo.h"


void alo::sensorInit()
{
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(3); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interrupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
}

void alo::init()
{
    sensorInit();
    stepCount = 0;
    roll = 0;
    pitch = 0;
    updateModelAxis();
    _curr_val = 0;  
}

void alo::updateModelAxis(void)
{
    int x,y,z;
    int16_t sum[MAX_AXIS] = {0};
    for(int i = 0; i < SAMPLING_MODEL_NUMBER; i++){
        adxl.readXYZ(&x, &y, &z);   
        sum[X_AXIS] += abs(x);
        sum[Y_AXIS] += abs(y);
        sum[Z_AXIS] += abs(z);
    }
    sum[X_AXIS] /= SAMPLING_MODEL_NUMBER;
    sum[Y_AXIS] /= SAMPLING_MODEL_NUMBER;
    sum[Z_AXIS] /= SAMPLING_MODEL_NUMBER;
    _model_axis = sum[X_AXIS] >= sum[Y_AXIS]?X_AXIS:Y_AXIS;
    _model_axis = sum[_model_axis] >= sum[Z_AXIS]?_model_axis:Z_AXIS;
    _model_val = sum[_model_axis];
    
    _model_ratio = (_model_val+MODEL_STANDARD_VALUE/2)/MODEL_STANDARD_VALUE;
}

void alo::getValue(void)
{
    int tmp_val[MAX_AXIS];
    _curr_val = 0;
    for(int i = 0; i < MAX_WINDOW; i++){
        adxl.readXYZ(&tmp_val[X_AXIS], &tmp_val[Y_AXIS], &tmp_val[Z_AXIS]);  
        _curr_val += abs(tmp_val[_model_axis]);
    }
    _curr_val /= MAX_WINDOW;
    
    _curr_val = (_curr_val + _model_ratio/2)/_model_ratio;
}

void alo::getValidValue(void)
{    
    do{
        getValue(); 
    }while((abs(_curr_val-_model_val) <= 2) || (_curr_val == _last_val));

    _last_val = _curr_val;
}

void alo::stepCalc()
{
    unsigned long timerStart,timerEnd;
    timerStart = millis();
    timerEnd = 100 + timerStart;//one step is more than 100ms
    getValidValue();
    if(_curr_val >= 23){
        while(1){
            getValidValue();  
            if(_curr_val <= 17){
                if(millis() > timerEnd) {
                    stepCount++;
                }
                break;
            }
        }
    }
}

void alo::inclinacion()
{
  int x, y, z;
  adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z

  double xyz[3];
  double ax, ay, az;
  adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];

  roll = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * 180 / PI;
  pitch = atan(-1 * ax / sqrt(pow(ay, 2) + pow(az, 2))) * 180 / PI;
}
