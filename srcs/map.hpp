#pragma once
#include <functional>
#include "utils/pair.hpp"
#include "utils/iterator.hpp"
#include "utils/tree/tree.hpp"
#include "utils/tree/tree_iterator.hpp"
#include "utils/enable_if_traits.hpp"
#include "utils/is_integral_traits.hpp"
#include "utils/lexicographical_compare.hpp"

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

	private:
		typedef ft::Node<value_type> Node;
		typedef ft::RedBalckTree<value_type, Node, key_compare, Allocator> Tree;
	
	public:
		typedef ft::tree_iterator<value_type, Node, Tree> iterator;
		typedef ft::tree_iterator<const value_type, Node, const Tree> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator> difference_type;
		typedef std::size_t size_type;

	private:
		typename allocator_type::template rebind<Node>::other node_allocator;

	public:
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
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
			this->allocator_ = alloc;
			this->size_ = 0;
			this->comp_ = comp;
		}

		template <class InputIterator>
  		map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
		  	const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{	
			this->allocator_ = alloc;
			this->size_ = 0;
			this->comp_ = comp;

			while (first != last) {
				this->insert(*first);
				first++;
			}
		}

		map(const map& m) {
			this->allocator_ = m.get_allocator();
			this->comp_ = map::key_compare();
			this->size_ = 0;
			this->insert(m.begin(), m.end());
		}

		map &operator=(const map& m) {
			if (this == &m)
				return *this;

			this->allocator_ = m.get_allocator();
			this->comp_ = map::key_compare();
			this->size_ = 0;
			this->clear();
			this->insert(m.begin(), m.end());

			return *this;
		}

		~map() { 
			this->tree_.clearTree(this->tree_.getRoot());
		}

		/* ITERATORS */
		iterator begin() {
			return iterator(tree_.minimum(tree_.getRoot()), &this->tree_);
		}

		const_iterator begin() const {

			return const_iterator(tree_.minimum(tree_.getRoot()), &this->tree_);
		}

		iterator end() {
			return iterator(NULL, &this->tree_);
		}

		const_iterator end() const {
			return const_iterator(NULL, &this->tree_);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(iterator(NULL, &this->tree_));
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(const_iterator(NULL, &this->tree_));
		}
		
		reverse_iterator rend() {
			return reverse_iterator(iterator(tree_.minimum(tree_.getRoot()), &this->tree_));	
		}

		const_reverse_iterator rend() const {
			return reverse_iterator(const_iterator(tree_.minimum(tree_.getRoot()), &this->tree_));
		}

		/* CAPACITY */
		bool empty() const {
			return !this->size_;
		}

		size_type size() const {
			return this->size_;
		}

		size_type max_size() const {

			return node_allocator.max_size();
		}

		/* ELEMENT ACCESSS */
		mapped_type& operator[] (const key_type& k) {
			ft::pair<Node *, bool> insert = this->tree_.insert(ft::make_pair(k, mapped_type()));

			if (insert.second)
				this->size_++;

			return insert.first->data.second;
		}

		/* MODIFIERS */
		ft::pair<iterator, bool> insert(const value_type& val) {
			ft::pair<Node *, bool> insert = this->tree_.insert(val);
			iterator it(insert.first, &this->tree_);

			if (insert.second)
				this->size_++;

			return ft::make_pair(it, insert.second);
		}

		iterator insert(iterator position, const value_type& val) {
			ft::pair<Node *, bool> insert = this->tree_.insertWithHint(position.base(), val);

			if (insert.second)
				this->size_++;

			return iterator(insert.first, &this->tree_);
		}

		template<class InputIterator>
		void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last ) {
			ft::pair<Node *, bool> insert;

			while (first != last) {
				
				insert = this->tree_.insert(*first);

				if (insert.second)
					this->size_++;
				first++;
			}

		}

		void erase(typename ft::enable_if<!ft::is_integral<iterator>::value, iterator>::type position) {
			key_type key = (*position).first;
			bool deleted = this->tree_.deleteNode(key);

			if (deleted)
				this->size_--;
		}

		size_type erase(const key_type& k) {
			bool deleted = this->tree_.deleteNode(k);

			if (deleted) {
				this->size_--;
				return 1;
			}
			return 0;
		}

		void erase(typename ft::enable_if<!ft::is_integral<iterator>::value, iterator>::type first, iterator last) {
			key_type key;
			bool deleted;
			iterator next_it;

			while (first != last) {
				next_it = first;
				next_it++;
				key = (*first).first;

				deleted = this->tree_.deleteNode(key);
				if (deleted)
					this->size_--;
				first = next_it;
			}
		}

		void swap(map& x) {
			allocator_type tmp_alloc = this->get_allocator();
			size_type tmp_size = this->size();
			Node *tmp_root = this->tree_.getRoot();
			Node *tmp_nullNode = this->tree_.getNullNode();

			this->allocator_ = x.get_allocator();
			this->size_ = x.size();
			this->tree_.setRoot(x.tree_.getRoot());
			this->tree_.setNullNode(x.tree_.getNullNode());

			x.allocator_ = tmp_alloc;
			x.size_ = tmp_size;
			x.tree_.setRoot(tmp_root);
			x.tree_.setNullNode(tmp_nullNode);
			
		}

		void clear() {
			this->tree_.clearTree(this->tree_.getRoot());
			this->size_ = 0;
		}

		/* OPERATIONS */

		iterator find(const key_type& k) {
			return iterator(this->tree_.findByKey(k), &this->tree_);
		}

		const_iterator find(const key_type& k) const {
			return const_iterator(this->tree_.findByKey(k), &this->tree_);
		}

		size_type count(const key_type& k) const {
			const_iterator found(this->tree_.findByKey(k), &this->tree_);

			if (found != this->end())
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type& k) {
			iterator it = this->begin();
			iterator end = this->end();

			while (it != end) {
				if ((*it).first >= k)
					break ;
				it++;
			}

			return it;
		}

		const_iterator lower_bound(const key_type& k) const {
			const_iterator it = this->begin();
			const_iterator end = this->end();

			while (it != end) {
				if ((*it).first >= k)
					break ;
				it++;
			}

			return it;
		}

		iterator upper_bound(const key_type& k) {
			iterator it = this->begin();
			iterator end = this->end();

			while (it != end) {
				if ((*it).first > k)
					break ;
				it++;
			}

			return it;
		}
		
		const_iterator upper_bound(const key_type& k) const {
			const_iterator it = this->begin();
			const_iterator end = this->end();

			while (it != end) {
				if ((*it).first > k)
					break ;
				it++;
			}

			return it;
		}

		ft::pair<iterator,iterator> equal_range(const key_type& k)  {
			iterator it_lower_bound = this->lower_bound(k);
			iterator it_upper_bound = this->upper_bound(k);

			return ft::make_pair(it_lower_bound, it_upper_bound);
		}
		
		pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
			const_iterator it_lower_bound = this->lower_bound(k);
			const_iterator it_upper_bound = this->upper_bound(k);

			return ft::make_pair(it_lower_bound, it_upper_bound);
		}

		/* ALLOCATOR */
		allocator_type get_allocator() const {
			return this->allocator_;
		}

		key_compare key_comp() const {
			return key_compare();
		}

		value_compare value_comp() const {
			return value_compare(this->comp_);
		}

	private:
		
		Tree tree_;
		size_type size_;
		allocator_type allocator_;
		key_compare comp_;

};

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {

	typename ft::map<Key,T,Compare,Alloc>::const_iterator it1 = lhs.begin();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator it2 = rhs.begin();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator ite1 = lhs.end();

	if (lhs.size() != rhs.size())
		return false;

	while (it1 != ite1) {
		if ((*it1).first != (*it2).first || (*it1).second != (*it2).second)
			return false;

		it1++;
		it2++;
	}

	return true;
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
	return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
	return !(lhs < rhs);
}

}
