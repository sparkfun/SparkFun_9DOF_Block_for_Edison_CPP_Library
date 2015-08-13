/******************************************************************************
SparkFun_9DOF_Edison_Block_Example.cpp
Example code for the 9DOF Edison Block
14 Jul 2015 by Mike Hord
https://github.com/sparkfun/SparkFun_9DOF_Block_for_Edison_CPP_Library

Demonstrates the major functionality of the SparkFun 9DOF block for Edison.

** Supports only I2C connection! **

Development environment specifics:
  Code developed in Intel's Eclipse IOT-DK
  This code requires the Intel mraa library to function; for more
  information see https://github.com/intel-iot-devkit/mraa

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#include "mraa.hpp"

#include <iostream>
#include <unistd.h>
#include "SFE_LSM9DS0.h"
using namespace std;

int main()
{
  LSM9DS0 *imu;
  imu = new LSM9DS0(0x6B, 0x1D);
  // The begin() function sets up some basic parameters and turns the device
  //  on; you may not need to do more than call it. It also returns the "whoami"
  //  registers from the chip. If all is good, the return value here should be
  //  0x49d4. Here are the initial settings from this function:
  //  Gyro scale:        245 deg/sec max
  //  Xl scale:          4g max
  //  Mag scale:         2 Gauss max
  //  Gyro sample rate:  95Hz
  //  Xl sample rate:    100Hz
  //  Mag sample rate:   100Hz
  // These can be changed either by calling appropriate functions or by
  //  pasing parameters to the begin() function. There are named constants in
  //  the .h file for all scales and data rates; I won't reproduce them here.
  //  Here's the list of fuctions to set the rates/scale:
  //  setMagScale(mag_scale mScl)      setMagODR(mag_odr mRate)
  //  setGyroScale(gyro_scale gScl)    setGyroODR(gyro_odr gRate)
  //  setAccelScale(accel_scale aScl)  setGyroODR(accel_odr aRate)
  // If you want to make these changes at the point of calling begin, here's
  //  the prototype for that function showing the order to pass things:
  //  begin(gyro_scale gScl, accel_scale aScl, mag_scale mScl, 
	//				gyro_odr gODR, accel_odr aODR, mag_odr mODR)
  uint16_t imuResult = imu->begin();
  cout<<hex<<"Chip ID: 0x"<<imuResult<<dec<<" (should be 0x49d4)"<<endl;

  bool newAccelData = false;
  bool newMagData = false;
  bool newGyroData = false;
  bool overflow = false;

  // Loop and report data
  while (1)
  {
    // First, let's make sure we're collecting up-to-date information. The
    //  sensors are sampling at 100Hz (for the accelerometer, magnetometer, and
    //  temp) and 95Hz (for the gyro), and we could easily do a bunch of
    //  crap within that ~10ms sampling period.
    while ((newGyroData & newAccelData & newMagData) != true)
    {
      if (newAccelData != true)
      {
        newAccelData = imu->newXData();
      }
      if (newGyroData != true)
      {
        newGyroData = imu->newGData();
      }
      if (newMagData != true)
      {
        newMagData = imu->newMData(); // Temp data is collected at the same
                                      //  rate as magnetometer data.
      } 
    }

    newAccelData = false;
    newMagData = false;
    newGyroData = false;

    // Of course, we may care if an overflow occurred; we can check that
    //  easily enough from an internal register on the part. There are functions
    //  to check for overflow per device.
    overflow = imu->xDataOverflow() | 
               imu->gDataOverflow() | 
               imu->mDataOverflow();

    if (overflow)
    {
      cout<<"WARNING: DATA OVERFLOW!!!"<<endl;
    }

    // Calling these functions causes the data to be read from the IMU into
    //  10 16-bit signed integer public variables, as seen below. There is no
    //  automated check on whether the data is new; you need to do that
    //  manually as above. Also, there's no check on overflow, so you may miss
    //  a sample and not know it.
    imu->readAccel();
    imu->readMag();
    imu->readGyro();
    imu->readTemp();

    // Print the unscaled 16-bit signed values.
    cout<<"-------------------------------------"<<endl;
    cout<<"Gyro x: "<<imu->gx<<endl;
    cout<<"Gyro y: "<<imu->gy<<endl;
    cout<<"Gyro z: "<<imu->gz<<endl;
    cout<<"Accel x: "<<imu->ax<<endl;
    cout<<"Accel y: "<<imu->ay<<endl;
    cout<<"Accel z: "<<imu->az<<endl;
    cout<<"Mag x: "<<imu->mx<<endl;
    cout<<"Mag y: "<<imu->my<<endl;
    cout<<"Mag z: "<<imu->mz<<endl;
    cout<<"Temp: "<<imu->temperature<<endl;
    cout<<"-------------------------------------"<<endl;

    // Print the "real" values in more human comprehensible units.
    cout<<"-------------------------------------"<<endl;
    cout<<"Gyro x: "<<imu->calcGyro(imu->gx)<<" deg/s"<<endl;
    cout<<"Gyro y: "<<imu->calcGyro(imu->gy)<<" deg/s"<<endl;
    cout<<"Gyro z: "<<imu->calcGyro(imu->gz)<<" deg/s"<<endl;
    cout<<"Accel x: "<<imu->calcAccel(imu->ax)<<" g"<<endl;
    cout<<"Accel y: "<<imu->calcAccel(imu->ay)<<" g"<<endl;
    cout<<"Accel z: "<<imu->calcAccel(imu->az)<<" g"<<endl;
    cout<<"Mag x: "<<imu->calcMag(imu->mx)<<" Gauss"<<endl;
    cout<<"Mag y: "<<imu->calcMag(imu->my)<<" Gauss"<<endl;
    cout<<"Mag z: "<<imu->calcMag(imu->mz)<<" Gauss"<<endl;
    // Temp conversion is left as an example to the reader, as it requires a
    //  good deal of device- and system-specific calibration. The on-board
    //  temp sensor is probably best not used if local temp data is required!
    cout<<"-------------------------------------"<<endl;
    sleep(1);
  }

	return MRAA_SUCCESS;
}
