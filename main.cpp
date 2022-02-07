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
	
	/*
	ft::vector<int> ft_vec1(10, 69);

	ft_vec1[0] = 1;
	ft_vec1[1] = 2;
	ft_vec1[2] = 3;
	ft_vec1[3] = 4;
	ft_vec1[4] = 5;
	ft_vec1[5] = 6;
	ft_vec1[6] = 7;
	ft_vec1[7] = 8;
	ft_vec1[8] = 9;
	ft_vec1[9] = 10;

	ft::vector<int> ft_vec2;
	ft_vec2[0] = -1;
	ft_vec2[1] = -2;
	ft_vec2[2] = -3;
	ft_vec2[3] = -4;
	*/


	ft::vector<int> vct(5);
	ft::vector<int> vct2;
	const int cut = 3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = i + 1;
	print_vector_stats(vct);
	print_vector_content(vct);

	vct2.insert(vct2.begin(), vct.begin(), vct.begin() + cut);
	print_vector_stats(vct2);
	print_vector_content(vct2);

	vct2.insert(vct2.begin(), vct.begin() + cut, vct.end());
	print_vector_stats(vct2);
	print_vector_content(vct2);

	vct2.insert(vct2.end(), vct.begin(), vct.begin() + cut);
	print_vector_stats(vct2);
	print_vector_content(vct2);

	std::cout << "insert return:" << std::endl;

	std::cout << *vct2.insert(vct2.end(), 42) << std::endl;
	std::cout << *vct2.insert(vct2.begin() + 5, 84) << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	print_vector_content(vct2);

	return 0;
}
