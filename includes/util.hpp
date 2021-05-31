#pragma once

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
		AVLNode(ft::pair<Key, T> *v): val(v), parent(NULL), left(NULL), right(NULL), height(1) {}
		AVLNode(ft::pair<Key, T> *v, AVLNode *p, AVLNode *l = NULL, AVLNode *r = NULL, size_t h = 0): val(v), parent(p), left(l), right(r), height(h) {}

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

		void swap_position(AVLNode &src)
		{
			std::swap(this->parent, src.parent);
			std::swap(this->left, src.left);
			std::swap(this->right, src.right);
			std::swap(this->height, src.height);
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