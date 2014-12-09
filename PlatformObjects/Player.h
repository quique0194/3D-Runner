#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

#include "./Car.h"

class Player: public Car {
	public:
		Player(string model, double velocity): Car(model, velocity){

		}

		q3Vec3 getPosition();
		void moveRight();
		void moveLeft();
		void stopMovingToSides();
		void jump();
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

#endif
