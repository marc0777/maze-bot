#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h
#include <math.h>

class Madgwick {
  private:
    static float invSqrt(float x);
    float beta;
    float q0;
    float q1;
    float q2;
    float q3;
    float invSampleFreq;
    float roll;
    float pitch;
    float yaw;
    char anglesComputed;
    void computeAngles();
  public:
    void begin(float sampleFrequency);
    void update(float gx, float gy, float gz, float ax, float ay, float az);
    float getYaw();
    float getPitch();
    float getRoll();
};
#endif

