#ifndef COINCONTACT_H
#define COINCONTACT_H

#include <algorithm>
using namespace std;

#include "../lib/qu3e/src/q3.h"
#include "../constants.h"
#include "../PlatformObject.h"
#include "../Platform.h"
#include "../PlatformObjects/Player.h"
#include "../gamesound.h"

class MyContactListener: public q3ContactListener {
	public: 
		MyContactListener(Platform* _platform, Player* _player):
			platform(_platform),
			player(_player) {

		}
		void BeginContact( const q3ContactConstraint *contact ) {
			PlatformObject* obj2 = (PlatformObject*)contact->bodyB->m_userData;
			PlatformObject* obj1 = (PlatformObject*)contact->bodyA->m_userData;
			// cout << obj1->body_type << endl;
			// cout << obj2->body_type << endl;
			if (obj2->body_type == TYPE_PLAYER) {
				swap(obj1, obj2);
			}
			if (obj1->body_type == TYPE_PLAYER) {
				if (obj2->body_type == TYPE_COIN) {
					play_hero_sound(HERO_COIND_SOUND);
					player->score += obj2->value;
					cout << "SCORE: " << player->score << endl;
					platform->removeObject(obj2);
					return;
				}
				if (obj2->body_type == TYPE_OBSTACLE) {
					play_hero_sound(HERO_CRASH_SOUND);
					player->score += obj2->value;
					cout << "SCORE: " << player->score << endl;
					return;	
				}
			}
		}

		void EndContact( const q3ContactConstraint *contact ) {
		}
	private:
		Platform* platform;
		Player* player;
};

#endif
