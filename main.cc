//Put your name(s) here: Noah Ethridge-Smith
//What bullet points did you do: 1, 2, and some of 3
#include "map.h"
#include "actor.h" //has const ints like TIMEOUT and ncurses
#include <memory>
#include <unistd.h>


int main() {
	turn_on_ncurses(); //DON'T DO CIN or COUT WHEN NCURSES MODE IS ON
	Map map;

	int money = 0;
	int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
	int old_x = -1, old_y = -1;

	Fighter hero1;
	hero1.set_name("Tordek");
	Lhosk monster1;
	monster1.set_name("Koko");

	vector<shared_ptr<Actor>> vec;
	vec.push_back(make_shared<Fighter>(hero1));
	vec.push_back(make_shared<Lhosk>(monster1));

	map.set_map(map.load_map("map.txt"), map);


	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') {
			map.save_map(map.get_map(), "map.txt");
			break;
		} else if (ch == RIGHT) {
			x++;
			if (x >= Map::SIZE) x = Map::SIZE - 22; //Clamp value
		} else if (ch == LEFT) {
			x--;
			if (x < 0) x = 0;
		} else if (ch == UP) {
			y--;
			if (y < 0) y = 0;
		} else if (ch == DOWN) {
			y++;
			if (y >= Map::SIZE) y = Map::SIZE - 1; //Clamp value
		} else if (ch == ERR) {
			;
		}  else if (ch == 's' || ch == 'S') { //save
			map.save_map(map.get_map(), "map.txt");
		}  else if (ch == 'l' || ch == 'L') { //load
			map.set_map(map.load_map("map.txt"), map);

		} else if (ch == 'r' || ch == 'R') { //redraw map
			map.init_map();
			money = 0;
			x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
		}


		if (money >= 10) game_over();

		//Stop flickering by only redrawing on a change
		if (x != old_x or y != old_y) {
			if (map.get(x, y) == Map::TREASURE) {
				map.set(x, y, Map::OPEN);
				money++;
			} else if (map.get(x, y) == Map::WALL || map.get(x, y) == Map::WATER) {
				x = old_x;
				y = old_y;
			} else if (map.get(x, y) == Map::MONSTER) {
				map.set(x, y, Map::OPEN);
			}
			//clear(); //Put this in if the screen is getting corrupted
			map.draw(x, y);
			mvprintw(Map::DISPLAY + 1, 0, "X: %i Y: %i, Treasure: %i\n", x, y, money);
			refresh();
		}
		old_x = x;
		old_y = y;
		usleep(1'000'000 / MAX_FPS);
	}
	turn_off_ncurses();
}


