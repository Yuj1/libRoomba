#ifndef LIBROOMBA_COMMON_HEADER_INCLUDED
#define LIBROOMBA_COMMON_HEADER_INCLUDED

#ifdef WIN32
// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ LIBROOMBA_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// LIBREVAST_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef LIBROOMBA_EXPORTS
#define LIBROOMBA_API __declspec(dllexport)
#else
#ifdef LIBROOMBA_STATIC_EXPORTS
#define LIBROOMBA_API 
#else

#define LIBROOMBA_API __declspec(dllimport)
#endif // LIBROOMBA_STATIC_EXPORTS
#endif

#else 
#define LIBROOMBA_API 
#endif // ifdef WIN32



/// Definitions 

/**
 * @brief Roomba's Modes.
 * 
 * Mainly Roomba has three modes, PASSIVE, SAFE, and FULL.
 * The other modes invode some specific behavior like spot-cleaning.
 * During those specific behaviors, Roomba is in PASSIVE modes.
 * These values are used in Roomba_setMode, Roomba_getMode functions.
 *
 * @see Roomba_setMode, Roomba_getMode
 */
enum Mode {
	MODE_START = 89, //!< Start Command
	MODE_OFF = 90, //!< Power Off mode
	MODE_PASSIVE = 100, //!< Passive Mode 
	MODE_SAFE, //!< Safe Mode
	MODE_FULL, //!< Full Control Mode
	MODE_SLEEP, //!< Sleep Mode
	MODE_SPOT_CLEAN, //!< Spot Clean (Passive Mode)
	MODE_NORMAL_CLEAN, //!< Normal Clean (Passive Mode)
	MODE_MAX_TIME_CLEAN, //!< Maximum Time Clean (Passive Mode)
	MODE_DOCK, //!< Search Dock Station (Passive Mode)
	MODE_POWER_DOWN, //!< Power Down
};

/**
 * @brief Roomba's LEDs Identifier
 * LEDs' Identifier used in Roomba_setLED
 * @see Roomba_setLED
 */
enum LED {
	LED_CHECK_ROBOT = 0x08, //!< LED of Check Roomba Mark (Red)
	LED_DOCK = 0x04, //!< LED of Dock (Green)
	LED_SPOT = 0x02, //!< LED of Spot (Green)
	LED_DEBRIS = 0x01, //!< LED of Debris Sensor (Debri Sign)
};

/**
 * @brief Return Code
 * Functions Return Code
 */
enum ReturnCode {
	PRECONDITION_NOT_MET = -1, //!< Precondition is not fine
	ROOMBA_OK = 0, //!< Return Code OK.
};

/**
 * @brief Motor Identifier
 * 
 * Motor Identifier used in Roomba_driveMotors functions
 * @see Roomba_driveMotors
 */
enum Motors {
	MOTOR_CCW = -1, //!< Motor Turns CCW
	MOTOR_OFF = 0, //!< Motor Off
	MOTOR_CW  = 1, //!< Motor Turns CW
	MOTOR_ON  = 1, //!< Motor On
};

/**
 * @brief Motor Identifier
 * These values represents motors on Roomba 500 series.
 *
 * @see Roomba_driveMotors
 */
enum MotorFlag {
	SideBrush = 0x01, //!< Side Brush
	Vacuum = 0x02, //!< Vacuum Motor
	MainBrush = 0x04, //!< Main Brush Motor
	SideBrushOpposite = 0x08, //!< Side Brush turns opposite flag
	MainBrushOpposite = 0x10, //!< Main Brush turns opposite flag
	LeftWheel = 0x10, //!< Left Wheel Motor
	RightWheel = 0x08, //!< Right Wheel Motor
};

/**
 * @brief Button Identifier.
 * Button Identifier used in Roomba_setButton
 *
 * @see Roomba_setButton
 */
enum ButtonFlag {
	Clock = 0x80, //!< Clock Button
	Schedule = 0x40, //!< Schedule Button
	Day = 0x20, //!< Day Button
	Hour = 0x10, //!< Hour Button
	Minute = 0x08, //!< Minute Button
	Dock = 0x04, //!< Dock Button
	Spot = 0x02, //!< Spot Button
	Clean = 0x01, //!< Clean Button
};


/**
 * @brief Charging State Identifier
 * These values represent charging state of Roomba
 *
 * @see Roomba_getChargingState
 */
enum ChargingState {
	NotCharging = 0, //!< Not Charging Now
	ReconditioningCharging, //!< Reconditioning (Preparing) Charging 
	FullCharging, //!< Full Charging
	TrickleCharging, //!< Trickle Charging (Nearly full)
	Waiting, //!< Waiting for charge
	ChargingFaultCondition //!< Fault state (Error)
};



#endif // #ifndef COMMON_HEADER_INCLUDED