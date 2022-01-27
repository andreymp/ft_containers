/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:34:25 by jobject           #+#    #+#             */
/*   Updated: 2022/01/27 16:10:25 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

namespace ft {
	template<class T, class Container = ft::Vector<T> >
	class Stack {
		public:
			typedef Container					container_type;
			typedef Container::value_type		value_type;
			typedef Container::size_type		size_type;
			typedef Container::reference		reference;
			typedef Container::const_reference	const_reference;
		protected:
			container_type	container;
		public:
			explicit Stack(const container_type & cont = container_type()) : container(cont) {}
			~Stack() {}
			Stack & operator=(const Stack & other) {
				if (this != &other)
					container = other.container;
				return *this;
			}
			reference top() {return container.front(); }
			const_reference top() const {return container.front(); }
			bool empty() const {return container.empty(); }
			size_type size() const {return container.size(); }
			void push(const_reference value) { container.push_back(); }
			void pop() { container.pop_back(); }
	};

	template<class T, class Container>
	bool operator==(const ft::Stack<T,Container> & lhs, const ft::Stack<T,Container> & rhs) {return lhs.container == rhs.container; }
	template<class T, class Container>
	bool operator!=(const ft::Stack<T,Container> & lhs, const ft::Stack<T,Container> & rhs) {return lhs.container != rhs.container; }
	template<class T, class Container>
	bool operator<(const ft::Stack<T,Container> & lhs, const ft::Stack<T,Container> & rhs) {return lhs.container < rhs.container; }
	template<class T, class Container>
	bool operator<=(const ft::Stack<T,Container> & lhs, const ft::Stack<T,Container> & rhs) {return lhs.container <= rhs.container; }
	template<class T, class Container>
	bool operator>(const ft::Stack<T,Container> & lhs, const ft::Stack<T,Container> & rhs) {return lhs.container > rhs.container; }
	template<class T, class Container>
	bool operator>=(const ft::Stack<T,Container> & lhs, const ft::Stack<T,Container> & rhs) {return lhs.container >= rhs.container; }
}

#endif