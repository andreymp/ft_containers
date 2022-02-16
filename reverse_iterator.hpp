/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:32:42 by jobject           #+#    #+#             */
/*   Updated: 2022/02/16 18:17:43 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

# include "utils.hpp"

namespace ft {
	template<class Iterator>
	class reverse_iterator {
		public:
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category 	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
		private:
			iterator_type it;
		public:
			reverse_iterator() : it() {}
			explicit reverse_iterator(iterator_type _it) : it(_it) {}
			template <class Iter>
  			reverse_iterator (const reverse_iterator<Iter> & rev_it) : it(rev_it.it) {}
			iterator_type base() const { return it; }
			reference operator*() const { iterator_type tmp(it); return *--tmp; }
			reverse_iterator operator+(difference_type n) const { return reverse_iterator(it - n); }
			reverse_iterator & operator++() { --it; return *this; }
			reverse_iterator operator++(int) {
				reverse_iterator tmp(*this);
				*this = operator++();
				return tmp;
			}
			reverse_iterator operator-(difference_type n) const { return reverse_iterator(it + n); }
			reverse_iterator & operator--() { ++it; return *this; }
			reverse_iterator operator--(int) {
				reverse_iterator tmp(*this);
				*this = operator--();
				return tmp;
			}
			reverse_iterator & operator+=(difference_type n) { it-= n; return *this; }
			reverse_iterator & operator-=(difference_type n) { it+= n; return *this; }
			pointer operator->() const { return &(operator*()); }
			reference operator[] (difference_type n) const { return base()[-n-1]; }
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() == rhs.base(); }
	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() != rhs.base(); }
	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() > rhs.base(); }
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() >= rhs.base(); }
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() < rhs.base(); }
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() <= rhs.base(); }
	template <class Iterator>
  	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> & rev_it) { return rev_it + n; }
	template <class Iterator>
  	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() - rhs.base(); }
}

# endif