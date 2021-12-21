#pragma once
#include <memory>
#include "./utils/IteratorBase.hpp"

namespace ft {

	template <class Category, class T>
	struct VectorIterator : public ft::IteratorBase<Category, T>
	{
		
		typedef typename ft::IteratorBase<Category, T>::value_type value_type;
		typedef typename ft::IteratorBase<Category, T>::difference_type difference_type;
		typedef typename ft::IteratorBase<Category, T>::pointer pointer;
		typedef typename ft::IteratorBase<Category, T>::reference reference;
		typedef typename ft::IteratorBase<Category, T>::iterator_category iterator_category;
	
		VectorIterator()
		{
			this->_ptr = nullptr;
		}

		VectorIterator(pointer p)
		{
			this->_ptr = p;
		}

		VectorIterator(reference r)
		{
			this->_ptr - &r;
		}
		
		template<class ItCategory, class ItT>
		VectorIterator(const VectorIterator<ItCategory, ItT> &it)
		{
			this->_ptr = it.base();
		}

		VectorIterator operator=(const VectorIterator &it)
		{
			if (this == &it)
				return *this;

			this->_ptr = it.base();
			return *this;
		}

		pointer base() const
		{
			return this->_ptr;
		}

		reference operator*()
		{
			return *this->_ptr;
		}

		pointer operator->() const
		{
			return this->_ptr;
		}

		reference operator[](const difference_type &n) const
		{
			return (this->_ptr[n]);
		}

		VectorIterator operator++()
		{
			++this->_ptr;
			return *this;
		}

		VectorIterator operator++(int)
		{
			VectorIterator tmp = *this;
			this->_ptr++;
			return tmp;
		}

		VectorIterator operator--()
		{
			--this->_ptr;
			return *this;
		}

		VectorIterator operator--(int)
		{
			VectorIterator tmp = *this;
			--this->_ptr;
			return tmp;
		}

		VectorIterator operator+(const difference_type &n)
		{
			return VectorIterator(this->_ptr + n);
		}

		VectorIterator &operator+=(const difference_type &n)
		{
			this->_ptr += n;
			return *this;
		}

		VectorIterator operator-(const difference_type &n)
		{
			return VectorIterator(this->_ptr - n);
		}

		VectorIterator &operator-=(const difference_type &n)
		{
			this->_ptr -= n;
			return *this;
		}

		bool operator==(const VectorIterator &it) const
		{
			return this->_ptr == it._ptr;
		}

		bool operator!=(const VectorIterator &it) const
		{
			return this->_ptr != it._ptr;
		}

		private:
			pointer _ptr;
	};

}
