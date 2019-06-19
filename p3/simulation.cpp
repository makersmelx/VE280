#include "simulation.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<cassert>
#include<stdio.h>
//#include "pch.h"
using namespace std;

static void split(string & str, 
	string * res, string & pattern)
{
	string::size_type pos;
	str += pattern;
	int size = str.size();
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		pos=str.find(pattern, i);
		if (pos < size)
		{
			if (i != pos)
			{
				string s = str.substr(i, pos-i);
				res[index] = s;
				index++;
			}
			i = pos + pattern.size()-1;
		}
	}
}

static terrain_t terr_dict(char t)
{
	switch (t)
	{
	case 'P':
		return PLAIN;
	case 'L':
		return LAKE;
	case 'F':
		return FOREST;
	case 'H':
		return HILL;
	default:
		return TERRAIN_SIZE;
	}
}

// //Not debugged
static unsigned int initialize_creature(world_t &world, ifstream &file, species_t *speciesList)//Error 3, Error 13, Error 14
{
	unsigned int itr = 0;
	if (!file.is_open())
	{
		cout << "File not open!" << endl;
		assert(0);
	}
	else
	{
		creature_t *c = world.creatures;
		int h = world.grid.height;
		int w = world.grid.width;
		string tmp;
		string argus[50];
		string pattern = " ";
		while (file)
		{
			getline(file, tmp);
			if (tmp.empty())
				break;
			split(tmp, argus, pattern);

			int index = 0;
			bool flag = false;
			while (!speciesList[index].name.empty())
			{
				if (speciesList[index].name == argus[0])
				{
					c[itr].species = speciesList + index;
					flag = true;
					break;
				}
				index++;
			}
			if (!flag)
			{
				cout << "Error: Species " << argus[0] << " not found!" << endl;
				assert(0);
			}
			for (int i = 0; i < 4;i++)
			{
				if (directName[i] == argus[1])
				{
					c[itr].direction = (enum direction_t)i;
					break;
				}
				if (i == 3)
				{
					cout << "Error: Direction" << " " << argus[1] << " is not recognized!" << endl;
					assert(0);
				}
			}
			c[itr].location.r = stoi(argus[2]);
			c[itr].location.c = stoi(argus[3]);
			if (c[itr].location.r > h - 1 ||c[itr].location.c > w - 1  )
			{
				cout << "Error: Creature (" << argus[0] << " "<< argus[1] << " "<< argus[2] << " "<< argus[3] << ") ";
				cout << "is out of bound!" << endl;
				cout << "The grid size is " << h << "-" << w << "." << endl;
				assert(0);
			}
			//needs rewrite as is dynamic
			for (int i = 0; i < itr; i++)
			{
				if (c[i].location.r == c[itr].location.r && c[i].location.c == c[itr].location.c)
				{
					cout << "Error: Creature (" << c[i].species->name << " " << directName[c[i].direction] << " " << c[i].location.r << " " << c[i].location.c << ") ";
					cout << "overlaps with ";
					cout << "creature (" << c[itr].species->name << " " << directName[c[itr].direction] << " " << c[itr].location.r << " " << c[itr].location.c << ")!" << endl;
					assert(0);
				}
			}
			c[itr].ability[0] = false;
			c[itr].ability[1] = false;
			//
			if (!argus[4].empty())
			{
				for (int i = 0; i < 2; i++)
				{
					if (abilityName[i] == argus[4].substr(0,1))
					{
						c[itr].ability[i] = true;
						break;
					}
					if (i == 1)
					{
						cout << "Error: Creature (" << argus[0] << " " << argus[2] << " " << argus[3] << ") has an invalid ability " << argus[4] << "!" << endl;
						assert(0);
					}
				}
			}
			if (!argus[5].empty())
			{
				for (int i = 0; i < 2;i++)
				{
					if (abilityName[i]==argus[5].substr(0,1))
					{
						c[itr].ability[i] = true;
						break;
					}
					if (i == 1)
					{
						cout << "Error: Creature (" << argus[0] << " " << argus[2] << " " << argus[3] << ") has an invalid ability " << argus[5] << "!" << endl;
						assert(0);
					}	
				}	
			}
			c[itr].hillActive = true;
			c[itr].programID = 0;
			world.grid.squares[c[itr].location.r][c[itr].location.c] = &c[itr];
			itr++;
		}
	}
	return itr;
}

static void initialize_grid(grid_t &g, ifstream &file) // ok on base that file is valid
{
	string tmp;
	getline(file, tmp);
	g.height = stoi(tmp);
	if (g.height > MAXHEIGHT)
	{
		cout << "Error: The grid height is illegal!" << endl;
		assert(0);
	}
	getline(file, tmp);
	g.width = stoi(tmp);
	if (g.width > MAXWIDTH)
	{
		cout << "Error: The grid width is illegal!" << endl;
		assert(0);
	}

	for (int h = 0; h < g.height; h++)
	{
		getline(file, tmp);
		for (int wi = 0; wi < g.width; wi++)
			if (terr_dict(tmp[wi]) != 4)
				g.terrain[h][wi] = terr_dict(tmp[wi]);
			else
			{
				cout << "Error: Terrain square (" << tmp[wi] << " " << h << " " << wi << ") is invalid!" << endl;
				assert(0);
			}
	}

	for (int i = 0; i < g.height; i++)
		for (int j = 0; j < g.width;j++)
			g.squares[i][j] = NULL;
}

