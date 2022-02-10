/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:10:49 by jobject           #+#    #+#             */
/*   Updated: 2022/02/10 21:03:15 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <memory>
# include "TreeIterator.hpp"
# include "utils.hpp"

namespace ft {
	template <class Val, class Comp = std::less<Val>, class Alloc = std::allocator<V> >
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
				alloc_node.construct(nil, node<value_type>());
				nil->isBlack = nil->isNil = true;
				head = alloc_node.allocate(1);
				alloc_node.construct(head, node<value_type>());
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
			void normalizeInsert(n_p noda) {
				if (noda == root || noda->parnet == root) { root->isBlack = true; return ; }
				for (; noda != root && noda->parent->isBlack;;) {
					n_p father = noda->parent;
					if (father == father->parent->right) {
						n_p fatherBrother = father->parent->left;
						if (fatherBrtother->isBlack) {
							if (noda == father->left) {
								noda = father;
								rotateRight(noda);
							}
							noda->parent->isBlack = true;
							noda->parent->parnet->isBlack = false;
							rotateLeft(noda->parent->parent);
						} else {
							father->isBlack = true;
							fatherBrother->isBlack = true;
							father->parent->isBlak = false;
							noda = father->parent;
						}
					} else {
						n_p fatherBrother = father->parent->right;
						if (fatherBrtother->isBlack) {
							if (noda == father->right) {
								noda = father;
								rotateLeft(noda);
							}
							noda->parent->isBlack = true;
							noda->parent->parnet->isBlack = false;
							rotateRight(noda->parent->parent);
						} else {
							father->isBlack = true;
							fatherBrother->isBlack = true;
							father->parent->isBlak = false;
							noda = father->parent;
						}
					}
				}
				root->isBlack = true;
			}
			void normalizeErase(n_p noda) {
				// TO DO
			}
			n_p insertRecursive(n_p where, n_p noda) {
				if (comp(*(noda->data), *(where->data))) {
					if (!_isNil(where->left))
						return insertRecursive(where->left, noda);
					where->left = noda; 	
				} else {
					if (!_isNil(where->right))
						return insertRecursive(where->right, noda);
					where->right = noda; 	
				}
				noda->parent = where;
				return noda;
			}
			n_p insertPrivate(n_p noda, n_p where) {
				if (root != head)
					where == root ? insertRecursive(where, noda) : insertRecursive(root, noda);
				else
					root = noda;
				return noda;
			}
			n_p findRecursive(const_reference value, n_p noda) const {
				if (!noda || _isNil(noda))
					return nullptr;
				if (comp(value, *(noda->data))
					return findRecursive(value, noda->left);
				if (comp(*(noda->data), value)
					return findRecursive(value, noda->right);
				return noda;
			}
			n_p copyParent(n_p other) {
				n_p res = alloc_node.allocate(1);
				alloc_node.construct(res, node<value_type>());
				res->isBlack = other->isBlack;
				res->isNil = other->isNil;
				if (other->value){
					res->value = alloc_value.allocate(1);
					alloc_value.construct(res->value, *other->value);
				return res;
			}
			void copyChildRecursive(n_p noda, n_p other) {
				if (!other->right->isNil)
					noda->right->isNil;
				else if (!other->right->right) {
					noda->right = head;
					head->parent = noda;
				} else {
					noda->right = copyParent(other->right);
					noda->right->parent = noda;
					copyChildRecursive(noda->left, other->right);
				}
				if (!other->left->isNil)
					noda->left->isNil;
				else {
					noda->left = copyParent(other->left);
					noda->left->parent = noda;
					copyChildRecursive(noda->left, other->left);
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
					for (; first != last; ++first)
						insert(*first);
			}
			RBTree(const RBTree & other) { *this = other; }
			RBTree & operator=(const RBTree & other) {
				if (this != &other) {
					alloc_node = other.alloc_node;
					alloc_value = other.alloc_value;
					comp = other.comp;
					head ? clearSubTree(root) : initNH();
					if (other.allocated) {
						root = alloc_node.allocate(1);
						alloc_node.construct(root, node<value_type>());
						root->isBlack = other->root->isBlack;
						root->isNil = other->root->isNil;
						if (other->root->value){
							root->value = alloc_value.allocate(1);
							alloc_value.construct(root->value, *other->root->value);
						copyChildRecursive(root, other.root);
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
			iterator begin() { return iterator(allocated ? minimum(root) : head); }
			const_iterator begin() const { return const_iterator(allocated ? minimum(root) : head); }
			iterator end() { return iterator(head); }
			const_iterator end() const { return const_iterator(head); }
			reverse_iterator rbegin() { return reverse_iterator(head); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(head); }
			reverse_iterator rend() { return reverse_iterator(allocated ? minimum(root) : head); }
			const_reverse_iterator rend() const { return const_reverse_iterator(allocated ? minimum(root) : head); }
			bool empty() const { return !allocated; }
			size_type size() const { return allocated; }
			size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(size_type); }
			void clear() {
				clearSubTree(root);
				allocated = 0;
				root = head;
				head->parent = nullptr;
			}
			void swap(RBTree & other) {
				std::swap(alloc_value, other.alloc_value);
				std::swap(alloc_node, other.alloc_node);
				std::swap(comp, other.comp);
				std::swap(root, other.root);
				std::swap(head, other.head);
				std::swap(nil, other.nil);
				std::swap(allocated, other.allocated);
			}
			pair<iterator, bool> insert(const_reference val) {
				iterator it = find(val);
				if (it != end())
					return pair<iterator, bool>(it, false);
				n_p noda = alloc_node.allocate(1);
				dataVal = alloc_value.allocate(1);
				alloc_value.construct(dataVal, val);
				alloc_node.construct(noda, node<value_type>(dataVal));
			 	noda->left = noda->right = nil;
				pair<iterator, bool> res(iterator(noda), true);
				normalizeInsert(noda);
				noda = maximum(root);
				noda->right = head;
				head->parent = noda;
				++allocated;
				return res;
			}
			iterator insert(iterator pos, const_reference value) {
				iterator it = find(value);
				if (it == end())
					return it;
				n_p noda = alloc_node.allocate(1);
				dataVal = alloc_value.allocate(1);
				alloc_value.construct(dataVal, val);
				alloc_node.construct(noda, node<value_type>(dataVal));
			 	noda->left = noda->right = nil;
				if (pos == end()) {
					--pos;
					insertPrivate(noda, end() == begin() || comp(value, *pos) ? root : head->parent);
				} else if (pos == begin())
					insertPrivate(noda, end() == begin() || comp(*pos, value) ? root : minimum(root));
				else 
					insertRecursive(noda, root);
				normalizeInsert(noda);
				n_p max_noda = maximum(root);
				max_noda->right = head;
				head->parent = max_noda;
				++allocated;
				return iterator(noda);
			}
			template<class InputIt>
			void insert(InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) {
				for (; first != last; ++first)
					insert(*first);
			}
			void erase(iterator pos) {
				// TO DO 
			}
			size_type erase(const_reference value) {
				size_type i = 0;
				while (true) {
					iterator it = find(value);
					if (it == end())
						break ;
					i++;
					erase(it);
				}
				return i;
			}
			void erase(iterator first, iterator last) {
				for (; first != last; ++first)
					erase(first);
			}
			value_compare value_comp() const { return comp; }
			iterator find(const_reference value) {
				if (!root || _isNil(root))
					return end();
				n_p tmp = findRecursive(value, root);
				return tmp ? iterator(tmp) : end();
			}
			const_iterator find(const_reference value) const {
				if (!root || _isNil(root))
					return end();
				n_p tmp = findRecursive(value, root);
				return tmp ? iterator(tmp) : end();
			}
			allocator_type get_allocator() const { return alloc_value; }
	};
}

#endif