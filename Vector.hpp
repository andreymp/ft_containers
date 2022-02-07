/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:26:44 by jobject           #+#    #+#             */
/*   Updated: 2022/02/07 21:01:43 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>
# include <memory>
# include "utils.hpp"
# include "VectorIterator.hpp"

# include <iostream>

namespace ft {
    template<class T,class Allocator = std::allocator<T> >
    class Vector {
        public:
            typedef T                                 					value_type;
            typedef Allocator                         					allocator_type;
            typedef std::size_t                       					size_type;
            typedef T&                            						reference;
            typedef const T&                          					const_reference;
            typedef T*                                					pointer;
            typedef const T*                          					const_pointer;
            typedef class ft::VectorIterator<T>			  				iterator;
            typedef class ft::ConstVectorIterator<T>      				const_iterator;
            typedef class ft::ReverseVectorIterator<T>      			reverse_iterator;
            typedef class ft::ConstReverseVectorIterator<T>  			const_reverse_iterator;
			typedef typename ft::VectorIterator<T>::difference_type		difference_type;
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
			explicit Vector(const allocator_type & _alloc = allocator_type()) : alloc(_alloc), _capacity(0), _size(0)  {}
			explicit Vector(size_type count, const_reference value = value_type(),
				const allocator_type & _alloc = allocator_type()) : alloc(_alloc), _capacity(count), _size(count) {
					ptr = alloc.allocate(count);
					for (size_type i = 0; i < _size; i++)
						alloc.construct(ptr + i, value);
			}
			Vector(const Vector & other) : alloc(allocator_type()), _capacity(0), _size(0), ptr(nullptr) { *this = other; }
			~Vector() { delVector(); }
			template<typename InputIt>
			Vector(InputIt first, InputIt last, const allocator_type & _alloc = allocator_type(), typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) :
				alloc(_alloc), _capacity(20), _size(0) {
				if (first > last)
					throw std::length_error("vector");
				ptr = alloc.allocate(_capacity);
				assign(first, last);
			}
			Vector & operator=(const Vector & other) {
				if (this != &other) {
					for (size_type i = 0; i < _size; i++)
						alloc.destroy(ptr + i);
					_size = other._size;
					if (_size > _capacity) {
						if (_capacity)
							alloc.deallocate(ptr, _capacity);
						_capacity = _size;
						ptr = alloc.allocate(_capacity);
					}
					for (int i = 0; i < _size; i++)
						alloc.construct(ptr + i, other[i]);
				}
				return *this;
			}
			void assign(size_type count, const_reference value) {
				if (!_capacity)
					ptr = alloc.allocate(count);
				for (size_type i = 0; i < _size; i++)
					alloc.destroy(ptr + i);
				if (_capacity < count) {
					alloc.deallocate(ptr, _capacity);
					_capacity = count;
					ptr = alloc.allocate(_capacity);
				}
				_size = count;
				for (int i = 0; i < count; i++) {
					alloc.construct(ptr + i, value);
				}
			}
			template<class InputIt>
			void assign(InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) {
				if (first > last)
					throw std::length_error("vector");
				for (size_type i = 0; i < _size; i++)
					alloc.destroy(ptr + i);
				int count = 0;
				for (InputIt it = first; it != last; ++it, ++count);
				if (_capacity < count) {
					alloc.deallocate(ptr, _capacity);
					_capacity = count;
					ptr = alloc.allocate(_capacity);
				}
				_size = count;
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
			void clear() { while (_size) pop_back(); }
			iterator insert(iterator pos, const_reference value) {
				size_type indexToInsert = 0;
				for (iterator it = begin(); it != pos; ++it, ++indexToInsert);
				if (!_capacity)
					reserve(1);
				if (_size == _capacity)
					reserve(_capacity * 2);
				for (size_type i = _size; i > indexToInsert; --i) {
					alloc.destroy(ptr + i);
					alloc.construct(ptr + i, ptr[i - 1]);
				}
				alloc.destroy(ptr + indexToInsert);
				alloc.construct(ptr + indexToInsert, value);
				++_size;
				return iterator(ptr + indexToInsert);
			}
			void insert(iterator pos, size_type count, const_reference value) {
				size_type indexToInsert = 0;
				for (iterator it = begin(); it != pos; ++it, ++indexToInsert);
				if (!_capacity)
					reserve(count);
				if (_size + count > _capacity)
					reserve(_size + count > _capacity * 2 ? _size + count : _capacity * 2);
				for (size_type i = _size; i > indexToInsert; --i) {
					alloc.destroy(ptr + i + count - 1);
					alloc.construct(ptr + i + count - 1, ptr[i - 1]);
				}
				for (size_type i = 0; i < count; ++i) {
					alloc.destroy(ptr + indexToInsert);
					alloc.construct(ptr + indexToInsert++, value);
				}
				_size += count;
			}
			template<class InputIt>
			void insert(iterator pos, InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) {
				size_type range = 0;
				size_type indexToInsert = 0;
				for (InputIt it = first; it != last; ++it, ++range);
				for (iterator it = begin(); it != pos; ++it, ++indexToInsert);
				if (_size + range > _capacity) {
					size_type newCap = _size + range > _capacity * 2 ? _size + range : _capacity * 2;
					pointer newArr = alloc.allocate(newCap);
					for (size_type i = 0; i < indexToInsert; i++)
						alloc.construct(newArr + i, ptr[i]);
					try {
						for (size_type i = 0; i < range; ++i, ++first)
							alloc.construct(newArr + indexToInsert + i, *first);
					} catch (...) {
						for (size_type i = 0; i < indexToInsert + range; ++i)
							alloc.destroy(newArr + i);
						alloc.deallocate(newArr, newCap);
						throw "vector";
					}
					for (size_type i = indexToInsert; i < _size; ++i)
						alloc.construct(newArr + range + i, ptr[i]);
					for (size_type i = 0; i < _size; ++i)
						alloc.destroy(ptr + i);
					alloc.deallocate(ptr, _capacity);
					_size += range;
					_capacity = newCap;
					ptr = newArr;
				} else {
					for (size_type i = _size; i > indexToInsert; --i) {
						alloc.destroy(ptr + i + range - 1);
						alloc.construct(ptr + i + range - 1, ptr[i - 1]);
					}
					for (size_type i = indexToInsert; i != indexToInsert + range; ++i) {
						alloc.construct(ptr + i, *first);
						++first;
					}
					_size += range;
				}
			}
			iterator erase(iterator pos) {
				size_type i = 0;
				iterator it = begin();
				for (; it != end() && it != pos; ++it, ++i);
				if (it == end()) {
					pop_back();
					return iterator(ptr + _size);
				}
				for (int j = i; j < _size - 1; j++) {
					alloc.destroy(ptr + j);
					alloc.construct(ptr + j, ptr[j + 1]);
				}
				--_size;
				return iterator(ptr + i);
			}
			iterator erase(iterator first, iterator last) {
				if (first > last)
					throw std::length_error("vector");
				size_type indexOfFirst = 0;
				size_type indexOfLast = _size;
				for (iterator it = begin(); it != first; ++it, ++indexOfFirst);
				for (iterator it = end(); it != last; --it, --indexOfLast);
				if (last == end()) {
					for (; indexOfLast != indexOfFirst; indexOfLast--)
						pop_back();
					return end();
				}
				size_type range = indexOfLast - indexOfFirst;
				for (int i = indexOfFirst; indexOfLast < _size; ++i) {
					alloc.destroy(ptr + i);
					alloc.construct(ptr + i, ptr[indexOfLast++]);
				}
				_size -= range;
				return iterator(ptr + indexOfFirst);
			}
			void push_back(const_reference value) {
				if (_size == _capacity)
					reserve(_capacity ? _capacity * 2 : 1);
				alloc.construct(ptr + _size++, value);
			}
			void pop_back() {
				if (!empty())
					alloc.destroy(ptr + _size--);
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
				std::swap(ptr, other.ptr);
				std::swap(_capacity, other._capacity);
				std::swap(_size, other._size);
				std::swap(alloc, other.alloc);
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
}

namespace std {
	template<class T, class Allocator>
	void swap(ft::Vector<T, Allocator> & lhs, ft::Vector<T, Allocator> & rhs) { lhs.swap(rhs); }
}

#endif