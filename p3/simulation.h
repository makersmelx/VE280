#ifndef SIMULATION_H
#define SIMULATION_H

#include "world_type.h"
#include <string>
//exception class
class worldError
{
public:
    worldError(int type, int val);
    worldError(int type, string *msg,int strLen);
    worldError(int type, int *val, int valLen, string *msg,int strLen);
    worldError(int type, string msg);
    worldError(int type, int len, creature_t **cr);
    void printError();
    //output error message

private:
    int errVal[10];
    string errMsg[10];
    creature_t *errCr[2];
    int errType;
};

void split(string &str, string *res, string &pattern);
//Spilt a string according to certain pattern

unsigned int initialize_creature(world_t &world, ifstream &file, species_t *speciesList); //Error 3, Error 13, Error 14
//initialize creature_t related attribute of world_t
//return creature numbers

void initialize_grid(grid_t &g, ifstream &file);
//initialize grid_t related attribute of world_t

void initialize_species(world_t &w);
//initialize species_t related attribute of world_t

void initialize_world(world_t &w, char *filename, species_t *species);
//generate world_t from reading world file, the main function

void read_file_species(string *list, string filename);
//read from the file "species", store the raw data in the array of string "list"

string *read_raw_instruction(string dir, string name);
//return an array of string, each item stands for one line of raw file data

struct instruction_t readable_instruct(string raw);
//translate the raw data of instruction into instruction_t

struct species_t *all_species(string *sp_list);
//interpretate commands from the species files, collect all the instruction for one species, then collect all the species
//return the list of all species loaded

point_t forward(point_t &loc, direction_t &d);
//return the point in front of the creature.
//arguments are the location and direction of the creature

bool out_of_boudary(point_t &loc, grid_t &g);
//return whether a certain point is out of the boundary of the world.

bool hop_helper(grid_t &g, point_t &loc, creature_t &c);
//return whether one creature meets all the requirement for one hop (no creature in front of it and not boundary)

void hop(creature_t &c, grid_t &g);
//execute instruction of hop

void left(creature_t &c);
//execute instruction of left

void right(creature_t &c);
//execute the instruction of right

void infect(creature_t &c, point_t &loc, grid_t &g);
//doing the process of infect

void action(creature_t &c, instruction_t *ins, grid_t &g, int count, bool v);
//execute the next instruction in the program list of one certain species
//count stands for the current program to execute

void print_round(int round);
//print the first line of the current round (Round n) during each round

void print_world(world_t &w);
//print the m*n world with creature information during each round

void take_round(world_t &w, int roundleft, bool verb);
// simulation the world in one round
// input is the world_t, the number of rounds (user input), whether in verbose mode(user input)

#endif