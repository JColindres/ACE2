#include <ADXL345.h>
#include "arduino.h"

#define MAX_AXIS                3
#define MAX_WINDOW              3
#define SAMPLING_MODEL_NUMBER   60
#define MODEL_STANDARD_VALUE    20

enum Axis{
    X_AXIS = 0,
    Y_AXIS = 1,
    Z_AXIS = 2,
};

class alo{
public:
    void init(void);
    void stepCalc(void);
    void inclinacion(void);
    uint16_t stepCount;
    float roll;
    float pitch;
    
private:
    void sensorInit(void);
    void updateModelAxis(void);
    void getValue(void);
    void getValidValue(void);
        
    ADXL345 adxl; 
    Axis _model_axis;
    int _model_val;
    int _curr_val;   
    int _model_ratio;
    int _last_val;
};
