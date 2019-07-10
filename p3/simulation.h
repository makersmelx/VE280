#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "world_type.h"
#include <string>
class worldError //Exception class for the simulation process
{
public:
    worldError(int type, int val);
    worldError(int type, string *msg, int strLen);
    worldError(int type, int *val, int valLen, string *msg, int strLen);
    worldError(int type, string msg);
    worldError(int type, int len, creature_t **cr);
    void printError();
    //EFFECT: Print the error message.

private:
    int errVal[10];
    string errMsg[10];
    creature_t *errCr[2];
    int errType;
};

void split(string &str, string *res, const string &pattern);
//EFFECT: Spilt a string into several parts according to the certain pattern and save the result in array "res"
//MODIFY: res

unsigned int initialize_creature(world_t &world, ifstream &file, species_t *speciesList, const int &sp_nums); //Error 3, Error 13, Error 14
//EFFECT: initialize ("world") all the creature_t, and set each of their location on "grid_t" of "world", according to input the world file "file"
//EFFECT: return the number of creatures
//MODIFY: "world"
//REQUIRE: void initialize_grid(grid_t &g, ifstream &file) has already been called

void initialize_grid(grid_t &g, ifstream &file);
//EFFECT: initialize the grid_t "g" according to the input world file "file"
//REQUIRE: file is opened
//MODIFY: "g"

void initialize_species(world_t &w);
//EFFECT: initialize "species[MAXSPECIES]" of the world_t "w" according to "creatures[MAXCREATURES]".
//REQUIRE: unsigned int initialize_creature(world_t &world, ifstream &file, species_t *speciesList) has already been called
//MODIFY: "w"

void initialize_world(world_t &w, char *filename, species_t *species, const int &sp_nums);
//EFFECT: initialize all the attributes of world_t "w"
//REQUIRE: "species" is not empty
//MODIFY: "w"

int read_file_species(string *list, const string filename);
//EFFECT: read from the file "filename", store the raw data in the array of string "list"
//EFFECT: return the species numbers on the file species.
//MODIFY: "list"

string *read_raw_instruction(const string dir, const string name);
//EFFECT: read and store all the raw data of instruction for one species in the species-named file.
//EFFECT: return an array of string, each item stands for one line of raw file data(Comments are ignored in the process).

struct instruction_t readable_instruct(const string raw);
//EFFECT: translate the raw data of instruction into structure instruction_t
//EFFRCT: return instruction_t interpretation of the instruction.

struct species_t *all_species(string *sp_list, const int &sp_nums);
//EFFECT: read instructions from all the creature files, collect all the instructions for one species, then collect all the species
//EFFECT: return the list of all species with all their instructions loaded

point_t forward(point_t &loc, direction_t &d);
//EFFECT: return the point in front of the creature. Arguments are the location and direction of the creature
//Note: can be out of boundary of the grid

bool out_of_boudary(point_t &loc, grid_t &g);
//EFFECT: return whether a certain point is out of the boundary of the grid of the world.

bool hop_helper(grid_t &g, point_t &loc, creature_t &c);
//EFFECT: return whether one creature meets all the requirement for one hop (no creature in front of it and not boundary)

void hop(creature_t &c, grid_t &g);
//EFFECT: execute instruction of hop

void left(creature_t &c);
//EFFECT: execute instruction of left

void right(creature_t &c);
//EFFECT: execute the instruction of right

void infect(creature_t &c, point_t &loc, grid_t &g);
//EFFECT: execute the instruction of infect

void action(creature_t &c, instruction_t *ins, grid_t &g, int count, bool v);
//EFFECT: execute the count th instruction in the program list of the creature "c"

void print_round(int round);
//EFFECT: print the first line of the current round (Round n) during each round

void print_world(world_t &w);
//EFFECT: print the m*n world with creature information during each round

void take_round(world_t &w, int roundleft, bool verb);
// EFFECT: simulation the world with "roundleft" rounds. The input is the world_t, the number of rounds (user input), whether in verbose mode(user input)
//MODIFY:"w"

#endif