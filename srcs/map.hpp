#include <functional>
#include "utils/pair.hpp"

namespace ft {

template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
	public:
		typedef typename Key key_type;
		typedef typename T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		//value_compare
		typedef typename Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		//iterator
		//const_iterator
		//reverse_iterator
		//const_reverse_iterator
		//difference_type
		typedef std::size_t size_type;
		


	priavte:

};

}
