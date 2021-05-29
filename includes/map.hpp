#pragma once

#include <memory>
#include "map_iterator.hpp"
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
		class												value_compare
		{
			friend class map;

		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

		public:
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
		typedef Mapnode<Key, T, Compare>*					node_type;

	private:
		node_type		_container;
		key_compare		_key_cmp;
		allocator_type	_allocator;
		size_type		_size;

		node_type init_node(value_type val, node_type parent, node_type left, node_type right)
		{
			node_type result = this->_allocator.allocate(1);
			result->val = val;
			result->parent = parent;
			result->left = left;
			result->right = right;
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
			this->_allocator.deallocate(target, 1);
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
			this->_container = init_node(value_type(), NULL, NULL, NULL);
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
			this->_container = init_node(value_type(), NULL, NULL, NULL);
			this->insert(first, last);
		}
		map(const map& x)
		{
			*this = x;
		}

		// (destructor)
		~map()
		{
			this->clear();
			this->_allocator.deallocate(this->_container, 1);
		}

		map& operator=(const map& x)
		{
			this->clear();
			this->insert(x.begin(), x.end());
		}

		// Iterators
		iterator begin()
		{
			return iterator(this->_container->first(), this->_container);
		}
		const_iterator begin() const
		{
			return const_iterator(this->_container->first(), this->_container);
		}
		iterator end()
		{
			return iterator(NULL, this->_container, 1);
		}
		const_iterator end() const
		{
			return const_iterator(NULL, this->_container, 1);
		}
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

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
			return (std::numeric_limits<size_type>::max() / sizeof(value_type));
		}

		// Element access
		mapped_type& operator[](const key_type& k);

		// Modifiers
		std::pair<iterator,bool> insert(const value_type& val)
		{
			if (this->_size == 0)
			{
				this->_container->val = val;
				this->_size += 1;
				return;
			}
			node_type target = this->_container;
			while (true)
			{
				if (this->_key_cmp(val.first, target->val.first) == false &&
					this->_key_cmp(target->val.first, val.first) == false)
					return std::pair<iterator,bool>(iterator(target, this->_container), false);
				if (this->_key_cmp(val.first, target->val.first))
				{
					if (target->left)
					{
						target = target->left;
						continue;
					}
					target->left = init_node(val, target, NULL, NULL);
					this->_size += 1;
					return std::pair<iterator,bool>(iterator(target->left, this->_container), false);
				}
				if (target->right)
				{
					target = target->right;
					continue;
				}
				target->right = init_node(val, target, NULL, NULL);
				this->_size += 1;
				return std::pair<iterator,bool>(iterator(target->right, this->_container), false);
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
			this->_size = 0;
		}

		// Observers
		key_compare key_comp() const
		{
			return (Compare());
		}
		value_compare value_comp() const
		{
			return (value_compare());
		}

		// Operations
		iterator find(const key_type& k)
		{
			if (this->empty())
				return this->end();
			node_type target = this->_container;
			while (true)
			{
				if (this->_key_cmp(k, target->val.first) == false &&
					this->_key_cmp(target->val.first, k) == false)
					return iterator(target);
				target = (this->_key_cmp(target->val.first, k) ? target->left : target->right);
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
				if (this->_key_cmp(k, target->val.first) == false &&
					this->_key_cmp(target->val.first, k) == false)
					return iterator(target);
				target = (this->_key_cmp(target->val.first, k) ? target->left : target->right);
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
		std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
		std::pair<iterator,iterator> equal_range(const key_type& k);
	};
}