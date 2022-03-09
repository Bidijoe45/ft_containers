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
	class bidirectional_iterator : ft::iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef T*		pointer;
			typedef T&		reference;

			bidirectional_iterator()
			{
				this->_elemPtr = NULL;
			}

			bidirectional_iterator(pointer ptr)
			{
				this->_elemPtr = ptr;
			}

			template <class U>
			bidirectional_iterator<U>(const bidirectional_iterator<U> &it)
			{
				this->_elemPtr = it.base();
			}

			virtual ~bidirectional_iterator() {}
	
			bidirectional_iterator &operator=(const bidirectional_iterator &it)
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
				return *this->_elemPtr;
			}

			pointer operator->() const
			{
				return this->_elemPtr;
			}

			/* OPERATIONS OPERATORS*/

			bidirectional_iterator &operator++()
			{
				this->_elemPtr++;
				return *this;
			}

			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator it(*this);
				this->_elemPtr++;
				return it;
			}
			
			bidirectional_iterator &operator--()
			{
				this->_elemPtr--;
				return *this;
			}

			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator it(*this);
				this->_elemPtr--;
				return it;
			}

		private:
			pointer _elemPtr;
			
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

			template <class U>
			random_access_iterator<U>(const random_access_iterator<U> &it)
			{
				this->_elemPtr = it.base();
			}

			virtual ~random_access_iterator() {}
	
			random_access_iterator &operator=(const random_access_iterator &it)
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
				return *this->_elemPtr;
			}

			reference operator[](difference_type n) const
			{
				return this->_elemPtr[n];
			}

			pointer operator->() const
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
				pointer tmpPtr = this->base() + n;
				random_access_iterator tmpIt(tmpPtr);
				return tmpIt;
			}

			random_access_iterator &operator+=(difference_type n)
			{
				this->_elemPtr += n;
				return *this;
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

			random_access_iterator operator-(difference_type n) const
			{
				pointer tmpPtr = this->base() - n;
				random_access_iterator tmpIt(tmpPtr);
				return tmpIt;
			}
			
			random_access_iterator &operator-=(difference_type n)
			{
				this->_elemPtr -= n;
				return *this;
			}

		
		private:
			pointer _elemPtr;
			
	};


		template <class U>
		ft::random_access_iterator<U> operator+(typename ft::random_access_iterator<U>::difference_type n, const ft::random_access_iterator<U> &it)
		{
			ft::random_access_iterator<U>  tmp_it(it);
			tmp_it += n;
			return tmp_it;
		}

		template <class U, class V>
		typename random_access_iterator<U>::difference_type operator-(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs)
		{
			return lhs.base() - rhs.base();
		}

		/* RELATIONAL OPERATORS */

		template <class U, class V>
		bool operator==(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
			return lhs.base() == rhs.base();
		}

		template <class U, class V>
		bool operator!=(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
			return lhs.base() != rhs.base();
		}

		template <class U, class V>
		bool operator<(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
			return lhs.base() < rhs.base();
		}

		template <class U, class V>
		bool operator<=(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
			return lhs.base() <= rhs.base();
		}

		template <class U, class V>
		bool operator>(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
			return lhs.base() > rhs.base();
		}

		template <class U, class V>
		bool operator>=(const random_access_iterator<U>& lhs, const random_access_iterator<V>& rhs) {
			return lhs.base() >= rhs.base();
		}
	
	
	template<class Iterator>
	class reverse_iterator {

		public:
			typedef Iterator iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer pointer;
			typedef typename ft::iterator_traits<Iterator>::reference reference;

		reverse_iterator() {
			this->_base_iterator = iterator_type();
		}

		reverse_iterator(iterator_type it) {
			this->_base_iterator = it;
		}

		template <class Iter>
  		reverse_iterator (const reverse_iterator<Iter>& rev_it)
		{
			this->_base_iterator = rev_it.base();
		}

		reference operator*() const
		{
			iterator_type tmp = this->_base_iterator;
			return *(--tmp);
		}
		
		reverse_iterator operator+(difference_type n)
		{	
			return reverse_iterator(this->_base_iterator - n);
		}

		reverse_iterator &operator++()
		{
			--this->_base_iterator;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			this->_base_iterator -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n)
		{
			return reverse_iterator(this->_base_iterator + n);
		}

		reverse_iterator &operator--()
		{
			++this->_base_iterator;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = this->_base_iterator;
			++this->_base_iterator;
			return tmp;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			this->_base_iterator += n;
			return *this;
		}

		pointer operator->() const
		{
			return (&(this->operator*()));
		}

		reference operator[](difference_type n) const
		{
			return this->_base_iterator[-n - 1];
		}

		iterator_type base() const {
			return (this->_base_iterator);
		}

		private:
			iterator_type _base_iterator;
	};

	template <class U, class V>
	bool operator==(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <class U, class V>
	bool operator!=(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <class U, class V>
	bool operator<(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <class U, class V>
	bool operator<=(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <class U, class V>
	bool operator>(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() < rhs.base();
	}

	template <class U, class V>
	bool operator>=(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <class Iter>
	ft::reverse_iterator<Iter> operator+(typename ft::reverse_iterator<Iter>::difference_type n, const ft::reverse_iterator<Iter> &it)
	{
		ft::reverse_iterator<Iter>  tmp_it(it);
		tmp_it += n;
		return tmp_it;
	}

	template <class U, class V>
	typename reverse_iterator<U>::difference_type operator-(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs)
	{
		return rhs.base() - lhs.base();
	}

}