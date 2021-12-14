#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "./srcs/vector.hpp"
#include "./srcs/utils/is_integral_traits.hpp"
#include "./srcs/utils/iterator_traits.hpp"
#include "./srcs/utils/Iterator.hpp"

//ALLOCATOR USE TEST
/*
class Person {
	private:
		std::string		_name;
		unsigned int	_age;
	
	public:
		Person(std::string name, unsigned int age) : 
			_name(name), _age(age)
		{
			std::cout << "Person constructor called" << std::endl;
		}
		const std::string &getName() const {return this->_name;}
		const unsigned int &getAge() const {return this->_age;}
		void setName(const std::string &name) {this->_name = name;}
		void setAge(const unsigned int &age) {this->_age = age;}
};

int main()
{
	srand(time(NULL));
	std::allocator<Person> allocator;

	Person *persons = allocator.allocate(3);

	for (int i = 0; i < 3; i++)
	{
		std::string name = "Person " + std::to_string(i + 1);
		unsigned int age = rand() % 100;
		allocator.construct(&persons[i], name, age);
	}

	for (int i=0; i < 3; i++)
	{
		std::cout << "Person: " << persons[i].getName() << ", " << persons[i].getAge() << std::endl;
	}

	return 0;
}
*/

template<class T>
void print_vector_stats(T &vec)
{
	std::cout << std::endl << "-- vector stats -- " << std::endl;
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	std::cout << std::endl;
}

//Vector TEST
int main ()
{
	
	//=======================================
	//==========  STD::VECTOR  ==============
	//=======================================


	//=======================================
	//===========  FT::VECTOR  ==============
	//=======================================

	ft::vector<int> ft_vec1(3, 2);

	ft::vector<int> ft_vec2(ft_vec1.begin(), ft_vec1.end());
	

	return 0;
}

