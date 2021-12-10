
template <class Iterator> class iterator_traits
{
	typename Iterator::diference_type diference_type;
	typename Iterator::value_type value_type
	typename Iterator::pointer pointer;
	typename Iterator::reference reference;
};