#pragma once
#include <type_traits>
#include "./Iterator.hpp"
#include "../VectorIterator.hpp"

namespace ft {
	template <class Iterator> struct iterator_traits
	{
		typedef typename Iterator::diference_type		diference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
}
