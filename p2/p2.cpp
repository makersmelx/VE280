// #include "pch.h"
#include <iostream>
#include "p2.h"
using namespace std;

int size(list_t list)
{
	return (list_isEmpty(list)) ? 0 : (1 + size(list_rest(list)));
}

bool memberOf(list_t list, int val)
{
	return !list_isEmpty(list) && ((list_first(list) == val) || memberOf(list_rest(list), val));
}

int dot(list_t v1, list_t v2)
{
	return (list_isEmpty(v1) && list_isEmpty(v2))?0 : (list_first(v1) * list_first(v2) + dot(list_rest(v1), list_rest(v2)));
}

bool isIncreasing(list_t v)
{
	return size(v) <= 1 || (list_first(v) < list_first(list_rest(v)) && isIncreasing(list_rest(v)));
}

static list_t reverse_helper(list_t list, list_t res)
{
	return (size(list) == 0)? res : reverse_helper(list_rest(list),list_make(list_first(list), res));
}

list_t reverse(list_t list)
{
	return reverse_helper(list, list_make());
}

static list_t append_helper(list_t first, list_t second)
{
	return (list_isEmpty(first)) ? second : append_helper(list_rest(first), list_make(list_first(first), second));
}

list_t append(list_t first, list_t second)
{
	return append_helper(reverse(first), second);
}

static int arith_helper(list_t v)//ensure that has at least two elems
{
	return list_first(list_rest(v)) - list_first(v);
}

bool isArithmeticSequence(list_t v)
{
	return size(v) <= 2 || (arith_helper(v) == arith_helper(list_rest(v)) && isArithmeticSequence(list_rest(v)));
}

static list_t filter_odd_helper(list_t list, list_t res)
{
	return (list_isEmpty(list)) ? res : filter_odd_helper(list_rest(list), ((list_first(list) % 2 == 1) ? list_make(list_first(list), res) : res));
}


list_t filter_odd(list_t list)
{
	return filter_odd_helper(list, list_make());
}


static list_t filter_helper(list_t list, list_t res, bool(*fn)(int))
{
	return (list_isEmpty(list)) ? res : filter_helper(list_rest(list),( fn(list_first(list)) ? list_make(list_first(list), res) : res) , fn);
}

list_t filter(list_t list, bool(*fn)(int))
{
	return filter_helper(list, list_make(),fn);
}

static list_t unique_helper(list_t list, list_t res)
{
	return list_isEmpty(list) ? res: unique_helper(list_rest(list),memberOf(res,list_first(list))? res : list_make(list_first(list),res) );
}

list_t unique(list_t list)
{
	return unique_helper(list, list_make());
}

static list_t first_front(list_t first , list_t res,unsigned int n)
{
	return (n == 0) ? res : first_front(list_rest(first), list_make(list_first(first), res), n - 1);
}

static list_t get_back(list_t first, unsigned int n)
{
	return (n == 1) ? list_rest(first) : get_back(list_rest(first), n - 1);
}

list_t insert_list(list_t first, list_t second, unsigned int n)
{
	if (n < 0 || n > size(first))
		return list_make();
	return append(first_front(first, list_make(), n), append(second, get_back(first, n)));
}

static list_t chop_helper(list_t first, list_t res, unsigned int n)
{
	return (n == 0) ? res : chop_helper(list_rest(first), list_make(list_first(first), res), n - 1);
}

list_t chop(list_t list, unsigned int n)
{
	return (n > 0) ? chop_helper(list, list_make(), size(list) - n) : list;
}

//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************
static int maxium(int a, int b)
{
	return a > b ? a : b;
}

static int minium(int a, int b)
{
	return a < b ? a : b;
}

static int tree_sum_helper(tree_t tree, int sum)
{
	if (tree_isEmpty(tree))
		return sum;
	else
	{
		sum += tree_sum_helper(tree_left(tree), sum) + tree_elt(tree) + tree_sum_helper(tree_right(tree), sum);
		return sum;
	}
}

int tree_sum(tree_t tree)
{
	return (tree_isEmpty(tree)) ? 0 : tree_sum_helper(tree, 0);
}

