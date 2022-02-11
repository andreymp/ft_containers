/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:09:40 by jobject           #+#    #+#             */
/*   Updated: 2022/02/11 21:33:26 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "RBTree.hpp"
namespace ft {
	template<class K, class Val, class Compare = std::less<K>, class Alloc = std::allocator<ft::pair<const K, Val> > >
	class Map {
		public:
			typedef K															key_type;
			typedef Val															mapped_type;
			typedef ft::pair<const key_type, Val>								value_type;
			typedef Compare														key_compare;
			typedef Alloc														allocator_type;
			typedef value_type &												reference;
			typedef const value_type &											const_reference;
			typedef value_type *												pointer;
			typedef const pointer												const_pointer;
			typedef std::size_t													size_type;
			typedef std::ptrdiff_t												difference_type;
			class value_compare {
				public:
					value_compare(key_compare _comp) : comparator(_comp) {}
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator() (const first_argument_type & x, const second_argument_type & y) const { return comparator(x.first, y.first); }
				protected:
					key_compare comparator;
			};
			typedef class ft::RBTree<value_type, value_compare, allocator_type>	rb_tree;
			typedef typename rb_tree::iterator									iterator;
			typedef typename rb_tree::const_iterator							const_iterator;
			typedef typename rb_tree::reverse_iterator							reverse_iterator;
			typedef typename rb_tree::const_reverse_iterator					const_reverse_iterator;
		private:
			key_compare		comp;
			allocator_type	alloc;
			rb_tree			tree;
		public:
			explicit Map(const key_compare & comparator = key_compare(), const allocator_type & _alloc = allocator_type()) : comp(comparator), alloc(_alloc),
				tree(rb_tree(comparator, _alloc)) {}
			template<class InputIt>
			Map(InputIt first, InputIt last,const key_compare & comparator = key_compare(), const allocator_type & _alloc = allocator_type(),
				typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) : comp(comparator), alloc(_alloc), tree(first, last, comp, alloc) {}
			Map(const Map & other) : comp(other.comp), alloc(other.alloc), tree(other.tree) {}
			Map & operator=(const Map & other) {
				if (this != &other) {
					alloc = other.alloc;
					comp = other.comp;
					tree = other.tree;
				}
				return *this;
			}
			mapped_type & at(const key_type & key) {
				iterator it = find(key);
				if (it == end())
					throw std::out_of_range("map");
				return it->second;
			}
			const mapped_type & at(const key_type & key) const {
				iterator it = find(key);
				if (it == end())
					throw std::out_of_range("map");
				return it->second;
			}
			iterator begin() { return tree.begin(); }
			const_iterator begin() const { return tree.begin(); }
			iterator end() { return tree.end(); }
			const_iterator end() const { return tree.end(); }
			reverse_iterator rbegin() { return tree.rbegin(); }
			const_reverse_iterator rbegin() const { return tree.rbegin(); }
			reverse_iterator rend() { return tree.rend(); }
			const_reverse_iterator rend() const { return tree.rend(); }
			bool empty() const { return tree.empty(); }
			size_type size() const { return tree.size(); }
			size_type max_size() const { return tree.max_size(); }
			mapped_type & operator[](const key_type & key) { insert(ft::make_pair(key, mapped_type())).first->second; }
			pair<iterator,bool> insert(const value_type & val) { return tree.insert(val); }
			iterator insert (iterator pos, const value_type & val) { return tree.insert(pos, val); }
			template<class InputIt>
			void insert(InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) { tree.insert(first, last); }
			void erase(iterator pos) { tree.erase(pos); }
			size_type erase(const key_type & key) { return tree.erase(make_pair(key, mapped_type())); }
			void erase(iterator first, iterator last) { tree.erase(first, last); }
			void swap(Map & other) {
				std::swap(alloc, other.alloc);
				std::swap(comp, other.comp);
				tree.swap(other.tree);
			}
			void clear() { tree.clear(); }
			key_compare key_comp() const { return comp; }
			value_compare value_comp() const { return value_compare(comp); }
			iterator find(const key_type & key) { return tree.find(ft::make_pair(key, mapped_type())); }
			const_iterator find(const key_type & key) const { return tree.find(ft::make_pair(key, mapped_type())); }
			size_type count(const key_type & key) const {
				size_type res = 0;
				for (iterator it = begin(); it != end(); ++it) {
					if (it->first == key)
						++res;
				}
				return res;
			}
			iterator lower_bound(const key_type & key) {
				for (iterator it = begin(); it != end(); ++it)
					if (!comp(it->first, key))
						return it;
				return end();
			}
			const_iterator lower_bound(const key_type & key) const {
				for (iterator it = begin(); it != end(); ++it)
					if (!comp(it->first, key))
						return static_cast<const_iterator>(it);
				return end();
			}
			iterator upper_bound(const key_type & key) {
				for (iterator it = begin(); it != end(); ++it)
					if (comp(key, it->first))
						return it;
				return end();
			}
			const_iterator upper_bound(const key_type & key) const {
				for (iterator it = begin(); it != end(); ++it)
					if (comp(key, it->first))
						return static_cast<const_iterator>(it);
				return end();
			}
			ft::pair<iterator,iterator> equal_range(const key_type & key) { return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)); }
			ft::pair<const_iterator,const_iterator> equal_range(const key_type & key) const { return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)); }
			allocator_type get_allocator() const { return alloc; }
	};
	
	template<class K, class T, class Compare, class Alloc>
	bool operator==(const ft::Map<K, T, Compare, Alloc> & x, const ft::Map<K, T, Compare, Alloc> & y) {
		if (x.size() == y.size()) {
			typename ft::Map<K, T, Compare, Alloc>::iterator it1 = x.begin();
			typename ft::Map<K, T, Compare, Alloc>::iterator it2 = y.begin();
			for (; it1 != x.end(); ++it1, ++it2) {
				if (*it1 != *it2)
					return false;
			}
			return true;
		}
		return false;
	}
	template<class K, class T, class Compare, class Alloc>
	bool operator!=(const ft::Map<K, T, Compare, Alloc> & x, const ft::Map<K, T, Compare, Alloc> & y) { return !(x == y); }
	template<class K, class T, class Compare, class Alloc>
	bool operator<(const ft::Map<K, T, Compare, Alloc> & x, const ft::Map<K, T, Compare, Alloc> & y) {
		typename ft::Map<K, T, Compare, Alloc>::iterator it1 = x.begin();
		typename ft::Map<K, T, Compare, Alloc>::iterator it2 = y.begin();
		for (; it1 != x.end() && it2 != y.end(); ++it1, ++it2) {
			if (*it1 != *it2)
				return *it1 < *it2;
		}
		return x.size() < y.size();
	}
	template<class K, class T, class Compare, class Alloc>
	bool operator>(const ft::Map<K, T, Compare, Alloc> & x, const ft::Map<K, T, Compare, Alloc> & y) { return y < x; }
	template<class K, class T, class Compare, class Alloc>
	bool operator<=(const ft::Map<K, T, Compare, Alloc> & x, const ft::Map<K, T, Compare, Alloc> & y) { return !(x > y); }
	template<class K, class T, class Compare, class Alloc>
	bool operator>=(const ft::Map<K, T, Compare, Alloc> & x, const ft::Map<K, T, Compare, Alloc> & y) { return !(x < y); }
}

namespace std {
	template<class K, class T, class Compare, class Alloc>
	void swap(ft::Map<K, T, Compare, Alloc> & x, ft::Map<K, T, Compare, Alloc> & y) { x.swap(y); }
}
#endif