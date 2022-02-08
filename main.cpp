#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include "./srcs/vector.hpp"
#include "./srcs/utils/is_integral_traits.hpp"
#include "./srcs/utils/iterator_traits.hpp"

//ALLOCATOR USE TEST

class Person {
	private:
		std::string		_name;
		unsigned int	_age;
	
	public:
		Person()
		{
			this->_name = "NO_NAME";
			this->_age = 0;
		}

		Person(std::string name, unsigned int age) : 
			_name(name), _age(age)
		{

		}

		~Person()
		{
			
		}

		Person &operator=(const Person &p)
		{
			this->_name = p.getName();
			this->_age = p.getAge();

			return *this;
		}

		const std::string &getName() const {return this->_name;}
		const unsigned int &getAge() const {return this->_age;}
		void setName(const std::string &name) {this->_name = name;}
		void setAge(const unsigned int &age) {this->_age = age;}
};

std::ostream& operator<<(std::ostream &os, const Person &p)
{
	os << "Person: " << p.getName() << " age: " << p.getAge();
	return os;
}

/*
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

template<class T>
void print_vector_content(T &vec)
{
	typename T::iterator it = vec.begin();
	typename T::iterator ite = vec.end();

	std::cout << "---- CONTENT ----" << std::endl;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "-----------------" << std::endl;
}

//Vector TEST
int main ()
{
	ft::vector<int> ft_vec1(4);

	ft_vec1[0] = 1;
	ft_vec1[1] = 2;
	ft_vec1[2] = 3;
	ft_vec1[3] = 4;

	ft::vector<int> ft_vec2(4);

	ft_vec2[0] = -1;
	ft_vec2[1] = -2;
	ft_vec2[2] = -3;
	ft_vec2[3] = -4;

	print_vector_stats(ft_vec1);

	ft_vec1.insert(ft_vec1.begin() + 2, ft_vec2.begin() + 1, ft_vec2.begin() + 3);


	print_vector_stats(ft_vec1);
	print_vector_content(ft_vec1);

	return 0;
}

/*

*/