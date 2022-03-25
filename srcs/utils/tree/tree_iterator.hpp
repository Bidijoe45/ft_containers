#pragma once

#include "tree.hpp"

namespace ft
{

template<class T, class Node, class Tree>
	class tree_iterator : ft::iterator<std::bidirectional_iterator_tag, Node> {
		public:
			typedef T value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Node>::value_type			node_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Node>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Node>::iterator_category		iterator_category;

			typedef Node*		node_pointer;
			typedef Node&		node_reference;

			typedef T*		pointer;
			typedef T&		reference;

			tree_iterator()
			{
				this->elemPtr_ = NULL;
				this->treePtr_ = NULL;
			}

			tree_iterator(Node *ptr, Tree *tree)
			{
				this->elemPtr_ = ptr;
				this->treePtr_ = tree;
			}

			template <class U, class V, class Y>
			tree_iterator(const tree_iterator<U, V, Y> &it)
			{
				this->elemPtr_ = it.base();
				this->treePtr_ = it.tree();
			}

			virtual ~tree_iterator() {}

			tree_iterator &operator=(const tree_iterator &it)
			{
				if (this == &it)
					return *this;

				this->elemPtr_ = it.elemPtr_;
				return *this;
			}

			node_pointer base() const
			{
				return this->elemPtr_;
			}

			Tree *tree() const {
				return this->treePtr_;
			}

			/* ACCESS OPERATORS*/

			reference &operator*() const
			{
				return this->elemPtr_->data;
			}

			pointer operator->() const
			{
				return &this->elemPtr_->data;
			}

		
			/* OPERATIONS OPERATORS*/
			tree_iterator &operator++()
			{
				this->elemPtr_ = this->treePtr_->next(this->elemPtr_);
				
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
				this->elemPtr_ = this->treePtr_->prev(this->elemPtr_);

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
				return this->elemPtr_ != it.elemPtr_;
			}

		private:
			Node *elemPtr_;
			Tree *treePtr_;
			
	};

}