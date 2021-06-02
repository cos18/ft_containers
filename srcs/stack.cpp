#include "stack.hpp"
#include <stack>

void stack_basic_test(ft::stack<int> &test, std::stack<int> &std_test)
{
	std::cout << "========START========\n";
	std::cout << "========FT========\n";
	std::cout << "size: " << test.size() << std::endl;

	std::cout << "========STD========\n";
	std::cout << "size: " << std_test.size() << std::endl;


	test.push(10);
	test.push(20);
	test.push(30);
	test.top() -= 4;
	std::cout << "========FT========\n";
	std::cout << "top: " << test.top() << std::endl;
	test.pop();
	test.pop();
	std::cout << "top: " << test.top() << std::endl;

	std_test.push(10);
	std_test.push(20);
	std_test.push(30);
	std_test.top() -= 4;
	std::cout << "========STD========\n";
	std::cout << "top: " << std_test.top() << std::endl;
	std_test.pop();
	std_test.pop();
	std::cout << "top: " << std_test.top() << std::endl;
	

	std::cout << "========FT========\n";
	std::cout << "size: " << test.size() << std::endl;

	std::cout << "========STD========\n";
	std::cout << "size: " << std_test.size() << std::endl;

	std::cout << "========END========\n";
	std::cout << std::endl << std::endl;
}

void stack_full_test()
{
	std::cout << "=========S T A C K=========" << std::endl << std::endl;
	std::cout << "int_stack\n";
	ft::stack<int> int_stack;
	std::stack<int> int_stack_std;
	stack_basic_test(int_stack, int_stack_std);
}