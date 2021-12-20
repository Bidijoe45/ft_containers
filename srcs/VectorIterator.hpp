#pragma once
#include <memory>
#include "./utils/Iterator.hpp"

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
		
		template<class ItCategory, class ItT, class ItDistance, class ItPointer, class ItReference>
		VectorIterator(const VectorIterator<ItCategory, ItT, ItDistance, ItPointer, ItReference> &it)
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
