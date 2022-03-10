#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include "./srcs/vector.hpp"
#include "./srcs/utils/is_integral_traits.hpp"
#include "./srcs/utils/iterator_traits.hpp"
#include "./srcs/map.hpp"

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

template<class T>
void print_map_content(T &map)
{
	typename T::iterator it = map.begin();
	typename T::iterator ite = map.end();

	std::cout << "---- CONTENT ----" << std::endl;
	while (it != ite) {
		std::cout << "[" << (*it).first << "] => " << (*it).second << std::endl;
		it++;
	}
	std::cout << "-----------------" << std::endl;
}

//Vector TEST
int main ()
{
	
	ft::map<int, int> map;

	map.insert(ft::make_pair(1, 1));

	map.printTree();

	//ft::map<int, int>::iterator it = map.begin();

	//std::cout << (*it).first << std::endl;

	/*
	std::map<int, int> std_map;

	std_map.insert(std::make_pair(1, 100));
	std_map.insert(std::make_pair(2, 20));
	std_map.insert(std::make_pair(3, 300));
	std_map.insert(std::make_pair(4, 4));

	std::map<int, int>::iterator std_it = std_map.begin();
	std::map<int, int>::iterator std_ite = std_map.end();

	print_map_content(std_map);
	*/

	return 0;
}

/*

*/