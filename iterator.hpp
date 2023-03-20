/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:20:18 by ebassi            #+#    #+#             */
/*   Updated: 2023/02/27 15:54:16 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include "utility.hpp"

namespace ft
{
	// Iterator traits

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	// Iterator types
	
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category 	iterator_category;
	};

	template <class T>
	struct forward_iterator : ft::iterator<ft::forward_iterator_tag, T>
	{
		typedef typename std::forward_iterator_tag									iterator_category;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::reference		reference;
		typedef T																	iterator_type;
	};

	template <class T>
	struct contiguous_iterator : ft::iterator<ft::contiguous_iterator_tag, T>
	{
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::value_type			value_type;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::pointer				pointer;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::iterator_category	iterator_category;
		typedef T																			iterator_type;
	};
	

	template <class T>
	class bidirectional_iterator : ft::iterator<bidirectional_iterator_tag, T>
	{
		public:
			typedef typename std::bidirectional_iterator_tag									iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
			typedef T																			iterator_type;

			bidirectional_iterator() : _pointed(NULL) {};
			bidirectional_iterator(pointer p) : _pointed(p)  {};
			bidirectional_iterator(bidirectional_iterator const & src) : _pointed(src._pointed) {};
			bidirectional_iterator& operator=(bidirectional_iterator const & src)
			{
				if (this == &src)
					return (*this);
				this->_pointed = src._pointed;
				return (*this);
			}
			virtual ~bidirectional_iterator() {};
			reference operator*() const { return *(this->_pointed); }
			bool	operator==(bidirectional_iterator const & src) { return ((this->_pointed == src._pointed) ? true : false); }
			bool	operator!=(bidirectional_iterator const & src) { return ((this->_pointed != src._pointed) ? true : false); }
			bidirectional_iterator&	operator++() { this->_pointed++; return *this; }
			bidirectional_iterator	operator++(int) { bidirectional_iterator tmp(*this); this->_pointed++; return (tmp); };
			bidirectional_iterator&	operator--() { this->_pointed--; return *this; };
			bidirectional_iterator	operator--(int) { bidirectional_iterator tmp(*this); this->_pointed--; return (tmp); };
			template <class InputIt>
			friend size_t operator-(InputIt const &lhs, InputIt const &rhs);

		private:
			pointer	_pointed;
	};

	template <class T>
	class random_access_iterator : ft::iterator<random_access_iterator_tag, T>
	{
		public:
			typedef typename std::random_access_iterator_tag									iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef size_t																		size_type;
			typedef T*																			iterator_type;

			random_access_iterator() : _pointed(NULL), _value(value_type()) {};
			random_access_iterator(pointer p) : _pointed(p), _value(value_type()) {};
			random_access_iterator(random_access_iterator const &src) : _value(src._value) { this->_pointed = src.pointed();}
			random_access_iterator&	operator=(random_access_iterator const & src)
			{
				if (this == &src)
					return (*this);
				this->_pointed = src._pointed;
				// this->_value = value_type();
				return (*this);
			}
			virtual	~random_access_iterator() {};
			reference				operator*() const { return (*_pointed); }
			pointer					operator->() { return &(this->operator*()); }
			random_access_iterator	operator+(difference_type n) const { return (_pointed + n); }
			random_access_iterator	operator-(difference_type n) const { return (_pointed - n); }
			random_access_iterator&	operator++() {_pointed++; return (*this); }
			random_access_iterator	operator++(int) {random_access_iterator ret(*this); _pointed++; return (ret); }
			random_access_iterator&	operator--() {_pointed--; return (*this); }
			random_access_iterator	operator--(int) {random_access_iterator ret(*this); _pointed--; return (ret); }
			random_access_iterator&	operator+=(difference_type n) {_pointed += n; return (*this); }
			random_access_iterator&	operator-=(difference_type n) {_pointed -= n; return (*this); }
			// bool					operator==(random_access_iterator const & src) { if (this->pointed() == src.pointed()) return true; return false; }
			bool					operator!=(random_access_iterator const & src) { if (this->pointed() == src.pointed()) return false; return true; }
			operator				random_access_iterator<const T>() const { return (random_access_iterator<const T>(this->_pointed)); }
			difference_type			operator-(random_access_iterator const & src) const { return (this->pointed() - src.pointed()); }
			difference_type			operator+(random_access_iterator const & src) const { return (this->pointed() + src.pointed()); }
			reference				operator[](difference_type n) { return (*(_pointed + n)); }
			pointer					pointed() const { return this->_pointed; }
			
		private:
			pointer	_pointed;
			T		_value;
	};

	template <class InputIterator>
	class reverse_iterator : ft::iterator<typename InputIterator::iterator_category, typename InputIterator::value_type>
	{
		public:
			typedef InputIterator													iterator_type;
			typedef typename ft::iterator_traits<InputIterator>::difference_type	difference_type;
			typedef typename ft::iterator_traits<InputIterator>::value_type			value_type;
			typedef typename ft::iterator_traits<InputIterator>::pointer			pointer;
			typedef typename ft::iterator_traits<InputIterator>::reference			reference;
			typedef typename ft::iterator_traits<InputIterator>::iterator_category	iterator_category;

			reverse_iterator() {};
			explicit reverse_iterator(iterator_type iter) : _base(iter) {};
			reverse_iterator&	operator=(reverse_iterator const & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_base = rhs.base();
				return (*this);
			}
			template <class ReverseIterator>
			reverse_iterator(reverse_iterator<ReverseIterator> const &other) : _base(other.base()) {};
			virtual	~reverse_iterator() {};
			iterator_type		base() const { return (_base); }
			reference			operator*() const { return (*(_base - 1)); }
			reverse_iterator	operator+(difference_type n) const { return reverse_iterator(_base - n); }
			reverse_iterator	operator-(difference_type n) const { return reverse_iterator(_base + n); }
			reverse_iterator&	operator++() { _base--; return(*this); }
			reverse_iterator	operator++(int) { reverse_iterator ret(*this); this->_base--; return(ret); }
			reverse_iterator&	operator--() { _base++; return(*this); }
			reverse_iterator	operator--(int) { reverse_iterator ret(*this); this->_base++; return(ret); }
			reverse_iterator&	operator+=(difference_type n) { _base -= n; return (*this); }
			reverse_iterator&	operator-=(difference_type n) { _base += n; return (*this); }
			pointer 			operator->() const { return &(*(_base - 1)); }
			reference			operator[](difference_type n) const { return (*(_base - n - 1)); }
			difference_type		operator+(reverse_iterator const & src) const { return (this->base() + src.base()); }	
			difference_type		operator-(reverse_iterator const & src) const { return (src.base() - this->base()); }	

		private:
			iterator_type	_base;
	};

	template <typename T, class Compare, class NodeType>
	class RBIterator
	{
		public:
			typedef T							value_type;
			typedef T*							pointer;
			typedef T&							reference;
			typedef NodeType*					nodePointer;
			typedef std::ptrdiff_t				difference_type;
			typedef bidirectional_iterator_tag	iterator_category;

			nodePointer	node;
			nodePointer	sentinel;
			nodePointer	root;
			nodePointer	minNode;
			nodePointer	maxNode;
			Compare 	c;

			RBIterator()
			{
				node = NULL;
				sentinel = NULL;
				c = Compare();
			}
			
			RBIterator(NodeType *start) : 
				node(start),
				sentinel(findSentinel()),
				root(findRoot()),
				c(Compare()),
				minNode(min(root)),
				maxNode(max(root))
			{}

			RBIterator(NodeType *start, NodeType *endPtr) :
				node(start),
				sentinel(endPtr),
				root(findRoot()),
				c(Compare()),
				minNode(min(root)),
				maxNode(max(root))
			{}

			RBIterator(RBIterator const &src) :
				node(src.node),
				sentinel(src.sentinel),
				root(src.root),
				minNode(src.minNode),
				maxNode(src.maxNode)
			{}

			template <class T2, class C2, class NodeType2>
			RBIterator(RBIterator<T2, C2, NodeType2> const &src) :
				node(src.node),
				sentinel(src.sentinel),
				root(src.root),
				minNode(src.minNode),
				maxNode(src.maxNode)
			{}

			RBIterator&	operator=(RBIterator const &rhs)
			{
				if (this == &rhs)
					return (*this);
				this->node = rhs.node;
				this->sentinel = rhs.sentinel;
				this->root = rhs.root;
				this->minNode = rhs.minNode;
				this->maxNode = rhs.maxNode;
				return (*this);
			}

			template <class InputIt>
			RBIterator&	operator=(InputIt const &rhs)
			{
				this->node = rhs.node;
				this->sentinel = rhs.sentinel;
				this->root = rhs.root;
				this->minNode = rhs.minNode;
				this->maxNode = rhs.maxNode;
				return (*this);
			}
			
			~RBIterator() {};

			// Overloads

			reference	operator*() const { return (this->node->key); }
			pointer		operator->() const { return &(this->node->key); }
			bool		operator==(RBIterator const &rhs) { return ((this->node == rhs.node) ? true : false); }
			bool		operator!=(RBIterator const &rhs)
			{
				if ((this->node && !rhs.node) || (!this->node && rhs.node))
					return (true);
				else if (!this->node && !rhs.node)
					return (false);
				return ((this->node == rhs.node) ? false : true);
			}
			RBIterator&	operator++() { this->node = getSuccessor(this->node); return (*this); }
			RBIterator operator++(int) { RBIterator ret(*this); ++(*this); return (ret); }
			RBIterator&	operator--() { this->node = getPredecessor(this->node); return (*this); }
			RBIterator operator--(int) { RBIterator ret(*this); --(*this); return (ret); }
			RBIterator	operator-(difference_type n) const
			{
				RBIterator	ret(*this);
				for (int i = 0; i < n; i++)
					ret--;
				return (ret);
			}
			RBIterator	operator+(difference_type n) const
			{
				RBIterator	ret(*this);
				for (int i = 0; i < n; i++)
					ret++;
				return (ret);
			}

		private:
			nodePointer min()
			{
				nodePointer*	node = &root;

				if (!(*node) || (*node) == sentinel)
					return (sentinel);

				while ((*node)->left && (*node)->left != sentinel)
					node = &(*node)->left;
				return (*node);
			}

			nodePointer	min(nodePointer &node)
			{
				nodePointer	*tmp = &node;

				if (!(*tmp) || !tmp)
					return (NULL);

				while (*tmp != sentinel && (*tmp)->left != sentinel)
					tmp = &((*tmp)->left);
				return (*tmp);
			}

			nodePointer max()
			{
				nodePointer	*node = &root;

				if (!(*node) || (*node) == sentinel || !node)
					return (sentinel);

				while ((*node)->right && (*node)->right != sentinel)
					node = &(*node)->right;
				return (*node);
			}

			nodePointer max(nodePointer &node)
			{
				nodePointer	*tmp = &node;

				if (!(*tmp) || !tmp)
					return (NULL);

				while (*tmp != sentinel && (*tmp)->right != sentinel)
					tmp = &((*tmp)->right);
				return (*tmp);
			}

			nodePointer findSentinel()
			{
				nodePointer	*tmp = &this->node;

				if (!(*tmp))
					return (NULL);
				
				while ((*tmp)->color != 2)
					tmp = &((*tmp)->left);
				return (*tmp);
			}

			nodePointer	findRoot()
			{
				nodePointer*	tmp = &this->node;
				
				while (tmp && *tmp && *tmp != sentinel && (*tmp)->parent != sentinel)
					tmp = &((*tmp)->parent);
				return (*tmp);
			}

			nodePointer	getSuccessor(nodePointer &node)
			{
				nodePointer*	tmp = &node;

				if (node == sentinel)
					return (sentinel);
				if (node == max(sentinel->parent))
					return (sentinel);
				if (node->parent == sentinel && node->left == sentinel && node->right == sentinel)
					return (sentinel);
				if ((*tmp)->right != sentinel)
					return (min((*tmp)->right));
				else
				{
					while ((*tmp)->parent != sentinel)
					{
						if ((*tmp)->parent->left == *tmp)
						{
							tmp = &((*tmp)->parent);
							break ;
						}
						tmp = &(*tmp)->parent;
					}
					return (*tmp);
				}
			}

			nodePointer	getPredecessor(nodePointer & node)
			{
				nodePointer*	tmp = &node;
				
				if (node == sentinel)
					return (max(node->parent));
				if (node == min(sentinel->parent))
					return (sentinel);
				if ((*tmp)->left != sentinel)
					return (max((*tmp)->left));
				else
				{
					while ((*tmp)->parent != sentinel)
					{
						if ((*tmp)->parent->right == *tmp)
						{
							tmp = &(*tmp)->parent;
							break ;
						}
						tmp = &(*tmp)->parent;
					}
					return (*tmp);
				}
			}
	};

	template <typename T, class Compare, class NodeType>
	class RBIteratorConst
	{
		public:
			typedef T							value_type;
			typedef const T*					pointer;
			typedef const T&					reference;
			typedef NodeType*					nodePointer;
			typedef std::ptrdiff_t				difference_type;
			typedef bidirectional_iterator_tag	iterator_category;

			nodePointer	node;
			nodePointer	sentinel;
			nodePointer	root;
			nodePointer	minNode;
			nodePointer	maxNode;
			Compare 	c;

			RBIteratorConst()
			{
				node = NULL;
				sentinel = NULL;
				c = Compare();
			}
			
			RBIteratorConst(NodeType *start) : 
				node(start),
				sentinel(findSentinel()),
				root(findRoot()),
				c(Compare()),
				minNode(min(root)),
				maxNode(max(root))
			{}

			RBIteratorConst(NodeType *start, NodeType *endPtr) :
				node(start),
				sentinel(endPtr),
				root(findRoot()),
				c(Compare()),
				minNode(min(root)),
				maxNode(max(root))
			{}

			RBIteratorConst(RBIteratorConst const &src) :
				node(src.node),
				sentinel(src.sentinel),
				root(src.root),
				minNode(src.minNode),
				maxNode(src.maxNode)
			{}

			template <class InputIt>
			RBIteratorConst(InputIt const &src)
			{
				if (src.node == NULL)
					return ;
				node = src.node;
				sentinel = src.sentinel;
				root = src.root;
				minNode = src.minNode;
				maxNode = src.maxNode;
			}

			RBIteratorConst&	operator=(RBIteratorConst const &rhs)
			{
				if (this == &rhs)
					return (*this);
				this->node = rhs.node;
				this->sentinel = rhs.sentinel;
				this->root = rhs.root;
				this->minNode = rhs.minNode;
				this->maxNode = rhs.maxNode;
				return (*this);
			}

			template <class InputIt>
			RBIteratorConst&	operator=(InputIt const &rhs)
			{
				this->node = rhs.node;
				this->sentinel = rhs.sentinel;
				this->root = rhs.root;
				this->minNode = rhs.minNode;
				this->maxNode = rhs.maxNode;
				return (*this);
			}
			
			~RBIteratorConst() {};

			// Overloads

			reference	operator*() const { return (this->node->key); }
			pointer		operator->() const { return &(this->node->key); }
			bool		operator==(RBIteratorConst const &rhs) { return ((this->node == rhs.node) ? true : false); }
			bool		operator!=(RBIteratorConst const &rhs)
			{
				if ((this->node && !rhs.node) || (!this->node && rhs.node))
					return (true);
				else if (!this->node && !rhs.node)
					return (false);
				return ((this->node == rhs.node) ? false : true);
			}
			RBIteratorConst&	operator++() { this->node = getSuccessor(this->node); return (*this); }
			RBIteratorConst	operator++(int) { RBIteratorConst ret(*this); ++(*this); return (ret); }
			RBIteratorConst&	operator--() { this->node = getPredecessor(this->node); return (*this); }
			RBIteratorConst	operator--(int) { RBIteratorConst ret(*this); --(*this); return (ret); }
			RBIteratorConst	operator-(difference_type n) const
			{
				RBIteratorConst	ret(*this);
				for (int i = 0; i < n; i++)
					ret--;
				return (ret);
			}
			RBIteratorConst	operator+(difference_type n) const
			{
				RBIteratorConst	ret(*this);
				for (int i = 0; i < n; i++)
					ret++;
				return (ret);
			}

		private:
			nodePointer min()
			{
				nodePointer*	node = &root;

				if (!(*node) || (*node) == sentinel)
					return (sentinel);

				while ((*node)->left && (*node)->left != sentinel)
					node = &(*node)->left;
				return (*node);
			}

			nodePointer	min(nodePointer &node)
			{
				nodePointer	*tmp = &node;

				if (!(*tmp) || !tmp)
					return (NULL);

				while (*tmp != sentinel && (*tmp)->left != sentinel)
					tmp = &((*tmp)->left);
				return (*tmp);
			}

			nodePointer max()
			{
				nodePointer	*node = &root;

				if (!(*node) || (*node) == sentinel || !node)
					return (sentinel);

				while ((*node)->right && (*node)->right != sentinel)
					node = &(*node)->right;
				return (*node);
			}

			nodePointer max(nodePointer &node)
			{
				nodePointer	*tmp = &node;

				if (!tmp || !(*tmp))
					return (NULL);

				while (*tmp != sentinel && (*tmp)->right != sentinel)
					tmp = &((*tmp)->right);
				return (*tmp);
			}

			nodePointer findSentinel()
			{
				nodePointer	*tmp = &this->node;

				if (!(*tmp) || !tmp)
					return (NULL);
					
				while (tmp && (*tmp)->color != 2)
					tmp = &((*tmp)->left);
				return (*tmp);
			}

			nodePointer	findRoot()
			{
				nodePointer*	tmp = &this->node;
				
				while (tmp && *tmp && *tmp != sentinel && (*tmp)->parent != sentinel)
					tmp = &((*tmp)->parent);
				return (*tmp);
			}

			nodePointer	getSuccessor(nodePointer &node)
			{
				nodePointer*	tmp = &node;

				if (node == sentinel)
					return (sentinel);
				if (node == max(sentinel->parent))
					return (sentinel);
				if (node->parent == sentinel && node->left == sentinel && node->right == sentinel)
					return (sentinel);
				if ((*tmp)->right != sentinel)
					return (min((*tmp)->right));
				else
				{
					while ((*tmp)->parent != sentinel)
					{
						if ((*tmp)->parent->left == *tmp)
						{
							tmp = &(*tmp)->parent;
							break ;
						}
						tmp = &(*tmp)->parent;
					}
					return (*tmp);
				}
			}

			nodePointer	getPredecessor(nodePointer & node)
			{
				nodePointer*	tmp = &node;
				
				if (node == sentinel)
					return (max(node->parent));
				if (node == min(sentinel->parent))
					return (sentinel);
				if ((*tmp)->left != sentinel)
					return (max((*tmp)->left));
				else
				{
					while ((*tmp)->parent != sentinel)
					{
						if ((*tmp)->parent->right == *tmp)
						{
							tmp = &(*tmp)->parent;
							break ;
						}
						tmp = &(*tmp)->parent;
					}
					return (*tmp);
				}
			}
	};

	// Overloads

	template <class InputIt>
	random_access_iterator<InputIt>	operator+(int n, random_access_iterator<InputIt> const & rhs) { return rhs.pointed() + n; }

	template <class InputIt>
	random_access_iterator<InputIt>	operator-(int n, random_access_iterator<InputIt> const & rhs) { return rhs.pointed() - n; }

	template <class InputIt>
	reverse_iterator<InputIt>	operator+(int n, reverse_iterator<InputIt> const & rhs) { return reverse_iterator<InputIt>(rhs.base() - n); }

	template <class InputIt>
	reverse_iterator<InputIt>	operator-(int n, reverse_iterator<InputIt> const & rhs) { return reverse_iterator<InputIt>(rhs.base() + n); }

	template <class InputIt>
	bool	operator==(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() == rhs.pointed()) ? true : false); }

	template <class InputIt, class InputIt2>
	bool	operator==(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() == rhs.pointed()) ? true : false); }

	template <class InputIt>
	bool	operator!=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() == rhs.pointed()) ? false : true); }

	template <class InputIt, class InputIt2>
	bool	operator!=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() == rhs.pointed()) ? false : true); }

	template <class InputIt>
	bool	operator<(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() < rhs.pointed()) ? true : false); }

	template <class InputIt, class InputIt2>
	bool	operator<(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() < rhs.pointed()) ? true : false); }

	template <class InputIt>
	bool	operator<=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() <= rhs.pointed()) ? true : false); }

	template <class InputIt, class InputIt2>
	bool	operator<=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() <= rhs.pointed()) ? true : false); }

	template <class InputIt>
	bool	operator>(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() > rhs.pointed()) ? true : false); }

	template <class InputIt, class InputIt2>
	bool	operator>(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() > rhs.pointed()) ? true : false); }
	
	template <class InputIt>
	bool	operator>=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() >= rhs.pointed()) ? true : false); }

	template <class InputIt, class InputIt2>
	bool	operator>=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() >= rhs.pointed()) ? true : false); }

	template <class InputIt>
	bool			operator==(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return (lhs.base() == rhs.base()); }

	template <class InputIt, class InputIt2>
	bool			operator==(reverse_iterator<InputIt2> const & lhs, reverse_iterator<InputIt> const & rhs) { return (lhs.base() == rhs.base()); }

	template <class InputIt>
	bool			operator!=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return ((lhs.base() == rhs.base()) ? false : true); }

	template <class InputIt, class InputIt2>
	bool			operator!=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt2> const & rhs) { return ((lhs.base() == rhs.base()) ? false : true); }

	template <class InputIt>
	bool	operator<(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return ((lhs.base() > rhs.base()) ? true : false); }

	template <class InputIt, class InputIt2>
	bool	operator<(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt2> const & rhs) { return ((lhs.base() > rhs.base()) ? true : false); }

	template <class InputIt>
	bool	operator<=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return ((lhs.base() >= rhs.base()) ? true : false); }

	template <class InputIt, class InputIt2>
	bool	operator<=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt2> const & rhs) { return ((lhs.base() >= rhs.base()) ? true : false); }

	template <class InputIt>
	bool	operator>(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return ((lhs.base() < rhs.base()) ? true : false); }

	template <class InputIt, class InputIt2>
	bool	operator>(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt2> const & rhs) { return ((lhs.base() < rhs.base()) ? true : false); }
	
	template <class InputIt>
	bool	operator>=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return ((lhs.base() <= rhs.base()) ? true : false); }

	template <class InputIt, class InputIt2>
	bool	operator>=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt2> const & rhs) { return ((lhs.base() <= rhs.base()) ? true : false); }

	// Operations

	template<class T>
	typename iterator_traits<T>::difference_type distance (T first, T last)
	{
		typename ft::iterator_traits<T>::difference_type ret = 0;

		while (first++ != last)
			ret++;
		return (ret);
	}

	template<class T1, class T2>
	typename iterator_traits<T1>::difference_type distance (T1 first, T2 last)
	{
		typename ft::iterator_traits<T1>::difference_type ret = 0;

		while (first++ != last)
			ret++;
		return (ret);
	}
}