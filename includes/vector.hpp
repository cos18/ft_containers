#pragma once

#include <iostream>
#include <memory>
#include "iterator.hpp"

namespace ft
{
	template <class T>
	class vec_iterator: public ft::iterator_traits<T>
	{
	public:
		using typename ft::iterator_traits<T>::difference_type;
		using typename ft::iterator_traits<T>::value_type;
		using typename ft::iterator_traits<T>::pointer;
		using typename ft::iterator_traits<T>::const_pointer;
		using typename ft::iterator_traits<T>::reference;
		using typename ft::iterator_traits<T>::const_reference;

	public:
		vec_iterator() {
			this->_p = NULL;
		}
		vec_iterator(pointer p) {
			this->_p = p;
		}
		vec_iterator(const vec_iterator &src) {
			this->_p = src._p;
		}
		virtual ~vec_iterator();

		vec_iterator &operator=(const vec_iterator &rhs) {
			this->_p = rhs._p;
			return *this;
		}
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
		reference operator[](size_t n) {
			return *(this->_p + n);
		}
		const_reference operator[](size_t n) const {
			return *(this->_p + n);
		}
	};

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		// TODO: Iterator 구현해야함!
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::vec_iterator<T>							iterator;
		typedef ft::vec_iterator<const T>					const_iterator;
		typedef ft::r_iterator<T, iterator>					reverse_iterator;
		typedef ft::r_iterator<const T, const_iterator>		const_reverse_iterator;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

	private:
		pointer			_container;
		size_type		_container_size;
		size_type		_container_length;
		allocator_type	_allocator;

	public:
		// (constructor)
		explicit vector(const allocator_type &alloc = allocator_type());
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
		template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
		vector(const vector& x);

		// (destructor)
		~vector();

		// operator=
		vector& operator=(const vector& x);

		// Iterators
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;

		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		// Capacity
		size_type	size() const;
		size_type	max_size() const;
		void		resize(size_type n, value_type val = value_type());
		size_type	capacity() const;
		bool		empty() const;
		void		reserve(size_type n);

		// Element Access
		reference		operator[](size_type n);
		const_reference	operator[](size_type n) const;
		reference		at(size_type n);
		const_reference	at(size_type n) const;
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		// Modifiers
		template <class InputIterator>
			void		assign(InputIterator first, InputIterator last);
		void			assign(size_type n, const value_type& u);
		void			push_back(const value_type &val);
		void			pop_back();
		iterator		insert(iterator position, const value_type &val);
		iterator		insert(iterator position, size_type n, const value_type &val);
		template <class InputIterator>
			iterator	insert(iterator position, InputIterator first, InputIterator last);
		iterator		erase(iterator position);
		iterator		erase(iterator first, iterator last);
		void			swap(vector &x);
		void			clear();
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);

	template <class T, class Alloc>
	void swap(vector<T,Alloc> &x, vector<T,Alloc> &y);
}