#pragma once
#include <memory>

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
struct VectorIterator
{

	typedef T value_type;
	typedef Distance difference_type;
	typedef Pointer pointer;
	typedef Reference reference;
	typedef Category iterator_category;

	VectorIterator(pointer p)
	{
		this->_ptr = p;
	}

	VectorIterator(reference it)
	{
		this->_ptr = it._ptr;
	}

	reference operator=(reference it)
	{
		if (this == &it)
			return *this;

		this->_ptr = it._ptr;
		return *this;
	}

	reference operator*()
	{
		return *this->_ptr;
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

	difference_type operator-(VectorIterator &other)
	{
		return this->_ptr - other._ptr;
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