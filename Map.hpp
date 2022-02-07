/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:09:54 by jobject           #+#    #+#             */
/*   Updated: 2022/02/07 16:12:11 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "utils.hpp"
# include "MapIterator.hpp"

namespace ft {
	template<class K, class V, class Compare = ft::less<K>, class Allocator = std::allocator<ft::pair<const K, V> > >
	class Map {
		public:
			typedef K									key_type;
			typedef V									mapped_type;
			typedef ft::pair<const K, V>				value_type;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef Compare								key_compare;
			typedef Allocator							allocator_type;
			typedef value_type &						reference;
			typedef const value_type &					const_reference;
			typedef ft::pair<const K, V> *				pointer;
			typedef const pointer						const_pointer;
			typedef ft::node<K, V> *					node;
			typedef	ft::MapIterator<K, V>				iterator;
			typedef ft::ConstMapIterator<K, V>			const_iterator;
			typedef ft::ReverseMapIterator<K, V>		reverse_iterator;
			typedef ft::ConstReverseMapIterator<K, V>	const_reverse_iterator;
		private:
			allocator_type	alloc;
			key_compare		comp;
			node			tree;
			pointer			ptr;
			size_type		_size;
			node minimum(node _ptr) { _ptr->left ? min(_ptr->left) : _ptr; }
			node maximum(node _ptr) { _ptr->right ? max(_ptr->right) : _ptr; }
			node newNode(value_type	val, node parent = nullptr) {
				node tNode = alloc.allocate(sizeof(ft::pair<K, V>));
				tNode->data = val;
				tNode->parent = parent;
				tNode->right = nullptr;
				tNode->left = nullptr;
				++_size;
			}
			void	freeMemory(node bNode) {
				if (bNode->left)
					freeMemory(bNode->left);
				if (bNode->right)
					freeMemory(bNode->right);
				alloc.deallocate(bNode, sizeof(ft::pair<K, V>));
			}
			node findPair(const key_type & key) {
				if (!tree)
					return nullptr;
				node next, curr;
				next = curr = tree;
				while (next) {
					curr = next;
					if (curr->data.first == key) 
						return newNode(curr->data);
					next = key < curr->data.first ? curr->left : curr->right;
				}
				return nullptr;
			}
			node insertPair(node pair, node tmp) {
				while (tmp) {
					if (pair->data > tmp->data) {
						if (tmp->right)
							tmp = tmp->right;
						else {
							pair->parent = tmp;
							tmp->right = pair;
							break ;
						}
					} else if (pair->data < tmp->data) {
						if (tmp->left)
							tmp = tmp->left;
						else {
							pair->parent = tmp;
							tmp->left = pair;
							break ;
						}
					}
				}
				return pair;
			}
			void deletePair(node pair) {
				if (!pair->left && !pair->right) {
					pair->parent->right == pair ? pair->parent->right = nullptr : pair->parent->left = nullptr;
					alloc.deallocate(pair, sizeof(ft::node<K, V>));
					return ;
				} else if (pair->left && !pair->right) {
					pair->parent->right == pair ? pair->parent->right = pair->left : pair->parent->left = pair->left;
					pair->left->parent = pair->parent;
					alloc.deallocate(pair, sizeof(ft::node<K, V>));
					return ;
				} else if (!pair->left && pair->right) {
					pair->parent->right == pair ? pair->parent->right = pair->right : pair->parent->left = pair->right;
					pair->right->parent = pair->parent;
					alloc.deallocate(pair, sizeof(ft::node<K, V>));
					return ;
				}
				iterator it = iterator(pair);
				iterator it2 = ++it;
				node next = it2 == end() ? it.getPointer() : it2.getPointer();
				next->data = pair->data;
				deletePair(next);	
			}
		public:
			class value_compare {
				public:
					typedef bool			result_type;
					typedef value_type		first_argument_type;
					typedef value_type		second_argument_type;
					result_type operator()(const_reference lhs, const_reference rhs) const { return comparator(lhs, rhs); }
				protected:
					value_compare(key_compare c) : comparator(c) {}
					key_compare comparator;
			};
			Map() : alloc(allocator_type()), comp(key_compare()), tree(nullptr), ptr(nullptr), _size(0) {}
			explicit Map(const key_compare & comp, const allocator_type & alloc = allocator_type()) : 
				alloc(alloc), comp(comp), tree(nullptr), ptr(nullptr), _size(0) {}
			template<class InputIt>
			Map(InputIt first, InputIt last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type(), typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) :
				alloc(alloc), comp(comp) {
				_size = 0;
				tree = newNode(*first);
				while (first != last) {
					++first;
					node next, curr;
					next = curr = tree;
					while (next) {
						curr = next;
						next = *first < curr->data ? curr->left : curr->right;
					}
					*first < curr->data ? curr->left = newNode(*first, curr) : curr->right = newNode(*first, curr);
				}
			}
			Map(const Map & other) { *this = other; }
			~Map() { freeMemory(tree); }
			Map & operator=(const Map & other) {
				if (this != &other) {
					if (tree)
						freeMemory(tree);
					_size = 0;
					alloc = other.alloc;
					comp = other.comp;
					iterator first = other.begin();
					tree = newNode(*first);
					while (first != other.end()) {
						++first;
						node next, curr;
						next = curr = tree;
						while (next) {
							curr = next;
							next = *first < curr->data ? curr->left : curr->right;
						}
						*first < curr->data ? curr->left = newNode(*first, curr) : curr->right = newNode(*first, curr);
					}
				}
				return *this;
			}
			allocator_type get_allocator() const { return alloc; }
			mapped_type & at(const key_type & key) {
				node tmp = findPair(key);
				if (!tmp)
					throw std::out_of_range("Out of range");
				mapped_type retval = tmp->data.second;
				alloc.deallocate(tmp, sizeof(ft::pair<K, V>));
				--_size;
				return retval;
			}
			const mapped_type & at(const key_type & key) const {
				node tmp = findPair(key);
				if (!tmp)
					throw std::out_of_range("Out of range");
				mapped_type retval = tmp->data.second;
				alloc.deallocate(tmp, sizeof(ft::pair<K, V>));
				--_size;
				return retval;
			}
			mapped_type & operator[](const key_type & key) {
				node tmp = findPair(key);
				if (!tmp) {
					if (!tree)
						return newNode(ft::make_pair(key, mapped_type()))->data.second;
					node next, curr;
					next = curr = tree;
					while (next) {
						curr = next;
						next = key < curr->data.first ? curr->left : curr->right;
					}
					return newNode(ft::make_pair(key, mapped_type(), curr))->data.second;
				}
				mapped_type retval = tmp->data.second;
				alloc.deallocate(tmp, sizeof(ft::pair<K, V>));
				return retval;
			}
			iterator begin() {
				iterator it = iterator(tree);
				return iterator(it.min(it.getPointer()));
			}
			const_iterator begin() const {
				const_iterator it = const_iterator(tree);
				return const_iterator(it.min(it.getPointer()));
			}
			iterator end() {
				iterator it = iterator(tree);
				return iterator(it.max(it.getPointer())->right);
			}
			const_iterator end() const {
				const_iterator it = const_iterator(tree);
				return const_iterator(it.max(it.getPointer())->right);
			}
			reverse_iterator rbegin() {
				reverse_iterator it = reverse_iterator(tree);
				return reverse_iterator(it.max(it.getPointer()));
			}
			const_reverse_iterator rbegin() const {
				const_reverse_iterator it = const_reverse_iterator(tree);
				return const_reverse_iterator(it.max(it.getPointer()));
			}
			reverse_iterator rend() {
				reverse_iterator it = reverse_iterator(tree);
				return reverse_iterator(it.min(it.getPointer())->left);
			}
			const_reverse_iterator rend() const {
				const_reverse_iterator it = const_reverse_iterator(tree);
				return const_reverse_iterator(it.min(it.getPointer())->left);
			}
			bool empty() const { return !_size; }
			size_type size() const { return _size; }
			size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(ft::node<key_type, mapped_type>); }
			void clear() { erase(begin(), end()); }
			ft::pair<iterator, bool> insert(const_reference value) {
				iterator tmp = find(value.first);
				if (tmp != end())
					return ft::make_pair(tmp, false);
				return ft::make_pair(iterator(insertPair(newNode(value))), true);
			}
			iterator insert(iterator hint, const_reference value) {
				iterator tmp = find(value.first);
				if (tmp == end())
					tmp = iterator(insertPair(newNode(value), hint.getPointer()));
				return tmp;
			}
			template<class InputIt>
			void insert(InputIt first, InputIt last) {
				for (; first != last; ++first)
					insert(*first);
			}
			void erase(iterator pos) {
				if (pos != end()) {
					--_size;
					deletePair(pos.getPointer());
				}
			}
			void erase(iterator first, iterator last) {
				for (; first != last; ++first)
					erase(first);
			}
			size_type erase(const key_type & key) {
				int counter = 0;
				while (true) {
					iterator it = find(key);
					if (it == end())
						break;
					erase(it);
					counter++; 
				}
			}
			void swap(Map & other) {
				std::swap(alloc, other.alloc);
				std::swap(comp, other.comp);
				std::swap(_size, other._size);
				std::swap(ptr, other.ptr);
				std::swap(tree, other.tree);
			}
			size_type count(const key_type & key) const {
				size_type res = 0;;
				for (iterator it = begin(); it != end(); ++it)
					if (it->first == key)
						++res;
				return res;
			}
			iterator find(const key_type & key) {
				for (iterator it = begin(); it != end(); ++it)
					if (it->first == key)
						return it;
				return end();
			}
			const_iterator find(const key_type & key) const {
				for (const_iterator it = begin(); it != end(); ++it)
					if (it->first == key)
						return it;
				return end();
			}
			ft::pair<iterator, iterator> equal_range(const key_type & key) { return ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)); }
			ft::pair<const_iterator, const_iterator> equal_range(const key_type & key) const { return ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)); }
			iterator lower_bound(const key_type & key) {
				for (iterator it = begin(); it != end(); ++it)
					if (it->first >= key)
						return it;
				return end();
			}
			const_iterator lower_bound(const key_type & key) const {
				for (const_iterator it = begin(); it != end(); ++it)
					if (it->first >= key)
						return it;
				return end();
			}
			iterator upper_bound(const key_type & key) {
				for (iterator it = begin(); it != end(); ++it)
					if (it->first > key)
						return it;
				return end();
			}
			const_iterator upper_bound(const key_type & key) const {
				for (const_iterator it = begin(); it != end(); ++it)
					if (it->first > key)
						return it;
				return end();
			}
			key_compare key_comp() const { return comp; }
			typename ft::Map<K, V>::value_compare value_comp() const { return value_compare(comp); }
	};
	
	template<class K, class V, class Compare, class Allocator>
	bool operator==(const ft::Map<K, V, Compare, Allocator> & lhs, const ft::Map<K, V, Compare, Allocator> & rhs) {
		if (lhs.size() == rhs.size()) {
			typename ft::Map<K, V, Compare, Allocator>::iterator it = lhs.begin();
			typename ft::Map<K, V, Compare, Allocator>::iterator it2 = rhs.begin();
			for (; it != lhs.end(); ++it, ++it2)
				if (*it != *it2)
					return false;
			return true;
		}
		return false;
	}
	template<class K, class V, class Compare, class Allocator>
	bool operator!=(const ft::Map<K, V, Compare, Allocator> & lhs, const ft::Map<K, V, Compare, Allocator> & rhs) { return !(lhs == rhs); }
	template<class K, class V, class Compare, class Allocator>
	bool operator<(const ft::Map<K, V, Compare, Allocator> & lhs, const ft::Map<K, V, Compare, Allocator> & rhs) {
		typename ft::Map<K, V, Compare, Allocator>::iterator it_size = lhs.size() > rhs.size() ? rhs.end() : lhs.end();
		typename ft::Map<K, V, Compare, Allocator>::iterator it = lhs.begin();
			typename ft::Map<K, V, Compare, Allocator>::iterator it2 = rhs.begin();
			for (; it != it_size; ++it, ++it2)
				if (*it != *it2)
					return *it < *it2;
		return lhs.size() < rhs.size();
	}
	template<class K, class V, class Compare, class Allocator>
	bool operator<=(const ft::Map<K, V, Compare, Allocator> & lhs, const ft::Map<K, V, Compare, Allocator> & rhs) { return lhs == rhs || lhs < rhs; }
	template<class K, class V, class Compare, class Allocator>
	bool operator>(const ft::Map<K, V, Compare, Allocator> & lhs, const ft::Map<K, V, Compare, Allocator> & rhs) { return !(lhs <= rhs); }
	template<class K, class V, class Compare, class Allocator>
	bool operator>=(const ft::Map<K, V, Compare, Allocator> & lhs, const ft::Map<K, V, Compare, Allocator> & rhs) { return !(lhs < rhs); }
}

namespace std {
	template<class K, class V, class Compare, class Allocator>
	void swap(ft::Map<K, V, Compare, Allocator> & lhs, ft::Map<K, V, Compare, Allocator> & rhs) { lhs.swap(rhs); }
}

#endif