static void initialize_species(world_t &w)
{
	w.numSpecies = 0;
	for (int i = 0; i < w.numCreatures; i++)
	{
		if (i == 0)
		{
			w.species[0] = *(w.creatures[0].species);
			w.numSpecies++;
		}

		else
		{
			for (int j = 0; j < i; j++)
			{
				if (w.creatures[i].species->name == w.creatures[j].species->name)
					break;
				if (j == i - 1)
				{
					w.species[w.numSpecies] = *(w.creatures[i].species);
					w.numSpecies++;
				}
			}
		}
	}
}

void initialize_world(world_t &w,char *filename,species_t *species)//Error 3 ,Error 7, Error 8, Error 9
{
	//*****************************
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Error: Cannot open file " << filename  << endl;
		assert(0);
	}
	initialize_grid((w.grid), file);
	w.numCreatures = initialize_creature(w ,file, species);
	initialize_species(w);
	file.close();
}

void read_summary(string *list,string filename)//Error 3
{
	ifstream file(filename);
	if (file.is_open())
	{
		int i = 0;
		while (file)
		{
			getline(file, list[i]);
			i++;
		}
		file.close();
	}
	else
	{
		cout << "Error: Cannot open file "<<filename<< endl;
		assert(0);
	}	
}


// 0 should change to read all instrcutions //should return string arrays, each item for one line //line numbers needed
static string *read_raw_instruction(string dir, string name)//including Error 3
{
	string *res = new string[MAXPROGRAM];
	string path = "./" + dir + "/" + name;
	ifstream file(path);
	int itr = 0;
	if (file.is_open())
	{
		while (file)//the down content may not be ignored, needed debugged
		{
			getline(file, res[itr]);
			itr++;
		}
		file.close();
	}
	else
	{
		cout << "Error: Cannot open file "<< dir << "/" << name <<"." <<endl;
		assert(0);
	}
	return res;		
}

static struct instruction_t readable_instruct(string raw)//Error 6
{
	struct instruction_t res;
	istringstream is;
	is.str(raw);
	string op;
	is >> op ;
	if (op.compare("infect") == 0 || 
				op.compare("hop") == 0    || 
				op.compare("right") == 0  ||
				op.compare("left") == 0    )
		res.address = 0;
	else
		is >> res.address;
	
	for (int i = 0; i < 9; i++)
	{
		if (opName[i] == op)
		{
			res.op = (enum opcode_t) i;
			break;
		}	
		if (i == 8)
		{
			cout << "Error: Instruction " + op + " is not recognized." << endl;
			assert(0);
		}
	}	
	return res;
}

//1 read all presetted instructions (done
struct species_t *all_species(string* sp_list)
{
	species_t *s = new species_t[MAXSPECIES];
	int index = 0;
	while(!sp_list[index+1].empty())
	{
		s[index].name = sp_list[index+1];
		string *res = read_raw_instruction(sp_list[0], sp_list[index+1]);
		int i = 0;
		while (!res[i].empty())
		{
			s[index].program[i] = readable_instruct(res[i]);
			i++;
		}
		s[index].programSize = i;
		index++;
	} 
	return s;
}

point_t forward(point_t &loc , direction_t &d)
{
	return {loc.r - (d % 2) * (d - 2), loc.c + (d % 2 - 1) * (d - 1)};
}

bool out_of_boudary(point_t &loc,grid_t &g)
{
	return (loc.r > (g.height - 1) ||loc.r < 0 || loc.c < 0 || loc.c > (g.width - 1)) ? true : false;	
}


bool hop_helper(grid_t &g, point_t &loc, creature_t &c)//true means can do
{
	return (out_of_boudary(loc, g) 
			|| ((g.terrain[loc.r][loc.c] == 1) && !c.ability[0])
			|| (g.squares[loc.r][loc.c] != NULL)) ? 
	false : true;
}

bool ifwall_helper(grid_t &g, point_t &loc , creature_t &c)//true means is a wall
{
	return (out_of_boudary(loc, g) 
			|| ((g.terrain[loc.r][loc.c] == 1) && !c.ability[0])) ? 
	true : false;
}

void infect(creature_t &c, point_t &loc , grid_t &g)
{
	if (out_of_boudary(loc,g)
			|| (g.terrain[loc.r][loc.c] == 2 && !c.ability[1])
			|| g.squares[loc.r][loc.c] == NULL
			|| g.squares[loc.r][loc.c] -> species -> name == c.species->name)
		return;
	else
	{
		g.squares[loc.r][loc.c]->species = c.species;
		g.squares[loc.r][loc.c]->programID = 0;
	}
		
}

