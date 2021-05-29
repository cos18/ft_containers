#pragma once

#include "util.hpp"

namespace ft
{
	template <typename Key, typename T, class Compare>
	class map_const_iterator;

	template <typename Key, typename T, class Compare>
	class map_iterator
	{
	public:
		typedef Key							key_type;
		typedef T							mapped_type;
		typedef std::pair<const Key, T>		value_type;
		typedef Compare						key_compare;
		typedef Mapnode<Key, T, Compare>*	node_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;

	protected:
		node_type	_p;
		node_type	_root;
		int			_margin;

		class OutOfRangeException : public std::exception
		{
			virtual const char * what() const throw()
			{
				return "map_iterator::OutOfRangeException";
			}
		};

	public:
		map_iterator(): _p(NULL), _root(NULL), _margin(0) {}
		map_iterator(node_type p, node_type root, int margin = 0): _p(p), _root(root), _margin(margin) {}
		map_iterator(const map_iterator &src): _p(src._p), _root(src._root), _margin(src._margin) {}
		map_iterator(const map_const_iterator<Key, T, Compare> &src): _p(src.getP()), _root(src.getRoot()), _margin(src.getMargin()) {}
		virtual ~map_iterator() {}

		map_iterator &operator=(const map_iterator &rhs)
		{
			this->_p = rhs._p;
			this->_root = rhs._root;
			this->_margin = rhs._margin;
			return *this;
		}

		bool operator==(const map_iterator &rhs)
		{
			return (this->_p == rhs._p && this->_margin == rhs._margin);
		}
		bool operator==(const map_const_iterator<Key, T, Compare> &rhs)
		{
			return (this->_p == rhs.getP() && this->_margin == rhs.getMargin());
		}
		bool operator!=(const map_iterator &rhs)
		{
			return (this->_p != rhs._p || this->_margin != rhs._margin);
		}
		bool operator!=(const map_const_iterator<Key, T, Compare> &rhs)
		{
			return (this->_p != rhs.getP() || this->_margin != rhs.getMargin());
		}

		reference operator*()
		{
			return &(this->_p->val);
		}
		const_reference operator*() const
		{
			return &(this->_p->val);
		}
		pointer operator->()
		{
			return this->_p->val;
		}
		const_pointer operator->() const
		{
			return this->_p->val;
		}

		map_iterator operator++(int) // 후위
		{
			map_iterator result(*this);
			switch (this->_margin)
			{
			case -1:
				this->_p = this->_root->first();
				this->_margin = 0;
				break;
			case 0:
				this->_p = this->_p->next();
				if (!(this->_p))
					this->_margin = 1;
				break;
			default:
				throw OutOfRangeException();
			}
			return (result);
		}
		map_iterator &operator++() // 전위
		{
			switch (this->_margin)
			{
			case -1:
				this->_p = this->_root->first();
				this->_margin = 0;
				break;
			case 0:
				this->_p = this->_p->next();
				if (!(this->_p))
					this->_margin = 1;
				break;
			default:
				throw OutOfRangeException();
			}
			return (*this);
		}
		map_iterator operator--(int) // 후위
		{
			map_iterator result(*this);
			switch (this->_margin)
			{
			case 1:
				this->_p = this->_root->last();
				this->_margin = 0;
				break;
			case 0:
				this->_p = this->_p->prev();
				if (!(this->_p))
					throw OutOfRangeException();
				break;
			default:
				throw OutOfRangeException();
			}
			return (result);
		}
		map_iterator &operator--() // 전위
		{
			switch (this->_margin)
			{
			case 1:
				this->_p = this->_root->last();
				this->_margin = 0;
				break;
			case 0:
				this->_p = this->_p->prev();
				if (!(this->_p))
					throw OutOfRangeException();
				break;
			default:
				throw OutOfRangeException();
			}
			return (*this);
		}

		const node_type getP() const
		{
			return this->_p;
		}
		const node_type getRoot() const
		{
			return this->_root;
		}
		int getMargin() const
		{
			return this->_margin;
		}
	};

