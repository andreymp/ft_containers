/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:34:25 by jobject           #+#    #+#             */
/*   Updated: 2022/02/04 18:09:57 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

namespace ft {
	template<class T, class Container = ft::Vector<T> >
	class Stack {
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
		protected:
			container_type	container;
		private:
			template<class T1, class C1>
			friend bool operator==(const Stack<T1,C1> & lhs, const Stack<T1,C1> & rhs);
			template<class T1, class C1>
			friend bool operator!=(const Stack<T1,C1> & lhs, const Stack<T1,C1> & rhs);
			template<class T1, class C1>
			friend bool operator<(const Stack<T1,C1> & lhs, const Stack<T1,C1> & rhs);
			template<class T1, class C1>
			friend bool operator<=(const Stack<T1,C1> & lhs, const Stack<T1,C1> & rhs);
			template<class T1, class C1>
			friend bool operator>(const Stack<T1,C1> & lhs, const Stack<T1,C1> & rhs);
			template<class T1, class C1>
			friend bool operator>=(const Stack<T1,C1> & lhs, const Stack<T1,C1> & rhs);
		public:
			explicit Stack(const container_type & c = container_type()) : container(c) {}
			~Stack() {}
			Stack & operator=(const Stack & other) {
				if (this != &other)
					container = other.container;
				return *this;
			}
			reference top() {return container.back(); }
			const_reference top() const {return container.back(); }
			bool empty() const {return container.empty(); }
			size_type size() const {return container.size(); }
			void push(const_reference value) { container.push_back(value); }
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