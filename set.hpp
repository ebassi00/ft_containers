/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:05:27 by ebassi            #+#    #+#             */
/*   Updated: 2023/03/06 13:38:44 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <functional>
#include "utility.hpp"
#include "iterator.hpp"
#include "rb_tree.hpp"

namespace ft
{
	template <class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set : public RBTree<Key, Node<Key>, RBIteratorConst<Key, Compare, Node<Key> >, RBIteratorConst<const Key, Compare, Node<Key> >, Compare, Alloc>
	{
		public:
			typedef Key													key_type;
			typedef Key													value_type;
			typedef Compare												key_compare;
			typedef typename Alloc::template rebind<Node<Key> >::other	allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename allocator_type::size_type					size_type;
			typedef RBIteratorConst<Key, Compare, Node<Key> >			iterator;
			typedef RBIteratorConst<const Key, Compare, Node<Key> >		const_iterator;

			explicit set(const Compare& comp = Compare(), const Alloc& alloc = Alloc())
			{
				this->_key_compare = comp;
				this->_key_type = key_type();
				this->_value_type = value_type();
				(void)alloc;
			}

			template <class InputIt>
			set(InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc())
			{
				this->_key_compare = comp;
				this->_key_type = key_type();
				this->_value_type = value_type();
				this->insert(first, last);
				(void)alloc;
			}

			set(const set& other)
			{
				this->_key_type = other._key_type;
				this->_value_type = other._value_type;
				this->_key_compare = other._key_compare;
				if (other.begin() != other.end())
					this->insert(other.begin(), other.end());
			}

			set &operator=(const set &rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_key_type = rhs._key_type;
				this->_value_type = rhs._value_type;
				this->_key_compare = rhs._key_compare;
				this->_alloc = rhs._alloc;
				this->clear();
				this->insert(rhs.begin(), rhs.end());
				return (*this);
			}

			virtual ~set() { clear(); }

			class value_compare : std::binary_function<value_type, value_type, bool> {
				friend class set<Key>;
					protected:
						key_compare comp;
					public:
						value_compare(key_compare c) : comp(c) {};
						typedef bool result_type;
						typedef value_type	first_argument_type;
						bool operator() (const value_type& x, const value_type& y) const { return comp(x, y); }
			};

			value_compare	value_comp() const { return (value_compare(this->key_comp())); }

			size_type	erase(Key const &key)
			{
				if (erase_deep(key) != iterator(NULL, this->_sentinel))
					return (1);
				return (0);
			}

			iterator	erase(iterator pos)
			{
				iterator	ret = this->getSuccessor(pos.node);

				this->erase_deep(*pos);
				return (ret);
			}

			iterator	erase(iterator first, iterator last)
			{
				while (first != last)
					this->erase_deep(*first++);
				return (last.node);
			}

			iterator	erase_deep(Key const & val)
			{
				pointer		node = this->find(val).node;
				pointer		tmp;
				pointer		successor;
				iterator	ret;
				
				if (node && node != this->_sentinel)
					ret = this->find(this->getSuccessor(node)->key);
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
					if (this->_c(node->key, this->_root->key))
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

			size_type	count(Key const & k) const
			{
				iterator	ret = find(k);
				if (ret == iterator(this->_sentinel, this->_sentinel))
					return (0);
				return (1);
			}

			iterator	find(Key const &val) const
			{
				pointer	node = this->_root;

				if (node && node != this->_sentinel)
					return (findPointer(node, val));
				return (iterator(this->_sentinel, this->_sentinel));
			}

			iterator	findPointer(pointer &start, Key const &val) const
			{
				if (!start || start->color == SENTINEL)
					return (iterator(this->_sentinel, this->_sentinel));
				if (this->_c(val, start->key) && start->key != val)
					return (findPointer(start->left, val));
				else if (this->_c(start->key, val) && start->key != val)
					return (findPointer(start->right, val));
				else
					return (iterator(start, this->_sentinel));
			}

			template <class InputIt>
			void	insert(InputIt first, InputIt last)
			{
				while (first != last)
					this->insert(*first++);
			};

			iterator	insert(iterator pos, const Key & val)
			{
				(void)pos;
				return (this->insert(val).first);
			}

			ft::pair<iterator, bool> insert(Key const &val)
			{
				ft::pair<iterator, bool>	ret;
				pointer						node = this->_alloc.allocate(1);

				node->color = RED;
				node->parent = this->_sentinel;
				node->left = this->_sentinel;
				node->right = this->_sentinel;
				node->key = val;

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
					if (this->_c(val, this->_root->key) && this->_root->key != val)
						return (createInsertNode(this->_root->left, node, this->_root, 1));
					else if (this->_c(this->_root->key, val) && this->_root->key != val)
						return (createInsertNode(this->_root->right, node, this->_root, 1));
					else
					{
						this->_alloc.deallocate(node, 1);
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
					if (this->_c(node->key, parent->key))
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
				if (this->_c(node->key, start->key))
					return (createInsertNode(start->left, node, start, flag));
				else if (this->_c(start->key, node->key))
					return (createInsertNode(start->right, node, start, flag));
				ret.first = iterator(node, this->_sentinel);
				this->_alloc.deallocate(node, 1);
				ret.second = false;
				return (ret);
			}

			void	clear()
			{
				iterator	iter = this->begin();
				iterator	end = this->end();

				while (iter != end)
					erase(*iter++);
			}

			iterator lower_bound(const Key& val)
			{
				iterator	ret = this->begin();

				while (ret != this->end())
				{
					if (!this->_c(ret.node->key, val))
						break ;
					ret++;
				}
				return (ret);
			}

			const_iterator lower_bound(const Key& val) const
			{
				const_iterator	ret = this->begin();

				while (ret != this->end())
				{
					if (!this->_c(ret.node->key, val))
						break ;
					ret++;
				}
				return (ret);
			}

			iterator upper_bound(const Key& val)
			{
				iterator	ret = this->begin();

				while (ret != this->end())
				{
					if (this->_c(val, ret.node->key))
						break ;
					ret++;
				}
				return (ret);
			}

			const_iterator upper_bound(const Key& val) const
			{
				const_iterator	ret = this->begin();

				while (ret != this->end())
				{
					if (this->_c(val, ret.node->key))
						break ;
					ret++;
				}
				return (ret);
			}

			ft::pair<iterator, iterator>	equal_range(const Key& key)
			{
				return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
			}

			ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const
			{
				return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
			}
	};

	template <class T, class Compare, class Alloc>
	bool operator==(set <T, Compare, Alloc> const &lhs, set <T, Compare, Alloc> const &rhs)
	{
		typename set<T, Compare, Alloc>::iterator	iter = lhs.begin();
		typename set<T, Compare, Alloc>::iterator	iter2 = rhs.begin();
	
		while (iter != lhs.end())
		{
			if (*iter != *iter2)
				return (0);
			iter++;
			iter2++;
		}
		if (iter2 != rhs.end())
			return (0);
		return (1);
	}

	template <class T, class Compare, class Alloc>
	bool operator!=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator<(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator<=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (!(lhs > rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator>(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator>=(set<T, Compare, Alloc> const & lhs, set<T, Compare, Alloc> const & rhs)
	{
		return (!(lhs < rhs));
	}
}