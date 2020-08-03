#include "main.h"

#define FRONT_LEFT 5
#define FRONT_RIGHT 10
#define BACK_LEFT 14
#define BACK_RIGHT 19

using namespace pros;

Motor frontLeft(FRONT_LEFT);
Motor frontRight(FRONT_RIGHT, true);
Motor backLeft(BACK_LEFT);
Motor backRight(BACK_RIGHT, true);
Controller vexController(E_CONTROLLER_MASTER);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	lcd::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


void opcontrol() {
	while(true) {

		double forward = 0.75 * vexController.get_analog(ANALOG_LEFT_Y);
		double turn = 0.5 * vexController.get_analog(ANALOG_LEFT_X);
		double strafe = 0.75 * vexController.get_analog(ANALOG_RIGHT_X);

		int frontLeftVoltage = forward + strafe + turn;
		int frontRightVoltage = forward - strafe - turn;
		int backLeftVoltage = forward + strafe - turn;
		int backRightVoltage = forward - strafe + turn;

		int deadZone = 5;

		bool frontLeftMoving = !(-deadZone < frontLeftVoltage && frontLeftMoving < deadZone);
		bool frontRightMoving = !(-deadZone < frontRightVoltage && frontRightVoltage < deadZone);
		bool backLeftMoving = !(-deadZone < backLeftVoltage && backLeftVoltage < deadZone);
		bool backRightMoving = !(-deadZone < backRightVoltage && backRightVoltage < deadZone);

		if(frontLeftMoving || frontRightMoving || backLeftMoving || backRightMoving){
			frontLeft.move(frontLeftVoltage);
			frontRight.move(frontRightVoltage);
			backLeft.move(backLeftVoltage);
			backRight.move(backRightVoltage);
		}else{
			frontLeft.move(0);
			frontRight.move(0);
			backLeft.move(0);
			backRight.move(0);
		}
		// frontLeft.move(forward + strafe + turn);
		// frontRight.move(forward - strafe - turn);
		// backLeft.move(forward + strafe - turn);
		// backRight.move(forward - strafe + turn);


		delay(20);
	}
}
