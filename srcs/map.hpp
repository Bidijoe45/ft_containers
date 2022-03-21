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
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::Node<value_type> Node;
		typedef ft::tree_iterator<Node, Compare> iterator;
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
			this->comp_ = comp;
		}

		template <class InputIterator>
  		map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
		  	const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			this->allocator_ = alloc;
			this->comp_ = comp;

			while (first != last) {
				this->insert(*first);
				first++;
			}
		}

		//FIXME: El prototipo de x tiene que ser const
		map(map& x) {
			this->allocator_ = x.get_allocator();
			this->comp_ = map::key_compare();
			this->insert(x.begin(), x.end());
		}

		//TODO:
		~map() {

		}

		/* ITERATORS */
		iterator begin() {
			return iterator(tree_.minimum(tree_.getRoot()));
		}

		//TODO:
		//const_iterator begin() const;

		iterator end() {
			return iterator(NULL);
		}

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

		mapped_type& operator[] (const key_type& k) {
			std::pair<iterator, bool> insert = this->tree_.insert(std::make_pair(k, mapped_type()));

			return (*(insert.first)).second;
		}

		/* MODIFIERS */

		std::pair<iterator, bool> insert(const value_type& val) {
			std::pair<iterator, bool> insert = this->tree_.insert(val);

			if (insert.second)
				this->size_++;

			return insert;
		}

		iterator insert(iterator position, const value_type& val) {
			std::pair<iterator, bool> insert = this->tree_.insertWithHint(position, val);

			if (insert.second)
				this->size_++;

			return insert.first;
		}

		template<class InputIterator>
		void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last ) {
			std::pair<iterator, bool> insert;

			while (first != last) {
				
				insert = this->tree_.insert(*first);

				if (insert.second)
					this->size_++;
				first++;
			}

		}

		void erase (typename ft::enable_if<!ft::is_integral<iterator>::value, iterator>::type position) {
			key_type key = (*position).first;
			bool deleted = this->tree_.deleteNode(key);

			if (deleted)
				this->size_--;
		}

		size_type erase (const key_type& k) {
			bool deleted = this->tree_.deleteNode(k);

			if (deleted) {
				this->size_--;
				return 1;
			}
			return 0;
		}

		void erase (typename ft::enable_if<!ft::is_integral<iterator>::value, iterator>::type first, iterator last) {
			key_type key;
			bool deleted;

			while (first != last) {
				key = (*first).first;

				deleted = this->tree_.deleteNode(key);
				if (deleted)
					this->size_--;
				first++;
			}
		}

		void swap (map& x) {
			allocator_type tmp_alloc = this->get_allocator();
			size_type tmp_size = this->size();
			RedBlackTree<value_type, Node, key_compare> tmp_tree(this->tree_);

			this->allocator_ = x.get_allocator();
			this->size_ = x.size();
			this->tree_ = x.tree_;

			x.allocator_ = tmp_alloc;
			x.size_ = tmp_size;
			x.tree_ = tmp_tree;
			
		}

		void clear() {
			iterator it = this->begin();
			iterator ite = this->end();

			while (it != ite) {
				this->erase(it);
				it++;
			}
		}

		/* OPERATIONS */

		iterator find(const key_type& k) {
			return this->tree_.findByKey(k);
		}

		//TODO:
		//const_iterator find(const key_type& k) const;

		//FIXME: el prototipo tiene const
		size_type count(const key_type& k) {
			iterator found = this->tree_.findByKey(k);

			if (found != this->end())
				return 1;
			return 0;
		}

		//TODO:
		iterator lower_bound(const key_type& k) {
			return this->tree_.lower_bound(k);
		}

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
			tree_.printTree();
		}

	private:
		RedBlackTree<value_type, Node, key_compare> tree_;
		size_type size_;
		allocator_type allocator_;
		key_compare comp_;

};

}
