#ifndef GCS_SBC_DATA_H
#define GCS_SBC_DATA_H

struct PID_StructData
{
    double P;
    double I;
    double D;
};

struct EulerAngle_StructData
{
    double pitch;
    double roll;
    double yaw;
};

struct Navigation_StructData
{
    double longitude;
    double altitude;
    double latitude;
};

struct SLAM_StructData
{
    int x;
    int y;
    double theta;
};

struct GCS_StructData
{

};

#endif // GCS_SBC_DATA_H
