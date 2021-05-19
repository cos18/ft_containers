#include "vector.hpp"
#include <iostream>

int main()
{
	ft::vector<int> int_vector(10);
	std::cout << "int_vector's size: " << int_vector.size() << std::endl;

	std::cout << "[int_vector's value]" << std::endl;
	ft::vec_iterator<int> ite = int_vector.end();
	for (ft::vec_iterator<int> it = int_vector.begin(); it != ite; it++)
		std::cout << *it << std::endl;
	int_vector[3] = 10;
	int_vector[5] = 3;
	std::cout << "[int_vector's reverse value]" << std::endl;
	ft::r_iterator< ft::vec_iterator<int> > rite = int_vector.rend();
	for (ft::r_iterator< ft::vec_iterator<int> > rit = int_vector.rbegin(); rit != rite; rit++)
		std::cout << *rit << std::endl;


	ft::vector<int> int_vector_val_ten(20, 10);

	return 0;
}