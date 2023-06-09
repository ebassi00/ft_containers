/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:35:49 by ebassi            #+#    #+#             */
/*   Updated: 2023/02/20 17:14:00 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utility.hpp"
#include "iterator.hpp"
#include "rb_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map: public RBTree<ft::pair<const Key, T>, Node<ft::pair<const Key, T> >, RBIterator<ft::pair<const Key, T>, Compare, Node<ft::pair<const Key, T> > >, RBIteratorConst<ft::pair<const Key, T>, Compare, Node<ft::pair<const Key, T> > >, Compare, Allocator>
	{
		public:
			typedef Key																key_type;
			typedef T																mapped_type;
			typedef ft::pair<const Key, T>											value_type;
			typedef typename ft::pair<const Key, T>									Pair;
			typedef typename ft::NodeRB2<Pair>										originalNode;
			typedef typename Allocator::template rebind<Node<value_type> >::other	allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef typename allocator_type::size_type								size_type;
			typedef RBIterator<value_type, Compare, Node<value_type> >				iterator;
			typedef RBIteratorConst<value_type, Compare, Node<value_type> >			const_iterator;
			typedef Compare															key_compare;

			map() {};
			
			explicit map(const Compare& comp, const Allocator& alloc = Allocator())
			{
				(void)comp;
				(void)alloc;
			}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			{
				this->insert(first, last);
				(void)comp;
				(void)alloc;
			}

			map (const map &other)
			{
				this->insert(other.begin(), other.end());
			}

			map&	operator=(map const & rhs)
			{
				if (this == &rhs)
					return (*this);
				clear();
				insert(rhs.begin(), rhs.end());
				return (*this);
			}

			~map() { clear(); }

			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T>;
				private:
					key_compare	_comp;
				public:
					value_compare(key_compare c) : _comp(c) {}
					bool	operator() (const value_type& x, const value_type& y) const { return _comp(x.first, y.first); }
			};

			value_compare	value_comp() const { return (value_compare(this->key_comp())); }
			
			void	erase(iterator pos)
			{
				this->erase_deep(*pos);
			}

			void	erase(iterator first, iterator last)
			{
				while (first != last)
					this->erase_deep(*first++);
			}

			size_type	erase(const key_type &key)
			{
				ft::pair<key_type, mapped_type>	tmp(key, mapped_type());

				if (erase_deep(tmp) != iterator(NULL, this->_sentinel))
					return (1);
				return (0);
			}

			iterator	erase_deep(ft::pair<const Key, T> const &val)
			{
				pointer		node = this->find(val.first).node;
				pointer		tmp;
				pointer		successor;
				iterator	ret;
				
				if (node && node != this->_sentinel)
					ret = this->find(this->getSuccessor(node)->key.first);
				else
					return (iterator(NULL, this->_sentinel));

				if ((!node->left && !node->right) || (node->left == this->_sentinel && node->right == this->_sentinel))
				{
					tmp = node->parent;
					if (node->color == BLACK && node != this->_root)
						this->balanceDelete(node);
					if (tmp != this->_sentinel)
						this->unlink(tmp, node);
					else
					{
						this->_root = this->_sentinel;
						this->_sentinel->parent = this->_root;
					}
				}
				else if (this->oneChild(node) != this->_sentinel)
				{
					if (node->color == BLACK && node != this->_root)
					{
						if (this->oneChild(node)->color != RED)
							this->balanceDelete(node);
						else
							this->oneChild(node)->color = BLACK;
					}
					this->oneChild(node)->parent = node->parent;
					if (node != this->_root)
						this->link(node->parent, node, this->oneChild(node));
					else
					{
						this->_root = this->oneChild(node);
						this->_sentinel->parent = this->_root;
					}
				}
				else
				{
					if (this->_c(node->key.first, this->_root->key.first))
						successor = this->getSuccessor(node);
					else
						successor = this->getPredecessor(node);
					this->balanceDelete(successor);
					if (successor->right != this->_sentinel)
					{
						successor->right = this->_sentinel;
					}
					if (node != this->_root)
					{
						this->unlink(successor->parent, successor);
						this->link(node->parent, node, successor);
						if (node->left != this->_sentinel)
						{
							node->left->parent = successor;
							successor->left = node->left;
						}
						if (node->right != this->_sentinel)
						{
							if (successor->right != this->_sentinel)
								this->link(successor->parent, successor, successor->right);
							node->right->parent = successor;
							successor->right = node->right;
						}
					}
					else
					{
						pointer toHandle = NULL;
						pointer	toHandle2 = NULL;
						this->_root = successor;
						this->_sentinel->parent = successor;
						if (this->_root->parent->left == this->_root)
							this->_root->parent->left = this->_sentinel;
						else
							this->_root->parent->right = this->_sentinel;
						this->_root->parent = this->_sentinel;
						if (node->right == successor)
						{
							if (node->right != this->_sentinel)
								toHandle = node->right;
							this->_root->left = node->left;
							node->left->parent = this->_root;
							this->_root->color = BLACK;
						}
						else
						{
							if (node->left != this->_sentinel)
								toHandle2 = node->left;
							this->_root->right = node->right;
							node->right->parent = this->_root;
							this->_root->color = BLACK;
						}
						if (toHandle)
							createInsertNode(this->_root, toHandle, this->_root, 0);
						if (toHandle2)
							createInsertNode(this->_root, toHandle2, this->_root, 0);
					}
				}
				this->_alloc.deallocate(node, 1);
				node = NULL;
				this->_size--;
				return (ret);
			}

			iterator	find(const Key &key)
			{
				pointer							node = this->_root;
				ft::pair<key_type, mapped_type>	tmp(key, mapped_type());

				if (!node || node == this->_sentinel)
					return (iterator(this->_sentinel, this->_sentinel));
				return (findPointer(node, tmp));
			}

			const_iterator	find(const Key &key) const
			{
				pointer							node = this->_root;
				ft::pair<key_type, mapped_type>	tmp(key, mapped_type());

				if (!node || node == this->_sentinel)
					return (iterator(this->_sentinel, this->_sentinel));
				return (findPointer(node, tmp));
			}

			iterator	findPointer(pointer &start, ft::pair<const Key, T> const &val) const
			{
				if (!start || start->color == SENTINEL)
					return (iterator(this->_sentinel, this->_sentinel));
				if (this->_c(val.first, start->key.first) && start->key.first != val.first)
					return (findPointer(start->left, val));
				else if (this->_c(start->key.first, val.first) && start->key.first != val.first)
					return (findPointer(start->right, val));
				else
					return (iterator(start, this->_sentinel));
			}

			iterator	insert(iterator position, const value_type &val)
			{
				(void)position;
				return (insert(val).first);
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					insert(*first++);
			}

			ft::pair<iterator, bool> insert(ft::pair<const Key, T> const &val)
			{
				ft::pair<iterator, bool> ret;
				pointer	node = new Node<value_type>(val);

				node->color = RED;
				node->parent = this->_sentinel;
				node->left = this->_sentinel;
				node->right = this->_sentinel;

				if (!this->_size)
				{
					this->_root = node;
					this->_sentinel->parent = node;
					node->color = BLACK;
					this->_size++;
					ret.first = iterator(node, this->_sentinel);
					ret.second = true;
					return (ret);
				}
				else
				{
					ret.first = iterator(node, this->_sentinel);
					ret.second = false;
					if (this->_c(val.first, this->_root->key.first) && this->_root->key.first != val.first)
						return (createInsertNode(this->_root->left, node, this->_root, 1));
					else if (this->_c(this->_root->key.first, val.first) && this->_root->key.first != val.first)
						return (createInsertNode(this->_root->right, node, this->_root, 1));
					else
					{
						delete node;
						ret.first = find(node->key.first);
						return (ret);
					}
				}
			}

			ft::pair<iterator, bool> createInsertNode(pointer &start, pointer &node, pointer &parent, int flag)
			{
				ft::pair<iterator, bool>	ret;
				
				if (!start || start == this->_sentinel)
				{
					node->parent = parent;
					if (this->_c(node->key.first, parent->key.first))
						parent->left = node;
					else
						parent->right = node;
					start = node;
					if (flag)
						this->_size++;
					this->balanceInsert(start);
					ret.first = iterator(node, this->_sentinel);
					ret.second = true;
					return (ret);
				}
				if (this->_c(node->key.first, start->key.first))
					return (createInsertNode(start->left, node, start, flag));
				else if (this->_c(start->key.first, node->key.first))
					return (createInsertNode(start->right, node, start, flag));
				ret.first = find(node->key.first);
				delete node;
				ret.second = false;
				return (ret);
			}

			T&	at(const Key &key)
			{
				iterator tmp = find(key);

				if (tmp.node == this->_sentinel)
					throw std::out_of_range("map: at");
				return ((*tmp).second);
			}

			void	clear()
			{
				while (this->size())
					erase(this->min());
			}

			T&	operator[](const Key& key)
			{
				try
				{
					return (at(key));
				}
				catch(const std::exception& e)
				{
					ft::pair<key_type, mapped_type>	ret(key, mapped_type());
					insert(ret);
					return (at(key));
				}				
			}

			size_type	count(const Key &key) const
			{
				if (find(key).node == this->_sentinel)
					return (0);
				return (1);
			}

			iterator		lower_bound(const Key& key)
			{
				iterator	ret = this->begin();

				while (ret != this->end())
				{
					if (!this->_c(ret.node->key.first, key))
						break ;
					ret++;
				}
				return (ret);
			}

			const_iterator	lower_bound(const Key& key) const
			{
				const_iterator	ret = this->begin();

				while (ret != this->end())
				{
					if (!this->_c(ret.node->key.first, key))
						break ;
					ret++;
				}
				return (ret);
			}

			iterator		upper_bound(const Key& key)
			{
				iterator	ret = this->begin();

				while (ret != this->end())
				{
					if (this->_c(key, ret.node->key.first))
						break ;
					ret++;
				}
				return (ret);
			}

			const_iterator	upper_bound(const Key& key) const
			{
				const_iterator	ret = this->begin();

				while (ret != this->end())
				{
					if (this->_c(key, ret.node->key.first))
						break ;
					ret++;
				}
				return (ret);
			}

			ft::pair<iterator, iterator>				equal_range(const Key& key)
			{
				return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
			}

			ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const
			{
				return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
			}
	};

	template <class T>
	bool	operator==(const T& lhs, const T& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return ((lhs == rhs) ? false : true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs > rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
}