#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector {
	
	public:
		class iterator {
			
		};

		class reverse_iterator {
			
		}

		typedef T value_type;
		typedef Alloc allocator_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		

	private:
		pointer _container;	
		size_type _container_size;
		size_type _container_length;
		allocator_type _allocator;

	public:
		explicit vector(const allocator_type& alloc = allocator_type()):
			_container(NULL),
			_container_size(0),
			_container_length(0),
			_allocator(alloc)
		{
			_container = _allocator.allocate(0);
		}

		explicit veector(size_type n, const value_type& val = value_type(),
						const allocator_type &alloc = allocator_type()):
			_container(NULL),
			_container_size(0),
			_container_length(0),
			_allocator(alloc)
		{
			_container = _allocator.allocate(0);
		}


		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last);
		
		void assign (size_type n, const value_type& val);

	};
}

#endif