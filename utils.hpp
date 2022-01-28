/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:37:27 by jobject           #+#    #+#             */
/*   Updated: 2022/01/28 18:28:19 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {
	template<typename T>
	void swap(T & a, T & b) {
		T tmp = a;
		a = b;
		b = tmp;
	}
	
	template<class T>
	struct less {
		typedef bool	result_type;
		typedef T		first_argument_type;
		typedef T		second_argument_type;
		result_type operator()(const first_argument_type & lhs, const second_argument_type & rhs) const { lhs < rhs; }
	};
	
	template<class K, class V>
	struct pair {
		typedef K	first_type;
		typedef V	second_type;
		first_type first;
		second_type second;
		pair() {}
		pair(const first_type & x, const second_type & y) : first(x), second(y) {}
		template<class U1, class U2>
		pair(const pair<U1, U2> & other) { *this = other; }
		pair & operator=(const pair & other) {
			if (this != &other) {
				first = other.first;
				second = other.second;
			}
			return *this;
		}
	};
	template<class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 t, T2 u) { return ft::pair<T1, T2>(t, u); }
	template< class T1, class T2 >
	bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {	return lhs.first == rhs.first && lhs.second == rhs.second; }
	template< class T1, class T2 >
	bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs == rhs); }
	template< class T1, class T2 >
	bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		if (lhs.first < rhs.first)
			return true;
		if (lhs.first > rhs.first)
			return false;
		return lhs.second < rhs.second;
	}
	template< class T1, class T2 >
	bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return lhs < rhs || lhs == rhs; }
	template< class T1, class T2 >
	bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs <= rhs); }
	template< class T1, class T2 >
	bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs < rhs); }

	template<class K, class V>
	struct node {
		pair<K, V>	data;
		node *		parent;
		node *		right;
		node *		left;
	};
}

#endif