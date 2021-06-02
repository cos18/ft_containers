#pragma once
#include <iostream>
#include <stdio.h>

namespace ft
{
	template <typename T>
	struct Node
	{
		T val;
		Node *prev;
		Node *next;

		Node() {}

		template<typename cT>
		Node(Node<cT> const &const_src)
		{
			this->val = const_cast<T>(const_src.val);
			this->prev = const_src.prev;
			this->next = const_src.next;
		}
	};

	template <typename T1, typename T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair(): first(first_type()), second(second_type()) {}
		template<class U, class V>
		pair(const pair<U,V>& pr): first(pr.first), second(pr.second) {}
		template<class U, class V>
		pair(const std::pair<U,V>& pr): first(pr.first), second(pr.second) {}
		pair(const first_type& a, const second_type& b): first(a), second(b) {}

		pair &operator=(const pair &rhs)
		{
			this->first = rhs.first;
			this->second = rhs.second;
			return *this;
		}
	};

	// Refernce: http://www.cplusplus.com/reference/utility/pair/operators/
	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	// Refernce: http://www.cplusplus.com/reference/utility/make_pair/
	template <class T1,class T2>
	ft::pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( ft::pair<T1,T2>(x,y) );
	}

	template <typename Key, typename T, class Compare>
	struct AVLNode
	{
		ft::pair<const Key, T> *val;
		AVLNode *parent;
		AVLNode *left;
		AVLNode *right;
		size_t height;

		AVLNode(): val(NULL), parent(NULL), left(NULL), right(NULL), height(1) {}
		AVLNode(ft::pair<Key, T> v): parent(NULL), left(NULL), right(NULL), height(1)
		{
			this->val = new ft::pair<const Key, T>(v.first, v.second);
		}
		AVLNode(ft::pair<Key, T> v, AVLNode *p, AVLNode *l = NULL, AVLNode *r = NULL, size_t h = 1): parent(p), left(l), right(r), height(h)
		{
			this->val = new ft::pair<const Key, T>(v.first, v.second);
		}

		~AVLNode()
		{
			delete this->val;
		}

		AVLNode *first()
		{
			AVLNode *target = this;
			while (target->left)
				target = target->left;
			return target;
		}

		AVLNode *last()
		{
			AVLNode *target = this;
			while (target->right)
				target = target->right;
			return target;
		}

		AVLNode *next()
		{
			AVLNode *target = this->right;
			if (target)
			{
				while (target->left)
					target = target->left;
				return target;
			}
			target = this->parent;
			AVLNode *prev = this;
			while (target && target->left != prev)
			{
				prev = target;
				target = target->parent;
			}
			return target;
		}

		AVLNode *prev()
		{
			AVLNode *target = this->left;
			if (target)
			{
				while (target->right)
					target = target->right;
				return target;
			}
			target = this->parent;
			AVLNode *prev = this;
			while (target && target->right != prev)
			{
				prev = target;
				target = target->parent;
			}
			return target;
		}

		void swap_position(AVLNode *src, AVLNode *root)
		{
			if (this->parent && this->parent != src)
			{
				if (this->parent->left == this)
					this->parent->left = src;
				else
					this->parent->right = src;
			}
			else if (!(this->parent))
				root->left = root->right = src;
			if (src->parent && src->parent != this)
			{
				if (src->parent->left == src)
					src->parent->left = this;
				else
					src->parent->right = this;
			}
			else if (!(src->parent))
				src->left = src->right = this;
			if (this->left && this->left != src)
				this->left->parent = src;
			if (this->right && this->right != src)
				this->right->parent = src;
			if (src->left && src->left != this)
				src->left->parent = this;
			if (src->right && src->right != this)
				src->right->parent = this;
			if (this->parent == src)
			{
				this->parent = src->parent;
				src->parent = this;
			}
			else if (src->parent == this)
			{
				src->parent = this->parent;
				this->parent = src;
			}
			else
				std::swap(this->parent, src->parent);
			if (this->left == src)
			{
				this->left = src->left;
				src->left = this;
			}
			else if (src->left == this)
			{
				src->left = this->left;
				this->left = src;
			}
			else
				std::swap(this->left, src->left);
			if (this->right == src)
			{
				this->right = src->right;
				src->right = this;
			}
			else if (src->right == this)
			{
				src->right = this->right;
				this->right = src;
			}
			else
				std::swap(this->right, src->right);
		}

		void reset_position(AVLNode *parent, AVLNode *left, AVLNode *right)
		{
			this->parent = parent;
			this->left = left;
			this->right = right;
		}

		void update_height(bool with_parent)
		{
			this->height = (this->left == NULL ? 1 : this->left->height + 1);
			if (this->right)
				this->height = (this->height > this->right->height + 1 ? this->height : this->right->height + 1);
			if (with_parent && this->parent != NULL)
				this->parent->update_height(with_parent);
		}

		int check_rotate(AVLNode *root)
		{
			int diff = (this->left ? this->left->height : 0);
			diff -= (this->right ? this->right->height : 0);
			if (-2 < diff && diff < 2)
				return (this->parent ? this->parent->check_rotate(root) : 0);
			AVLNode *target_right = NULL, *target_left = NULL, *target_root = NULL, *ll = NULL, *lr = NULL, *rl = NULL, *rr = NULL;
			switch (diff)
			{
				case 2:
				{
					target_right = this;
					rr = this->right;
					int diff_left = this->left->left ? this->left->left->height : 0;
					diff_left -= (this->left->right ? this->left->right->height : 0);
					switch (diff_left)
					{
						case -1:
							target_left = target_right->left;
							target_root = target_left->right;
							lr = target_root->left;
							break;
						case 1:
						default:
							target_root = target_right->left;
							target_left = target_root->left;
							lr = target_left->right;
							break;
					}
					ll = target_left->left;
					rl = target_root->right;
					break;
				}
				case -2:
				{
					target_left = this;
					ll = this->left;
					int diff_right = this->right->left ? this->right->left->height : 0;
					diff_right -= (this->right->right ? this->right->right->height : 0);
					switch (diff_right)
					{
						case 1:
							target_right = target_left->right;
							target_root = target_right->left;
							rl = target_root->right;
							break;
						case -1:
						default:
							target_root = target_left->right;
							target_right = target_root->right;
							rl = target_right->left;
							break;
					}
					lr = target_root->left;
					rr = target_right->right;
					break;
				}
				default:
					break;
			}
			target_root->reset_position(this->parent, target_left, target_right);
			if (!this->parent)
			{
				root->left = target_root;
				root->right = target_root;
			}
			else
			{
				if (this->parent->left == this)
					this->parent->left = target_root;
				else
					this->parent->right = target_root;
			}
			target_left->reset_position(target_root, ll, lr);
			target_right->reset_position(target_root, rl, rr);
			if (ll)
				ll->parent = target_left;
			if (lr)
				lr->parent = target_left;
			if (rl)
				rl->parent = target_right;
			if (rr)
				rr->parent = target_right;
			target_left->update_height(false);
			target_right->update_height(true);
			return (target_root->parent ? target_root->parent->check_rotate(root) : 0);
		}
	};

	template <typename Key, typename T, class Compare>
	bool check_AVL_equal(AVLNode<Key, T, Compare> *x, AVLNode<Key, T, Compare> *y)
	{
		if (x == NULL && y == NULL)
			return true;
		if (x == NULL || y == NULL)
			return false;
		if (Compare()(x->val->first, y->val->first) ||
			Compare()(y->val->first, x->val->first) ||
			x->val->second != y->val->second)
			return false;
		return check_AVL_equal(x->left, y->left) && check_AVL_equal(x->right, y->right);
	}

	template <class It1, class It2>
	bool	lexicographical_compare(It1 begin1, It1 end1, It2 begin2, It2 end2)
	{
		while (begin1 != end1 && begin2 != end2 && *begin1 == *begin2)
		{
			++begin1;
			++begin2;
		}
		if (begin1 == end1)
			return (begin2 != end2);
		if (begin2 == end2)
			return (false);
		return (*begin1 < *begin2);
	}

	template <bool B>
	struct enable_if {};

	template <>
	struct enable_if<true>
	{
		typedef int type;
	};

	template <class T>
	struct is_integral
	{
		static const bool value = false;
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<short>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long long>
	{
		static const bool value = true;
	};
}