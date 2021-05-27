#pragma once

#include <memory>
#include "util.hpp"

namespace ft
{
	template < class Key,
			   class T,
			   class Compare = std::less<Key>,
			   class Allocator = std::allocator< std::pair<const Key, T> >
			   >
	class map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		class												value_compare;

		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		// TODO: iterator 구현해야 함
		typedef ft::list_iterator<T>						iterator;
		typedef ft::list_const_iterator<T>					const_iterator;
		typedef ft::list_rev_iterator<T>					reverse_iterator;
		typedef ft::list_rev_const_iterator<T>				const_reverse_iterator;

		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

	private:
		key_compare		_key_cmp;
		allocator_type	_allocator;
		size_type	_size;

	public:
		// (constructor)
		explicit map(const key_compare& comp = key_compare(),
			   		 const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
	  		const key_compare& comp = key_compare(),
	  		const allocator_type& alloc = allocator_type());
		map(const map& x);

		// (destructor)
		~map() {}

		map& operator= (const map& x);

		// Iterators
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		// Capacity
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		// Element access
		mapped_type& operator[](const key_type& k);

		// Modifiers
		pair<iterator,bool> insert(const value_type& val);
		iterator insert(iterator position, const value_type& val);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);
		void erase(iterator position);
		size_type erase(const key_type& k);
		void erase(iterator first, iterator last);
		void swap(map& x);
		void clear();

		// Observers
		key_compare key_comp() const;
		value_compare value_comp() const;

		// Operations
		iterator find (const key_type& k);
		const_iterator find (const key_type& k) const;
		size_type count (const key_type& k) const;
		iterator lower_bound (const key_type& k);
		const_iterator lower_bound (const key_type& k) const;
		iterator upper_bound (const key_type& k);
		const_iterator upper_bound (const key_type& k) const;
		std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		std::pair<iterator,iterator>             equal_range (const key_type& k);
	};
}