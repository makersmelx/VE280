#include "simulation.h"
#include "world_type.h"
#include <cassert>
#include <iostream>
#include <string>
int main(int argc, char **argv)
{
    if (argc < 3) //Error 1
    {
        std::cout << "Error: Missing arguments!" << endl;
        std::cout << "Usage: ./p3 <specices-summary> <world-file> <rounds> [v|verbose]" << endl;
        assert(0);
    }

    string _round = argv[3];
    int round = stoi(_round);
    if (round < 0)
    {
        std::cout << "Error: Number of Simulation rounds is negative!" << endl;
        assert(0);
    }

    bool verbose = false;
    if (argc == 5)
    {
        string _ver = argv[4];
        if (_ver == "v" || _ver == "verbose")
            verbose = true;
    }

    std::string dir_species[MAXSPECIES + 1];
    struct world_t world;

    read_summary(dir_species, argv[1]);
    species_t *species = all_species(dir_species);

    initialize_world(world, argv[2], species);

    take_round(world, round, verbose);
    

    //work part
}