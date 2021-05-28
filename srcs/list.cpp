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

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}

#define TESTED_TYPE2 foo<int>

void list_rite_arrow()
{
	const int size = 5;
	ft::list<TESTED_TYPE2> lst(size);
	ft::list<TESTED_TYPE2>::reverse_iterator it(lst.rbegin());
	ft::list<TESTED_TYPE2>::const_reverse_iterator ite(lst.rend());

	for (int i = 1; it != ite; ++i)
		*it++ = (i * 7);

	it = lst.rbegin();
	ite = lst.rbegin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	it->m();
	ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	(*it).m();
	(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;
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

	list_rite_arrow();
}
