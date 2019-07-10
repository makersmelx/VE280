#include "simulation.h"
#include "world_type.h"
#include <iostream>
#include <string>
int main(int argc, char **argv)
{
    try
    {
        if (argc < 4)
        {
            throw worldError(1, 0);
        }

        string _round = argv[3];
        int round = stoi(_round);
        if (round < 0)
        {
            throw worldError(2, 0);
        }
        //Determine verbose mode
        bool verbose = false;
        if (argc == 5)
        {
            string _ver = argv[4];
            if (_ver == "v" || _ver == "verbose")
                verbose = true;
        }

        std::string dir_species[MAXSPECIES + 1];
        struct world_t world;
        //inintialize list of species
        int sp_nums = read_file_species(dir_species, argv[1]);
        species_t *species = all_species(dir_species, sp_nums);
        //create the world
        initialize_world(world, argv[2], species, sp_nums);
        //run simulation
        take_round(world, round, verbose);
    }
    //Exception handle
    catch (worldError &e)
    {
        e.printError();
    }
}