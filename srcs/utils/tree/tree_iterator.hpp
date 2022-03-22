#pragma once

#include "tree.hpp"

namespace ft
{

template<class T, class Node, class Compare>
	class tree_iterator : ft::iterator<std::bidirectional_iterator_tag, Node> {
		public:
			typedef T value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Node>::value_type			node_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Node>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Node>::iterator_category		iterator_category;

			//FIXME: Esto tiene que ser privado
			typedef RedBlackTree<value_type, Node, Compare> tree;
			typedef Node*		node_pointer;
			typedef Node&		node_reference;

			typedef T*		pointer;
			typedef T&		reference;
			
			tree_iterator(const Compare comp = Compare()) : comp_(comp)
			{
				this->_elemPtr = NULL;
				this->tree_ptr_ = NULL;
			}

			tree_iterator(Node *ptr, tree *tree_ptr, const Compare comp = Compare()) : comp_(comp)
			{
				this->_elemPtr = ptr;
				this->tree_ptr_ = tree_ptr;
			}

			template <class U, class V, class X>
			tree_iterator<U, V, X>(const tree_iterator<U, V, X> &it)
			{
				this->_elemPtr = it.base();
				this->tree_ptr_ = it.tree_ptr_;
			}

			virtual ~tree_iterator() {}
	
			tree_iterator &operator=(const tree_iterator &it)
			{
				if (this == &it)
					return *this;

				this->_elemPtr = it._elemPtr;
				this->tree_ptr_ = it.tree_ptr_;
				return *this;
			}

			node_pointer base() const
			{
				return this->_elemPtr;
			}

			/* ACCESS OPERATORS*/

			reference &operator*() const
			{
				return this->_elemPtr->data;
			}

			pointer operator->() const
			{
				return this->_elemPtr;
			}

			/* OPERATIONS OPERATORS*/
			tree_iterator &operator++()
			{
				Node *p;

				if (!this->_elemPtr->right->isEmpty()) {
					this->_elemPtr = this->_elemPtr->right;
					while (!this->_elemPtr->left->isEmpty())
						this->_elemPtr = this->_elemPtr->left;
				} else {
					p = this->_elemPtr->parent;
					while (p != NULL && this->_elemPtr == p->right) {
						this->_elemPtr = p;
						p = p->parent;
					}
        			this->_elemPtr = p;
				}

				return *this;
			}

			tree_iterator operator++(int)
			{
				tree_iterator tmp_it(*this);
				this->operator++();
				return tmp_it;
			}
			
			tree_iterator &operator--()
			{
				if (this->_elemPtr == NULL) {
					this->_elemPtr = this->tree_ptr_->maximum();
					return *this;
				}

				if (!this->_elemPtr->left->isEmpty()) {
					this->_elemPtr = this->_elemPtr->left;
					while (!this->_elemPtr->right->isEmpty())
						this->_elemPtr = this->_elemPtr->right;
				} else {
					Node *p = this->_elemPtr->parent;
					while (p != NULL && this->_elemPtr == p->left) {
						this->_elemPtr = p;
						p = p->parent;
					}
					this->_elemPtr = p;
				}

				return *this;
			}

			tree_iterator operator--(int)
			{
				tree_iterator tmp_it(*this);
				this->operator--();
				return tmp_it;
			}

			bool operator!=(const tree_iterator &it)
			{
				return this->_elemPtr != it._elemPtr;
			}

		private:
			Node *_elemPtr;
			Compare comp_;
			tree *tree_ptr_;
			
	};

}