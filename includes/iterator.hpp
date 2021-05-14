#pragma once

#include <cstddef>

namespace ft
{
	class iterator_traits
	{
	};

	template <class Iterator = ft::iterator_traits>
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
		reference operator*() {
			Iterator result(*this);
			return (*(--result));
		}
		r_iterator &operator++() {
			r_iterator result(*this);
			this->Iterator::operator--();
			return (result);
		}
		r_iterator &operator--() {
			r_iterator result(*this);
			this->Iterator::operator++();
			return (result);
		}
		pointer operator->() {
			Iterator result(*this);
			return (&*(--result));
		}
		const_pointer operator->() const {
			Iterator result(*this);
			return (&*(--result));
		}
	};

	template <class T>
	class vec_iterator: public ft::iterator_traits
	{
	public:
		typedef std::ptrdiff_t	difference_type;
		typedef T				value_type;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef T&				reference;
		typedef const T&		const_reference;
	
	private:
		pointer	_p;

	public:
		// copy-constructible, copy-assignable and destructible
		vec_iterator(const vec_iterator &src) {
			this->_p = src._p;
		}
		vec_iterator &operator=(const vec_iterator &rhs) {
			this->_p = rhs._p;
			return *this;
		}
		virtual ~vec_iterator();

		// Can be incremented
		vec_iterator operator++(int) {
			vec_iterator result(*this);
			++(this->p);
			return (result);
		}
		vec_iterator &operator++() {
			++(this->p);
			return (**this);
		}

		// Supports equality/inequality comparisons
		bool operator==(const vec_iterator &rhs) const {
			return (this->_p == rhs._p);
		}
		bool operator!=(const vec_iterator &rhs) const {
			return (this->_p != rhs._p);
		}

		// Can be dereferenced as an rvalue & lvalue
		reference operator*() {
			return *(this->_p);
		}
		const_reference operator*() const {
			return *(this->_p);
		}
		pointer operator->() {
			return this->_p;
		}
		const_pointer operator->() const {
			return this->_p;
		}

		// 	default-constructible
		vec_iterator() {
			this->_p = NULL;
		}

		// Can be decremented
		vec_iterator operator--(int) {
			vec_iterator result(*this);
			--(this->p);
			return (result);
		}
		vec_iterator &operator--() {
			--(this->p);
			return (**this);
		}

		// Supports arithmetic operators + and -
		vec_iterator operator+(int n) {
			vec_iterator result(*this);
			result._p += n;
			return result;
		}
		vec_iterator operator-(int n) {
			vec_iterator result(*this);
			result._p -= n;
			return result;
		}
		difference_type operator-(const vec_iterator &rhs) const {
			return (this->_p - rhs._p);
		}

		// Supports inequality comparisons (<, >, <= and >=) between iterators
		bool operator<(const vec_iterator &rhs) const {
			return (this->_p < rhs._p);
		}
		bool operator<=(const vec_iterator &rhs) const {
			return (this->_p <= rhs._p);
		}
		bool operator>(const vec_iterator &rhs) const {
			return (this->_p > rhs._p);
		}
		bool operator>=(const vec_iterator &rhs) const {
			return (this->_p >= rhs._p);
		}

		// Supports compound assignment operations += and -=
		vec_iterator &operator+=(int n) {
			this->_p += n;
			return (*this);
		}
		vec_iterator &operator-=(int n) {
			this->_p -= n;
			return (*this);
		}

		// Supports offset dereference operator ([])
		reference operator[](size_t n) {
			return *(this->_p + n);
		}
		const_reference operator[](size_t n) const {
			return *(this->_p + n);
		}

		// etc
		vec_iterator(pointer p) {
			this->_p = p;
		}
	};
}