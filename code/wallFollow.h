#pragma once // Makes sure the header file is not defined ( conditional define statement )

// Function prototypes
void wallFollowPidControl(float sensor_left, float sensor_right);
void leftWallFollowPidControl(float sensor_left);
void rightWallFollowPidControl(float sensor_right);
void noWallFollowPidControl();
