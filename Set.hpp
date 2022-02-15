/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:34:57 by jobject           #+#    #+#             */
/*   Updated: 2022/02/15 20:56:59 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "RBTree.hpp"

namespace ft {
	template<class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class Set {
		public:
			typedef T															key_type;
			typedef T															value_type;
			typedef Compare														key_compare;
			typedef Compare														value_compare;
			typedef Alloc														allocator_type;
			typedef T&															reference;
			typedef const T&													const_reference;
			typedef T*															pointer;
			typedef const T*													const_pointer;
			typedef std::size_t													size_type;
			typedef std::ptrdiff_t												difference_type;
			typedef class ft::RBTree<value_type, key_compare, allocator_type>	rb_tree;
			typedef typename rb_tree::iterator									iterator;
			typedef typename rb_tree::const_iterator							const_iterator;
			typedef typename rb_tree::reverse_iterator							reverse_iterator;
			typedef typename rb_tree::const_reverse_iterator					const_reverse_iterator;
		private:
			rb_tree tree;
		public:
			explicit Set(const key_compare & _comp = key_compare(), const allocator_type & _alloc = allocator_type()) : tree(rb_tree(_comp, _alloc)) {}
			template<class InputIt>
			Set(InputIt first, InputIt last,const key_compare & comparator = key_compare(), const allocator_type & _alloc = allocator_type(),
				typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) : tree(first, last, comparator, _alloc) {}
			Set(const Set & other) : tree(other.tree) {}
			~Set() {}
			Set & operator=(const Set & other) {
				if (this != &other) 
					tree = other.tree;
				return *this;
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
			pair<iterator,bool> insert(const value_type & val) { return tree.insert(val); }
			iterator insert (iterator pos, const value_type & val) { return tree.insert(pos, val); }
			template<class InputIt>
			void insert(InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) { tree.insert(first, last); }
			void erase(iterator pos) { tree.erase(pos); }
			size_type erase(const key_type & val) { return tree.erase(val); }
			void erase(iterator first, iterator last) { tree.erase(first, last); }
			void swap(Set & other) { tree.swap(other.tree); }
			void clear() { tree.clear(); }
			key_compare key_comp() const { return key_compare(); }
			value_compare value_comp() const { return value_compare(); }
			iterator find(const value_type & val) { return tree.find(val); }
			const_iterator find(const value_type & val) const { return tree.find(val); }
			size_type count(const value_type & val) const {
				size_type res = 0;
				for (iterator it = begin(); it != end(); ++it) {
					if (*it == val)
						++res;
				}
				return res;
			}
			iterator lower_bound(const value_type & key) { return tree.lower_bound(key); }
			const_iterator lower_bound(const value_type & key) const { return tree.lower_bound(key); }
			iterator upper_bound(const value_type & key) { return tree.upper_bound(); }
			const_iterator upper_bound(const value_type & key) const { return tree.upper_bound(); }
			ft::pair<iterator,iterator> equal_range(const value_type & key) { return tree.equal_range(key); }
			ft::pair<const_iterator,const_iterator> equal_range(const value_type & key) const { return tree.equal_range(key); }
			allocator_type get_allocator() const { return tree.get_allocator(); }
	};
	
	template<class T, class Compare, class Alloc>
	bool operator==(const ft::Set<T, Compare, Alloc> & x, const ft::Set<T, Compare, Alloc> & y) {
		if (x.size() == y.size()) {
			typename ft::Set<T, Compare, Alloc>::iterator it1 = x.begin();
			typename ft::Set<T, Compare, Alloc>::iterator it2 = y.begin();
			for (; it1 != x.end(); ++it1, ++it2) {
				if (*it1 != *it2)
					return false;
			}
			return true;
		}
		return false;
	}
	template<class T, class Compare, class Alloc>
	bool operator!=(const ft::Set<T, Compare, Alloc> & x, const ft::Set<T, Compare, Alloc> & y) { return !(x == y); }
	template<class T, class Compare, class Alloc>
	bool operator<(const ft::Set<T, Compare, Alloc> & x, const ft::Set<T, Compare, Alloc> & y) {
		typename ft::Set<T, Compare, Alloc>::iterator it1 = x.begin();
		typename ft::Set<T, Compare, Alloc>::iterator it2 = y.begin();
		for (; it1 != x.end() && it2 != y.end(); ++it1, ++it2) {
			if (*it1 != *it2)
				return *it1 < *it2;
		}
		return x.size() < y.size();
	}
	template<class T, class Compare, class Alloc>
	bool operator>(const ft::Set<T, Compare, Alloc> & x, const ft::Set<T, Compare, Alloc> & y) { return y < x; }
	template<class T, class Compare, class Alloc>
	bool operator<=(const ft::Set<T, Compare, Alloc> & x, const ft::Set<T, Compare, Alloc> & y) { return !(x > y); }
	template<class T, class Compare, class Alloc>
	bool operator>=(const ft::Set<T, Compare, Alloc> & x, const ft::Set<T, Compare, Alloc> & y) { return !(x < y); }
}

namespace std {
	template<class T, class Compare, class Alloc>
	void swap(ft::Set<T, Compare, Alloc> & x, ft::Set<T, Compare, Alloc> & y) { x.swap(y); }
}

#endif