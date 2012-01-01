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
#define LIBROOMBA_API __declspec(dllimport)
#endif

#endif // ifdef WIN32



/// Definitions 

/**
 * @brief Roomba's Modes.
 * 
 * Mainly Roomba has three modes, PASSIVE, SAFE, and FULL.
 * The other modes invode some specific behavior like spot-cleaning.
 * During those specific behaviors, Roomba is in PASSIVE modes.
 */
enum Mode {
	MODE_OFF = 90,
	MODE_PASSIVE = 100,
	MODE_SAFE,
	MODE_FULL,
	SLEEP,
	SPOT_CLEAN,
	NORMAL_CLEAN,
	MAX_TIME_CLEAN,
	DOCK,
	POWER_DOWN,
};


/**
 * @brief Roomba's LEDs
 */
enum OP_LED {
	LED_CHECK_ROBOT = 0x08,
	LED_DOCK = 0x04,
	LED_SPOT = 0x02,
	LED_DEBRIS = 0x01,
};


enum Motors {
	MOTOR_CCW = -1,
	MOTOR_OFF = 0,
	MOTOR_CW  = 1,
	MOTOR_ON  = 1,
};

enum MotorFlag {
	SideBrush = 0x01,
	Vacuum = 0x02,
	MainBrush = 0x04,
	SideBrushOpposite = 0x08,
	MainBrushOpposite = 0x10,
	LeftWheel = 0x10,
	RightWheel = 0x08,
};

enum ButtonFlag {
	Clock = 0x80,
	Schedule = 0x40,
	Day = 0x20,
	Hour = 0x10,
	Minute = 0x08,
	Dock = 0x04,
	Spot = 0x02,
	Clean = 0x01,
};

enum ChargingState {
	NotCharging = 0,
	ReconditioningCharging,
	FullCharging,
	TrickleCharging,
	Waiting,
	ChargingFaultCondition
};



#endif // #ifndef COMMON_HEADER_INCLUDED