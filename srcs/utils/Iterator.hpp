#pragma once

namespace ft {
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
	class Iterator {
		protected:
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
	};
}
