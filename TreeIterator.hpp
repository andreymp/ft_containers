/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:44:54 by jobject           #+#    #+#             */
/*   Updated: 2022/02/11 21:58:38 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

# include "utils.hpp"

namespace ft {
	template<class Val>
	class TreeIterator {
		public:
			typedef Val											value_type;
			typedef Val &										reference;
			typedef Val * 										pointer;
			typedef const Val & 								const_reference;
			typedef const pointer								const_pointer;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;
			typedef node<typename remove_const<Val>::type> *	node_pointer;
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
			pointer operator->() { return root->data; }
			reference operator*() { return *(root->data); }
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
				*this = operator++();
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

	template<class Val>
	class ConstTreeIterator : public TreeIterator<Val> {
		public:
			typedef typename TreeIterator<Val>::const_pointer	const_pointer;
			typedef typename TreeIterator<Val>::const_reference	const_reference;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;
			typedef typename TreeIterator<Val>::node_pointer	node_pointer;
			
			ConstTreeIterator() : TreeIterator<Val>() {}
			ConstTreeIterator(node_pointer	ptr) : TreeIterator<Val>(ptr) {}
			ConstTreeIterator(const ConstTreeIterator<typename remove_const<Val>::type> & other) : TreeIterator<Val>(other) { *this = other; }
			ConstTreeIterator & operator=(const ConstTreeIterator<typename remove_const<Val>::type> & other) {
				if (this != &other)
					this->root = other.root;
				return *this;
			}
			~ConstTreeIterator() {}
			const_pointer operator->() const { return this->root->data; }
			const_reference operator*() const { return *(this->root->data); }
			template<class T>
			bool operator==(const ConstTreeIterator<T>  & other) { return this->root == other.root; }
			template<class T>
			bool operator!=(const ConstTreeIterator<T>  & other) { return this->root != other.root; }
	};
	
	template<class Val>
	class ReverseTreeIterator : public TreeIterator<Val> {
		public:
			typedef typename TreeIterator<Val>::pointer			pointer;
			typedef typename TreeIterator<Val>::reference		reference;
			typedef typename TreeIterator<Val>::const_pointer	const_pointer;
			typedef typename TreeIterator<Val>::const_reference	const_reference;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;
			typedef typename TreeIterator<Val>::node_pointer	node_pointer;

			ReverseTreeIterator() : TreeIterator<Val>() {}
			ReverseTreeIterator(node_pointer ptr) : TreeIterator<Val>(ptr) {}
			ReverseTreeIterator(const ReverseTreeIterator<typename remove_const<Val>::type> & other) : TreeIterator<Val>(other) { *this = other; }
			ReverseTreeIterator & operator=(const ReverseTreeIterator<typename remove_const<Val>::type> & other) {
				if (this != &other)
					this->root = other.root;
				return *this;
			}
			~ReverseTreeIterator() {}
			ReverseTreeIterator & operator++() {
				if (this->root->left && !this->root->left->isNil)
					this->root = this->maximum(this->root->left);
				else {
					node_pointer tmp = this->root->parent;
					while (tmp && this->root == tmp->left) {
						this->root = tmp;
						tmp = tmp->parent;
					}
					this->root = tmp;
				}
				return *this;
			}
			ReverseTreeIterator operator++(int) {
				ReverseTreeIterator<Val> tmp(*this);
				*this = operator++();
				return tmp;
			}
			ReverseTreeIterator & operator--() {
				if (this->root->right && !this->root->right->isNil)
					this->root = this->minimum(this->root->right);
				else {
					node_pointer tmp = this->root->parent;
					while (tmp && this->root == tmp->right) {
						this->root = tmp;
						tmp = tmp->parent;
					}
					this->root = tmp;
				}
				return *this;
			}
			ReverseTreeIterator operator--(int) {
				ReverseTreeIterator<Val> tmp(*this);
				*this = operator--();
				return tmp;
			}
			template<class T>
			bool operator==(const ReverseTreeIterator<T>  & other) { return this->root == other.root; }
			template<class T>
			bool operator!=(const ReverseTreeIterator<T>  & other) { return this->root != other.root; }
	};
	
	template<class Val>
	class ConstReverseTreeIterator : public ReverseTreeIterator<Val> {
		public:
			typedef typename ReverseTreeIterator<Val>::const_pointer	const_pointer;
			typedef typename ReverseTreeIterator<Val>::const_reference	const_reference;
			typedef std::ptrdiff_t										difference_type;
			typedef std::size_t											size_type;
			typedef typename ReverseTreeIterator<Val>::node_pointer		node_pointer;
			
			ConstReverseTreeIterator() : ReverseTreeIterator<Val>() {}
			ConstReverseTreeIterator(node_pointer ptr) : ReverseTreeIterator<Val>(ptr) {}
			ConstReverseTreeIterator(const ConstReverseTreeIterator<typename remove_const<Val>::type> & other) { *this = other; }
			ConstReverseTreeIterator & operator=(const ConstReverseTreeIterator<typename remove_const<Val>::type> & other) {
				if (this != &other)
					this->root = other.root;
				return *this;
			}
			~ConstReverseTreeIterator() {}
			const_pointer operator->() const { return this->root->data; }
			const_reference operator*() const { return *(this->root->data); }
			template<class T>
			bool operator==(const ConstReverseTreeIterator<T>  & other) { return this->root == other.root; }
			template<class T>
			bool operator!=(const ConstReverseTreeIterator<T>  & other) { return this->root != other.root; }
	};
}

#endif