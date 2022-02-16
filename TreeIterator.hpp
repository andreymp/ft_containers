/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:44:54 by jobject           #+#    #+#             */
/*   Updated: 2022/02/16 18:13:25 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

# include "utils.hpp"

namespace ft {
	template<class Val>
	class TreeIterator {
		public:
			typedef std::bidirectional_iterator_tag 						iterator_category;
			typedef typename ft::iterator_traits<Val *>::value_type 		value_type;
			typedef typename ft::iterator_traits<Val *>::reference 			reference;
			typedef typename ft::iterator_traits<Val *>::pointer			pointer;
			typedef const typename ft::iterator_traits<Val *>::reference 	const_reference;
			typedef const typename ft::iterator_traits<Val *>::pointer		const_pointer;
			typedef typename ft::iterator_traits<Val *>::difference_type	difference_type;
			typedef std::size_t												size_type;
			typedef node<typename remove_const<Val>::type> *				node_pointer;
		protected:
			node_pointer root;
			node_pointer minimum(node_pointer ptr) const {
				while (ptr->left && !ptr->left->isNil)
					ptr = ptr->left;
				return ptr;
			}
			node_pointer maximum(node_pointer ptr) const {
				while (!ptr->right->isNil)
					ptr = ptr->right;
				return ptr;
			}
		public:
			TreeIterator() {}
			TreeIterator(node_pointer ptr) : root(ptr) {}
			TreeIterator(const TreeIterator<typename remove_const<Val>::type> & other) { *this = other; }
			TreeIterator & operator=(const TreeIterator<typename remove_const<Val>::type> & other) {
				if (this != &other)
					root = other.root;
				return *this;
			}
			~TreeIterator() {}
			reference operator*() { return *root->data; }
			pointer operator->() { return &operator*(); }
			const_reference operator*() const { return *(root->data); }
			const_pointer operator->() const { return &operator*(); }
			node_pointer getPointer() const { return root; }
			TreeIterator & operator++() {
				if (root->right && !root->right->isNil)
					root = minimum(root->right);
				else {
					node_pointer tmp = root->parent;
					while (tmp && root == tmp->right) {
						root = tmp;
						tmp = tmp->parent;
					}
					root = tmp;
				}
				return *this;
			}
			TreeIterator operator++(int) {
				TreeIterator<value_type> tmp(*this);
				if (!root->right->isNil)
					root = minimum(root->right);
				else {
					node_pointer tmp = root->parent;
					while (tmp && root == tmp->right) {
						root = tmp;
						tmp = tmp->parent;
					}
					root = tmp;
				}
				return tmp;
			}
			TreeIterator & operator--() {
				if (root->left && !root->left->isNil)
					root = maximum(root->left);
				else {
					node_pointer tmp = root->parent;
					while (tmp && root == tmp->left) {
						root = tmp;
						tmp = tmp->parent;
					}
					root = tmp;
				}
				return *this;
			}
			TreeIterator operator--(int) {
				TreeIterator<value_type> tmp(*this);
				*this = operator--();
				return tmp;
			}
			template<class T>
			bool operator==(const TreeIterator<T>  & other) { return root == other.root; }
			template<class T>
			bool operator!=(const TreeIterator<T>  & other) { return root != other.root; }
	};
}

#endif