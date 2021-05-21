#pragma once

#include <cstddef>

namespace ft
{
	class iterator_traits
	{
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
	
	protected:
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
		virtual ~vec_iterator()
		{
		}

		// Can be incremented
		vec_iterator operator++(int) { // 후위
			vec_iterator result(*this);
			++(this->_p);
			return (result);
		}
		vec_iterator &operator++() { // 전위
			++(this->_p);
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
			--(this->_p);
			return (result);
		}
		vec_iterator &operator--() {
			--(this->_p);
			return (*this);
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
		pointer getP() const {
			return this->_p;
		}
		template<typename cT>
		vec_iterator(vec_iterator<cT> const &const_src): _p((cT*)const_src.getP()) {}
	};

	template <class T>
	class vec_rev_iterator: public vec_iterator<T>
	{
	public:
		using typename vec_iterator<T>::difference_type;
		using typename vec_iterator<T>::value_type;
		using typename vec_iterator<T>::pointer;
		using typename vec_iterator<T>::const_pointer;
		using typename vec_iterator<T>::reference;
		using typename vec_iterator<T>::const_reference;

		vec_rev_iterator(): vec_iterator<T>() {}
		vec_rev_iterator(const vec_iterator<T> &src): vec_iterator<T>(src) {}
		vec_rev_iterator(const vec_rev_iterator &src): vec_iterator<T>(src._p) {}
		vec_rev_iterator &operator=(const vec_rev_iterator &rhs) {
			this->_p = rhs._p;
			return *this;
		}
		reference operator*() {
			vec_iterator<T> result(*this);
			return (*(--result));
		}
		vec_rev_iterator operator++(int) { // 후위
			vec_rev_iterator result(*this);
			--(this->_p);
			return (result);
		}
		vec_rev_iterator &operator++() { // 전위
			--(this->_p);
			return (this);
		}
		vec_rev_iterator operator--(int) { // 후위
			vec_rev_iterator result(*this);
			++(this->_p);
			return (result);
		}
		vec_rev_iterator &operator--() { // 전위
			++(this->_p);
			return (this);
		}
		pointer operator->() {
			vec_iterator<T> result(*this);
			return (&*(--result));
		}
		const_pointer operator->() const {
			vec_iterator<T> result(*this);
			return (&*(--result));
		}

/*
		pointer getP() const {
			return this->_p;
		}
		template<typename cT>
		vec_iterator(vec_rev_iterator<cT> const &const_src): _p((cT*)vec_rev_iterator.getP()) {}
		*/
	};

	
}