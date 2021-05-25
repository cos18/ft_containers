#pragma once

#include <cstddef>
#include "util.hpp"

namespace ft
{
	template <class T>
	class list_iterator
	{
	public:
		typedef T					value_type;
		typedef const T				const_value_type;
		typedef ft::Node<T>*		pointer;
		typedef const ft::Node<T>*	const_pointer;
		typedef T&					reference;
		typedef const T&			const_reference;
	
	protected:
		pointer	_p;

	public:
		// copy-constructible, copy-assignable and destructible
		list_iterator()
		{
			this->_p = NULL;
		}
		list_iterator(pointer p): _p(p) {}
		list_iterator(const list_iterator &src)
		{
			this->_p = src._p;
		}
		list_iterator &operator=(const list_iterator &rhs)
		{
			this->_p = rhs._p;
			return *this;
		}
		virtual ~list_iterator()
		{
		}

		// Can be incremented
		list_iterator operator++(int) // 후위
		{
			list_iterator result(*this);
			this->_p = this->_p->next;
			return (result);
		}
		list_iterator &operator++() // 전위
		{
			this->_p = this->_p->next;
			return (*this);
		}

		// Supports equality/inequality comparisons
		bool operator==(const list_iterator &rhs) const
		{
			return (this->_p == rhs._p);
		}
		bool operator!=(const list_iterator &rhs) const
		{
			return (this->_p != rhs._p);
		}

		// Can be dereferenced as an rvalue & lvalue
		reference operator*()
		{
			return this->_p->val;
		}
		const_reference operator*() const
		{
			return this->_p->val;
		}
		value_type *operator->()
		{
			return &(this->_p->val);
		}
		const_value_type *operator->() const
		{
			return &(this->_p->val);
		}

		// Can be decremented
		list_iterator operator--(int)
		{
			list_iterator result(*this);
			this->_p = this->_p->prev;
			return (result);
		}
		list_iterator &operator--()
		{
			this->_p = this->_p->prev;
			return (*this);
		}

		// etc
		pointer getP() const
		{
			return this->_p;
		}
		
		template<typename cT>
		list_iterator(list_iterator<cT> const &const_src): _p(const_cast<T*>(const_src.getP())) {}
	};

	template <class T>
	class list_rev_iterator: public list_iterator<T>
	{
	public:
		using typename list_iterator<T>::value_type;
		using typename list_iterator<T>::const_value_type;
		using typename list_iterator<T>::pointer;
		using typename list_iterator<T>::const_pointer;
		using typename list_iterator<T>::reference;
		using typename list_iterator<T>::const_reference;

		list_rev_iterator(): list_iterator<T>() {}
		list_rev_iterator(const list_iterator<T> &src): list_iterator<T>(src) {}
		list_rev_iterator(const list_rev_iterator &src): list_iterator<T>(src._p) {}

		list_rev_iterator &operator=(const list_rev_iterator &rhs)
		{
			this->_p = rhs._p;
			return *this;
		}
		reference operator*()
		{
			list_rev_iterator<T> result(*this);
			return (*(--result));
		}

		list_rev_iterator operator++(int) // 후위
		{
			list_rev_iterator result(*this);
			this->_p = this->_p->prev;
			return (result);
		}
		list_rev_iterator &operator++() // 전위
		{
			this->_p = this->_p->prev;
			return (*this);
		}
		list_rev_iterator operator--(int) // 후위
		{
			list_rev_iterator result(*this);
			this->_p = this->_p->next;
			return (result);
		}
		list_rev_iterator &operator--() // 전위
		{
			this->_p = this->_p->next;
			return (*this);
		}

		pointer operator->() {
			list_rev_iterator<T> result(*this);
			return (&*(--result));
		}
		const_pointer operator->() const {
			list_rev_iterator<T> result(*this);
			return (&*(--result));
		}
		list_rev_iterator<T> base() const
		{
			return this->_p;
		}
	};
}
