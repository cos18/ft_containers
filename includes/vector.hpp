#pragma once

#include <iostream>
#include <memory>
#include "vec_iterator.hpp"
#include "util.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::vec_iterator<T>							iterator;
		typedef ft::vec_iterator<const T>					const_iterator;
		typedef ft::vec_rev_iterator<T>						reverse_iterator;
		typedef ft::vec_rev_iterator<const T>				const_reverse_iterator;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

	private:
		pointer			_container;
		size_type		_container_size; // 들어있는 데이터 갯수
		size_type		_container_length; // allocator 총 사이즈
		allocator_type	_allocator;

	public:
		// (constructor)
		explicit vector(const allocator_type &alloc = allocator_type()):
			_container(NULL),
			_container_size(0),
			_container_length(0),
			_allocator(alloc)
		{
			this->_container = this->_allocator.allocate(0);
		}
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()):
			_container(NULL),
			_container_size(0),
			_container_length(0),
			_allocator(alloc)
		{
			this->_container = this->_allocator.allocate(0);
			this->assign(n, val);
		}
		template	<class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type tmp = 0):
			_container(NULL),
			_container_size(0),
			_container_length(0),
			_allocator(alloc)
		{
			(void)tmp;
			this->_container = this->_allocator.allocate(0);
			this->assign(first, last);
		}
		vector(const vector& x):
			_container(NULL),
			_container_size(0),
			_container_length(0),
			_allocator(allocator_type())
		{
			this->_container = this->_allocator.allocate(0);
			*this = x;
		}

		// (destructor)
		virtual ~vector()
		{
			this->_allocator.deallocate(this->_container, this->_container_length);
		}

		// operator=
		vector& operator=(const vector& x)
		{
			this->assign(x.begin(), x.end());
			return (*this);
		}

		// Iterators
		iterator				begin()
		{
			return iterator(this->_container);
		}
		const_iterator			begin() const
		{
			return const_iterator(this->_container);
		}
		iterator				end()
		{
			return iterator(this->_container + this->_container_size);
		}
		const_iterator			end() const
		{
			return const_iterator(this->_container + this->_container_size);
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
		size_type	size() const
		{
			return this->_container_size;
		}
		size_type	max_size() const
		{
			return (std::numeric_limits<size_type>::max() / sizeof(value_type));
		};
		void		resize(size_type n, value_type val = value_type())
		{
			this->reserve(n);
			for (size_type index = this->_container_size; index < n; index++)
				this->_container[index] = val;
			this->_container_size = n;
		}
		size_type	capacity() const
		{
			return this->_container_length;
		}
		bool		empty() const
		{
			return (this->_container_size == 0);
		}
		void		reserve(size_type n)
		{
			if (n <= this->_container_length)
				return;
			n = (this->_container_length * 2 > n ? this->_container_length * 2 : n);
			pointer tmp_container = this->_allocator.allocate(n);
			for (size_type index = 0; index < this->_container_size; index++)
				tmp_container[index] = this->_container[index];
			this->_allocator.deallocate(this->_container, this->_container_length);
			this->_container = tmp_container;
			this->_container_length = n;
		}

		// Element Access
		reference		operator[](size_type n)
		{
			return this->_container[n];
		}
		const_reference	operator[](size_type n) const
		{
			return this->_container[n];
		}
		reference		at(size_type n)
		{
			if (n >= this->_container_size)
				throw std::out_of_range("out of range");
			return this->_container[n];
		}
		const_reference	at(size_type n) const
		{
			if (n >= this->_container_size)
				throw std::out_of_range("out of range");
			return this->_container[n];
		}
		reference		front()
		{
			return this->_container[0];
		}
		const_reference	front() const
		{
			return this->_container[0];
		}
		reference		back()
		{
			return this->_container[this->_container_size - 1];
		}
		const_reference	back() const
		{
			return this->_container[this->_container_size - 1];
		}

		// Modifiers
		template	<class InputIterator>
		void		assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type tmp = 0)
		{
			(void)tmp;
			size_t n = 0;
			InputIterator first_tmp = first;
			while (first_tmp != last)
			{
				n++;
				first_tmp++;
			}
			if (this->_container_length < n)
				this->reserve(n);
			for (size_t index = 0; index < n; index++)
				this->_container[index] = *(first++);
			this->_container_size = n;
		}
		void		assign(size_type n, const value_type& u)
		{
			if (this->_container_length < n)
				this->reserve(n);
			for (size_t index = 0; index < n; index++)
				this->_container[index] = u;
			this->_container_size = n;
		}
		void		push_back(const value_type &val)
		{
			this->reserve(this->_container_size + 1);
			this->_container[this->_container_size] = val;
			(this->_container_size)++;
		}
		void		pop_back()
		{
			(this->_container_size)--;
		}
		iterator	insert(iterator position, const value_type &val)
		{
			size_type target_index = 0;
			while (iterator(this->_container + target_index) != position && target_index < this->_container_size)
				target_index++;
			this->reserve(this->_container_size + 1);
			size_type data_index = this->_container_size;
			while (data_index > target_index)
			{
				this->_container[data_index] = this->_container[data_index - 1];
				data_index--;
			}
			this->_container[target_index] = val;
			(this->_container_size)++;
			return iterator(this->_container + target_index);
		}
		void		insert(iterator position, size_type n, const value_type &val)
		{
			size_type target_index = 0;
			while (iterator(this->_container + target_index) != position && target_index < this->_container_size)
				target_index++;
			this->reserve(this->_container_size + n);
			size_type data_index = this->_container_size + n - 1;
			while (data_index >= target_index + n)
			{
				this->_container[data_index] = this->_container[data_index - n];
				data_index--;
			}
			while (target_index <= data_index)
			{
				this->_container[target_index] = val;
				target_index++;
			}
			this->_container_size += n;
		}
		template	<class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type tmp = 0)
		{
			(void)tmp;
			size_t n = 0;
			InputIterator first_tmp = first;
			while (first_tmp != last)
			{
				n++;
				first_tmp++;
			}
			size_type target_index = 0;
			while (iterator(this->_container + target_index) != position && target_index < this->_container_size)
				target_index++;
			for (size_type index = 0; index < n; index++)
			{
				iterator begin = this->begin();
				this->insert(begin + target_index + index, *first);
				first++;
			}
		}
		iterator	erase(iterator position)
		{
			return this->erase(position, position + 1);
		}
		iterator	erase(iterator first, iterator last)
		{
			size_type n = last - first;
			iterator target = first;
			while (target + n != this->end())
			{
				*target = *(target + n);
				target++;
			}
			this->_container_size -= n;
			return first;
		}
		void		swap(vector &x)
		{
			std::swap(this->_container, x._container);
			std::swap(this->_container_size, x._container_size);
			std::swap(this->_container_length, x._container_length);
			std::swap(this->_allocator, x._allocator);
		}
		void		clear()
		{
			this->_container_size = 0;
		}
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t index = 0; index < lhs.size(); index++)
		{
			if (lhs[index] != rhs[index])
				return false;
		}
		return true;
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		size_t n = lhs.size();
		n = (n > rhs.size() ? rhs.size() : n);
		for (size_t index = 0; index < n; index++)
		{
			if (lhs[index] != rhs[index])
				return (lhs[index] < rhs[index]);
		}
		return (lhs.size() < rhs.size());
	}
	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		return (!(lhs > rhs));
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap(vector<T,Alloc> &x, vector<T,Alloc> &y)
	{
		x.swap(y);
	}
}
