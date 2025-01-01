#ifndef PID_H
#define PID_H

// we probably won't use I (intergral) but referred as pid anyway

class PID {
public:
    // Constructor
    PID();

    // Destructor
    virtual ~PID();

    // Initialize PID
    void Init(double Kp, double Kd);

    // Update the PID error variables given cross track error
    void UpdateError(double cte);

    // Calculate the total PID error
    double TotalError();

    // Get the steering value
    double GetSteering();

private:
    // PID Errors
    double p_error;
    double d_error;

    // PID Coefficients
    double Kp;
    double Kd;

    // Previous CTE
    double prev_cte;
};


#endif // PID_H