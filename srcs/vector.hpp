#pragma once
#include <memory>
#include "VectorIterator.hpp"

namespace ft
{

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{

		public:
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef VectorIterator<std::random_access_iterator_tag, T> iterator;
			typedef VectorIterator<std::random_access_iterator_tag, const T> const_iterator;


			// TODO:
			explicit vector(const Allocator &alloc = Allocator())
			{
				this->_size = 0;
				this->_capacity = 0;
			}

			// FIXME: no es seguro, controlar mejor si se intenta alocar una cantidad mayor que max_size
			explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator())
			{
				this->_allocator = alloc;
				if (count > this->max_size())
					throw std::runtime_error("vector: trying to allocate more than possible");
				this->_size = count;
				this->_capacity = count;
				this->_data = this->_allocator.allocate(count);
				for (size_type i = 0; i < count; i++)
					this->_allocator.construct(&this->_data[i], value);
			}

			// TODO:
			/*
					template < class InputIt >
					vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
					{

					}
					*/

			// TODO:
			vector(const vector &other)
			{
				

			}

			// TODO:
			~vector()
			{
			}

			// TODO:
			vector &operator=(const vector &other)
			{
			}

			/* ITERATORS */
			iterator begin()
			{
				return iterator(&this->_data[0]);
			}

			iterator end()
			{
				return iterator(&this->_data[this->_size]);
			}

			const_iterator begin() const
			{
				return const_iterator(&this->_data[0]);
			}

			const_iterator end() const
			{
				return const_iterator(&this->_data[this->_size]);
			}

			/* CAPACITY */

			size_type size() const
			{
				return this->_size;
			}

			size_type max_size() const
			{
				return this->_allocator.max_size();
			}

			// TODO:
			void resize(size_type n, value_type val = value_type())
			{
				if (n <= this->_size)
				{
					size_type rest = this->_size - (this->_size - n) - 1;
					for (size_type i = this->_size - 1; i > rest; i--)
						this->_allocator.destroy(&this->_data[i]);

					this->_size = n;
				}
				else
				{
					if (n > this->_capacity)
					{
						pointer tmp = this->_allocator.allocate(n);

						size_type i = 0;
						for (; i < this->_size; i++)
							tmp[i] = this->_data[i];
						for (; i < n; i++)
							this->_allocator.construct(&tmp[i], val);

						this->_allocator.deallocate(this->_data, this->_capacity);
						this->_data = tmp;
						this->_size = n;
						this->_capacity = n;
					}
					else
					{
						for (size_type i = this->_size; i < n; i++)
							this->_allocator.construct(&this->_data[i], val);
					}
				}
			}

			size_type capacity() const
			{
				return this->_capacity;
			}

			bool empty() const
			{
				return this->_size;
			}

			// TODO:
			void reserve(size_type n)
			{
			}

			/* ELEMENT ACCESS */

			// TODO:
			reference operator[](size_type n)
			{
				return this->_data[n];
			}

			const_reference operator[](size_type n) const
			{
				return this->_data[n];
			}

			reference at(size_type pos)
			{
				if (pos > this->_size)
					throw std::out_of_range("ft:vector: at -> out of range");
				return this->_data[pos];
			}

			const_reference at(size_type pos) const
			{
				if (pos > this->_size)
					throw std::out_of_range("ft:vector: at -> out of range");
				return this->_data[pos];
			}

			reference front()
			{
				return this->_data[0];
			}

			const_reference front() const
			{
				return this->_data[0];
			}

			reference back()
			{
				return this->_data[this->_size - 1];
			}

			const_reference back() const
			{
				return this->_data[this->_size - 1];
			}

			/* MODIFIERS */

			// TODO:
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
			}

			// TODO:
			void push_back(const value_type &val)
			{
			}

			// TODO:
			void pop_back()
			{
			}

			// TODO:
			// insert

			// TODO:
			// erase

			// TODO:
			// swap

			// TODO:
			// clear

			// TODO:

			/* ALLOCATOR */

			// TODO
			// get_allocator

		private:
			size_type _size;
			size_type _capacity;
			pointer _data;
			Allocator _allocator;
		};
}