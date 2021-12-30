#pragma once
#include <memory>
#include "./utils/iterator.hpp"
#include "./utils/iterator_traits.hpp"

namespace ft {

	template <class T>
	struct VectorIterator 
	{
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T * pointer;
		typedef T & reference;
		typedef std::random_access_iterator_tag iterator_cateogry;
	
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
		
		template<class ItT>
		VectorIterator(const VectorIterator<ItT> &it)
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

	template<class T>
	VectorIterator<T> operator+(typename VectorIterator<T>::difference_type n, const VectorIterator<T> &it)
	{
		return VectorIterator<T>(it.base() + n);
	}

	template<class T, class U>
	const typename VectorIterator<T>::difference_type operator-(const VectorIterator<T> &lhs, const VectorIterator<U> &rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <class T, class U>
	bool operator==(const VectorIterator<T> &lhs, const VectorIterator<U> &rhs)
	{
		return rhs.base() == lhs.base();
	}

	template <class T, class U>
	bool operator!=(const VectorIterator<T> &lhs, const VectorIterator<U> &rhs)
	{
		return lhs.base() != rhs.base();
	}
					

	template <class T, class U>
	bool operator<(const VectorIterator<T> &lhs, const VectorIterator<U> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class T, class U>
	bool operator<=(const VectorIterator<T> &lhs, const VectorIterator<U> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class T, class U>
	bool operator>(const VectorIterator<T> &lhs, const VectorIterator<U> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class T, class U>
	bool operator>=(const VectorIterator<T> &lhs, const VectorIterator<U> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

}

