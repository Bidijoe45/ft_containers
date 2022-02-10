#pragma once
#include <memory>
#include "utils/iterator_traits.hpp"
#include "utils/is_integral_traits.hpp"
#include "utils/enable_if_traits.hpp"
#include "utils/iterator.hpp"

#include <iostream>

namespace ft
{

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{

		public:
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t 	difference_type;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef ft::random_access_iterator<value_type> iterator;
			typedef ft::random_access_iterator<const value_type> const_iterator;

			/* CONSTRUCTORS */

			explicit vector(const Allocator &alloc = Allocator())
			{
				this->_size = 0;
				this->_capacity = 0;
				this->_allocator = alloc;
				this->_data = NULL;
			}

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

			template <class InputIt>
			vector(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last, const Allocator& alloc = Allocator())
			{
				InputIt tmpFirst = first;
				size_type size = 0;

				while (tmpFirst++ != last)
					size++;
				
				this->_allocator = alloc;
				this->_data = this->_allocator.allocate(size);
				this->_size = size;
				this->_capacity = size;

				iterator it = this->begin();
				iterator ite = this->end();

				while (it != ite)
				{
					*it = *first;
					it++;
					first++;
				}

			}
				
			vector(const vector &other)
			{
				if (this == &other)
					return ;

				this->_size = other.size();
				this->_capacity = other.capacity();
				this->_allocator = other.get_allocator();

				this->_data = this->_allocator.allocate(this->capacity());

				for (size_type i=0; i < this->size(); i++)
					this->_data[i] = other[i];
			}

			~vector()
			{
				if (this->_data == NULL)
					return ;

				for (int i; i < this->size(); i++)
					this->_allocator.destroy(&this->_data[i]);
				this->_allocator.deallocate(this->_data, this->capacity());
			}

			// TODO:
			vector &operator=(const vector &other)
			{
				if (this == &other)
					return *this;

				this->assign(other.begin(), other.end());

				return *this;
			}

			/* ITERATORS */
			const_iterator begin() const
			{
				return const_iterator(&this->_data[0]);
			}

			const_iterator end() const
			{
				return const_iterator(&this->_data[this->_size]);
			}

			iterator begin()
			{
				return iterator(&this->_data[0]);
			}

			iterator end()
			{
				return iterator(&this->_data[this->_size]);
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

			void resize(size_type n, value_type val = value_type())
			{
				
				if (n < this->size())
				{
					for (size_type i = this->size(); i > n; i--) {
						this->_allocator.destroy(&this->_data[i]);
					}
					this->_size = n;

					return ;
				}


				if (n > this->capacity())
					this->reserve(n);

				for (size_type i = this->size(); i < n; i++)
					this->_data[i] = val;

				this->_size = n;
				
			}

			size_type capacity() const
			{
				return this->_capacity;
			}

			bool empty() const
			{
				return !this->_size;
			}

			//FIXME: Al reservar el iterator debe ponerse en el ultimo elemento, pero no lo hace
			void reserve(size_type n)
			{
				if (n <= this->_capacity)
					return ;

				pointer tmp = this->_allocator.allocate(n);

				for (size_type i=0; i < this->_size; i++)
					this->_allocator.construct(&tmp[i], this->_data[i]);
				
				for (size_type i=0; i < this->_size; i++)
					this->_allocator.destroy(&this->_data[i]);

				if (this->_data != NULL)
					this->_allocator.deallocate(this->_data, this->_capacity);

				this->_data = tmp;
				this->_capacity = n;

			}

			/* ELEMENT ACCESS */

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
			template <class InputIterator>
			void assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
			{
				this->clear();

				size_type n = count_elements(first, last);
				
				if (n > this->capacity())
				{
					this->reserve(n);

					for (size_type i=0; i < n; i++)
					{
						this->_data[i] = *first;
						first++;
					}

					this->_capacity = n;
				}
				else
				{
					for (size_type i=0; i < n; i++)
					{
						this->_data[i] = *first;
						first++;
					}
				}
				
				this->_size = n;
			}

			void assign (size_type n, const value_type& val)
			{

				this->clear();

				if (n > this->capacity())
				{
					this->reserve(n);

					for (size_type i=0; i < n; i++)
						this->_data[i] = val;

					this->_capacity = n;
				}
				else
				{
					for (size_type i=0; i < n; i++)
						this->_data[i] = val;
				}

				this->_size = n;
			}

			void push_back(const value_type &val)
			{
				this->insert(this->end(), val);
			}

			// TODO:
			void pop_back()
			{
				this->_allocator.destroy(&this->_data[this->size() - 1]);
				this->_size = this->size() - 1;
			}

			// TODO: Lanzar excepcion si no se puede alocar la nueva cantidad
		
			void insert(iterator position, size_type n, const value_type &val)
			{
				size_type new_size = this->size() + n;
				size_type position_i = position - this->begin();

				if (new_size > this->capacity())
				{
					size_type new_capacity = this->get_new_capacity_size_for(new_size);
					pointer new_data = this->_allocator.allocate(new_capacity);

					size_type i = 0;
					size_type copy_i = 0;
					while (i < this->size())
					{
						if (i == position_i)
							copy_i += n;

						new_data[copy_i] = this->_data[i];
						copy_i++;
						i++;
					}

					size_type copy_until = position_i + n;
					while (position_i < copy_until)
					{
						new_data[position_i] = val;
						position_i++;
					}
					
					for (size_type i=0; i < this->size(); i++)
						this->_allocator.destroy(&this->_data[i]);
					this->_allocator.deallocate(this->_data, this->_capacity);

					this->_data = new_data;
					this->_capacity = new_capacity;
				}
				else
				{
					size_type copy_i = new_size - 1;
					size_type i = this->size() - 1;
					while (i >= position_i)
					{
						this->_data[copy_i] = this->_data[i];
						i--;
						copy_i--;
					}

					size_type copy_until = position_i + n;
					while (position_i < copy_until)
					{
						this->_data[position_i] = val;
						position_i++;
					}
				}

				this->_size = new_size;
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type new_size = this->size() + 1;
				size_type position_i = position - this->begin();

				if (new_size > this->capacity())
				{
					size_type new_capacity = this->get_new_capacity_size_for(new_size);
					pointer new_data = this->_allocator.allocate(new_capacity);

					size_type i = 0;
					size_type copy_i = 0;
					while (i < this->size())
					{
						if (i == position_i)
							copy_i++;

						new_data[copy_i] = this->_data[i];
						i++;
						copy_i++;
					}

					new_data[position_i] = val;

					for (size_type i=0; i < this->size(); i++)
						this->_allocator.destroy(&this->_data[i]);
					this->_allocator.deallocate(this->_data, this->_capacity);

					this->_data = new_data;
					this->_capacity = new_capacity;
				}
				else
				{
					for (size_type i = new_size; i > position_i; i--)
						this->_data[i] = this->_data[i - 1];

					this->_data[position_i] = val;
				}

				this->_size = new_size;

				return iterator(&this->_data[position_i]);
			}
		
			template <class InputIterator>
			void insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
			{
				size_type n = this->count_elements(first, last);
				size_type new_size = this->size() + n;
				size_type position_i = position - this->begin();

				if (new_size > this->capacity())
				{
					size_type new_capacity = this->get_new_capacity_size_for(new_size);
					pointer new_data = this->_allocator.allocate(new_capacity);

					size_type i = 0;
					size_type copy_i = 0;
					while (i < this->size())
					{
						if (i == position_i)
							copy_i += n;

						new_data[copy_i] = this->_data[i];
						copy_i++;
						i++;
					}

					while (first != last)
					{
						new_data[position_i] = *first;
						position_i++;
						first++;
					}

					for (size_type i=0; i < this->size(); i++)
						this->_allocator.destroy(&this->_data[i]);
					this->_allocator.deallocate(this->_data, this->_capacity);

					this->_data = new_data;
					this->_capacity = new_capacity;
				}
				else
				{
					size_type copy_i = new_size - 1;
					size_type i = this->size() - 1;
					while (i >= position_i)
					{
						this->_data[copy_i] = this->_data[i];
						i--;
						copy_i--;
					}
					
					while (first != last)
					{
						this->_data[position_i] = *first;
						first++;
						position_i++;
					}	
				}

				this->_size = new_size;
			}

			// TODO:
			iterator erase(iterator position)
			{
				size_type position_i = position - this->begin();

				this->_allocator.destroy(&this->_data[position_i]);

				size_type i = position_i;
				while (i < this->size())
				{
					this->_data[i] = this->_data[i + 1];
					i++;
				}
				
				this->_size = this->size() - 1;

				return iterator(&this->_data[position_i]);
			}

			iterator erase(iterator first, iterator last)
			{
				size_type n = last - first;
				size_type first_i = first - this->begin();
				size_type elements_after = this->end() - last;

				for (size_type i = first_i; i < n; i++)
					this->_allocator.destroy(&this->_data[i]);
				
				size_type copy_i = first_i + n;
				size_type i = first_i;

				while (i <= elements_after)
				{
					this->_data[i] = this->_data[copy_i];
					i++;
					copy_i++;
				}

				this->_size = this->size() - n;

				return iterator(&this->_data[first_i]);
			}

			// TODO:
			// swap

			void clear()
			{
				if (this->_data == NULL)
					return ;

				for (size_type i=0; i < this->_size; i++)
					this->_allocator.destroy(&this->_data[i]);
				this->_size = 0;
			}

			// TODO:

			/* ALLOCATOR */

			allocator_type get_allocator() const
			{
				return this->_allocator;
			}


		private:
			size_type _size;
			size_type _capacity;
			pointer _data;
			Allocator _allocator;

			size_type get_new_capacity_size_for(size_type n)
			{
				if (this->_capacity <= 1)
					return n;

				size_type new_capacity = this->_capacity;

				while (new_capacity < n)
					new_capacity *= 2;

				return new_capacity;
			}

			template<class InputIterator>
			size_type count_elements(InputIterator first, InputIterator last) {
				size_type n = 0;

				while (first != last)
				{
					first++;
					n++;
				}

				return n;
			}

		};
}