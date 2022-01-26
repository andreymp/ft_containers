/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:26:44 by jobject           #+#    #+#             */
/*   Updated: 2022/01/26 21:47:51 by jobject          ###   ########.fr       */
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
            typedef T                                   value_type;
            typedef Allocator                           allocator_type;
            typedef std::size_t                         size_type;
            typedef std::ptrdiff_t                      difference_type;
            typedef T&                                  reference;
            typedef const T&                            const_reference;
            typedef T*                                  pointer;
            typedef const T*                            const_pointer;
            typedef ft::VectorIterator<T>               iterator;
            typedef ft::ConstVectorIterator<T>          const_iterator;
            typedef ft::ReverseVectorIterator<T>        reverse_iterator;
            typedef ft::ConstReverseVectorIterator<T>   const_reverse_iterator;
        private:
            allocator_type  alloc;
            size_type       capacity;
            size_type       size;
			pointer			ptr;
			void ft_realloc(size_type new_capacity) {
				pointer	tmp = alloc.allocate(new_capacity);
				for (int i=0; i < size; i++)
					tmp[i] = ptr[i];
				alloc.deallocate(ptr, capacity);
				capacity = new_capacity;
				ptr = tmp;
			}
        public:
            Vector() : capacity(0), size(0), alloc(allocator_type()) { ptr = alloc.allocate(0); }
			Vector(const allocator_type & _alloc) : capacity(0), size(0), alloc(_alloc) { ptr = alloc.allocate(0); }
			explicit Vector(size_type count, const_reference value = value_type(),
				const allocator_type & _alloc = allocator_type()) : alloc(_alloc), capacity(count), size(0) {
					ptr = alloc.allocate(size);
					for (int i = 0; i < size; i++)
						ptr[i] = value;
			}
			explicit Vector(size_type count) : alloc(allocator_type()), capacity(count), size(0) { ptr = alloc.allocate(count); }
			template<class InputIt>
			Vector(InputIt first, InputIt last, const allocator_type & _alloc = allocator_type()) :
				alloc(_alloc), capacity(0), size(0) {
				for (InputIt tmp = first; tmp != last; ++size, ++tmp);
				capacity = size;
				ptr = alloc.allocate(capacity);
				for (int i = 0; i < size && first != last, ++first, ++i)
					ptr[i] = first;
			}
			Vector(const Vector & other) : Vector() { *this = other; }
			~Vector() { alloc.deallocate(ptr, capacity); }
			Vector & operator=(const Vector & other) {
				if (this != &other) {
					if (ptr)
						alloc.deallocate(ptr, capacity);
					alloc = other.alloc;
					capacity = other.capacity;
					size = other.size;
					ptr = alloc.allocate(capacity);
					for (int i = 0; i < size; i++)
						ptr[i] = other[i];
				}
				return *this;
			}
			void assign(size_type count, const_reference value) {
				if (ptr)
					alloc.dealocate(ptr, capacity);
				size = capacity = count;
				ptr = alloc.allocate(capacity);
				for (int i = 0; i < size; i++)
					ptr[i] = value;
			}
			template<class InputIt>
			void assign(InputIt first, InputIt last) {
				if (ptr)
					alloc.dealocate(ptr, capacity);
				size = capacity = 0;
				for (InputIt tmp = first; tmp != last; ++size, ++tmp);
				capacity = size;
				ptr = alloc.allocate(capacity);
				for (int i = 0; i < size && first != last, ++first, ++i)
					ptr[i] = first;
			}
			allocator_type get_allocator() const { return alloc; }
			reference at(size_type pos) {
				if (pos > size)
					throw std::out_of_range();
				return ptr[pos];
			}
			const_reference at(size_type pos) const {
				if (pos > size)
					throw std::out_of_range();
				return ptr[pos];
			}
			reference operator[](size_type pos) { return ptr[pos]; }
			const_reference operator[](size_type pos) const { return ptr[pos]; }
			reference front() { return ptr[0]; }
			const_reference front() const { return ptr[0]; }
			reference back() { return ptr[size - 1]; }
			const_reference back() const { return ptr[size - 1]; }
			pointer data() { return size ? ptr : nullptr; }
			const_pointer data() const { return size ? ptr : nullptr; }
			iterator begin() { return iterator(ptr); }
			const_iterator begin() const { return const_iterator(ptr); }
			iterator end() { return iterator(ptr + size); }
			const_iterator end() const { return const_iterator(ptr + size); }
			reverse_iterator rbegin() { return reverse_iterator(ptr + size - 1); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(ptr + size - 1); }
			reverse_iterator rend() { return reverse_iterator(ptr - 1); }
			const_reverse_iterator rend() const { return const_reverse_iterator(ptr - 1); }
			bool empty() const {return !size; }
			size_type size() const { return size; }
			size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(size_type); }
			size_type capacity() const { return capacity; }
			void reserve(size_type new_cap) {
				if (new_cap > max_size())
					throw std::length_error();
				if (new_cap > capacity)
					ft_realloc(new_cap);
			}
			void clear() { erase(begin(), end()); }
			iterator insert(iterator pos, const_reference value) {
				size_type i = pos - begin();
				if (size == capacity)
					ft_realloc(capacity * 2);
				if (i < size) {
					++size;
					for (int j = size - 1; j != i; j--)
						ptr[j] = ptr[j - 1]
					ptr[i] = value;
				} else {
					while (i >= capacity)
						ft_realloc(capacity * 2);
					ptr[i] = value;
					size = i + 1;
				}
				return iterator(ptr + i);
			}
			void insert(iterator pos, size_type count, const_reference value) {
				while (n--)
					pos = insert(pos, value);
			}
			template<class InputIt>
			void insert(iterator pos, InputIt first, InputIt last) {
				while (first != last) {
					pos = insert(pos, *first);
					++first;
				}
			}
			iterator erase(iterator pos) {
				size_type i = pos - begin();
				if (i > size - 1)
					return end();
				for (int j = i; j < size; j++)
					ptr[j] = ptr[j + 1];
				--size;
				return iterator(ptr + i);
			}
			iterator erase(iterator first, iterator last) {
				for (; first != last; last--)
					erase(first);
				return first;
			}
			void push_back(const_reference value) {
				if (size == capacity)
					ft_realloc(capacity * 2);
				ptr[size++] = value;
			}
			void pop_back() {
				if (!empty())
					erase(end() - 1);
			}
			void resize(size_type count) {
				if (count < size)
					for (size_type tmp = size; tmp != count; tmp--)
						pop_back();
				else
					for (size_type tmp = size; tmp != count; tmp++)
						push_back(0);
			}
			void resize(size_type count, value_type value = value_type()) {
				if (count < size)
					for (size_type tmp = size; tmp != count; tmp--)
						pop_back();
				else
					for (size_type tmp = size; tmp != count; tmp++)
						push_back(value);
			}
			void swap(vector & other) {
				ft::swap(alloc, other.alloc);
				ft::swap(ptr, other.ptr);
				ft::swap(size, other.size);
				ft::swap(capacity, other.capacity);
			}
    };
	template<class T, class Allocator>
	bool operator==(const ft::Vector<T, Allocator> & lhs, const ft::Vector<T, Allocator> & rhs) {
		if (lhs.size() == rhs.size()) {
			int i = 0;
			for (; i < lhs.size() && lhs[i] == rhs[i]; i++);
			if (i == lsh.size())
				return true;
		}
		return false;
	}
	
	template<class T, class Allocator>
	bool operator!=(const ft::Vector<T, Allocator> & lhs, const ft::Vector<T, Allocator> & rhs) { return !(lhs == rhs); }
}

#endif