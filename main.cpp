#include <iostream>
#include <memory>
#include <vector>
#include "./srcs/vector.hpp"

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

	std::vector<int> std_vec;

	std_vec.push_back(3);
	std_vec.push_back(7);
	std_vec.push_back(5);
	std_vec.push_back(1);
	std_vec.push_back(0);
	std_vec.push_back(8);
	
	print_vector_stats(std_vec);
	
	std_vec.resize(4);

	print_vector_stats(std_vec);


	ft::vector<int> ft_vec(6, 69);

	print_vector_stats(ft_vec);

	ft_vec.resize(4);

	print_vector_stats(ft_vec);
	

	//=======================================
	//===========  FT::VECTOR  ==============
	//=======================================
	/*
	ft::vector<int> ft_vec(3, 69);

	std::cout << "ft_vec" << std::endl;
	print_ftvector_stats(ft_vec);
	std::cout << ft_vec.at(3) << std::endl;

	int &vec_elem10 = ft_vec.at(2);
	vec_elem10 = 1;

	std::cout << "-- iterator start --" << std::endl;
	
	ft::vector<int>::iterator ftit = ft_vec.begin();
	ft::vector<int>::iterator ftite = ft_vec.end();

	for (; ftit != ftite; ftit++)
	{
		std::cout << *ftit << " ";
	}

	std::cout << std::endl;

	std::cout << "-- iterator end --" << std::endl;

	std::cout << "-- vector reserve start -- " << std::endl;
	
	print_ftvector_stats(ft_vec);

	ft_vec.reserve(20);

	print_ftvector_stats(ft_vec);

	ftit = ft_vec.begin();
	ftite = ft_vec.end();

	for (; ftit != ftite; ftit++)
	{
		std::cout << *ftit << " ";
	}

	std::cout << std::endl;

	std::cout << "-- vector reserve end -- " << std::endl;
	*/
	return 0;
}

