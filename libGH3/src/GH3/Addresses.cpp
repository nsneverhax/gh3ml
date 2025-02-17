#include <GH3/Addresses.hpp>

float* GH3::Time::CurrentFrameTime = reinterpret_cast<float*>(0x009596b4);
float* GH3::Time::CurrentSlowDown = reinterpret_cast<float*>(0x009596b8);
float* GH3::Time::NoSlowFrameTime = reinterpret_cast<float*>(0x00b544ac);
float* GH3::Time::DeltaTime = reinterpret_cast<float*>(0x009596BC);
double* GH3::Time::UnknownFrameTimeRelated_009596c8 = reinterpret_cast<double*>(0x009596c8);
double* GH3::Time::DOUBLE_00b544b0 = reinterpret_cast<double*>(0x00b544b0);
double* GH3::Time::DOUBLE_00b544b8 = reinterpret_cast<double*>(0x00b544b8);


double* GH3::Time::DOUBLE_008b1058 = reinterpret_cast<double*>(0x008b1058);