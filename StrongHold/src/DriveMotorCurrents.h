/*
 * DriveMotorCurrents.h
 *
 *  Created on: Feb 6, 2016
 *      Author: RoboGym
 */

#ifndef SRC_DRIVEMOTORCURRENTS_H_
#define SRC_DRIVEMOTORCURRENTS_H_

class DriveMotorCurrents {
public:
	enum MotorId {
		firstMotor = 0,
		frontLeft = firstMotor,
		frontRight,
		backLeft,
		backRight,
		lastMotor = backRight,
		numMotors
	};

	DriveMotorCurrents(double frontLeft, double frontRight, double backLeft, double backRight) {
		currents[MotorId::frontLeft] = frontLeft;
		currents[MotorId::frontRight] = frontRight;
		currents[MotorId::backLeft] = backLeft;
		currents[MotorId::backRight] = backRight;
	}

	double getCurrent(MotorId mi) const {
		return currents[mi];
	}

private:
	double currents[4];
};

#endif /* SRC_DRIVEMOTORCURRENTS_H_ */
