#pragma once
#include <functional>
#include "utils/pair.hpp"
#include "utils/iterator.hpp"
#include "utils/tree/tree.hpp"
#include "utils/tree/tree_iterator.hpp"

namespace ft {

template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
	public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::tree_iterator<Node<value_type>, value_type, Compare> iterator;
		//typedef ft::tree_iterator<const value_type> const_iterator;
		//typedef ft::reverse_iterator<ft::tree_iterator<T> > reverse_iterator;
		//typedef ft::reverse_iterator<ft::tree_iterator<const T> > const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator> difference_type;
		typedef std::size_t size_type;

		class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, Allocator>;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				
				public:
					typedef bool result_type;
  					typedef value_type first_argument_type;
  					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const {
						return (comp(x.first, y.first));
					}
			};

		/* CONSTRUCTORS */
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			this->allocator_ = alloc;
			this->size_ = 0;
		}

		//TODO:
		template <class InputIterator>
  		map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
		  	const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			this->allocator_ = alloc;
		}

		//TODO:
		map(const map& x);

		//TODO:
		~map() {

		}

		/* ITERATORS */
		//TODO:
		iterator begin() {
	
			return iterator(data_.minimum(data_.getRoot()));
		}

		//TODO:
		//const_iterator begin() const;

		//TODO:
		iterator end();

		//TODO:
		//const_iterator end() const;

		//TODO:
		//reverse_iterator rbegin();

		//TODO:
		//const_reverse_iterator rbegin() const;
		
		//TODO:
		//reverse_iterator rend();

		//TODO:
		//const_reverse_iterator rend() const;

		/* CAPACITY */
		bool empty() const {
			return this->size_;
		}

		size_type size() const {
			return this->size_;
		}

		size_type max_size() const {
			return this->allocator_.max_size();
		}

		/* ELEMENT ACCESSS */
		//TODO:
		mapped_type& operator[] (const key_type& k) {
			//aqui usar find
		}

		/* MODIFIERS */
		//TODO:
		ft::pair<iterator,bool> insert (const value_type& val) {
			return data_.insert(val);
		}

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
		//const_iterator find(const key_type& k) const;

		//TODO:
		size_type count(const key_type& k) const;

		//TODO:
		iterator lower_bound(const key_type& k);

		//TODO:
		//const_iterator lower_bound(const key_type& k) const;

		//TODO:
		iterator upper_bound(const key_type& k);

		//TODO:
		//const_iterator upper_bound(const key_type& k) const;

		//TODO:
		//pair<const_iterator,const_iterator>equal_range(const key_type& k) const;

		//TODO:
		pair<iterator,iterator>equal_range(const key_type& k);

		/* ALLOCATOR */
		allocator_type get_allocator() const {
			return this->allocator_;
		}

		void printTree() {
			data_.printTree();
		}

	private:
		RedBlackTree<value_type, Compare> data_;
		size_type size_;
		allocator_type allocator_;

};

}
