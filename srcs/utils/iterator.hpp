#pragma once
#include <memory>

namespace ft
{

	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator {
		public:
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;
			typedef Category iterator_category;
	};

	template<class T>
	class random_access_iterator : ft::iterator<std::random_access_iterator_tag, T>{
		public:
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef T*		pointer;
			typedef T&		reference;

			random_access_iterator()
			{
				this->_elemPtr = NULL;
			}

			random_access_iterator(pointer ptr)
			{
				this->_elemPtr = ptr;
			}

			template<class U>
			random_access_iterator(const random_access_iterator<U> &it)
			{
				this->_elemPtr = it.elemPtr;
			}

			virtual ~random_access_iterator() {}
			

			random_access_iterator &operator=(const random_access_iterator &it)
			{
				this->_elemPtr = it._elemPtr;
				return *this;
			}

			/* COMPARSION OPERATORS */

			template<class U>
			bool operator==(const random_access_iterator<U> &it)
			{
				return this->_elemPtr == it._elemPtr;
			}

			template<class U>
			bool operator!=(const random_access_iterator<U> &it)
			{
				return this->_elemPtr != it._elemPtr;
			}

			template<class U>
			bool operator<(const random_access_iterator<U> &it)
			{
				return this->_elemPtr < it._elemPtr;
			}

			template<class U>
			bool operator<=(const random_access_iterator<U> &it)
			{
				return this->_elemPtr <= it._elemPtr;
			}

			template<class U>
			bool operator>(const random_access_iterator<U> &it)
			{
				return this->_elemPtr > it._elemPtr;
			}

			template<class U>
			bool operator>=(const random_access_iterator<U> &it)
			{
				return this->_elemPtr >= it._elemPtr;
			}

			/* ACCESS OPERATORS*/
			template<class U>
			reference operator*()
			{
				return *this->_elemPtr;
			}

			reference operator[](difference_type n)
			{
				return *this->_elemPtr[n];
			}


			/* OPERATIONS OPERATORS*/
			//TODO:


		private:
			pointer _elemPtr;
	};

} 
