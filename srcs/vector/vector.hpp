#include <memory>

namespace ft
{

	template < class T, class Allocator = std::allocator<T> >
	class vector {


		public:
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;

			//TODO:
			explicit vector(const Allocator& alloc = Allocator())
			{
				this->_size = 0;
				this->_capacity = 0;
			}

			//FIXME: no es seguro, comprobar si count es menor que max_size
			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
			{
				this->_allocator = alloc;
				this->_size = count;
				this->_capacity = count;
				this->_data = this->_allocator.allocate(count);
				for (size_type i=0; i < count; i++)
					this->_data[i] = value;
			}

			//TODO:
			/*
			template < class InputIt > 
			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
			{

			}
			*/

			//TODO:
			vector(const vector &other)
			{
				
			}

			//TODO:
			~vector()
			{

			}

			//TODO:			
			vector &operator=(const vector &other)
			{

			}
			
			bool empty() const
			{
				return (this->_size > 0) ? false : true;
			}

			size_type size() const
			{
				return this->_size;
			}

			//TODO:
			size_type max_size() const
			{

			}

			size_type capacity() const
			{
				return this->_capacity;
			}

			//FIXME: falta comprobar los limites
			reference at(size_type pos)
			{
				return this->_data[pos];
			}

			//TODO:
			const_reference at(size_type pos) const
			{

			}

			private:
				size_type	_size;
				size_type	_capacity;
				pointer		_data;
				Allocator	_allocator;


	};

}