/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:26:44 by jobject           #+#    #+#             */
/*   Updated: 2022/02/03 21:13:18 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>
# include <memory>
# include "utils.hpp"
# include "VectorIterator.hpp"

namespace ft {
    template<class T,class Allocator = std::allocator<T> >
    class Vector {
        public:
            typedef T                                   		value_type;
            typedef Allocator                           		allocator_type;
            typedef std::size_t                         		size_type;
            typedef std::ptrdiff_t                      		difference_type;
            typedef T&                                 			reference;
            typedef const T&                            		const_reference;
            typedef T*                                  		pointer;
            typedef const T*                            		const_pointer;
            typedef class ft::VectorIterator<T>			    	iterator;
            typedef class ft::ConstVectorIterator<T>         	const_iterator;
            typedef class ft::ReverseVectorIterator<T>       	reverse_iterator;
            typedef class ft::ConstReverseVectorIterator<T>  	const_reverse_iterator;
        private:
            allocator_type  alloc;
            size_type       _capacity;
            size_type       _size;
			pointer			ptr;
			void ft_realloc(size_type new_capacity) {
				pointer tmp = alloc.allocate(new_capacity);
				for (size_type i = 0; i < _size; i++)
					alloc.construct(tmp + i, ptr[i]);
				size_type tmp_size = _size;
				delVector();
				_size = tmp_size;
				_capacity = new_capacity;
				ptr = tmp;
			}
			void delVector() {
				if (_capacity > 0) {
					for (size_type i = 0; i < _size; i++)
						alloc.destroy(ptr + i);
					alloc.deallocate(ptr, _capacity);
					_size = _capacity = 0;
				}
			}
        public:
			explicit Vector(const allocator_type & _alloc = allocator_type()) : alloc(_alloc), _capacity(20), _size(0)  { ptr = alloc.allocate(20); }
			explicit Vector(size_type count, const_reference value = value_type(),
				const allocator_type & _alloc = allocator_type()) : alloc(_alloc), _capacity(count), _size(count) {
					ptr = alloc.allocate(count);
					for (size_type i = 0; i < _size; i++)
						alloc.construct(ptr + i, value);
			}
			Vector(const Vector & other) { *this = other; }
			~Vector() { delVector(); }
			template<typename InputIt>
			Vector(InputIt first, InputIt last, const allocator_type & _alloc = allocator_type(), typename std::enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) :
				alloc(_alloc), _capacity(20), _size(0) {
				if (first > last)
					throw std::length_error("vector");
				int i = 0;
				ptr = alloc.allocate(_capacity);
				for (InputIt it = first; it != last; ++it, ++i, ++_size) {
					if (_size == _capacity)
						ft_realloc(_capacity * 2);
					alloc.construct(ptr + i, *it);
				}
			}
			Vector & operator=(const Vector & other) {
				if (this != &other) {
					// delVector();
					alloc = other.alloc;
					_capacity = other._capacity;
					_size = other._size;
					ptr = alloc.allocate(_capacity);
					for (int i = 0; i < _size; i++)
						alloc.construct(ptr + i, other[i]);
				}
				return *this;
			}
			void assign(size_type count, const_reference value) {
				delVector();
				ptr = alloc.allocate(count);
				_size = _capacity = count;
				for (int i = 0; i < count; i++)
					alloc.construct(ptr + i, value);
			}
			template<class InputIt>
			void assign(InputIt first, InputIt last, typename std::enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) {
				delVector();
				for (InputIt it = first; it != last; ++it, ++_capacity);
				ptr = alloc.allocate(_capacity);
				_size = _capacity;
				for (int i = 0; first != last; ++first, ++i)
					alloc.construct(ptr + i, *first);
			}
			allocator_type get_allocator() const { return alloc; }
			reference at(size_type pos) {
				if (pos > _size)
					throw std::out_of_range("Out of range");
				return ptr[pos];
			}
			const_reference at(size_type pos) const {
				if (pos > _size)
					throw std::out_of_range("Out of range");
				return ptr[pos];
			}
			reference operator[](size_type pos) { return ptr[pos]; }
			const_reference operator[](size_type pos) const { return ptr[pos]; }
			reference front() { return ptr[0]; }
			const_reference front() const { return ptr[0]; }
			reference back() { return ptr[_size - 1]; }
			const_reference back() const { return ptr[_size - 1]; }
			pointer data() { return _size ? ptr : nullptr; }
			const_pointer data() const { return _size ? ptr : nullptr; }
			iterator begin() { return iterator(ptr); }
			const_iterator begin() const { return const_iterator(ptr); }
			iterator end() { return iterator(ptr + _size); }
			const_iterator end() const { return const_iterator(ptr + _size); }
			reverse_iterator rbegin() { return reverse_iterator(ptr + _size - 1); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(ptr + _size - 1); }
			reverse_iterator rend() { return reverse_iterator(ptr - 1); }
			const_reverse_iterator rend() const { return const_reverse_iterator(ptr - 1); }
			bool empty() const {return !_size; }
			size_type size() const { return _size; }
			size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(size_type); }
			size_type capacity() const { return _capacity; }
			void reserve(size_type new_cap) {
				if (new_cap > max_size())
					throw std::length_error("Out of range");
				if (new_cap > _capacity)
					ft_realloc(new_cap);
			}
			void clear() { erase(begin(), end()); }
			iterator insert(iterator pos, const_reference value) {
				size_type i = 0;
				iterator it;
				for (it = begin(); it != end() && it != pos; ++it, i++);
				if (_size + 1 > _capacity)
					ft_realloc(_capacity * 2);
				if (it != end()) {
					++_size;
					for (size_type j = _size; j != i; j--) {
						alloc.destroy(ptr + j);
						alloc.construct(ptr + j, ptr[j - 1]);
					}
					alloc.destroy(ptr + i);
					alloc.construct(ptr + i, value); }
				// } else {
				// 	while (i >= _capacity)
				// 		ft_realloc(_capacity * 2);
				// 	ptr[i] = value;
				// 	_size = i + 1;
				// }
				return iterator(ptr + i);
			}
			void insert(iterator pos, size_type count, const_reference value) {
				while (count--)
					pos = insert(pos, value);
			}
			template<class InputIt>
			void insert(iterator pos, InputIt first, InputIt last, typename std::enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) {
				while (first != last) {
					pos = insert(pos, *first) + 1;
					++first;
				}
			}
			iterator erase(iterator pos) {
				size_type i = 0;
				iterator it;
				for (it = begin(); it != end() && it != pos; ++it, i++);
				if (it == end()) {
					pop_back();
					return iterator(ptr + _size);
				}
				for (int j = i; j < _size - 1; j++)
					ptr[j] = ptr[j + 1];
				--_size;
				return iterator(ptr + i);
			}
			iterator erase(iterator first, iterator last) {
				for (; first != last; last--)
					erase(first);
				return first;
			}
			void push_back(const_reference value) {
				if (_size + 1 > _capacity)
					reserve(_capacity ? _capacity * 2 : 20);
				alloc.construct(ptr + _size, value);
				++_size;
			}
			void pop_back() {
				if (!empty())
					--_size;
			}
			void resize(size_type count, value_type value = value_type()) {
				if (count < _size)
					for (size_type tmp = _size; tmp != count; tmp--)
						pop_back();
				else
					for (size_type tmp = _size; tmp != count; tmp++)
						push_back(value);
			}
			void swap(Vector & other) {
				ft::swap(alloc, other.alloc);
				ft::swap(ptr, other.ptr);
				ft::swap(_size, other._size);
				ft::swap(_capacity, other._capacity);
			}
    };
	
	template<class T, class Allocator>
	bool operator==(const ft::Vector<T, Allocator> & lhs, const ft::Vector<T, Allocator> & rhs) {
		if (lhs.size() == rhs.size()) {
			size_t i = 0;
			for (; i < lhs.size() && lhs[i] == rhs[i]; i++);
			if (i == lhs.size())
				return true;
		}
		return false;
	}
	
	template<class T, class Allocator>
	bool operator!=(const ft::Vector<T, Allocator> & lhs, const ft::Vector<T, Allocator> & rhs) { return !(lhs == rhs); }
	
	template<class T, class Allocator>
	bool operator<(const ft::Vector<T, Allocator> & lhs, const ft::Vector<T, Allocator> & rhs) {
		int size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		for (int i = 0; i < size; i++)
			if (rhs[i] != lhs[i])
				return lhs[i] < rhs[i];
		return lhs.size() < rhs.size();
	}

	template<class T, class Allocator>
	bool operator<=(const ft::Vector<T, Allocator> & lhs, const ft::Vector<T, Allocator> & rhs) {return lhs == rhs || lhs < rhs; }

	template<class T, class Allocator>
	bool operator>(const ft::Vector<T, Allocator> & lhs, const ft::Vector<T, Allocator> & rhs)	{return !(lhs <= rhs); }

	template<class T, class Allocator>
	bool operator>=(const ft::Vector<T, Allocator> & lhs, const ft::Vector<T, Allocator> & rhs)	{return !(lhs < rhs); }

	template<class T, class Allocator>
	void swap(ft::Vector<T, Allocator> & lhs, ft::Vector<T, Allocator> & rhs) { lhs.swap(rhs); }
}

#endif