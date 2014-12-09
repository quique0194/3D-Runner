#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

#include <GL/glut.h>

#include "./Car.h"
#include "../constants.h"

class Player: public Car {
	public:
		Player(string model, double velocity):
			Car(model, velocity, TYPE_PLAYER),
			score(0) {

		}

		q3Vec3 getPosition();
		void moveRight();
		void moveLeft();
		void stopMovingToSides();
		void jump();
		void nitroOn();
		void nitroOff();

		int score;
};

q3Vec3 Player::getPosition() {
	return body->GetTransform().position;
}

void Player::moveRight() {
	q3Vec3 vel = body->GetLinearVelocity();
	vel[0] = 0;
	body->SetLinearVelocity(vel + q3Vec3(5, 0, 0));
}

void Player::moveLeft() {
	q3Vec3 vel = body->GetLinearVelocity();
	vel[0] = 0;
	body->SetLinearVelocity(vel + q3Vec3(-5, 0, 0));
}

void Player::stopMovingToSides() {
	q3Vec3 vel = body->GetLinearVelocity();
	vel[0] = 0;
	body->SetLinearVelocity(vel);
}

void Player::jump() {
	q3Vec3 vel = body->GetLinearVelocity();
	body->SetLinearVelocity(vel + q3Vec3(0, 10, 0));
}

void Player::nitroOn() {
	q3Vec3 vel = body->GetLinearVelocity();
	vel[2] = 2*velocity;
	body->SetLinearVelocity(vel);
}

void Player::nitroOff() {
	q3Vec3 vel = body->GetLinearVelocity();
	vel[2] = velocity;
	body->SetLinearVelocity(vel);
}

#endif
