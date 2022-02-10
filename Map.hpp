/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:09:40 by jobject           #+#    #+#             */
/*   Updated: 2022/02/10 21:36:13 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "RBTree.hpp"
namespace ft {
	template<class K, class Val, class Compare = std::less<K>, class Alloc = std::allocator<ft::pair<const K, Val>> >
	class Map {
		public:
			typedef K															key_type;
			typedef Val															mapped_type;
			typedef ft::pair<const key_type, Val>								value_type;
			typedef Compare														key_compare;
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef std::size_t													size_type;
			typedef std::ptrdiff_t												difference_type;
			typedef class ft::RBTree<value_type, value_compare, allocator_type>	rb_tree;
			typedef typename rb_tree::iterator									iterator;
			typedef typename rb_tree::const_iterator							const_iterator;
			typedef typename rb_tree::reverse_iterator							reverse_iterator;
			typedef typename rb_tree::const_reverse_iterator					const_reverse_iterator;
			class value_compare {
				public:
					value_compare(key_compare _comp) : comparator(_comp) {}
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator() (const first_argument_type & x, const second_argument_type & y) const { return comp(x.first, y.first); }
				protected:
					key_compare comparator;
			};
		private:
			rb_tree			tree;
			key_compare		comp;
			allocator_type	alloc;
		public:	
	};
}
#endif