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