
namespace ft {

	template <class Iterator>
	class iterator_traits {
		typename Iterator::difference_type difference_type;
		typename Iteraotr::value_type value_type;
		typename Iterator::pointer pointer;
		typename Iterator::reference reference
		typename Iterator::iterator_category iterator_category;
	};

}