	template <typename Key, typename T, class Compare>
	class map_const_iterator
	{
	public:
		typedef Key							key_type;
		typedef T							mapped_type;
		typedef std::pair<const Key, T>		value_type;
		typedef Compare						key_compare;
		typedef Mapnode<Key, T, Compare>*	node_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;

	protected:
		node_type	_p;
		node_type	_root;
		int			_margin;

		class OutOfRangeException : public std::exception
		{
			virtual const char * what() const throw()
			{
				return "map_const_iterator::OutOfRangeException";
			}
		};

	public:
		map_const_iterator(): _p(NULL), _root(NULL), _margin(0) {}
		map_const_iterator(node_type p, node_type root, int margin = 0): _p(p), _root(root), _margin(margin) {}
		map_const_iterator(const map_const_iterator &src): _p(src._p), _root(src._root), _margin(src._margin) {};
		map_const_iterator(const map_iterator<Key, T, Compare> &src): _p(src.getP()), _root(src.getRoot()), _margin(src.getMargin()) {}
		virtual ~map_const_iterator() {}

		map_const_iterator &operator=(const map_const_iterator &rhs)
		{
			this->_p = rhs._p;
			this->_root = rhs._root;
			this->_margin = rhs._margin;
			return *this;
		}

		bool operator==(const map_iterator<Key, T, Compare> &rhs)
		{
			return (this->_p == rhs.getP() && this->_margin == rhs.getMargin());
		}
		bool operator==(const map_const_iterator &rhs)
		{
			return (this->_p == rhs._p && this->_margin == rhs._margin);
		}
		bool operator!=(const map_iterator<Key, T, Compare> &rhs)
		{
			return (this->_p != rhs.getP() || this->_margin != rhs.getMargin());
		}
		bool operator!=(const map_const_iterator &rhs)
		{
			return (this->_p != rhs._p || this->_margin != rhs._margin);
		}

		const_reference operator*() const
		{
			return &(this->_p->val);
		}
		const_pointer operator->() const
		{
			return this->_p->val;
		}

		map_const_iterator operator++(int) // 후위
		{
			map_const_iterator result(*this);
			switch (this->_margin)
			{
			case -1:
				this->_p = this->_root->first();
				this->_margin = 0;
				break;
			case 0:
				this->_p = this->_p->next();
				if (!(this->_p))
					this->_margin = 1;
				break;
			default:
				throw OutOfRangeException();
			}
			return (result);
		}
		map_const_iterator &operator++() // 전위
		{
			switch (this->_margin)
			{
			case -1:
				this->_p = this->_root->first();
				this->_margin = 0;
				break;
			case 0:
				this->_p = this->_p->next();
				if (!(this->_p))
					this->_margin = 1;
				break;
			default:
				throw OutOfRangeException();
			}
			return (*this);
		}
		map_const_iterator operator--(int) // 후위
		{
			map_const_iterator result(*this);
			switch (this->_margin)
			{
			case 1:
				this->_p = this->_root->last();
				this->_margin = 0;
				break;
			case 0:
				this->_p = this->_p->prev();
				if (!(this->_p))
					throw OutOfRangeException();
				break;
			default:
				throw OutOfRangeException();
			}
			return (result);
		}
		map_const_iterator &operator--() // 전위
		{
			switch (this->_margin)
			{
			case 1:
				this->_p = this->_root->last();
				this->_margin = 0;
				break;
			case 0:
				this->_p = this->_p->prev();
				if (!(this->_p))
					throw OutOfRangeException();
				break;
			default:
				throw OutOfRangeException();
			}
			return (*this);
		}

		const node_type getP() const
		{
			return this->_p;
		}
		const node_type getRoot() const
		{
			return this->_root;
		}
		int getMargin() const
		{
			return this->_margin;
		}
	};

	template <typename Key, typename T, class Compare>
	class map_rev_iterator;

	template <typename Key, typename T, class Compare>
	class map_rev_const_iterator;
}