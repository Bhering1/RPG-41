#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <ncurses.h>
using namespace std;

class Map {
	vector<vector<char>> map;
	default_random_engine gen;
	public:
	//TODO: Write a getter and a setter to get/set the characters in the map
	//TODO: Write a function to save the map and reload the map
	char get(int x, int y) const { 
		return map.at(y).at(x);
	}

	void set(int x, int y, char place) {
		map.at(y).at(x) = place;
	}

	vector<vector<char>> get_map() const{
		return map;
	}

	void set_map(const vector<vector<char>>& mapCp, Map& mapOg) { 

		for(int i = 0; i <SIZE-1; ++i)  {
			for (int j = 0; j <SIZE-1; ++j) {
				mapOg.set(i, j, mapCp.at(j).at(i));

			}
		}
	}

	void save_map(const vector<vector<char>>& map_S, const string& filename){

		ofstream map_save(filename);

		if (!map_save) {
			cout << "Error: coudln't open " << filename << " for writing." << endl;
			exit(1);
		}

		for (const vector<char>& row : map_S) {
			for (char col : row) {
				map_save << col;
			}
			map_save << endl;
		}
		map_save.close();
	}

	vector<vector<char>> load_map(const string& filename){ 

		ifstream map_load(filename);
		if(!map_load){
			cout << "Unable to read from " << filename << ".\n";
			exit(1);
		}
		vector<vector<char>> retval(SIZE, vector<char>(SIZE));
		for (vector<char>& row : retval) {
			for (auto &col : row) {
				col = map_load.get();
				if(!map_load){
					cout << "Unable to read from " << filename << ".\n";
					exit(1);
				}
			}
		}	
		map_load.close();

		return retval;
	}
	/*	vector<vector<char>> load_(const string& filename) {//makes a 2d vec of chars for set_map

		ifstream map_load(filename);
		if(!map_load){
		cout << "Unable to read from " << filename << ".\n";
		exit(1);
		}
		vector<vector<char>> retval(SIZE, vector<char>(SIZE));
		for (vector<char>& row : retval) {
		for (auto &col : row) {
		col = map_load.get();
		if(!map_load){
		cout << "Unable to read from " << filename << ".\n";
		exit(1);
		}
		}
		}
		}
		*/
	static const char HERO     = 'H';
	static const char MONSTER  = 'M';
	static const char WALL     = '#';
	static const char WATER    = '~';
	static const char OPEN     = '.';
	static const char TREASURE = '$';
	static const size_t SIZE = 100; //World is a 100x100 map
	static const size_t DISPLAY = 30; //Show a 30x30 area at a time
									  //Randomly generate map
	void init_map() {


		uniform_int_distribution<int> d100(1,100);
		map.clear();
		map.resize(SIZE); //100 rows tall
		for (auto &v : map) v.resize(SIZE,'.'); //100 columns wide
		for (size_t i = 0; i < SIZE; i++) {
			for (size_t j = 0; j < SIZE; j++) {
				//Line the map with walls
				if (i == 0 or j == 0 or i == SIZE-1 or j == SIZE-1) 
					map.at(i).at(j) = WALL;
				else if (i == SIZE/2 and j == SIZE/2) 
					map.at(i).at(j) = HERO;
				else {
					//5% chance of monster
					if (d100(gen) <= 5) {
						map.at(i).at(j) = MONSTER;
					}
					else if (d100(gen) <= 3) {
						map.at(i).at(j) = TREASURE;
					}
					else if (d100(gen) <= 10) { //10% each spot is wall
						map.at(i).at(j) = WALL;
					}
					else if (d100(gen) <= 3) { //3% each spot is water
						map.at(i).at(j) = WATER;
					}
					else if (d100(gen) <= 40) { //40% chance of water near other water
						if (map.at(i-1).at(j) == WATER or map.at(i+1).at(j) == WATER or map.at(i).at(j-1) == WATER or map.at(i).at(j+1) == WATER)
							map.at(i).at(j) = WATER;
					}
				}
			}
		}
	}
	//Draw the DISPLAY tiles around coordinate (x,y)
	void draw(int x, int y) {
		int start_x = x - DISPLAY/2;
		int end_x = x + DISPLAY/2;
		int start_y = y - DISPLAY/2;
		int end_y = y + DISPLAY/2;

		//Bounds check to handle the edges
		if (start_x < 0) {
			end_x = end_x - start_x;
			start_x = 0;
		}
		if (end_x > SIZE-1) {
			start_x = start_x - (end_x - (SIZE-1));
			end_x = SIZE-1;
		}
		if (start_y < 0) {
			end_y = end_y - start_y;
			start_y = 0;
		}
		if (end_y > SIZE-1) {
			start_y = start_y - (end_y - (SIZE-1));
			end_y = SIZE-1;
		}

		//Now draw the map using NCURSES
		for (size_t i = start_y; i <= end_y; i++) {
			for (size_t j = start_x; j <= end_x; j++) {
				if (i == y && j == x) {
					attron(A_UNDERLINE | A_BOLD);
					mvaddch(i-start_y,j-start_x,'H');
					attroff(A_UNDERLINE | A_BOLD);
				}
				else {
					int color = 1;
					if (map.at(i).at(j) == WALL)
						color = 5;
					else if (map.at(i).at(j) == WATER)
						color = 2;
					else if (map.at(i).at(j) == HERO)
						color = 3;
					else if (map.at(i).at(j) == TREASURE)
						color = 4;
					else if (map.at(i).at(j) == MONSTER)
						color = 6;

					attron(COLOR_PAIR(color));
					mvaddch(i-start_y,j-start_x,map.at(i).at(j));
					attroff(COLOR_PAIR(color));
				}
			}
		}
	}
	Map() {
		init_map();
	}
};
