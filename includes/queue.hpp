#pragma once

#include <iostream>
#include <memory>
#include "list.hpp"
#include "list_iterator.hpp"
#include "util.hpp"

namespace ft
{
	template <class T, class Container = ft::list<T> >
	class queue
	{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

	private:
		container_type _container;

	public:
		// (constructor)
		explicit queue(const container_type& ctnr = container_type()): _container(ctnr) {}

		// (destructor)
		virtual ~queue()
		{

		}

		bool empty() const
		{
			return this->_container.empty();
		}

		size_type size() const
		{
			return this->_container.size();
		}

		value_type& front()
		{
			return this->_container.front();
		}
		const value_type& front() const
		{
			return this->_container.front();
		}
		value_type& back()
		{
			return this->_container.back();
		}
		const value_type& back() const
		{
			return this->_container.back();
		}

		void push(const value_type& val)
		{
			return this->_container.push_back(val);
		}
		void pop()
		{
			return this->_container.pop_front();
		}

		friend
		bool operator==(const queue<T,Container> &lhs, const queue<T,Container> &rhs)
		{
			return (lhs._container == rhs._container);
		}
		friend
		bool operator<(const queue<T,Container> &lhs, const queue<T,Container> &rhs)
		{
			return (lhs._container < rhs._container);
		}
	};


	template <class T, class Container>
	bool operator!=(const queue<T,Container> &lhs, const queue<T,Container> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator>(const queue<T,Container> &lhs, const queue<T,Container> &rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Container>
	bool operator<=(const queue<T,Container> &lhs, const queue<T,Container> &rhs)
	{
		return (!(lhs > rhs));
	}
	template <class T, class Container>
	bool operator>=(const queue<T,Container> &lhs, const queue<T,Container> &rhs)
	{
		return (!(lhs < rhs));
	}
}
