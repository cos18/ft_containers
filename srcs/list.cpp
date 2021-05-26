#include "list.hpp"
#include <list>

void list_basic_test(ft::list<int> &test, std::list<int> &std_list)
{
	std::cout << "========FT========\n";
	std::cout << "size: " << test.size() << std::endl;
	std::cout << "[value]" << std::endl;
	ft::list<int>::iterator ite = test.end();
	for (ft::list<int>::iterator it = test.begin(); it != ite; it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "========STD========\n";
	std::cout << "size: " << std_list.size() << std::endl;
	std::cout << "[value]" << std::endl;
	std::list<int>::iterator std_ite = std_list.end();
	for (std::list<int>::iterator std_it = std_list.begin(); std_it != std_ite; std_it++)
		std::cout << *std_it << " ";
	std::cout << std::endl << std::endl;

	test.push_front(1);
	test.push_back(3);
	test.insert(test.begin(), 100);
	test.insert(test.begin(), 3, 5);
	std_list.push_front(1);
	std_list.push_back(3);
	std_list.insert(std_list.begin(), 100);
	std_list.insert(std_list.begin(), 3, 5);

	std::cout << "========FT========\n";
	std::cout << "size: " << test.size() << std::endl;
	std::cout << "[rvalue]" << std::endl;
	ft::list<int>::const_reverse_iterator cite = test.rend();
	for (ft::list<int>::const_reverse_iterator cit = test.rbegin(); cit != cite; cit++)
		std::cout << *cit << " ";
	std::cout << std::endl;

	std::cout << "========STD========\n";
	std::cout << "size: " << std_list.size() << std::endl;
	std::cout << "[rvalue]" << std::endl;
	std::list<int>::const_reverse_iterator std_cite = std_list.rend();
	for (std::list<int>::const_reverse_iterator std_cit = std_list.rbegin(); std_cit != std_cite; std_cit++)
		std::cout << *std_cit << " ";
	std::cout << std::endl << std::endl;
}

#define TESTED_TYPE std::string

void	checkErase(ft::list<TESTED_TYPE> const &lst, ft::list<TESTED_TYPE>::const_iterator const &it)
{
static int i = 0;

int j = 0;
ft::list<TESTED_TYPE>::const_iterator ite = lst.end();
while (it != ite--)
	++j;

std::cout << "[" << i++ << "] " << "erase: " << j << std::endl;
}

int		test_erase(void)
{
	ft::list<TESTED_TYPE> lst(10);
	ft::list<TESTED_TYPE>::iterator it = lst.begin();

	for (unsigned long int i = 0; i < lst.size(); ++i)
		*it++ = std::string((lst.size() - i), i + 65);

	checkErase(lst, lst.erase(++lst.begin()));

	checkErase(lst, lst.erase(lst.begin()));
	checkErase(lst, lst.erase(--lst.end()));

	checkErase(lst, lst.erase(lst.begin(), ++(++(++lst.begin()))));
	checkErase(lst, lst.erase(--(--(--lst.end())), --lst.end()));

	lst.push_back("Hello");
	lst.push_back("Hi there");
	checkErase(lst, lst.erase(--(--(--lst.end())), lst.end()));

	lst.push_back("ONE");
	lst.push_back("TWO");
	lst.push_back("THREE");
	lst.push_back("FOUR");
	checkErase(lst, lst.erase(lst.begin(), lst.end()));

	return (0);
}


void list_full_test()
{
	std::cout << "int_list(5)\n";
	ft::list<int> int_list(5);
	std::list<int> int_list_std(5);
	list_basic_test(int_list, int_list_std);

	std::cout << "int_list_val_ten(5, 10)\n";
	ft::list<int> int_list_val_ten(5, 10);
	std::list<int> int_list_val_ten_std(5, 10);
	list_basic_test(int_list_val_ten, int_list_val_ten_std);

	std::cout << "assign_test.assign(int_list_val_ten.begin(), int_list_val_ten.end())\n";
	ft::list<int> assign_test;
	std::list<int> assign_test_std;
	assign_test.assign(int_list_val_ten.begin(), int_list_val_ten.end());
	assign_test_std.assign(int_list_val_ten_std.begin(), int_list_val_ten_std.end());
	list_basic_test(assign_test, assign_test_std);


	ft::list<int> test_this(int_list);
	std::cout << "front: " << test_this.front() << std::endl;
	int_list.sort();
	test_this.sort();
	int_list.merge(test_this);

	ft::list<int>::iterator ite = int_list.end();
	for (ft::list<int>::iterator it = int_list.begin(); it != ite; it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	test_erase();
}
