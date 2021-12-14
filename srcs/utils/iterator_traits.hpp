#pragma once
#include <type_traits>
#include "./Iterator.hpp"
#include "../VectorIterator.hpp"

namespace ft {
	template <class Iterator> class iterator_traits
	{
		typename Iterator::diference_type diference_type;
		typename Iterator::value_type value_type;
		typename Iterator::pointer pointer;
		typename Iterator::reference reference;
	};

	template <class Iterator> struct is_iterator : std::false_type {};
	template <> struct is_iterator<ft::Iterator> : std::true_type {};
	template <class T> struct is_iterator<ft::VectorIterator<std::random_access_iterator_tag, T> > : std::true_type {};
	
}
