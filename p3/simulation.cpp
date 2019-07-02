#include "simulation.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
//#include "pch.h"
using namespace std;

worldError::worldError(int type, int val)
{
	errType = type;
	errVal[0] = val;
}

worldError::worldError(int type, string msg)
{
	errType = type;
	errMsg[0] = msg;
}

worldError::worldError(int type, string *msg, int strLen)
{
	errType = type;
	int i = 0;
	while (i < strLen)
	{
		errMsg[i] = msg[i];
		i++;
	}
}

worldError::worldError(int type, int *val, int valLen, string *msg, int strLen)
{
	errType = type;
	int i = 0;
	while (i < strLen)
	{
		errMsg[i] = msg[i];
		i++;
	}
	i = 0;
	while (i < valLen)
	{
		errVal[i] = val[i];
		i++;
	}
}

worldError::worldError(int type, int len, creature_t **cr)
{
	errType = type;
	for (int i = 0; i < len; i++)
	{
		errCr[i] = cr[i];
	}
}

void worldError::printError()
{
	switch (errType)
	{
	case 1:
	{
		cout << "Error: Missing arguments!" << endl;
		cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
		break;
	}
	case 2:
	{
		std::cout << "Error: Number of simulation rounds is negative!" << endl;
		break;
	}
	case 3:
	{
		cout << "Error: Cannot open file " << errMsg[0] << "!" << endl;
		break;
	}
	case -3: // dir/file situation
	{
		cout << "Error: Cannot open file " << errMsg[0]
			 << "/" << errMsg[1] << "!" << endl;
		break;
	}
	case 4:
	{
		cout << "Error: Too many species!" << endl;
		cout << "Maximal number of species is " << MAXSPECIES << "." << endl;
		break;
	}
	case 5:
	{
		cout << "Error: Too many instructions for species "
			 << errMsg[0] << "!" << endl;
		cout << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
		break;
	}
	case 6:
	{
		cout << "Error: Instruction " << errMsg[0] << " is not recognized!" << endl;
		break;
	}
	case 7:
	{
		cout << "Error: Too many creatures!" << endl;
		cout << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
		break;
	}
	case 8:
	{
		cout << "Error: Species " << errMsg[0] << " not found!" << endl;
		break;
	}
	case 9:
	{
		cout << "Error: Direction"
			 << " " << errMsg[0] << " is not recognized!" << endl;
		break;
	}
	case 10:
	{
		cout << "Error: The grid height is illegal!" << endl;
		break;
	}
	case 11:
	{
		cout << "Error: The grid width is illegal!" << endl;
		break;
	}
	case 12:
	{
		cout << "Error: Creature (" << errMsg[0] << " " << errMsg[1] << " " << errMsg[2] << " " << errMsg[3] << ") ";
		cout << "is out of bound!" << endl;
		cout << "The grid size is " << errVal[0] << "-by-" << errVal[1] << "." << endl;
		break;
	}
	case 13:
	{
		cout << "Error: Creature (" << errCr[0]->species->name << " " << directName[errCr[0]->direction] << " " << errCr[0]->location.r << " " << errCr[0]->location.c << ") ";
		cout << "overlaps with ";
		cout << "creature (" << errCr[1]->species->name << " " << directName[errCr[1]->direction] << " " << errCr[1]->location.r << " " << errCr[1]->location.c << ")!" << endl;
		break;
	}
	default:
		break;
	}
	exit(0);
}

void split(string &str,
		   string *res, const string &pattern)
{
	string::size_type pos;
	str += pattern;
	int size = str.size();
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (int(pos) < size)
		{
			if (i != int(pos))
			{
				string s = str.substr(i, pos - i);
				res[index] = s;
				index++;
			}
			i = pos + pattern.size() - 1;
		}
	}
}

unsigned int initialize_creature(world_t &world, ifstream &file, species_t *speciesList, const int &sp_nums)
{
	unsigned int creature_num = 0;
	creature_t *c = world.creatures;
	int h = world.grid.height;
	int w = world.grid.width;
	string creature_tmp;
	string argv[50];
	string pattern = " ";
	while (getline(file, creature_tmp))
	{
		if (creature_tmp.empty())
			break;
		if (creature_num >= MAXCREATURES)
		{
			file.close();
			throw worldError(7, 0);
		}

		split(creature_tmp, argv, pattern);
		//define the species of the current creature
		int index = 0;
		bool flag = false;
		while (index < sp_nums)
		{
			if (speciesList[index].name == argv[0])
			{
				c[creature_num].species = speciesList + index;
				flag = true;
				break;
			}
			index++;
		}
		if (!flag)
		{
			file.close();
			throw worldError(8, argv[0]);
		}
		//direction setting
		for (int i = 0; i < 4; i++)
		{
			if (directName[i] == argv[1])
			{
				c[creature_num].direction = (enum direction_t)i;
				break;
			}
			if (i == 3)
			{
				file.close();
				throw worldError(9, argv[1]);
			}
		}
		//location setting
		c[creature_num].location.r = stoi(argv[2]);
		c[creature_num].location.c = stoi(argv[3]);
		if (c[creature_num].location.r > h - 1 || c[creature_num].location.c > w - 1)
		{
			string err[4] = {argv[0], argv[1], argv[2], argv[3]};
			int erri[2] = {h, w};
			file.close();
			throw worldError(12, erri, 2, err, 4);
		}
		for (unsigned int i = 0; i < creature_num; i++)
		{
			if (c[i].location.r == c[creature_num].location.r && c[i].location.c == c[creature_num].location.c)
			{
				creature_t *err[2] = {c + creature_num, c + i};
				file.close();
				throw worldError(13, 2, err);
			}
		}
		c[creature_num].programID = 0;
		world.grid.squares[c[creature_num].location.r][c[creature_num].location.c] = &c[creature_num];
		creature_num++;
	}

	return creature_num;
}

