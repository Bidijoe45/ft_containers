#include <iostream>
#include <memory>
#include <vector>
#include "./srcs/vector/vector.hpp"

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


//Vector TEST
int main ()
{
	
	//=======================================
	//==========  STD::VECTOR  ==============
	//=======================================

	std::vector<int> std_vec;

	std_vec.push_back(3);
	std_vec.push_back(7);
	std_vec.push_back(5);
	std_vec.push_back(1);
	std_vec.push_back(0);
	std_vec.push_back(8);
	
	std::cout << "std_vec" << std::endl;
	std::cout << "size: " << std_vec.size() << std::endl;
	std::cout << "capacity: " << std_vec.capacity() << std::endl;
	
	std::cout << "std_vec2" << std::endl;
	std::vector<int> std_vec2(3, 69);
	std::cout << "size: " << std_vec2.size() << std::endl;
	std::cout << "capacity: " << std_vec2.capacity() << std::endl;

	std::vector<int>::iterator it = std_vec2.begin();
	std::vector<int>::iterator ite = std_vec2.end();

	for(; it != ite; it++)
		std::cout << *it << ", ";
	std::cout << std::endl;

	std::cout << "--------" << std::endl;

	//=======================================
	//===========  FT::VECTOR  ==============
	//=======================================

	ft::vector<int> ft_vec(3, 69);

	std::cout << "ft_vec" << std::endl;
	std::cout << "size: " << ft_vec.size() << std::endl;
	std::cout << "capacity: " << ft_vec.capacity() << std::endl;
	std::cout << ft_vec.at(3) << std::endl;



	return 0;
}

