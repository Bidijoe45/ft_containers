#pragma once
#include "./vector.hpp"
#include "./utils/iterator_traits.hpp"

namespace ft {

	template<class T, class Container = ft::vector<T> >
	class stack {
		
		public:
			typedef Container	container_type;
			typedef T			value_type;
			typedef size_t		size_type;

			stack(const container_type &ctnr = container_type()) {
				this->_container = ctnr;
			}

			bool empty() const
			{
				return this->_container.empty();
			}

			size_type size() const
			{
				return this->_container.size();
			}

			value_type &top()
			{
				return this->_container.back();
			}

			const value_type &top() const
			{
				return this->_container.back();
			}

			void push(const value_type &val)
			{
				this->_container.push_back(val);
			}

			void pop()
			{
				this->_container.pop_back();
			}

		protected:
			container_type _container;

  	friend bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs._container == rhs._container;
	}

  	friend bool operator!=(const stack<T, Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs._container != rhs._container;
	}

	friend bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs._container < rhs._container;
	}

	friend bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs._container <= rhs._container;
	}

	friend bool operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs._container > rhs._container;
	}

  	friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs._container >= rhs._container;
	}
	};




}