void initialize_grid(grid_t &g, ifstream &file)
{
	string tmp;
	getline(file, tmp);
	g.height = stoi(tmp);
	if (g.height > MAXHEIGHT || g.height < 1)
	{
		file.close();
		throw worldError(10, 0);
	}
	getline(file, tmp);
	g.width = stoi(tmp);
	if (g.width > MAXWIDTH || g.width < 1)
	{
		file.close();
		throw worldError(11, 0);
	}

	for (unsigned int i = 0; i < g.height; i++)
		for (unsigned int j = 0; j < g.width; j++)
			g.squares[i][j] = NULL;
}

void initialize_species(world_t &w)
{
	w.numSpecies = 0;
	for (unsigned int i = 0; i < w.numCreatures; i++)
	{
		if (i == 0)
		{
			w.species[0] = *(w.creatures[0].species);
			w.numSpecies++;
		}
		else
		{
			for (unsigned int j = 0; j < i; j++)
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
	if (w.numSpecies > MAXSPECIES)
	{
		throw worldError(4, 0);
	}
}

void initialize_world(world_t &w, char *filename, species_t *species, const int &sp_nums)
{
	//*****************************
	ifstream file(filename);
	if (!file.is_open())
	{
		throw worldError(3, filename);
	}
	initialize_grid((w.grid), file);
	w.numCreatures = initialize_creature(w, file, species, sp_nums);
	initialize_species(w);
	file.close();
}

int read_file_species(string *list, const string filename)
{
	ifstream file(filename);
	if (file.is_open())
	{
		int i = 0;
		string sp_tmp;
		while (getline(file, sp_tmp))
		{
			if (sp_tmp.empty())
				break;
			if (i > int(MAXSPECIES))
			{
				file.close();
				throw worldError(4, 0);
			}
			list[i] = sp_tmp;
			i++;
		}
		file.close();
		return i - 1;
	}
	else
	{
		throw worldError(3, filename);
	}
}

string *read_raw_instruction(const string dir, const string name)
{
	string *res = new string[MAXPROGRAM];
	string path = "./" + dir + "/" + name;
	ifstream file(path);
	int itr = 0;
	if (file.is_open())
	{
		string ins_tmp;
		while (getline(file, ins_tmp)) //IGNORE COMMENTS BELOW
		{
			if (ins_tmp.empty())
			{
				break;
			}
			if (itr >= int(MAXPROGRAM))
			{
				file.close();
				throw worldError(5, name);
			}
			res[itr] = ins_tmp;
			itr++;
		}
		file.close();
	}
	else
	{
		string err[2] = {dir, name};
		file.close();
		throw worldError(-3, err, 2);
	}
	return res;
}

struct instruction_t readable_instruct(const string raw)
{
	struct instruction_t res;
	istringstream is;
	is.str(raw);
	string op;
	is >> op;
	if (op.compare("infect") == 0 ||
		op.compare("hop") == 0 ||
		op.compare("right") == 0 ||
		op.compare("left") == 0)
		res.address = 0;
	else
		is >> res.address;

	for (int i = 0; i < 9; i++)
	{
		if (opName[i] == op)
		{
			res.op = (enum opcode_t)i;
			break;
		}
		if (i == 8)
		{
			throw worldError(6, op);
		}
	}
	return res;
}

struct species_t *all_species(string *sp_list, const int &sp_nums)
{
	species_t *s = new species_t[MAXSPECIES];
	int current_sp = 0;
	while (current_sp + 1 <= sp_nums)
	{
		s[current_sp].name = sp_list[current_sp + 1];
		string *res = read_raw_instruction(sp_list[0], sp_list[current_sp + 1]);
		int i = 0; //instruction iterator
		while (!res[i].empty())
		{
			s[current_sp].program[i] = readable_instruct(res[i]);
			i++;
		}
		s[current_sp].programSize = i;
		current_sp++;
	}
	return s;
}

point_t forward(point_t &loc, direction_t &d)
{
	return {loc.r - (d % 2) * (d - 2), loc.c + (d % 2 - 1) * (d - 1)};
}

bool out_of_boudary(point_t &loc, grid_t &g)
{
	return (loc.r > int(g.height - 1) || loc.r < 0 || loc.c < 0 || loc.c > int(g.width - 1)) ? true : false;
}

bool hop_helper(grid_t &g, point_t &loc, creature_t &c) //true means can do
{
	return (out_of_boudary(loc, g) || (g.squares[loc.r][loc.c] != NULL)) ? false : true;
}

void hop(creature_t &c, grid_t &g)
{
	point_t tmp_0 = forward(c.location, c.direction);
	if (hop_helper(g, tmp_0, c))
	{
		g.squares[c.location.r][c.location.c] = NULL;
		c.location.r = tmp_0.r;
		c.location.c = tmp_0.c;
		g.squares[c.location.r][c.location.c] = &c;
	}
}

void left(creature_t &c)
{
	int i = c.direction;
	if (i > 0)
		c.direction = (enum direction_t)(i - 1);
	else
		c.direction = (enum direction_t)3;
}

void right(creature_t &c)
{
	int i = c.direction;
	if (i < 3)
		c.direction = (enum direction_t)(i + 1);
	else
		c.direction = (enum direction_t)0;
}

void infect(creature_t &c, point_t &loc, grid_t &g)
{
	if (out_of_boudary(loc, g) || g.squares[loc.r][loc.c] == NULL || g.squares[loc.r][loc.c]->species->name == c.species->name)
		return;
	else
	{
		g.squares[loc.r][loc.c]->species = c.species;
		g.squares[loc.r][loc.c]->programID = 0;
	}
}

void action(creature_t &c, instruction_t *ins, grid_t &g, int count, bool v)
//count starts from 0  count means the now stream
{
	//verbose console part
	if (v)
	{
		cout << "Instruction " << count + 1 << ": " << opName[ins[count].op];
		if (ins[count].address != 0)
			cout << " " << ins[count].address;
		cout << endl;
	}
	switch (ins[count].op)
	{
	case 0:
	{
		hop(c, g);
		break;
	}

	case 1:
	{
		left(c);
		break;
	}

	case 2:
	{
		right(c);
		break;
	}

	case 3:
	{
		point_t tmp_3 = forward(c.location, c.direction);
		infect(c, tmp_3, g);
		break;
	}

	case 4:
	{
		point_t tmp_4 = forward(c.location, c.direction);
		if (!out_of_boudary(tmp_4, g) && g.squares[tmp_4.r][tmp_4.c] == NULL)
		{
			action(c, ins, g, ins[count].address - 1, v);
		}
		else
		{
			action(c, ins, g, count + 1, v);
		}
		return;
	}

	case 5:
	{
		point_t tmp_5 = forward(c.location, c.direction);
		if (!out_of_boudary(tmp_5, g) && g.squares[tmp_5.r][tmp_5.c] != NULL && g.squares[tmp_5.r][tmp_5.c]->species->name != c.species->name)
		{
			action(c, ins, g, ins[count].address - 1, v);
		}
		else
		{
			action(c, ins, g, count + 1, v);
		}
		return;
	}

	case 6:
	{
		point_t tmp_6 = forward(c.location, c.direction);
		if (!out_of_boudary(tmp_6, g) && g.squares[tmp_6.r][tmp_6.c] != NULL && g.squares[tmp_6.r][tmp_6.c]->species->name == c.species->name)
		{
			action(c, ins, g, ins[count].address - 1, v);
		}
		else
		{
			action(c, ins, g, count + 1, v);
		}
		return;
	}

	case 7:
	{
		point_t tmp_7 = forward(c.location, c.direction);
		if (out_of_boudary(tmp_7, g))
		{
			action(c, ins, g, ins[count].address - 1, v);
		}
		else
		{
			action(c, ins, g, count + 1, v);
		}
		return;
	}

	case 8:
		action(c, ins, g, ins[count].address - 1, v);
		return;

	default:
		break;
	}

	if (!v)
		cout << " " << opName[ins[count].op] << endl;
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
	for (unsigned int i = 0; i < w.grid.height; i++)
	{
		for (unsigned int j = 0; j < w.grid.width; j++)
		{
			if (w.grid.squares[i][j] == NULL)
				cout << "____"
					 << " ";
			else
				cout << w.grid.squares[i][j]->species->name.substr(0, 2) << "_" << directName[w.grid.squares[i][j]->direction].substr(0, 1) << " ";
		}
		cout << endl;
	}
}

void take_round(world_t &w, int roundLeft, bool verb)
{
	int max = roundLeft;
	print_round(max - roundLeft);
	print_world(w);
	while (roundLeft > 0)
	{
		print_round(max - roundLeft + 1);
		for (unsigned int i = 0; i < w.numCreatures; i++)
		{
			creature_t &target = w.creatures[i];
			cout << "Creature "
				 << "(" << target.species->name << " " << directName[target.direction] << " " << target.location.r << " " << target.location.c << ")"
				 << " takes action:";
			if (verb)
				cout << endl;
			action(target, target.species->program, w.grid, target.programID, verb);
			if (verb)
				print_world(w);
		}
		roundLeft--;
		if (!verb)
			print_world(w);
	}
}
