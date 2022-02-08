/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:10:49 by jobject           #+#    #+#             */
/*   Updated: 2022/02/08 21:24:51 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "TreeIterator.hpp"
# include "utils.hpp"

template <class Val, class Comp = ft::less(), class Alloc = std::allocator<V> >
class RBTree {
	public:
		typedef Val																value_type;
		typedef Comp															value_compare;
		typedef Alloc															allocator_type;
		typedef typename allocator_type::rebind<ft::node<value_type> >::other	node_allocator;
		typedef typename node_allocator::pointer								n_p;
		typedef typename allocator_type::pointer								pointer;
		typedef typename allocator_type::reference								reference;
		typedef typename allocator_type::const_reference						const_reference;
		typedef typename allocator_type::const_pointer							const_pointer;
		typedef std::size_t														size_type;
		typedef std::ptrdiff_t													difference_type;
		typedef class ft::TreeIterator<Val>										iterator;
		typedef class ft::ConstTreeIterator<Val>								const_iterator;
		typedef class ft::ReverseTreeIterator<Val>								reverse_iterator;
		typedef class ft::ConstReverseTreeIterator<Val>							const_reverse_iterator;
	private:
		allocator_type 	alloc_value;
		node_allocator	alloc_node;
		value_compare	comp;
		n_p				root;
		n_p				head;
		n_p				nil;
		size_type		allocated;
		
		void initNH() {
			nil = alloc_node.allocate(1);
			alloc_node.construct(nil, ft::node<value_type>());
			nil->isBlack = nil->isNil = true;
			head = alloc_node.allocate(1);
			alloc_node.construct(head, ft::node<value_type>());
			head->data = alloc_value.allocate(1);
			alloc_value.construct(head->data, value_type());
			head->isBlack = true;
		}
		bool _isNil(n_p ptr) const { return ptr == nil || ptr == head; }
		n_p maximum(n_p ptr) const {
			while (ptr && !_isNil(ptr->right))
				ptr = ptr->right;
			return ptr;
		}
		n_p minimum(n_p ptr) const {
			while (ptr->left && !_isNil(ptr->left)l)
				ptr = ptr->left;
			return ptr;
		}
		void rotateRight(n_p ptr) {
			n_p tmp = ptr->left;
			ptr->left = tmp->right;
			if (!_isNil(tmp->right))
				tmp->right->parent = ptr;
			tmp->parent = ptr->parent;
			if (!ptr->parent)
				root = tmp;
			else if (ptr == ptr->parent->left)
				ptr->parent->left = tmp;
			else 
				ptr->parent->right = tmp;
			tmp->right = ptr;
			ptr->parent = tmp;
		}
		void rotateLeft(n_p ptr) {
			n_p tmp = ptr->right;
			ptr->right = tmp->left;
			if (!_isNil(tmp->left))
				tmp->left->parent = ptr;
			tmp->parent = ptr->parent;
			if (!ptr->parent)
				root = tmp;
			else if (ptr == ptr->parent->right)
				ptr->parent->right = tmp;
			else
				ptr->parent->left = tmp;
			tmp->left = ptr;
			ptr->parent = tmp;
		}
		void clearList(n_p toDelete) {
			alloc_value.destory(toDelete->data);
			alloc_value.deallocate(toDelete->data, 1);
			alloc_node.deallocate(toDelete, 1);
		}
		void clearSubTree(n_p toDelete) {
			if (toDelete && !_isNil(toDelete)) {
				clearSubTree(toDelete->right);
				clearSubTree(toDelete->left);
				clearList(toDelete);
			}
		}
	public:
		RBTree() : alloc_value(allocator_type()), alloc_node(node_allocator()), comp(value_compare()) {
			initNH();
			root = head;
			allocated = 0;
		}
		explicit RBTree(const value_compare & comp = value_compare(), const allocator_type & alloc = allocator_type()) :
			alloc_value(alloc), alloc_node(node_allocator()), comp(comp) {
			initNH();
			root = head;
			allocated = 0;
		}
		template<class InputIt>
		RBTree(InputIt first, InputIt last, const value_compare & comp = value_compare(), const allocator_type & alloc = allocator_type(),
			typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) :
			alloc_value(alloc), alloc_node(node_allocator()), comp(comp) {
				initNH();
				root = head;
				allocated = 0;
				//insert()
		}
		RBTree(const RBTree & other) { *this = other; }
		RBTree & operator=(const RBTree & other) {
			if (this != &other) {
				alloc_node = other.alloc_node;
				alloc_value = other.alloc_value;
				comp = other.comp;
				head ? clearSubTree(root) : initNH();
				if (other.allocated) {
					// copy
				} else 
					root = head;
				allocated = other.allocated;
			}
			return *this;
		}
		~RBTree() {
			clearSubTree(root);
			clearList(head);
			alloc.deallocte(nil, 1);
		}
};

#endif