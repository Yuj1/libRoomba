#pragma once

#include <windows.h>

#include "common.h"
#include "op_code.h"
#include "Transport.h"

#include <RoombaException.h>

namespace net {
	namespace ysuga {
		namespace roomba {
			class Roomba
			{
			private:
				enum ReturnCode {
					ROOMBA_INVALID_PRECONDITION = -1,
					ROOMBA_OK = 0,
				};

			public:

				/**
				 * @brief Roomba's Modes.
				 * 
				 * Mainly Roomba has three modes, PASSIVE, SAFE, and FULL.
				 * The other modes invode some specific behavior like spot-cleaning.
				 * During those specific behaviors, Roomba is in PASSIVE modes.
				 */
				enum Mode {
					PASSIVE = 100,
					SAFE,
					FULL,
					SLEEP,
					SPOT_CLEAN,
					NORMAL_CLEAN,
					MAX_TIME_CLEAN,
					DOCK,
					POWER_DOWN,
				};

			private:
				Mode m_CurrentMode;

			private:
				Transport *m_pTransport;

			public:

				/**
				 * @brief Constructor
				 *
				 * @param portName Port Name that Roomba is connected (e.g., "\\\\.\\COM4", "/dev/ttyUSB0")
				 * @param baudrate Baud Rate. Default 115200.
				 */
				LIBROOMBA_API Roomba(const char *portName, const int baudrate = 115200);

				/**
				 * @brief Destructor
				 */
				LIBROOMBA_API virtual ~Roomba(void);


			public:
				/** 
				 * @brief Set Roomba's mode 
				 *
				 * Roomba's Mode definitions are as follows: <br />
				 *  -- SAFE   Safe mode. (Precondition must be FULL)
				 *  -- FULL   Full control mode. No safety features. 
				 *  -- POWER  Power Down Roomba (In this mode, Roomba is in PASSIVE mode.)
				 *  -- SPOT_CLEAN  Start Spot cleaning (In this mode, Roomba is in PASSIVE mode.)
				 *  -- NORMAL_CLEAN  Start normal cleaning (In this mode, Roomba is in PASSIVE mode.)
				 *  -- MAX_TIME_CLEAN  Start cleaning in maximum time (In this mode, Roomba is in PASSIVE mode.)
				 *  -- DOCK Start seeking dock station (In this mode, Roomba is in PASSIVE mode.)
				 *
				 * @param mode Mode Definition
				 */
				LIBROOMBA_API void SetMode(Mode mode);

				/** 
				 * @brief Get Roomba's mode 
				 *
				 * Roomba's Mode definitions are as follows: <br />
				 *  -- SAFE   Safe mode. (Precondition must be FULL)
				 *  -- FULL   Full control mode. No safety features. 
				 *  -- POWER  Power Down Roomba (In this mode, Roomba is in PASSIVE mode.)
				 *  -- SPOT_CLEAN  Start Spot cleaning (In this mode, Roomba is in PASSIVE mode.)
				 *  -- NORMAL_CLEAN  Start normal cleaning (In this mode, Roomba is in PASSIVE mode.)
				 *  -- MAX_TIME_CLEAN  Start cleaning in maximum time (In this mode, Roomba is in PASSIVE mode.)
				 *  -- DOCK Start seeking dock station (In this mode, Roomba is in PASSIVE mode.)
				 *
				 * @param mode Mode Definition
				 */
				LIBROOMBA_API Mode GetMode() const {
					return m_CurrentMode;
				}
			public:


				/**
				 * @brief Drive Roomba with Translation Velocity and Turn Radius.
				 *
				 * @param translation Translation Velcoity (-500 – 500 mm/s)  
				 * @param turnRadius Radius (-2000 – 2000 mm) (negative => CCW)
				 * @throw PreconditionNotMetError
				 */
				LIBROOMBA_API void Drive(unsigned short translation, unsigned short turnRadius);


