#pragma once

#include <cstddef>

namespace ft
{
	template <class T>
	class iterator_traits
	{
	public:
		typedef std::ptrdiff_t	difference_type;
		typedef T				value_type;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef T&				reference;
		typedef const T&		const_reference;
	
	protected:
		pointer	_p;
	};

	template <class T, class Iterator = ft::iterator_traits<T> >
	class r_iterator: public Iterator
	{
	public:
		using typename Iterator::difference_type;
		using typename Iterator::value_type;
		using typename Iterator::pointer;
		using typename Iterator::const_pointer;
		using typename Iterator::reference;
		using typename Iterator::const_reference;

		r_iterator(): Iterator() {}
		r_iterator(const Iterator &src): Iterator(src) {}
		r_iterator(const r_iterator &src): Iterator(src._p) {}
		r_iterator &operator=(const r_iterator &rhs) {
			this->_p = rhs._p;
			return *this;
		}
	};
}