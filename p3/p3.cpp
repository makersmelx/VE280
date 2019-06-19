#include "simulation.h"
#include "world_type.h"
#include <cassert>
#include <iostream>
#include <string>
int main(int argc, char **argv)
{
    if (argc < 4) //Error 1
    {
        std::cout << "Error: Missiong arguments!" << endl;
        std::cout << "Usage: ./p3 <specices-summary> <world-file> <rounds> [v|verbose]" << endl;
        assert(0);
    }
    if (atoi(argv[3]) < 0)
    {
        std::cout << "Error: Number of Simulation rounds is negative!" << endl;
        assert(0);
    }
    std::string dir_species[MAXSPECIES + 1];
    read_summary(dir_species, argv[1]);
    species_t *species = all_species(dir_species);

    struct world_t world;
    initialize_world(world, argv[2], species);

    int round = atoi(argv[3]);

    bool verbose = false;
    if (argc == 5)
        if (argv[4][0] == 'v')
            verbose = true;

    take_round(world, round,verbose);
    //work part
    //output part? do this with debug?
}