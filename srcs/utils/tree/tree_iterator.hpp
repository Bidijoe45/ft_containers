#pragma once


namespace ft
{

template<class Node, class Compare>
	class tree_iterator : ft::iterator<std::bidirectional_iterator_tag, Node> {
		public:
			typedef typename Node::value_type value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Node>::value_type			node_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Node>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Node>::iterator_category		iterator_category;
			typedef Node*		pointer;
			typedef Node&		reference;

			tree_iterator(const Compare comp = Compare()) : comp_(comp)
			{
				this->_elemPtr = NULL;
			}

			tree_iterator(Node *ptr, const Compare comp = Compare()) : comp_(comp), last_(NULL)
			{
				this->_elemPtr = ptr;
			}


			template <class T, class U>
			tree_iterator<T, U>(const tree_iterator<U, T> &it)
			{
				this->_elemPtr = it.base();
			}

			virtual ~tree_iterator() {}
	
			tree_iterator &operator=(const tree_iterator &it)
			{
				if (this == &it)
					return *this;

				this->_elemPtr = it._elemPtr;
				return *this;
			}

			pointer base() const
			{
				return this->_elemPtr;
			}

			/* ACCESS OPERATORS*/
			value_type &operator*()
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
				if (!this->_elemPtr->right->isEmpty()) {
					this->_elemPtr = this->_elemPtr->right;
					while (!this->_elemPtr->left->isEmpty())
						this->_elemPtr = this->_elemPtr->left;
				} else {
					Node *p = this->_elemPtr->parent;
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
			Node *last_;
			Compare comp_;
			
	};


}