void action(creature_t &c , instruction_t *ins,grid_t &g,int count,bool v)
//count starts from 0  count means the now stream
//return the next instruction to do
{
	if (c.hillActive 
		&& g.terrain[c.location.r][c.location.c] == 3)
	{
		c.hillActive = false;
		return;
	}
	if(v)
	{
		cout << "Instruction " << count + 1 << ": " << opName[ins[count].op];
		if (ins[count].address != 0)
			cout << " " << ins[count].address;
		cout << endl;
	}
	
	if(!c.hillActive)
		c.hillActive = true;

	if (ins[count].op == 8)
	{
		action(c, ins, g,ins[count].address-1,v);
		return;
	}
	else if (ins[count].op == 4)
	{
		point_t tmp_4 = forward(c.location, c.direction);
		if (!out_of_boudary(tmp_4,g) 
				&& g.squares[tmp_4.r][tmp_4.c] == NULL)
		{
			action(c, ins, g,ins[count].address-1,v);
			return;
		}
		else
		{
			action(c, ins, g,count+1,v);
			return;
		}	
	}
	else if (ins[count].op == 5)
	{
		point_t tmp_5 = forward(c.location, c.direction);
		if (!out_of_boudary(tmp_5,g)
				&&(c.ability[1] || g.terrain[tmp_5.r][tmp_5.c] != 2)
				&& g.squares[tmp_5.r][tmp_5.c] != NULL
				&& g.squares[tmp_5.r][tmp_5.c]->species->name != c.species->name)
		{
			action(c, ins, g,ins[count].address-1,v);
			return;
		}
		else
		{
			action(c, ins, g,count+1,v);
			return;
		}	
	}
	else if (ins[count].op == 6)
	{
		point_t tmp_6 = forward(c.location, c.direction);
		if (!out_of_boudary(tmp_6,g)
				&& g.squares[tmp_6.r][tmp_6.c] != NULL
				&& g.terrain[tmp_6.r][tmp_6.c] != 2 
				&& g.squares[tmp_6.r][tmp_6.c]->species->name == c.species->name)
		{
			action(c, ins, g,ins[count].address-1,v);
			return;
		}
		else
		{
			action(c, ins, g,count+1,v);
			return;
		}	
	}
	else if (ins[count].op == 7)
	{
		point_t tmp_7 = forward(c.location, c.direction);
		if (ifwall_helper(g,tmp_7,c))
		{
			action(c, ins, g,ins[count].address-1,v);
			return;
		}
		else
		{
			action(c, ins, g,count+1,v);
			return;
		}		
	}
	else if (ins[count].op == 0)
	{
		point_t tmp_0 = forward(c.location, c.direction);
		if(hop_helper(g,tmp_0,c))
		{
			g.squares[c.location.r][c.location.c] = NULL;
			c.location.r = tmp_0.r;
			c.location.c  = tmp_0.c;
			g.squares[c.location.r][c.location.c] = &c;
		}
	}
	else if (ins[count].op == 1 )
	{
		int i = c.direction;
		if (i > 0)
			c.direction = (enum direction_t)(i - 1);
		else
			c.direction = (enum direction_t) 3;
	}
	else if (ins[count].op == 2 )
	{	
		int i = c.direction;
		if (i < 3)
			c.direction = (enum direction_t)(i + 1);
		else
			c.direction = (enum direction_t) 0;
	}
	else if (ins[count].op == 3 )//infect
	{
		point_t tmp_3 = forward(c.location, c.direction);
		if (c.ability[1])
		{
			while (out_of_boudary(tmp_3,g))
			{
				infect(c, tmp_3, g);
				tmp_3 = forward(tmp_3, c.direction);
			}
		}
		else
		{
			infect(c, tmp_3, g); //bookmark
		}
	}
	if(!v)
		cout << " "<< opName[ins[count].op] << endl;
	c.programID = count + 1;
}

void print_round(int round)
{
	if (round == 0)
		cout << "Initial state" << endl;
	else
		cout << "Round " << round << endl;
}

void print_world(world_t &w)
{
	for (int i = 0;  i < w.grid.height;i++)
	{
		for (int j = 0; j < w.grid.width; j++)
		{
			if (w.grid.squares[i][j] == NULL)
				cout << "____" << " ";
			else
				cout << w.grid.squares[i][j]->species->name.substr(0, 2) << "_" << directName[w.grid.squares[i][j]->direction].substr(0, 1) << " ";
		}
		cout << endl;
	}
}

void take_round(world_t &w,int roundLeft,bool verb)
//now strats from 1
{
	int max = roundLeft;
	print_round(max - roundLeft);
	print_world(w);
	while (roundLeft > 0)
	{
		print_round(max - roundLeft + 1);
		for (int i = 0; i < w.numCreatures;i++)
		{
			creature_t &target = w.creatures[i];
			cout << "Creature "<< "(" << target.species->name << " " << directName[target.direction] << " " << target.location.r << " " << target.location.c << ")" << " takes action:" ;
			if(verb)
				cout << endl;
			action(target, target.species->program,w.grid,target.programID,verb);
			if(verb)
				print_world(w);
		}
		roundLeft--;
		if (!verb)
			print_world(w);
	}
}
