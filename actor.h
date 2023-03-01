#pragma once
#include <string>
#include <unistd.h>
using namespace std;

const int MAX_FPS = 90; //Cap frame rate //stuffed in here for my sanity
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;
const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish


//Turns on full screen text mode
void turn_on_ncurses() {
	initscr();//Start curses mode
	start_color(); //Enable Colors if possible
	init_pair(1, COLOR_WHITE, COLOR_BLACK); //Set up some color pairs
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	clear();
	noecho();
	cbreak();
	timeout(TIMEOUT); //Set a max delay for key entry
}

//Exit full screen mode - also do this if you ever want to use cout or gtest or something
void turn_off_ncurses() {
	clear();
	endwin(); // End curses mode
	if (system("clear")) {}
}

void game_over() {
	turn_off_ncurses();
	usleep(500'000);
	(void)!system("figlet You Found Enough Gold!\n");
	usleep(2'000'000);
	if (system("clear")) {}
	(void)!system("figlet GAME OVER");
	usleep(2'000'000);
	exit(0);

}

struct Actor {
	int health = 0;
	int attack = 0;
	int defense = 0;
	int speed = 0;
	string name;
	
	int get_health() const {return health;}
	int get_attack() const {return attack;}
	int get_defense() const {return defense;}
	int get_speed() const {return speed;}
	string get_name() const {return name;}

	void set_health(int h) {health = h;}
	void set_attack(int a) {attack = a;}
	void set_defense(int d) {defense = d;}
	void set_speed(int s) {speed = s;}
	void set_name(const string str) {name = str;}
};

struct Hero : Actor {
 int action_points = 0;

 int get_ap() const {return action_points;}
 void set_ap(int ap) {action_points = ap;}
};

struct  Monster : Actor {
 int mutations = 0;

 int get_mutations() const {return mutations;}
 void set_mutation(int m) {mutations = m;}
};

struct Fighter : Hero {
	string feat = "Power Attack";

	string get_feat() const {return feat;}
	void set_feat(const string str) {feat = str;}

	Fighter() {
		set_health(100);
		set_attack(30);
		set_defense(10);
		set_speed(4);
	}
};

struct Lhosk : Monster {
	string ability = "Entangling Web";

	string get_ability() const {return ability;}
	void set_ability(const string ab) {ability = ab;}

	Lhosk() {
		set_health(400);
		set_attack(50);
		set_defense(20);
		set_speed(2);
	}
};
