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

	template <typename Key, typename T, class Compare>
	struct Mapnode
	{
		std::pair<Key, T> *val;
		Mapnode *parent;
		Mapnode *left;
		Mapnode *right;

		Mapnode(std::pair<Key, T> *v): val(v), parent(NULL), left(NULL), right(NULL) {}
		Mapnode(std::pair<Key, T> *v, Mapnode *p, Mapnode *l = NULL, Mapnode *r = NULL): val(v), parent(p), left(l), right(r) {}

		Mapnode *first()
		{
			Mapnode *target = this;
			while (target->left)
				target = target->left;
			return target;
		}

		Mapnode *last()
		{
			Mapnode *target = this;
			while (target->right)
				target = target->right;
			return target;
		}

		Mapnode *next()
		{
			Mapnode *target = this->right;
			if (target)
			{
				while (target->left)
					target = target->left;
				return target;
			}
			target = this->parent;
			Mapnode *prev = this;
			while (target && target->left != prev)
			{
				prev = target;
				target = target->parent;
			}
			return target;
		}

		Mapnode *prev()
		{
			Mapnode *target = this->left;
			if (target)
			{
				while (target->right)
					target = target->right;
				return target;
			}
			target = this->parent;
			Mapnode *prev = this;
			while (target && target->right != prev)
			{
				prev = target;
				target = target->parent;
			}
			return target;
		}

		void swap_position(Mapnode &src)
		{
			std::swap(this->parent, src.parent);
			std::swap(this->left, src.left);
			std::swap(this->right, src.right);
		}
	};

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