#pragma once
#include <functional>
#include "utils/pair.hpp"
#include "utils/iterator.hpp"
#include "utils/tree.hpp"

namespace ft {

template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
	public:

		typedef typename Key key_type;
		typedef typename T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef typename Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::bidirectional_iterator<T> iterator;
		typedef ft::bidirectional_iterator<const T> const_iterator;
		typedef ft::reverse_iterator<ft::bidirectional_iterator<T> > reverse_iterator;
		typedef ft::reverse_iterator<ft::bidirectional_iterator<const T> > const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator> difference_type;
		typedef std::size_t size_type;

		template<class Key, class T, class Compare = key_compare, class Allocator= allocator_type>
		class value_compare
		{
			friend class ft::map;

			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {};
			
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				result_type operator() (const value_type &x, const value_type &y) const
				{
					return comp(x.first, y.first);
				}
		}

		/* CONSTRUCTORS */
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			this->_allocator = alloc;
			this->_size = 0;
			this->_data = NULL;
		}

		//TODO:
		template <class InputIterator>
  		map(ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
			const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			this->_allocator = alloc;
		}
			  

		//TODO:
		map(const map& x);

		//TODO:
		~map() {

		}

		/* ITERATORS */
		//TODO:
		iterator begin();

		//TODO:
		const_iterator begin() const;

		//TODO:
		iterator end();

		//TODO:
		const_iterator end() const;

		//TODO:
		reverse_iterator rbegin();

		//TODO:
		const_reverse_iterator rbegin() const;
		
		//TODO:
		reverse_iterator rend();

		//TODO:
		const_reverse_iterator rend() const;

		/* CAPACITY */
		bool empty() const {
			return this->_size;
		}

		size_type size() const {
			return this->_size;
		}

		size_type max_size() const {
			return this->_allocator.max_size();
		}

		/* ELEMENT ACCESSS */
		//TODO:
		mapped_type& operator[] (const key_type& k) {
			//aqui usar find
		}

		/* MODIFIERS */
		//TODO:
		pair<iterator,bool> insert (const value_type& val);

		//TODO:
		iterator insert (iterator position, const value_type& val);

		//TODO:
		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last);

		//TODO:
		void erase (iterator position);

		//TODO:
		size_type erase (const key_type& k);

		//TODO:
		void erase (iterator first, iterator last);

		//TODO:
		void swap (map& x);

		//TODO:
		void clear();

		/* OPERATIONS */
		//TODO:
		iterator find(const key_type& k);

		//TODO:
		const_iterator find(const key_type& k) const;

		//TODO:
		size_type count(const key_type& k) const;

		//TODO:
		iterator lower_bound(const key_type& k);

		//TODO:
		const_iterator lower_bound(const key_type& k) const;

		//TODO:
		iterator upper_bound(const key_type& k);

		//TODO:
		const_iterator upper_bound(const key_type& k) const;

		//TODO:
		pair<const_iterator,const_iterator>equal_range(const key_type& k) const;

		//TODO:
		pair<iterator,iterator>equal_range(const key_type& k);

		/* ALLOCATOR */
		allocator_type get_allocator() const {
			return this->_allocator;
		}

	private:
		Tree *_data;
		size_type _size;
		allocator_type _allocator;

};

}
