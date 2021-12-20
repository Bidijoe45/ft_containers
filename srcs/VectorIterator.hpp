#pragma once
#include <memory>

namespace ft {
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct VectorIterator
	{

		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;

		VectorIterator()
		{
			this->_ptr = NULL;
		}

		VectorIterator(pointer p)
		{
			this->_ptr = p;
		}

		VectorIterator(reference r)
		{
			this->_ptr = &r;
		}

		template<class ItCategory, class ItT, class ItDistance, class ItPointer, class ItReference>
		VectorIterator(const VectorIterator<ItCategory, ItT, ItDistance, ItPointer, ItReference> &it)
		{
			this->_ptr = it.base();
		}

		VectorIterator &operator=(const VectorIterator &it)
		{
			if (this == &it)
				return *this;

			this->_ptr = it._ptr;
			return *this;
		}

		reference operator*()
		{
			if (this->_ptr == NULL)
				return 0x0;
			return *this->_ptr;
		}

		pointer operator->()
		{
			return this->_ptr;
		}

		reference operator[](difference_type n)
		{
			return this->_ptr[n];
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

		difference_type operator-(difference_type n)
		{
			return this->_ptr - n;
		}

		difference_type operator-=(difference_type n)
		{
			return this->_ptr - n;
		}

		difference_type operator+(difference_type n)
		{
			return this->_ptr + n;
		}

		difference_type operator+=(difference_type n)
		{
			return this->_ptr + n;
		}

		bool operator==(const VectorIterator &it) const
		{
			return this->_ptr == it._ptr;
		}

		bool operator!=(const VectorIterator &it) const
		{
			return this->_ptr != it._ptr;
		}

		pointer base() const
		{
			return this->_ptr;
		}

		private:
			pointer _ptr;
	};



}

