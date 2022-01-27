/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:09:54 by jobject           #+#    #+#             */
/*   Updated: 2022/01/27 20:40:23 by jobject          ###   ########.fr       */
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
			typedef const reference						const_reference;
			typedef Allocator::pointer					pointer;
			typedef Allocator::const_pointer			const_pointer;
			typedef	ft::MapIterator<K, V>				iterator;
			typedef ft::ConstMapIterator<K, V>			const_iterator;
			typedef ft::ReverseMapIterator<K, V>		reverse_iterator;
			typedef ft::ConstReverseMapIterator<K, V>	const_reverse_iterator;
		private:
			allocator_type		alloc;
			ft::node<K, V> *	ptr;
			size_type			size;
		public:
			class value_compare {
				public:
					typedef bool	result_type;
					typedef T		first_argument_type;
					typedef T		second_argument_type;
					result_type operator()(const_reference lhs, const_reference rhs ) const { return comparator()}
				protected:
					value_compare(key_compare c) : comparator(c) {}
					key_compare comparator;
			};
			Map() : alloc(0), ptr(nullptr), size(0) {}
			explicit map(const key_compare & comp, const allocator_type & alloc = allocator_type()) : ;
	};
}

#endif