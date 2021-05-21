#include "vector.hpp"
#include <iostream>
#include <vector>

void vector_basic_test(ft::vector<int> &test)
{
	std::cout << "size: " << test.size() << std::endl;

	std::cout << "[value]" << std::endl;
	ft::vec_iterator<int> ite = test.end();
	for (ft::vec_iterator<int> it = test.begin(); it != ite; it++)
		std::cout << *it << std::endl;
	test[1] = 1;
	test[3] = 3;
	test.insert(test.begin(), 100);
	test.insert(test.begin() + 2, 3, 5);
	std::cout << "[rvalue]" << std::endl;
	ft::vector<int>::const_reverse_iterator cite = test.rend();
	for (ft::vector<int>::const_reverse_iterator cit = test.rbegin(); cit != cite; cit++)
		std::cout << *cit << std::endl;
}

int main()
{
	ft::vector<int> int_vector(5);
	vector_basic_test(int_vector);

	ft::vector<int> int_vector_val_ten(5, 10);
	vector_basic_test(int_vector_val_ten);

	return 0;
}