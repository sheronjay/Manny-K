#include "pid.h"

PID::~PID()
{

}

void PID::Init(double Kp, double Ki, double Kd)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    p_error = 0;
    i_error = 0;
    d_error = 0;
    prev_cte = 0;
}

void PID::UpdateError(double cte)
{
}

double PID::TotalError()
{
    return 0.0;
}

double PID::GetSteering()
{
    return 0.0;
}