bool tree_search(tree_t tree, int key)
{
	return (tree_isEmpty(tree)) ? false : (tree_elt(tree) == key || tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key));
}

int depth(tree_t tree)
{
	return (tree_isEmpty(tree)) ? 0 : maxium(depth(tree_left(tree)), depth(tree_right(tree))) + 1;
}

static int max_helper(tree_t tree, int max)
{
	return (tree_isEmpty(tree)) ? max : maxium(maxium(max_helper(tree_left(tree), max), max_helper(tree_right(tree), max)), tree_elt(tree));
}

int tree_max(tree_t tree)
{	
	return (tree_isEmpty(tree)) ? INT_MAX : max_helper(tree, tree_elt(tree));
}

static void traversal_helper(tree_t tree, list_t &res) // make to list_t return
{
	if (tree_isEmpty(tree))
		return;
	else
	{
		traversal_helper(tree_right(tree), res);
		res = list_make(tree_elt(tree), res);
		traversal_helper(tree_left(tree), res);
	}
}

list_t traversal(tree_t tree)
{
	list_t res = list_make();
	traversal_helper(tree, res);
	return res;
}

static bool mono_helper(tree_t tree, int mode,int cur,int depth)//1 for increase , 0 for decrease
{
	if(tree_isEmpty(tree))
		return (depth == cur) ? true : false;
	int mode_l = mode, mode_r = mode;
	int l = (!tree_isEmpty(tree_left(tree)) && tree_elt(tree_left(tree)) > tree_elt(tree));
	int r = (!tree_isEmpty(tree_left(tree)) && tree_elt(tree_left(tree)) > tree_elt(tree));
	if(mode == -1)
	{
		mode_l = l;
		mode_r = r;
	}
	return ((mode == l) && mono_helper(tree_left(tree), mode_l, cur + 1, depth)) || ((mode == r) && mono_helper(tree_right(tree), mode_r, cur + 1, depth));
}

bool tree_hasMonotonicPath(tree_t tree)
{
	return tree_isEmpty(tree) ? false : mono_helper(tree, -1 ,0,depth(tree));
}

static bool tree_allPathSumGreater_helper(tree_t tree, int sum, int path)
{
	if (tree_isEmpty(tree))
		return (sum > path) ? true : false;
	else
		return tree_allPathSumGreater_helper(tree_left(tree), sum, path + tree_elt(tree)) && tree_allPathSumGreater_helper(tree_right(tree), sum, path + tree_elt(tree));
}


bool tree_allPathSumGreater(tree_t tree, int sum)
{
	return (tree_isEmpty(tree)) ? false : tree_allPathSumGreater_helper(tree, sum, 0);
}
		
bool covered_by(tree_t A, tree_t B)
{
	if (tree_isEmpty(A))
		return tree_isEmpty(B);
	else if (tree_isEmpty(B))
		return false;
	return tree_elt(A) == tree_elt(B) && covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B));
}

static bool subtree(tree_t A, tree_t B,bool flag)
{
	if (tree_isEmpty(B))
		return false;
	if (flag)
		return (tree_elt(A) == tree_elt(B)) ? subtree(tree_left(A), tree_left(B), flag) && subtree(tree_right(A), tree_right(B), flag) : false;
	else
	{
		if (tree_elt(A) == tree_elt(B))
			flag = true;
		return subtree(A, tree_left(B), flag) || subtree(A, tree_right(B), flag);
	}	
}

bool contained_by(tree_t A, tree_t B)
{
	return (covered_by(A, B)) || subtree(A, B,false);
}

tree_t insert_tree(int elt, tree_t tree)
{
	if (tree_isEmpty(tree))
		return tree_make(elt, tree_make(), tree_make());
	else
		return tree_make(tree_elt(tree),tree_elt(tree) < elt ? tree_left(tree) : insert_tree(elt,tree_left(tree))  ,  tree_elt(tree) < elt ?  insert_tree(elt,tree_right(tree)) : tree_right(tree));  
}
