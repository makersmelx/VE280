#ifndef SIMULATION_H
#define SIMULATION_H

#include "world_type.h"
#include <string>

struct string_error
{
    string val;
    int type;
};

struct int_error
{
    int val;
    int type;
};

void split(string &str, string *res, string &pattern);
//Spilt a string according to certain pattern
//checked

unsigned int initialize_creature(world_t &world, ifstream &file, species_t *speciesList); //Error 3, Error 13, Error 14
//initialize creature_t related attribute of world_t
//return creature numbers

void initialize_grid(grid_t &g, ifstream &file);
//initialize grid_t related attribute of world_t
//checked

void initialize_species(world_t &w);
//initialize species_t related attribute of world_t

void initialize_world(world_t &w, char *filename, species_t *species); //Error 3 ,Error 7, Error 8, Error 9
//generate world_t from reading world file, the main function

void read_summary(string *list, string filename);
//read from "species"

string *read_raw_instruction(string dir, string name);
//return an array of string, each item stands for one line of raw file content, including comments
//checked

struct instruction_t readable_instruct(string raw);
//translate the raw string into instruction_t
//checked

struct species_t *all_species(string *sp_list);
//interpretate commands from files and collect all the instruction for one species and collect all the species
//checked
point_t forward(point_t &loc, direction_t &d);

bool out_of_boudary(point_t &loc, grid_t &g);

bool hop_helper(grid_t &g, point_t &loc, creature_t &c); //true means can do

void infect(creature_t &c, point_t &loc, grid_t &g);

void action(creature_t &c, instruction_t *ins, grid_t &g, int count, bool v);

void print_round(int round);

void print_world(world_t &w);

void take_round(world_t &w, int now, bool verb);

// void pos_change(world_t &w, creature_t cr, int dest_r, int dest_c);
// //respond on grid_t of the world, the pos_change of creature.

#endif