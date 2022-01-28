/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:10:47 by jobject           #+#    #+#             */
/*   Updated: 2022/01/28 20:22:29 by jobject          ###   ########.fr       */
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
			pointer min(pointer ptr) { ptr->left ? min(ptr->left) : ptr; }
			pointer max(pointer ptr) { ptr->right ? max(ptr->right) : ptr; }
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
			bool operator==(const MapIterator & other) {return this->ptr->data == other.ptr->data; }
			bool operator!=(const MapIterator & other) {return this->ptr->data != other.ptr->data; }
			bool operator<(const MapIterator & other) {return this->ptr->data < other.ptr->data; }
			bool operator<=(const MapIterator & other) {return this->ptr->data <= other.ptr->data; }
			bool operator>(const MapIterator & other) {return this->ptr->data > other.ptr->data; }
			bool operator>=(const MapIterator & other) {return this->ptr->data >= other.ptr->data; }
			MapIterator & operator++() { ptr = inc(ptr); return *this; }
			MapIterator & operator--() { ptr = dec(ptr); return *this; }
			MapIterator operator++(int) {
				MapIterator res(*this);
				++(*this);
				return res;
			}
			MapIterator operator--(int) {
				MapIterator res(*this);
				--(*this);
				return res;
			}
	};

	template<class K, class V>
	class ConstMapIterator : public MapIterator<K, V> {
		public:
			typedef typename ft::MapIterator<K, V>::value_type			value_type;
			typedef typename ft::MapIterator<K, V>::pointer				pointer;
			typedef typename ft::MapIterator<K, V>::reference			reference;
			typedef const ft::pair<K, V> &								const_reference;
			
			ConstMapIterator() : MapIterator<K, V>(nullptr) {}
			ConstMapIterator(const pointer _ptr) : MapIterator<K, V>(_ptr) {}
			ConstMapIterator(const ConstMapIterator & other) { *this = other; }
			ConstMapIterator & operator=(const ConstMapIterator & other) {
				if (this != &other)
					this->ptr = other.ptr;
				return *this;
			}
			const_reference operator*() { return this->ptr->data; }
			const value_type * operator->() { return &this->ptr->data; }
			ConstMapIterator & operator++() { this->ptr = inc(this->ptr); return *this; }
			ConstMapIterator & operator--() { this->ptr = dec(this->ptr); return *this; }
			ConstMapIterator operator++(int) {
				ConstMapIterator res(*this);
				++(*this);
				return res;
			}
			ConstMapIterator operator--(int) {
				ConstMapIterator res(*this);
				--(*this);
				return res;
			}
	};

	template<class K, class V>
	class ReverseMapIterator : public MapIterator<K, V> {
		public:
			typedef typename ft::MapIterator<K, V>::value_type			value_type;
			typedef typename ft::MapIterator<K, V>::pointer				pointer;
			typedef typename ft::MapIterator<K, V>::reference			reference;
			typedef const ft::pair<K, V> &								const_reference;

			ReverseMapIterator() : MapIterator<K, V>(nullptr) {}
			ReverseMapIterator(const pointer _ptr) : MapIterator<K, V>(_ptr) {}
			ReverseMapIterator(const ReverseMapIterator & other) { *this = other; }
			ReverseMapIterator & operator=(const ReverseMapIterator & other) {
				if (this != &other)
					this->ptr = other.ptr;
				return *this;
			}
			bool operator==(const ReverseMapIterator & other) {return this->ptr->data == other.ptr->data; }
			bool operator!=(const ReverseMapIterator & other) {return this->ptr->data != other.ptr->data; }
			bool operator<(const ReverseMapIterator & other) {return this->ptr->data < other.ptr->data; }
			bool operator<=(const ReverseMapIterator & other) {return this->ptr->data <= other.ptr->data; }
			bool operator>(const ReverseMapIterator & other) {return this->ptr->data > other.ptr->data; }
			bool operator>=(const ReverseMapIterator & other) {return this->ptr->data >= other.ptr->data; }
			ReverseMapIterator & operator++() { this->ptr = dec(this->ptr); return *this; }
			ReverseMapIterator & operator--() { this->ptr = inc(this->ptr); return *this; }
			ReverseMapIterator operator++(int) {
				ReverseMapIterator res(*this);
				++(*this);
				return res;
			}
			ReverseMapIterator operator--(int) {
				ReverseMapIterator res(*this);
				--(*this);
				return res;
			}
	};

	template<class K, class V>
	class ConstReverseMapIterator : public ReverseMapIterator<K, V> {
		public:
			typedef typename ft::MapIterator<K, V>::value_type			value_type;
			typedef typename ft::MapIterator<K, V>::pointer				pointer;
			typedef typename ft::MapIterator<K, V>::reference			reference;
			typedef const ft::pair<K, V> &								const_reference;
			
			ConstReverseMapIterator() : ReverseMapIterator<K, V>(nullptr) {}
			ConstReverseMapIterator(const pointer _ptr) : ReverseMapIterator<K, V>(_ptr) {}
			ConstReverseMapIterator(const ConstReverseMapIterator & other) { *this = other; }
			ConstReverseMapIterator & operator=(const ConstReverseMapIterator & other) {
				if (this != &other)
					this->ptr = other.ptr;
				return *this;
			}
			const reference operator*() { return this->ptr->data; }
			const value_type * operator->() { return &this->ptr->data; }
			ConstReverseMapIterator & operator++() { this->ptr = dec(this->ptr); return *this; }
			ConstReverseMapIterator & operator--() { this->ptr = inc(this->ptr); return *this; }
			ConstReverseMapIterator operator++(int) {
				ConstReverseMapIterator res(*this);
				++(*this);
				return res;
			}
			ConstReverseMapIterator operator--(int) {
				ConstReverseMapIterator res(*this);
				--(*this);
				return res;
			}
	};
}

#endif