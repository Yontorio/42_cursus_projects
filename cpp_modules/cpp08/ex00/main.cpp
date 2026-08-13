#include <iostream>
#include <vector>
#include <list>
#include <deque>

#include "easyfind.hpp"

int main()
{
	std::vector<int> vec;
	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 3);
		std::cout << "Found in vector: " << *it << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	//////////////////////////////
	std::deque<int> deq;
	for (int i = 0; i < 50; i++)
		deq.push_back(i);
	try
	{
		std::deque<int>::const_iterator it = easyfind(deq, 99);
		std::cout << "Found in deque: " << *it << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	//////////////////////////////
	std::list<int> lst;
	for (int i = 0; i < 100; i++)
		lst.push_back(i);
	try
	{
		std::list<int>::const_iterator it = easyfind(lst, 99);
		std::cout << "Found in list: " << *it << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
