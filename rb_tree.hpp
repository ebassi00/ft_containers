/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:04:35 by ebassi            #+#    #+#             */
/*   Updated: 2023/03/06 13:43:53 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <utility>
#include <iostream>
#include <limits.h>
#include "utility.hpp"
#include "iterator.hpp"

namespace ft
{
	enum node_color
	{
		RED,
		BLACK,
		SENTINEL
	};
	
	template <typename T>
	struct Node
	{
		node_color	color;
		Node		*left;
		Node		*right;
		Node		*parent;
		T			key;

		template <class U, class V>
		Node(ft::pair<U, V> const &val) : key(val) {};
	};

	template <class Pair>
	struct NodeRB2 {
		NodeRB2					*parent;
		NodeRB2 				*left;
		NodeRB2 				*right;
		Pair					key; 
		int 					color;
	};

	template <class Key, class NodeType, class Iterator, class ConstIterator, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class RBTree
	{
		public:
			typedef NodeRB2<Key>											originalNode;
			typedef Key														key_type;
			typedef Key														value_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef typename Alloc::template rebind<NodeType>::other		allocator_type;
			typedef typename Alloc::template rebind<originalNode>::other	allocator_type2;
			typedef typename allocator_type::size_type						size_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef Iterator												iterator;
			typedef ConstIterator											const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			
			RBTree(): _root(NULL), _size(0), _alloc(allocator_type()) 
			{
				_sentinel = _alloc.allocate(1);
				_sentinel->color = SENTINEL;
				_root = _sentinel;
				_sentinel->parent = _root;
			}

			RBTree(RBTree const &src)
			{
				_alloc = allocator_type();
				_sentinel = _alloc.allocate(1);
				_sentinel->color = SENTINEL;
				_root = _sentinel;
				_sentinel->parent = _root;
				_root = _sentinel;
				_size = 0;
				iterator	iter = src.begin();
				while (iter != src.end())
					this->insert(*iter++);
			}

			RBTree &operator=(RBTree const &rhs)
			{
				if (this == &rhs)
					return (*this);
				_alloc = rhs.get_allocator();
				_sentinel = _alloc.allocate(1);
				_sentinel->color = SENTINEL;
				_root = _sentinel;
				_sentinel->parent = _root;
				_root = _sentinel;
				_size = 0;
				this->insert(rhs.begin(), rhs.end());
				return (*this);
			}

			~RBTree() { _alloc.deallocate(_sentinel, 1); }

			allocator_type	get_allocator() const { return (this->_alloc); }
			bool empty() const { return ((!this->_size) ? true : false); }
			size_type size() const { return this->_size; }
			size_type max_size() const { return _alloc2.max_size(); }

			iterator				begin() { return (iterator(min(), _sentinel)); }
			const_iterator			begin() const { return (const_iterator(min(), _sentinel)); }
			iterator				end() { return iterator(_sentinel, _sentinel); }
			const_iterator			end() const { return const_iterator(_sentinel, _sentinel); }
			reverse_iterator		rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator	rbegin() const { return (const_iterator(end())); }
			reverse_iterator		rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }


			virtual iterator					findPointer(pointer &start, Key const &val) const = 0;
			virtual iterator					erase_deep(Key const &val) = 0;
			virtual ft::pair<iterator, bool>	insert(Key const &val) = 0;
			virtual ft::pair<iterator, bool>	createInsertNode(pointer &start, pointer &node, pointer &parent, int flag) = 0;
			virtual void						clear()	= 0;


			pointer	min() const
			{
				const pointer*	node = &_root;

				if (!(*node) || (*node) == _sentinel)
					return (_sentinel);

				while ((*node)->left && (*node)->left != _sentinel)
					node = &(*node)->left;
				return (*node);
			}

			pointer	min(pointer const &node) const
			{
				const pointer*	tmp = &node;

				if (!(*tmp) || (*tmp) == _sentinel)
					return (_sentinel);

				while ((*tmp)->left && (*tmp)->left != _sentinel)
					tmp = &(*tmp)->left;
				return (*tmp);
			}

			pointer	max() const
			{
				pointer	node = _root;

				if (!node || node == _sentinel)
					return (_sentinel);

				while (node->right && node->right != _sentinel)
					node = node->right;
				return (node);
			}

			pointer	max(pointer const &node) const
			{
				pointer	tmp = node;

				if (!node || node == _sentinel)
					return (_sentinel);

				while (tmp->right != _sentinel)
					tmp = tmp->right;
				return (tmp);
			}

			pointer	getPredecessor(pointer const &node) const
			{
				pointer	tmp = node;
				
				if (node == min())
					return (_sentinel);
				if (tmp->left != _sentinel)
					return (max(tmp->left));
				else
				{
					while (tmp->parent != _sentinel)
					{
						if (tmp->parent->right == tmp)
						{
							tmp = tmp->parent;
							break ;
						}
						tmp = tmp->parent;
					}
					return (tmp);
				}
			}

			pointer	getSuccessor(pointer const &node) const
			{
				pointer	tmp = node;
				
				if (node == max())
					return (_sentinel);
				if (tmp->right != _sentinel)
					return (min(tmp->right));
				else
				{
					while (tmp->parent != _sentinel)
					{
						if (tmp->parent->left == tmp)
						{
							tmp = tmp->parent;
							break ;
						}
						tmp = tmp->parent;
					}
					return (tmp);
				}
			}

			void	swap(RBTree &rhs)
			{
				if (this == &rhs)
					return ;

				pointer			tmpRoot = this->_root;
				pointer			tmpSentinel = this->_sentinel;
				size_type		tmpSize = this->_size;
				allocator_type	tmpAlloc = this->_alloc;
				Compare			tmpCompare = this->_c;

				this->_root = rhs._root;
				this->_c = rhs._c;
				this->_sentinel = rhs._sentinel;
				this->_size = rhs._size;
				this->_alloc = rhs._alloc;

				rhs._root = tmpRoot;
				rhs._alloc = tmpAlloc;
				rhs._c = tmpCompare;
				rhs._sentinel = tmpSentinel;
				rhs._size = tmpSize;
			}

			key_compare		key_comp() const { return (this->_key_compare); }

		protected:
			key_type		_key_type;
			value_type		_value_type;
			key_compare		_key_compare;
			value_compare	_value_compare;
			pointer			_root;
			pointer			_sentinel;
			size_type		_size;
			allocator_type	_alloc;
			allocator_type2	_alloc2;
			Compare			_c;

			void	getFamily(pointer &parent, pointer &grandParent, pointer &uncle)
			{
				if (parent != _sentinel)
					grandParent = parent->parent;
				else
					grandParent = NULL;
				if (grandParent != _sentinel && grandParent)
				{
					if (grandParent->left == parent && grandParent->right != _sentinel)
						uncle = grandParent->right;
					else if (grandParent->right == parent && grandParent->left != _sentinel)
						uncle = grandParent->left;
					else
						uncle = NULL;
				}
				else
					uncle = NULL;
			}

			void	balanceInsert(pointer &node)
			{
				pointer*	tmp = &node;
				pointer		parent = node->parent;
				pointer		grandParent;
				pointer		uncle;

				while (1 && *tmp && *tmp != _sentinel)
				{
					parent = (*tmp)->parent;
					getFamily(parent, grandParent, uncle);
					if (!parent || parent == _sentinel)
					{
						(*tmp)->color = BLACK;
						break ;
					}
					else if (parent->color == BLACK)
						break ;
					else if (uncle && (*tmp)->color == RED && parent->color == RED && uncle->color == RED)
					{
						parent->color = BLACK;
						uncle->color = BLACK;
						grandParent->color = RED;
						tmp = &(*tmp)->parent->parent;
					}
					else if ((*tmp)->color == RED && parent->color == RED)
					{
						if (parent->right == (*tmp) && grandParent->left == parent)
							tmp = rotateLeft(parent);
						else if (parent->left == (*tmp) && grandParent->right == parent)
							tmp = rotateRight(parent);
						else if (parent->right == (*tmp) && grandParent->right == parent)
						{
							parent->color = BLACK;
							grandParent->color = RED;
							rotateLeft(grandParent);
							break ;
						}
						else if (parent->left == (*tmp) && grandParent->left == parent)
						{
							parent->color = BLACK;
							grandParent->color = RED;
							rotateRight(grandParent);
							break ;
						}
					}
					else
						break ;
				}
			}

			pointer*	rotateLeft(pointer &node)
			{
				pointer*	tmp = &node;
				pointer*	ret;
				pointer		toHandle;
				
				if ((*tmp)->right->left != _sentinel)
					toHandle = (*tmp)->right->left;
				else
					toHandle = NULL;
				if ((*tmp) == _root)
				{
					_root = (*tmp)->right;
					_sentinel->parent = _root;
					(*tmp)->right->parent = _sentinel;
				}
				else
				{
					(*tmp)->right->parent = (*tmp)->parent;
					if ((*tmp)->parent->right == (*tmp))
						(*tmp)->parent->right = (*tmp)->right;
					else
						(*tmp)->parent->left = (*tmp)->right;
				}
				(*tmp)->parent = (*tmp)->right;
				(*tmp)->right->left = (*tmp);
				(*tmp)->right = _sentinel;
				if (toHandle)
					createInsertNode((*tmp)->parent, toHandle, (*tmp)->parent, 0);
				ret = &(*tmp)->left;
				return (ret);
			}

			pointer*	rotateRight(pointer &node)
			{
				pointer*	tmp = &node;
				pointer		toHandle;
				pointer*	ret;

				if ((*tmp) && (*tmp)->left != _sentinel && (*tmp)->left->right != _sentinel)
					toHandle = (*tmp)->left->right;
				else
					toHandle = NULL;
				if ((*tmp) == _root)
				{
					_root = (*tmp)->left;
					_sentinel->parent = _root;
					(*tmp)->left->parent = _sentinel;
				}
				else
				{
					(*tmp)->left->parent = (*tmp)->parent;
					if ((*tmp)->parent->right == (*tmp))
						(*tmp)->parent->right = (*tmp)->left;
					else
						(*tmp)->parent->left = (*tmp)->left;
				}
				(*tmp)->parent = (*tmp)->left;
				(*tmp)->left->right = (*tmp);
				(*tmp)->left = _sentinel;
				if (toHandle)
					createInsertNode((*tmp), toHandle, (*tmp), 0);
				ret = &(*tmp)->right;
				return (ret);
			}

			void	getFamilyDelete(pointer &node, pointer &sibiling, pointer &leftNephew, pointer &rightNephew)
			{
				if (node->parent->left != _sentinel && node->parent->color != SENTINEL && node->parent->left == node && node->parent->right && node->parent->right != _sentinel)
					sibiling = node->parent->right;
				else if (node->parent->right != _sentinel && node->parent->color != SENTINEL && node->parent->left && node->parent->left != _sentinel)
					sibiling = node->parent->left;
				else
				{
					sibiling = NULL;
					leftNephew = NULL;
					rightNephew = NULL;
					return ;
				}
				if (sibiling && sibiling->left && sibiling->left != _sentinel)
					leftNephew = sibiling->left;
				else
					leftNephew = NULL;
				if (sibiling && sibiling->right && sibiling->right != _sentinel)
					rightNephew = sibiling->right;
				else
					rightNephew = NULL;
			}

			void	balanceDelete(pointer &node)
			{
				pointer*	tmp = &node;
				pointer		leftNephew;
				pointer		rightNephew;
				pointer		sibiling;

				while ((*tmp) != _root && (*tmp)->color == BLACK)
				{
					getFamilyDelete((*tmp), sibiling, leftNephew, rightNephew);
					if ((*tmp) == (*tmp)->parent->left)
					{
						if (sibiling && sibiling->color == RED)
						{
							(*tmp)->parent->color = RED;
							sibiling->color = BLACK;
							tmp = rotateLeft((*tmp)->parent);
						}
						else
						{
							if (leftNephew && leftNephew->color == BLACK && rightNephew && rightNephew->color == BLACK)
							{
								sibiling->color = RED;
								tmp = &(*tmp)->parent;
							}
							else if (leftNephew && leftNephew->color == RED && rightNephew && rightNephew->color == BLACK)
							{
								leftNephew->color = BLACK;
								sibiling->color = RED;
								tmp = rotateRight(sibiling);
							}
							else if (rightNephew && rightNephew->color == RED)
							{
								sibiling->color = (*tmp)->parent->color;
								(*tmp)->parent->color = BLACK;
								rightNephew->color = BLACK;
								rotateLeft((*tmp)->parent);
								break ;
							}
							else if (oneChild(*tmp) && oneChild(*tmp)->color == RED)
							{
								oneChild(*tmp)->color = BLACK;
								break ;
							}
							else if (sibiling && sibiling->color == BLACK && (*tmp)->color == BLACK)
							{
								sibiling->color = RED;
								(*tmp)->parent->color = BLACK;
								tmp = &(*tmp)->parent;
								break ;
							}
							else
								tmp = &(*tmp)->parent;
						}
					}
					else
					{
						if (sibiling && sibiling->color == RED)
						{
							(*tmp)->parent->color = RED;
							sibiling->color = BLACK;
							tmp = rotateRight((*tmp)->parent);
						}
						else
						{
							if (rightNephew && rightNephew->color == BLACK && leftNephew && leftNephew->color == BLACK)
							{
								sibiling->color = RED;
								tmp = &(*tmp)->parent;
							}
							else if (rightNephew && rightNephew->color == RED && leftNephew && leftNephew->color == BLACK)
							{
								rightNephew->color = BLACK;
								sibiling->color = RED;
								tmp = rotateLeft(sibiling);
							}
							else if (leftNephew && leftNephew->color == RED)
							{
								sibiling->color = (*tmp)->parent->color;
								(*tmp)->parent->color = BLACK;
								leftNephew->color = BLACK;
								rotateRight((*tmp)->parent);
								break ;
							}
							else if (oneChild(*tmp)->color == RED)
							{
								oneChild(*tmp)->color = BLACK;
								break ;
							}
							else if (sibiling && sibiling->color == BLACK && (*tmp)->color == BLACK)
							{
								sibiling->color = RED;
								(*tmp)->parent->color = BLACK;
								tmp = &(*tmp)->parent;
								break ;
							}
							else
								tmp = &(*tmp)->parent;
						}
					}
				}
			}

			pointer&	oneChild(pointer& node)
			{
				if (node->left != _sentinel && node->right == _sentinel)
					return (node->left);
				else if (node->right != _sentinel && node->left == _sentinel)
					return (node->right);
				return (_sentinel);
			}

			void	link(pointer& parent, pointer& oldSon, pointer& node)
			{
				if (parent == _sentinel)
					parent->parent = node;
				else if (parent->left == oldSon)
					parent->left = node;
				else
					parent->right = node;
				if (node != _sentinel)
					node->parent = parent;
			}

			void	unlink(pointer& parent, pointer& node)
			{
				if (parent->left == node)
				{
					parent->left = _sentinel;
					if (node->left != _sentinel && node->right == _sentinel)
					{
						parent->left = node->left;
						node->left->parent = parent;
					}
				}
				else
				{
					parent->right = _sentinel;
					if (node->right != _sentinel && node->left == _sentinel)
					{
						parent->right = node->right;
						node->right->parent = parent;
					}
				}
				node->parent = _sentinel;
			}
	};
}