#include "pid.h"

// Constructor
PID::PID() {}

// Destructor
PID::~PID() {}

// Initialize the PID controller with coefficients
void PID::Init(double Kp, double Kd)
{
    this->Kp = Kp;
    this->Kd = Kd;
    p_error = 0.0;
    d_error = 0.0;
    prev_cte = 0.0;
}

// Update the error values based on cross-track error (cte)
void PID::UpdateError(double cte)
{
    // Proportional error
    p_error = cte;

    // Derivative error (rate of change of cte)
    d_error = cte - prev_cte;

    // Update previous cte for the next iteration
    prev_cte = cte;
}

// Calculate the total error for steering control
double PID::TotalError()
{
    return -(Kp * p_error + Kd * d_error); // Negative sign to correct direction
}

// Get the steering angle based on the total error
double PID::GetSteering()
{
    double steering = TotalError();

    // Clamp the steering value to [-1, 1] range (if required by your system)
    if (steering > 1.0)
    {
        steering = 1.0;
    }
    else if (steering < -1.0)
    {
        steering = -1.0;
    }

    return steering;
}
