#include "queue.hpp"
#include <queue>

void queue_basic_test(ft::queue<int> &test, std::queue<int> &std_test)
{
	std::cout << "========START========\n";
	std::cout << "========FT========\n";
	std::cout << "size: " << test.size() << std::endl;

	std::cout << "========STD========\n";
	std::cout << "size: " << std_test.size() << std::endl;


	test.push(10);
	test.push(20);
	test.push(30);
	test.front() -= 4;
	std::cout << "========FT========\n";
	std::cout << "front: " << test.front() << std::endl;
	std::cout << "back: " << test.back() << std::endl;
	test.pop();
	test.pop();
	test.push(40);
	test.push(50);
	std::cout << "front: " << test.front() << std::endl;
	std::cout << "back: " << test.back() << std::endl;

	std_test.push(10);
	std_test.push(20);
	std_test.push(30);
	std_test.front() -= 4;
	std::cout << "========FT========\n";
	std::cout << "front: " << std_test.front() << std::endl;
	std::cout << "back: " << std_test.back() << std::endl;
	std_test.pop();
	std_test.pop();
	std_test.push(40);
	std_test.push(50);
	std::cout << "front: " << std_test.front() << std::endl;
	std::cout << "back: " << std_test.back() << std::endl;
	

	std::cout << "========FT========\n";
	std::cout << "size: " << test.size() << std::endl;

	std::cout << "========STD========\n";
	std::cout << "size: " << std_test.size() << std::endl;

	std::cout << "========END========\n";
	std::cout << std::endl << std::endl;
}

void queue_full_test()
{
	std::cout << "=========Q U E U E=========" << std::endl << std::endl;
	std::cout << "int_queue\n";
	ft::queue<int> int_queue;
	std::queue<int> int_queue_std;
	queue_basic_test(int_queue, int_queue_std);
}