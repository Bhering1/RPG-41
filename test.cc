#include "actor.h"
#include <iostream>
using namespace std;

int main() {
	Actor act;
	act.set_attack(1);
	act.set_defense(2);
	act.set_speed(3);
	act.set_name("something");
	cout << act.get_attack() << act.get_defense() << act.get_speed() << act.get_name() << endl;


	Fighter Tordek;
	Lhosk Koko;

	Tordek.set_attack(1);
	Tordek.set_defense(2);
	Tordek.set_speed(3);
	Tordek.set_name("something");
	cout << Tordek.get_attack() << Tordek.get_defense() << Tordek.get_speed() << Tordek.get_name() << Tordek.get_feat() << endl;
}
