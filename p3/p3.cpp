#include "simulation.h"
#include "world_type.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
int main(int argc, char **argv)
{
    if (argc < 3) //Error 1
    {
        std::cout << "Error: Missing arguments!" << endl;
        std::cout << "Usage: ./p3 <specices-summary> <world-file> <rounds> [v|verbose]" << endl;
        assert(0);
    }
    if (argv[2] - '0' < 0)
    {
        std::cout << "Error: Number of Simulation rounds is negative!" << endl;
        assert(0);
    }
    std::string dir_species[MAXSPECIES + 1];
    read_summary(dir_species, argv[1]);
    species_t *species = all_species(dir_species);

    struct world_t world;
    initialize_world(world, argv[2], species);

    string _round = argv[3];
    stringstream ss;
    ss << _round;
    int round;
    ss >> round;

    bool verbose = false;
    if (argc == 4)
        if (argv[3][0] == 'v')
            verbose = true;

    take_round(world, round, verbose);
    //work part
    //output part? do this with debug?
}