#pragma once

#include <memory>
#include "map_iterator.hpp"
#include "util.hpp"

namespace ft
{
	template < class Key,
			   class T,
			   class Compare = std::less<Key>,
			   class Allocator = std::allocator< ft::pair<const Key, T> >
			   >
	class map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		class												value_compare
		{
		protected:
			Compare comp;

		public:
			value_compare (Compare c) : comp(c) {}
			typedef bool									result_type;
			typedef value_type								first_argument_type;
			typedef value_type								second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef ft::map_iterator<Key, T, Compare>			iterator;
		typedef ft::map_const_iterator<Key, T, Compare>		const_iterator;
		typedef ft::map_rev_iterator<Key, T, Compare>		reverse_iterator;
		typedef ft::map_rev_const_iterator<Key, T, Compare>	const_reverse_iterator;

		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef AVLNode<Key, T, Compare>*					node_type;

	private:
		node_type		_container;
		key_compare		_key_cmp;
		allocator_type	_allocator;
		size_type		_size;

		node_type init_node(value_type val, node_type parent)
		{
			node_type result = new AVLNode<Key, T, Compare>;
			result->val = new value_type(val);
			result->parent = parent;
			return result;
		}

		void deallocate_node_recur(node_type target)
		{
			if (target == NULL)
				return;
			if (target->left)
				deallocate_node_recur(target->left);
			if (target->right)
				deallocate_node_recur(target->right);
			delete target->val;
			delete target;
		}

	public:
		// (constructor)
		explicit map(const key_compare& comp = key_compare(),
					 const allocator_type& alloc = allocator_type()):
					 _container(NULL),
					 _key_cmp(comp),
					 _allocator(alloc),
					 _size(0)
		{
			this->_container = init_node(value_type(), NULL);
		}
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type tmp = 0):
			_container(NULL),
			_key_cmp(comp),
			_allocator(alloc),
			_size(0)
		{
			(void)tmp;
			this->_container = init_node(value_type(), NULL);
			this->insert(first, last);
		}
		map(const map& x):
			_container(NULL),
			_key_cmp(key_compare()),
			_allocator(allocator_type()),
			_size(0)
		{
			this->_container = init_node(value_type(), NULL);
			*this = x;
		}

		// (destructor)
		~map()
		{
			this->clear();
			delete this->_container->val;
			delete this->_container;
		}

		map& operator=(const map& x)
		{
			this->clear();
			this->insert(x.begin(), x.end());
			return *this;
		}

		// Iterators
		iterator begin()
		{
			if (this->empty())
				return iterator(NULL, this->_container, true);
			return iterator(this->_container->first(), this->_container);
		}
		const_iterator begin() const
		{
			if (this->empty())
				return iterator(NULL, this->_container, true);
			return const_iterator(this->_container->first(), this->_container);
		}
		iterator end()
		{
			return iterator(NULL, this->_container, true);
		}
		const_iterator end() const
		{
			return const_iterator(NULL, this->_container, true);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(this->end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(this->end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(this->begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(this->begin());
		}

		// Capacity
		bool empty() const
		{
			return (this->_size == 0);
		}
		size_type size() const
		{
			return this->_size;
		}
		size_type max_size() const
		{
			return (std::numeric_limits<difference_type>::max() / (sizeof(AVLNode<Key, T, Compare>) / 2 ?: 1));
		}

		// Element access
		mapped_type& operator[](const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
		}

		// Modifiers
		ft::pair<iterator,bool> insert(const value_type& val)
		{
			if (this->_size == 0)
			{
				delete this->_container->val;
				this->_container->val = new value_type(val);
				this->_size += 1;
				return ft::pair<iterator,bool>(iterator(this->_container, this->_container), true);
			}
			node_type target = this->_container;
			while (true)
			{
				if (this->_key_cmp(val.first, target->val->first) == false &&
					this->_key_cmp(target->val->first, val.first) == false)
					return ft::pair<iterator,bool>(iterator(target, this->_container), false);
				if (this->_key_cmp(val.first, target->val->first))
				{
					if (target->left)
					{
						target = target->left;
						continue;
					}
					target->left = init_node(val, target);
					this->_size += 1;
					return ft::pair<iterator,bool>(iterator(target->left, this->_container), true);
				}
				if (target->right)
				{
					target = target->right;
					continue;
				}
				target->right = init_node(val, target);
				this->_size += 1;
				return ft::pair<iterator,bool>(iterator(target->right, this->_container), true);
			}
		}
		iterator insert(iterator position, const value_type& val)
		{
			(void)position;
			return this->insert(val).first;
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type tmp = 0)
		{
			(void)tmp;
			while (first != last)
			{
				this->insert(*first);
				++first;
			}
		}
		void erase(iterator position);
		size_type erase(const key_type& k);
		void erase(iterator first, iterator last);
		void swap(map& x)
		{
			std::swap(this->_allocator, x._allocator);
			std::swap(this->_container, x._container);
			std::swap(this->_size, x._size);
		}
		void clear()
		{
			deallocate_node_recur(this->_container->left);
			deallocate_node_recur(this->_container->right);
			this->_container->left = NULL;
			this->_container->right = NULL;
			delete this->_container->val;
			this->_container->val = new value_type;
			this->_size = 0;
		}

		// Observers
		key_compare key_comp() const
		{
			return (key_compare());
		}
		value_compare value_comp() const
		{
			return (value_compare(key_compare()));
		}

		// Operations
		iterator find(const key_type& k)
		{
			if (this->empty())
				return this->end();
			node_type target = this->_container;
			while (true)
			{
				if (this->_key_cmp(k, target->val->first) == false &&
					this->_key_cmp(target->val->first, k) == false)
					return iterator(target, this->_container);
				target = (this->_key_cmp(target->val->first, k) ? target->left : target->right);
				if (!target)
					return this->end();
			}
		}
		const_iterator find(const key_type& k) const
		{
			if (this->empty())
				return this->end();
			node_type target = this->_container;
			while (true)
			{
				if (this->_key_cmp(k, target->val->first) == false &&
					this->_key_cmp(target->val->first, k) == false)
					return iterator(target, this->_container);
				target = (this->_key_cmp(target->val->first, k) ? target->left : target->right);
				if (!target)
					return this->end();
			}
		}
		size_type count(const key_type& k) const
		{
			iterator it = this->find(k);
			return (it == this->end() ? 0 : 1);
		}
		iterator lower_bound(const key_type& k);
		const_iterator lower_bound(const key_type& k) const;
		iterator upper_bound(const key_type& k);
		const_iterator upper_bound(const key_type& k) const;
		ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
		ft::pair<iterator,iterator> equal_range(const key_type& k);
	};
}