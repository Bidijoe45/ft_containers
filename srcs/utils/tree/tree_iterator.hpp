namespace ft
{

template<class Node, class T, class Compare>
	class tree_iterator : ft::iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef T*		pointer;
			typedef T&		reference;

			tree_iterator()
			{
				this->_elemPtr = NULL;
			}

			tree_iterator(Node *ptr)
			{
				this->_elemPtr = ptr;
			}

			//TODO:
			/*
			template <class U>
			tree_iterator<U>(const tree_iterator<U> &it)
			{
				this->_elemPtr = it.base();
			}
			*/

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
			reference operator*()
			{
				return this->_elemPtr->data;
			}

			pointer operator->() const
			{
				return this->_elemPtr;
			}

			/* OPERATIONS OPERATORS*/

			//TODO:
			tree_iterator &operator++()
			{

				return *this;
			}

			//TODO:
			tree_iterator operator++(int)
			{
				tree_iterator it(*this);
				this->_elemPtr++;
				return it;
			}
			
			//TODO:
			tree_iterator &operator--()
			{
				this->_elemPtr--;
				return *this;
			}

			//TODO:
			tree_iterator operator--(int)
			{
				tree_iterator it(*this);
				this->_elemPtr--;
				return it;
			}

		private:
			Node *_elemPtr;
			
	};

}