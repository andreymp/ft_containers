/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:10:47 by jobject           #+#    #+#             */
/*   Updated: 2022/01/27 20:31:30 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "utils.hpp"

namespace ft {
	template<class K, class V>
	class MapIterator {
		public:
			typedef ft::pair<K, V>		value_type;
			typedef ft::node<K, V> *	pointer;
			typedef ft::pair<K, V> &	reference;
		protected:
			pointer ptr;
			pointer min(pointer ptr) { ptr->left : min(ptr->left) : ptr; }
			pointer max(pointer ptr) { ptr->right : min(ptr->right) : ptr; }
			pointer inc(pointer ptr) {
				if (ptr->right)
					return min(ptr->right);
				pointer tmp = ptr->parent;
				while (tmp && ptr == tmp->right) {
					ptr = tmp;
					tmp = tmp->parent;
				}
				return tmp;
			}
			pointer dec(pointer ptr) {
				if (ptr->left)
					return max(ptr->left);
				pointer tmp = ptr->parent;
				while (tmp && ptr == tmp->left) {
					ptr = tmp;
					tmp = tmp->parent;
				}
				return tmp;
			}
		public:
			MapIterator() : ptr(nullptr) {}
			MapIterator(const pointer _ptr) : ptr(_ptr) {}
			MapIterator(const MapIterator & other) { *this = other; }
			MapIterator & operator=(const MapIterator & other) {
				if (this != &other)
					ptr = other.ptr;
				return *this;
			}
			pointer getPointer() {return ptr; }
			reference operator*() { return ptr->data; }
            value_type * operator->() { return &ptr->data; }
			bool operator==(const MapIterator & other) {return ptr->data == other.ptr->data; }
			bool operator!=(const MapIterator & other) {return ptr->data != other.ptr->data; }
			bool operator<(const MapIterator & other) {return ptr->data < other.ptr->data; }
			bool operator<=(const MapIterator & other) {return ptr->data <= other.ptr->data; }
			bool operator>(const MapIterator & other) {return ptr->data > other.ptr->data; }
			bool operator>=(const MapIterator & other) {return ptr->data >= other.ptr->data; }
			MapIterator & operator++() { ptr = inc(ptr); return *this; }
			MapIterator & operator--() { ptr = dec(ptr); return *this; }
			MapIterator operator++() {
				MapIterator res(*this);
				++(*this);
				return res;
			}
			MapIterator operator--() {
				MapIterator res(*this);
				--(*this);
				return res;
			}
	};

	template<class K, class V>
	class ConstMapIterator : public MapIterator<K, V> {
		public:
			typedef const ft::pair<K, V> &	const_reference;
			ConstMapIterator() : ptr(nullptr) {}
			ConstMapIterator(const pointer _ptr) : ptr(_ptr) {}
			ConstMapIterator(const ConstMapIterator & other) { *this = other; }
			ConstMapIterator & operator=(const ConstMapIterator & other) {
				if (this != &other)
					ptr = other.ptr;
				return *this;
			}
			const_reference operator*() { return ptr->data; }
			const value_type * operator->() { return &ptr->data; }
			ConstMapIterator & operator++() { ptr = inc(ptr); return *this; }
			ConstMapIterator & operator--() { ptr = dec(ptr); return *this; }
			ConstMapIterator operator++() {
				ConstMapIterator res(*this);
				++(*this);
				return res;
			}
			ConstMapIterator operator--() {
				ConstMapIterator res(*this);
				--(*this);
				return res;
			}
	};

	template<class K, class V>
	class ReverseMapIterator : public MapIterator<K, V> {
		public:
			ReverseMapIterator() : ptr(nullptr) {}
			ReverseMapIterator(const pointer _ptr) : ptr(_ptr) {}
			ReverseMapIterator(const ReverseMapIterator & other) { *this = other; }
			ReverseMapIterator & operator=(const ReverseMapIterator & other) {
				if (this != &other)
					ptr = other.ptr;
				return *this;
			}
			bool operator==(const ReverseMapIterator & other) {return ptr->data == other.ptr->data; }
			bool operator!=(const ReverseMapIterator & other) {return ptr->data != other.ptr->data; }
			bool operator<(const ReverseMapIterator & other) {return ptr->data < other.ptr->data; }
			bool operator<=(const ReverseMapIterator & other) {return ptr->data <= other.ptr->data; }
			bool operator>(const ReverseMapIterator & other) {return ptr->data > other.ptr->data; }
			bool operator>=(const ReverseMapIterator & other) {return ptr->data >= other.ptr->data; }
			ReverseMapIterator & operator++() { ptr = dec(ptr); return *this; }
			ReverseMapIterator & operator--() { ptr = inc(ptr); return *this; }
			ReverseMapIterator operator++() {
				ReverseMapIterator res(*this);
				++(*this);
				return res;
			}
			ReverseMapIterator operator--() {
				ReverseMapIterator res(*this);
				--(*this);
				return res;
			}
	};

	template<class K, class V>
	class ConstReverseMapIterator : public ReverseMapIterator<K, V> {
		public:
			ConstReverseMapIterator() : ptr(nullptr) {}
			ConstReverseMapIterator(const pointer _ptr) : ptr(_ptr) {}
			ConstReverseMapIterator(const ConstReverseMapIterator & other) { *this = other; }
			ConstReverseMapIterator & operator=(const ConstReverseMapIterator & other) {
				if (this != &other)
					ptr = other.ptr;
				return *this;
			}
			const reference operator*() { return ptr->data; }
			const value_type * operator->() { return &ptr->data; }
			ConstReverseMapIterator & operator++() { ptr = dec(ptr); return *this; }
			ConstReverseMapIterator & operator--() { ptr = inc(ptr); return *this; }
			ConstReverseMapIterator operator++() {
				ConstReverseMapIterator res(*this);
				++(*this);
				return res;
			}
			ConstReverseMapIterator operator--() {
				ConstReverseMapIterator res(*this);
				--(*this);
				return res;
			}
	};
}

#endif