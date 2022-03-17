#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include "./srcs/vector.hpp"
#include "./srcs/utils/tree/tree.hpp"
#include "./srcs/utils/is_integral_traits.hpp"
#include "./srcs/utils/iterator_traits.hpp"
#include "./srcs/map.hpp"

//ALLOCATOR USE TEST
/*

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

	map.insert(std::make_pair(2, 1));
	map.insert(std::make_pair(4, 22));
	std::pair<ft::map<int, int>::iterator, bool> insert_ret = map.insert(std::make_pair(6, 333));
	map.insert(std::make_pair(8, 4444));
	map.insert(std::make_pair(10, 55555));

	ft::map<int, int>::iterator it = insert_ret.first;

	map.insert(it, std::make_pair(12, 123));

	ft::map<int, int>::iterator find1 = map.find(123123);

	if (find1 != map.end())
		std::cout << "encontrad 1" << std::endl;

	ft::map<int, int>::iterator find2 = map.find(200);

	if (find2 != map.end())
		std::cout << "encontrad 2" << std::endl;
	

	std::cout << std::endl << "-------- TREE ---------" << std::endl;
	map.printTree();
	std::cout << std::endl << "-----------------------" << std::endl << std::endl;


	/*
	while (it != ite) {
		std::cout << (*it).first << " : " << (*it).second << std::endl;
		it++;
	}
	*/
	
	return 0;
}
