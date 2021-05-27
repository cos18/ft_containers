#pragma once

#include <iostream>
#include <memory>
#include "list_iterator.hpp"
#include "util.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class list
	{
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::list_iterator<T>						iterator;
		typedef ft::list_const_iterator<T>					const_iterator;
		typedef ft::list_rev_iterator<T>					reverse_iterator;
		typedef ft::list_rev_const_iterator<T>				const_reverse_iterator;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef ft::Node<value_type>*						node_type;

	private:
		node_type		_start_node;
		node_type		_end_node;
		size_type		_size;
		allocator_type	_allocator;

		node_type init_node(value_type val, node_type prev, node_type next)
		{
			node_type result = new ft::Node<value_type>();
			result->prev = prev;
			result->val = val;
			result->next = next;
			return result;
		}
		void init_list()
		{
			this->_start_node = init_node(value_type(), NULL, NULL);
			this->_end_node = init_node(value_type(), this->_start_node, NULL);
			this->_start_node->next = this->_end_node;
		}
		void swap_node(node_type n)
		{
			if (n == NULL || n == this->_start_node || n->next == NULL || n->next == this->_end_node)
				return;
			node_type m = n->next, n_before = n->prev, m_after = n->next->next;
			n_before->next = m;
			m_after->prev = n;
			n->prev = m;
			n->next = m_after;
			m->prev = n_before;
			m->next = n;
		}

	public:
		// (constructor)
		explicit list (const allocator_type& alloc = allocator_type()):
			_start_node(NULL),
			_end_node(NULL),
			_size(0),
			_allocator(alloc)
		{
			this->init_list();
		}
		explicit list (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()):
			_start_node(NULL),
			_end_node(NULL),
			_size(0),
			_allocator(alloc)
		{
			this->init_list();
			this->assign(n, val);
		}
		template <class InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			  typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type tmp = 0):
			  _start_node(NULL),
			  _end_node(NULL),
			  _size(0),
			  _allocator(alloc)
		{
			(void)tmp;
			this->init_list();
			this->assign(first, last);
		}
		list (const list& x):
			_start_node(NULL),
			_end_node(NULL),
			_size(0)
		{
			this->init_list();
			*this = x;
		}

		// (destructor)
		virtual ~list()
		{
			this->clear();
			delete this->_start_node;
			delete this->_end_node;
		}

		// operator=
		list& operator=(const list& x)
		{
			this->assign(x.begin(), x.end());
			return (*this);
		}

		// Iterators
		iterator				begin()
		{
			return iterator(this->_start_node->next);
		}
		const_iterator			begin() const
		{
			return const_iterator(this->_start_node->next);
		}
		iterator				end()
		{
			return iterator(this->_end_node);
		}
		const_iterator			end() const
		{
			return const_iterator(this->_end_node);
		}

		reverse_iterator		rbegin()
		{
			return reverse_iterator(this->end());
		}
		const_reverse_iterator	rbegin() const
		{
			return const_reverse_iterator(this->end());
		}
		reverse_iterator		rend()
		{
			return reverse_iterator(this->begin());
		}
		const_reverse_iterator	rend() const
		{
			return const_reverse_iterator(this->begin());
		}

		// Capacity
		bool		empty() const
		{
			return (this->_size == 0);
		}
		size_type	size() const
		{
			return this->_size;
		}
		size_type	max_size() const
		{
			return (std::numeric_limits<size_type>::max() / (sizeof(ft::Node<T>)));
		};

		// Element Access
		reference		front()
		{
			return this->_start_node->next->val;
		}
		const_reference	front() const
		{
			return this->_start_node->next->val;
		}
		reference		back()
		{
			return this->_end_node->prev->val;
		}
		const_reference	back() const
		{
			return this->_end_node->prev->val;
		}

		// Modifiers
		template	<class InputIterator>
		void		assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type tmp = 0)
		{
			(void)tmp;
			this->clear();
			while (first != last)
				push_back(*(first++));
		}
		void		assign(size_type n, const value_type& val)
		{
			this->clear();
			while ((n--) > 0)
				push_back(val);
		}
		void		push_front(const value_type &val)
		{
			node_type target = init_node(val, this->_start_node, this->_start_node->next);
			this->_start_node->next->prev = target;
			this->_start_node->next = target;
			(this->_size)++;
		}
		void		pop_front()
		{
			if (this->empty())
				throw std::exception();
			node_type target = this->_start_node->next;
			this->_start_node->next = target->next;
			this->_start_node->next->prev = this->_start_node;
			delete target;
			(this->_size)--;
		}
		void		push_back(const value_type &val)
		{
			node_type target = init_node(val, this->_end_node->prev, this->_end_node);
			this->_end_node->prev->next = target;
			this->_end_node->prev = target;
			(this->_size)++;
		}
		void		pop_back()
		{
			if (this->empty())
				throw std::exception();
			node_type target = this->_end_node->prev;
			this->_end_node->prev = target->prev;
			this->_end_node->prev->next = this->_end_node;
			delete target;
			(this->_size)--;
		}
		iterator	insert(iterator position, const value_type &val)
		{
			node_type pos_node = position.getP();
			node_type target = init_node(val, pos_node->prev, pos_node);
			pos_node->prev->next = target;
			pos_node->prev = target;
			(this->_size)++;
			return iterator(target);
		}
		void		insert(iterator position, size_type n, const value_type &val)
		{
			while ((n--) > 0)
				this->insert(position, val);
		}
		template	<class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type tmp = 0)
		{
			(void)tmp;
			while (first != last)
				this->insert(position, *(first++));
		}
		iterator	erase(iterator position)
		{
			node_type pos_node = position.getP();
			pos_node->next->prev = pos_node->prev;
			pos_node->prev->next = pos_node->next;
			node_type result = pos_node->next;
			delete pos_node;
			(this->_size)--;
			return iterator(result);
		}
		iterator	erase(iterator first, iterator last)
		{
			size_type n = 0;
			node_type first_node = first.getP(), last_node = last.getP();
			first_node->prev->next = last_node;
			last_node->prev = first_node->prev;
			while (first_node != last_node)
			{
				node_type tmp = first_node->next;
				delete first_node;
				first_node = tmp;
				n++;
			}
			this->_size -= n;
			return iterator(last_node);
		}
		void		swap(list &x)
		{
			node_type tmp = this->_start_node;
			this->_start_node = x._start_node;
			x._start_node = tmp;
			tmp = this->_end_node;
			this->_end_node = x._end_node;
			x._end_node = tmp;
			size_type size_tmp = this->_size;
			this->_size = x._size;
			x._size = size_tmp;
		}
		void		resize(size_type n, value_type val = value_type())
		{
			if (n == this->_size)
				return;
			if (n > this->_size)
			{
				for (size_type tmp = this->_size; tmp < n; tmp++)
					this->push_back(val);
				return;
			}
			iterator target = this->end();
			size_type del_len = this->_size - n;
			while (del_len--)
				target--;
			this->erase(target, this->end());
		}
		void		clear()
		{
			node_type target = this->_start_node->next;
			while (target != this->_end_node)
			{
				node_type tmp = target->next;
				delete target;
				target = tmp;
			}
			this->_start_node->next = this->_end_node;
			this->_end_node->prev = this->_start_node;
			this->_size = 0;
		}

		// Operations
		void splice(iterator position, list& x)
		{
			this->splice(position, x, x.begin(), x.end());
		}
		void splice(iterator position, list& x, iterator i)
		{
			iterator next = i;
			next++;
			this->splice(position, x, i, next);
		}
		void splice(iterator position, list& x, iterator first, iterator last)
		{
			size_type splice_size = 0;
			iterator tmp = first;
			while (tmp != last)
			{
				tmp++;
				splice_size++;
			}

			node_type pos_node = position.getP(), begin_node = first.getP(), end_node = last.getP();
			node_type before_node = begin_node->prev;

			pos_node->prev->next = begin_node;
			begin_node->prev = pos_node->prev;
			pos_node->prev = end_node->prev;
			end_node->prev->next = pos_node;

			before_node->next = end_node;
			end_node->prev = before_node;

			this->_size += splice_size;
			x._size -= splice_size;
		}
		void remove(const value_type& val)
		{
			iterator target = this->begin();
			while (target != this->end())
			{
				iterator tmp = iterator(target.getP()->next);
				if (*target == val)
					this->erase(target);
				target = tmp;
			}
		}
		template <class Predicate>
		void remove_if (Predicate pred)
		{
			iterator target = this->begin();
			while (target != this->end())
			{
				iterator tmp = iterator(target.getP()->next);
				if (pred(*target))
					this->erase(target);
				target = tmp;
			}
		}
		void unique()
		{
			iterator target = this->begin();
			while (target != this->end())
			{
				while (true)
				{
					iterator next = target;
					next++;
					if (next == this->end() || *target != *next)
						break;
					this->erase(next);
				}
				target++;
			}
		}
		template <class BinaryPredicate>
		void unique(BinaryPredicate binary_pred)
		{
			iterator target = this->begin();
			while (target != this->end())
			{
				while (true)
				{
					iterator next = target;
					next++;
					if (next == this->end() || !binary_pred(*target, *next))
						break;
					this->erase(next);
				}
				target++;
			}
		}
		void merge(list &x)
		{
			if (this->begin() == x.begin())
				return;
			iterator target = this->begin();
			while (target != this->end())
			{
				iterator x_target = x.begin();
				while (((*x_target) < (*target)) && x_target != x.end())
				{
					this->splice(target, x, x_target);
					x_target = x.begin();
				}
				target++;
			}
			if (x.empty())
				return;
			this->splice(this->end(), x, x.begin(), x.end());
		}
		template <class Compare>
		void merge(list &x, Compare comp)
		{
			if (this->begin() == x.begin())
				return;
			iterator target = this->begin();
			while (target != this->end())
			{
				iterator x_target = x.begin();
				while (comp(*x_target, *target) && x_target != x.end())
				{
					this->splice(target, x, x_target);
					x_target = x.begin();
				}
				target++;
			}
			if (x.empty())
				return;
			this->splice(this->end(), x, x.begin(), x.end());
		}
		void sort()
		{
			if (this->empty())
				return;
			size_type n = this->_size - 1;
			while (n > 0)
			{
				node_type target = this->_start_node->next;
				for (size_type i = 0; i < n; i++)
				{
					if (target->next->val < target->val)
						swap_node(target);
					else
						target = target->next;
				}
				n--;
			}
		}
		template <class Compare>
		void sort (Compare comp)
		{
			if (this->empty())
				return;
			size_type n = this->_size - 1;
			while (n > 0)
			{
				node_type target = this->_start_node->next;
				for (size_type i = 0; i < n; i++)
				{
					if (comp(target->next->val, target->val))
						swap_node(target);
					else
						target = target->next;
				}
				n--;
			}
		}
		void reverse()
		{
			if (this->empty())
				return;
			node_type target = this->_start_node;
			while (target != NULL)
			{
				node_type tmp = target->next;
				target->next = target->prev;
				target->prev = tmp;
				target = tmp;
			}
			target = this->_start_node;
			this->_start_node = this->_end_node;
			this->_end_node = target;
		}
	};

	template <class T, class Alloc>
	bool operator==(const list<T,Alloc> &lhs, const list<T,Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		list_iterator<T> lhs_it = lhs.begin(), rhs_it = rhs.begin();
		while (lhs_it != lhs.end())
		{
			if (*lhs_it != *rhs_it)
				return false;
			lhs_it++;
			rhs_it++;
		}
		return true;
	}
	template <class T, class Alloc>
	bool operator!=(const list<T,Alloc> &lhs, const list<T,Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool operator<(const list<T,Alloc> &lhs, const list<T,Alloc> &rhs)
	{
		list_iterator<T> lhs_it = lhs.begin(), rhs_it = rhs.begin();
		while (lhs_it != lhs.end() && rhs_it != rhs.end())
		{
			if (*lhs_it != *rhs_it)
				return (*lhs_it < *rhs_it);
			lhs_it++;
			rhs_it++;
		}
		return (lhs.size() < rhs.size());
	}
	template <class T, class Alloc>
	bool operator>(const list<T,Alloc> &lhs, const list<T,Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator<=(const list<T,Alloc> &lhs, const list<T,Alloc> &rhs)
	{
		return (!(lhs > rhs));
	}
	template <class T, class Alloc>
	bool operator>=(const list<T,Alloc> &lhs, const list<T,Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap(list<T,Alloc> &x, list<T,Alloc> &y)
	{
		x.swap(y);
	}
}
