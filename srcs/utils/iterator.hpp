#pragma once
#include "iterator_traits.hpp"
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
	class random_access_iterator : ft::iterator<std::random_access_iterator_tag, T> {
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
			

			//TODO: comprobar si esto esta bien asi o es un template y hay que indicar el tipo de iterador
			random_access_iterator &operator=(const random_access_iterator &it)
			{
				this->_elemPtr = it._elemPtr;
				return *this;
			}


			/* ACCESS OPERATORS*/
			reference operator*()
			{
				return *this->_elemPtr;
			}

			reference operator[](difference_type n)
			{
				return *this->_elemPtr[n];
			}

			pointer operator->()
			{
				return this->_elemPtr;
			}


			/* OPERATIONS OPERATORS*/

			random_access_iterator &operator++()
			{
				this->_elemPtr++;
				return *this;
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator it(*this);
				this->_elemPtr++;
				return it;
			}

			random_access_iterator operator+(difference_type n) const
			{
				random_access_iterator it(*this);
				it->_elemPtr += n;
				return it;
			}

			random_access_iterator &operator+=(difference_type n)
			{
				this->_elemPtr += n;
				return *this;
			}

			template <class U>
			friend random_access_iterator<U> operator+(typename random_access_iterator<U>::difference_type n, const random_access_iterator<U> &it)
			{
				random_access_iterator  tmp_it(it);
				tmp_it += n;
				return tmp_it;
			}

			random_access_iterator &operator--()
			{
				this->_elemPtr--;
				return *this;
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator it(*this);
				this->_elemPtr--;
				return it;
			}

			random_access_iterator &operator-(difference_type n) const
			{
				random_access_iterator it(*this);
				it->_elemPtr -= n;
				return it;
			}
			
			random_access_iterator &operator-=(difference_type n)
			{
				this->_elemPtr -= n;
				return *this;
			}


			template <class U, class V>
 			friend typename random_access_iterator<U>::difference_type operator-(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs)
			{
				return lhs._elemPtr - rhs._elemPtr;
			}

			/* RELATIONAL OPERATORS */

			template <class U, class V>
			friend bool operator==(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
				return lhs._elemPtr == rhs._elemPtr;
			}

			template <class U, class V>
			friend bool operator!=(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
				return lhs._elemPtr != rhs._elemPtr;
			}

			template <class U, class V>
			friend bool operator<(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
				return lhs._elemPtr < rhs._elemPtr;
			}

			template <class U, class V>
			friend bool operator<=(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
				return lhs._elemPtr <= rhs._elemPtr;
			}

			template <class U, class V>
			friend bool operator>(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
				return lhs._elemPtr > rhs._elemPtr;
			}

			template <class U, class V>
			friend bool operator>=(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
				return lhs._elemPtr >= rhs._elemPtr;
			}
			
			

		private:
			pointer _elemPtr;
	};

	
} 
