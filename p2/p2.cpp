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
	return list_isEmpty(list)?false: ((list_first(list) == val) || memberOf(list_rest(list), val));
}

int dot(list_t v1, list_t v2)
{
	return (list_isEmpty(v1) || list_isEmpty(v2))?0 : (list_first(v1) * list_first(v2) + dot(list_rest(v1), list_rest(v2)));
}

bool isIncreasing(list_t v)
{
	return size(v) <= 1 || (list_first(v) <= list_first(list_rest(v)) && isIncreasing(list_rest(v)));
}

static list_t reverse_helper(list_t list, list_t res)
{
	return (list_isEmpty(list))? res : reverse_helper(list_rest(list),list_make(list_first(list), res));
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

list_t filter_odd(list_t list)
{
	return list_isEmpty(list)? list_make() : (list_first(list) % 2 == 1 ? list_make(list_first(list),filter_odd(list_rest(list))):filter_odd(list_rest(list)) );
}

list_t filter(list_t list, bool(*fn)(int))
{
	return list_isEmpty(list)?list_make() : (fn(list_first(list)) ? list_make(list_first(list),filter(list_rest(list),fn)):filter(list_rest(list),fn));
}

static list_t unique_helper(list_t list, list_t res)
{
	return list_isEmpty(list) ? res: unique_helper(list_rest(list),memberOf(res,list_first(list))? res : list_make(list_first(list),res) );
}

list_t unique(list_t list)
{
	return reverse(unique_helper(list, list_make()));
}

list_t insert_list(list_t first, list_t second, unsigned int n)
{
	return append(chop(first, size(first) - n), append(second, reverse(chop(reverse(first),n))));
}

list_t chop(list_t list, unsigned int n)
{
	return  n <= 0 ? list :reverse(list_rest(reverse(chop(list,n-1))));
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

// static int minium(int a, int b)
// {
// 	return a < b ? a : b;
// }


int tree_sum(tree_t tree)
{
	return (tree_isEmpty(tree)) ? 0 : (tree_sum(tree_left(tree)) + tree_elt(tree) + tree_sum(tree_right(tree)));
}

bool tree_search(tree_t tree, int key)
{
	return (tree_isEmpty(tree)) ? false : (tree_elt(tree) == key || tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key));
}

int depth(tree_t tree)
{
	return (tree_isEmpty(tree)) ? 0 : maxium(depth(tree_left(tree)), depth(tree_right(tree))) + 1;
}


int tree_max(tree_t tree)
{	
	return tree_isEmpty(tree)? INT32_MIN: maxium(maxium(tree_max(tree_left(tree)), tree_max(tree_right(tree))), tree_elt(tree));
}

list_t traversal(tree_t tree)
{
	return tree_isEmpty(tree) ? list_make() : append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
}

static bool mono_helper(tree_t tree, bool(*fn)(int,int))
{
	return (tree_isEmpty(tree_left(tree)) || (fn(tree_elt(tree), tree_elt(tree_left(tree))) && mono_helper(tree_left(tree), fn))) || (tree_isEmpty(tree_right(tree)) || (fn(tree_elt(tree), tree_elt(tree_right(tree))) && mono_helper(tree_right(tree), fn)));
}

bool tree_hasMonotonicPath(tree_t tree)
{
	return tree_isEmpty(tree) ? false : mono_helper(tree, [](int a, int b)->bool { return a >= b; }) || mono_helper(tree, [](int a, int b)-> bool { return a <= b; });
}

static bool tree_allPathSumGreater_helper(tree_t tree, int sum, int path)
{
	
	if (tree_isEmpty(tree))
		return (path > sum) ? true : false;
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
		return true;
	else if (tree_isEmpty(B))
		return false;
	return tree_elt(A) == tree_elt(B) && covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B));
}


bool contained_by(tree_t A, tree_t B)
{
	return covered_by(A, B) ||( !tree_isEmpty(B) && (covered_by(A, tree_left(B)) || (covered_by(A, tree_right(B)))));
}

tree_t insert_tree(int elt, tree_t tree)
{

	if (tree_isEmpty(tree))
		return tree_make(elt, tree_make(), tree_make());
	else
		return tree_make(tree_elt(tree),tree_elt(tree) < elt ? tree_left(tree) : insert_tree(elt,tree_left(tree))  ,  tree_elt(tree) < elt ?  insert_tree(elt,tree_right(tree)) : tree_right(tree));  
}