				/**
				 * @brief Drive Each Wheel Directly
				 *
				 * @param rightWheel Translation Velocity (-500 - 500 mm/s)
				 * @param leftWheel  Translation Velocity (-500 - 500 mm/s)
				 * @throw PreconditionNotMetError
				 */
				LIBROOMBA_API void DriveDirect(unsigned short rightWheel, unsigned short leftWheel);


				
				enum OP_LED {
					LED_CHECK_ROBOT = 0x08,
					LED_DOCK = 0x04,
					LED_SPOT = 0x02,
					LED_DEBRIS = 0x01,
				};

				/**
				 * @brief Set LEDs on Roomba
				 *
				 * This function changes LEDs lighting states.
				 * The first argument must be the OR of following values:
				 *  LED_CHECK_ROBOT, LED_DOCK, LED_SPORT, LED_DEBRIS.
				 * The second argument indicates the intensity (0 - 255)
				 * The third argument indicates the color of CLEAN/POWER button 
				 * which places on the center of the top panel of the robot.
				 * 0 and 255 corresponds to green and red respectively. The other
				 * values mean intermediate colors.
				 *
				 * @param leds flags that indicates leds. (0-255)
				 * @param intensity intensity of the leds. (0-255)
				 * @param color color of the CLEAN/POWER button (0-green, 255-red).
				 */
				LIBROOMBA_API void SetLED(unsigned char leds, unsigned char intensity, unsigned char color = 127);

			private:
				void RequestSensor(unsigned char sensorId, short *value);
				void RequestSensor(unsigned char sensorId, unsigned short *value);
				void RequestSensor(unsigned char sensorId, char *value);
				void RequestSensor(unsigned char sensorId, unsigned char *value);

			public:

				LIBROOMBA_API int IsRightWheelDropped() {
					unsigned char buf;
					RequestSensor(BUMPS_AND_WHEEL_DROPS, &buf);
					return buf & 0x04 ? true : false;
				}

				LIBROOMBA_API int IsLeftWheelDropped() {
					unsigned char buf;
					RequestSensor(BUMPS_AND_WHEEL_DROPS, &buf);
					return buf & 0x08 ? true : false;
				}

				LIBROOMBA_API int IsRightBump() {
					unsigned char buf;
					RequestSensor(BUMPS_AND_WHEEL_DROPS, &buf);
					return buf & 0x01 ? true : false;
				}

				LIBROOMBA_API int IsLeftBump() {
					unsigned char buf;
					RequestSensor(BUMPS_AND_WHEEL_DROPS, &buf);
					return buf & 0x02 ? true : false;
				}

				LIBROOMBA_API int IsCliffLeft() {
					unsigned char buf;
					RequestSensor(CLIFF_LEFT, &buf);
					return buf;
				}

				LIBROOMBA_API int IsCliffFrontLeft() {
					unsigned char buf;
					RequestSensor(CLIFF_FRONT_LEFT, &buf);
					return buf;
				}

				LIBROOMBA_API int IsCliffFrontRight() {
					unsigned char buf;
					RequestSensor(CLIFF_FRONT_RIGHT, &buf);
					return buf;
				}

				LIBROOMBA_API int IsCliffRight() {
					unsigned char buf;
					RequestSensor(CLIFF_RIGHT, &buf);
					return buf;
				}


				LIBROOMBA_API int GetTemperature() {
					char buf;
					RequestSensor(TEMPERATURE, &buf);
					return buf;
				}
				
				LIBROOMBA_API int IsVirtualWall() {
					unsigned char buf;
					RequestSensor(VIRTUAL_WALL, &buf);
					return buf;
				}



				LIBROOMBA_API int GetVoltage() {
					unsigned short buf;
					RequestSensor(VOLTAGE, &buf);
					return buf;
				}

				LIBROOMBA_API int GetRequestedVelocity() {
					short buf;
					RequestSensor(VOLTAGE, &buf);
					return buf;
				}
			};

		}
	}
}
