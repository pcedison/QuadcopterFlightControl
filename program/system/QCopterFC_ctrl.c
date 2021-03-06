/*=====================================================================================================*/
/*=====================================================================================================*/
#include "QuadCopterConfig.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
vs16 PWM_M1 = PWM_MOTOR_MIN;
vs16 PWM_M2 = PWM_MOTOR_MIN;
vs16 PWM_M3 = PWM_MOTOR_MIN;
vs16 PWM_M4 = PWM_MOTOR_MIN;
static __IO uint16_t rc_ctrl_timeout = 0;
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
void Update_RC_Control(int16_t *Roll, int16_t  *Pitch, int16_t  *Yaw, int16_t  *Thr, uint8_t *safety)
{
	/*Get PWM3 Input capture to control trottle*/
	if ((global_var[PWM3_CCR].param > MIN_PWM_INPUT) &&
	    (global_var[PWM3_CCR].param < MAX_PWM_INPUT)) {

		*Thr = (PWM_MOTOR_MAX - PWM_MOTOR_MIN) / (MAX_PWM3_INPUT - MIN_PWM3_INPUT) *
		       (global_var[PWM3_CCR].param - MIN_PWM3_INPUT) + PWM_MOTOR_MIN;

	}

	/*Get PWM1 Input capture to control roll*/
	if ((global_var[PWM1_CCR].param > MIN_PWM_INPUT) &&
	    (global_var[PWM1_CCR].param < MAX_PWM_INPUT)) {

		//*Roll = (MAX_CTRL_ROLL - MIN_CTRL_ROLL) / (MAX_PWM1_INPUT - MIN_PWM1_INPUT) *
		//        (global_var[PWM1_CCR].param - MIN_PWM1_INPUT) + MIN_CTRL_ROLL;

		*Roll = MAX_CTRL_ROLL / (MAX_PWM1_INPUT - MID_PWM1_INPUT) *
			(global_var[PWM1_CCR].param - MID_PWM1_INPUT) ;


	}

	/*Get PWM2 Input capture to control pitch*/
	if ((global_var[PWM2_CCR].param > MIN_PWM_INPUT) &&
	    (global_var[PWM2_CCR].param < MAX_PWM_INPUT)) {

		//*Pitch = (MAX_CTRL_PITCH - MIN_CTRL_PITCH) / (MAX_PWM2_INPUT - MIN_PWM2_INPUT) *
		//        (global_var[PWM2_CCR].param - MIN_PWM2_INPUT) + MIN_CTRL_PITCH;

		*Pitch = MAX_CTRL_PITCH / (MAX_PWM2_INPUT - MID_PWM2_INPUT) *
			 (global_var[PWM2_CCR].param - MID_PWM2_INPUT) ;

	}

	/*Get PWM4 Input capture to control yaw*/
	if ((global_var[PWM4_CCR].param > MIN_PWM_INPUT) &&
	    (global_var[PWM4_CCR].param < MAX_PWM_INPUT)) {

		//*Yaw = (MAX_CTRL_YAW- MIN_CTRL_YAW) / (MAX_PWM4_INPUT - MIN_PWM4_INPUT) *
		//        (global_var[PWM4_CCR].param - MIN_PWM4_INPUT) + MIN_CTRL_YAW;

		*Yaw = MAX_CTRL_YAW / (MAX_PWM4_INPUT - MID_PWM4_INPUT) *
		       (global_var[PWM4_CCR].param - MID_PWM4_INPUT) ;

	}

	/*Get PWM5 Input capture to set safety switch*/
	if (global_var[PWM5_CCR].param > (MAX_PWM5_INPUT + MIN_PWM5_INPUT) / 2)
		*safety = 1;
	else
		*safety = 0;

	Bound(*Roll, MIN_CTRL_ROLL, MAX_CTRL_ROLL);
	Bound(*Pitch, MIN_CTRL_PITCH, MAX_CTRL_PITCH);
	Bound(*Yaw, MIN_CTRL_YAW, MAX_CTRL_YAW);
	Bound(*Thr, PWM_MOTOR_MIN, PWM_MOTOR_MAX);


}

RC_State remote_signal_check()
{
	RC_State rc_state = GET_SIGNAL;

	/*Get PWM3 Input capture to control trottle*/
	if ((global_var[PWM3_CCR].param > MIN_PWM_INPUT) &&
	    (global_var[PWM3_CCR].param < MAX_PWM_INPUT)) {

		rc_state |= GET_SIGNAL;

	} else {

		rc_state |= NO_SIGNAL;

	}

	/*Get PWM1 Input capture to control roll*/
	if ((global_var[PWM1_CCR].param > MIN_PWM_INPUT) &&
	    (global_var[PWM1_CCR].param < MAX_PWM_INPUT)) {

		rc_state |= GET_SIGNAL;

	} else {

		rc_state |= NO_SIGNAL;

	}

	/*Get PWM2 Input capture to control pitch*/
	if ((global_var[PWM2_CCR].param > MIN_PWM_INPUT) &&
	    (global_var[PWM2_CCR].param < MAX_PWM_INPUT)) {

		rc_state |= GET_SIGNAL;

	} else {

		rc_state |= NO_SIGNAL;
	}

	/*Get PWM4 Input capture to control yaw*/
	if ((global_var[PWM4_CCR].param > MIN_PWM_INPUT) &&
	    (global_var[PWM4_CCR].param < MAX_PWM_INPUT)) {

		rc_state |= GET_SIGNAL;

	} else {

		rc_state |= NO_SIGNAL;

	}

	// /*Get PWM5 Input capture to set safety switch*/
	// if( global_var[PWM5_CCR].param > (MAX_PWM5_INPUT - MIN_PWM5_INPUT)/2 )
	//         rc_state |= NO_SIGNAL;
	// else
	//         rc_state |= GET_SIGNAL;

	return rc_state;


}

