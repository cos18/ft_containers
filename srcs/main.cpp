#include "vector.hpp"
#include <iostream>

void vector_basic_test(ft::vector<int> &test)
{
	std::cout << "size: " << test.size() << std::endl;

	std::cout << "[value]" << std::endl;
	ft::vec_iterator<int> ite = test.end();
	for (ft::vec_iterator<int> it = test.begin(); it != ite; it++)
		std::cout << *it << std::endl;
	test[3] = 1;
	test[5] = 3;
	std::cout << "[reverse value]" << std::endl;
	ft::r_iterator< ft::vec_iterator<int> > rite = test.rend();
	for (ft::r_iterator< ft::vec_iterator<int> > rit = test.rbegin(); rit != rite; rit++)
		std::cout << *rit << std::endl;
}

int main()
{
	ft::vector<int> int_vector(10);
	vector_basic_test(int_vector);

	ft::vector<int> int_vector_val_ten(10, 20);
	vector_basic_test(int_vector_val_ten);

	return 0;
}