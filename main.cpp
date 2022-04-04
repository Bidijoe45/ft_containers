#include <iostream>

#include <vector>
#include "srcs/vector.hpp"

#define NOCOLOR "\e[0m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"

#define SHOW_OUTPUT false

void check_leaks() {
	system("leaks ft_containers");
}

/* -------------- VECTOR TESTER -------------- */

template<class T>
std::string get_vector_content_std(typename std::vector<T> &vec) {
	std::string output = "";

	output += ("size: " + std::to_string(vec.size()) + "\n");

	typename std::vector<T>::iterator it = vec.begin();
	typename std::vector<T>::iterator ite = vec.end();

	output += "--- CONTENT: ---" ;
	output += "\n";
	while (it != ite) {
		output += std::to_string(*it) + "\n";
		it++;
	}

	output += "\n";
	output += "----------------";
	output += '\n';

	if (SHOW_OUTPUT) {
		std::cout << "======= STD OUTPUT ========" << std::endl;
		std::cout << output;
		std::cout << "==========================" << std::endl;
	}

	return output;
}

template<class T>
std::string get_vector_content_ft(typename ft::vector<T> &vec) {
	std::string output = "";

	output += ("size: " + std::to_string(vec.size()) + "\n");

	typename ft::vector<T>::iterator it = vec.begin();
	typename ft::vector<T>::iterator ite = vec.end();

	output += "--- CONTENT: ---" ;
	output += "\n";
	while (it != ite) {
		output += std::to_string(*it) + "\n";
		it++;
	}

	output += "\n";
	output += "----------------";
	output += '\n';

	if (SHOW_OUTPUT) {
		std::cout << "======= FT OUTPUT ========" << std::endl;
		std::cout << output;
		std::cout << "==========================" << std::endl;
	}

	return output;
}

bool compare_vector_test_output(int test_number, std::string (*func1)(void), std::string(*func2)(void)) {
	if (SHOW_OUTPUT) {
		std::cout << "=============" << " TEST " << test_number << " =============" << std::endl;
	}

	std::string output1 = func1();
	std::string output2 = func2();

	return output1 == output2;
}

void print_outputs_result(int test_number, bool test_result) {
	
	std::cout << "Test " << test_number << " => " << ((test_result) ? GREEN "OK" : RED "KO") << NOCOLOR << std::endl;
}

//############ TEST 1 #################

std::string vector_test_1_std() {
	
	std::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	return get_vector_content_std(vec);
}

std::string vector_test_1_ft() {
	
	ft::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	return get_vector_content_ft(vec);
}

//############ TEST 2 #################

std::string vector_test_2_std() {
	
	std::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vec.pop_back();
	vec.pop_back();

	return get_vector_content_std(vec);
}

std::string vector_test_2_ft() {
	
	ft::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vec.pop_back();
	vec.pop_back();

	return get_vector_content_ft(vec);
}

//############ TEST 3 #################

std::string vector_test_3_std() {
	
	std::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vec.pop_back();
	vec.pop_back();

	std::vector<int>::iterator pos = vec.begin();

	vec.insert(pos, 69);

	pos = vec.end();

	vec.insert(pos, 0);

	return get_vector_content_std(vec);
}

std::string vector_test_3_ft() {
	
	ft::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vec.pop_back();
	vec.pop_back();

	ft::vector<int>::iterator pos = vec.begin();

	vec.insert(pos, 69);

	pos = vec.end();

	vec.insert(pos, 0);

	return get_vector_content_ft(vec);
}

//############ TEST 4 #################

std::string vector_test_4_std() {
	
	std::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vec.pop_back();
	vec.pop_back();

	std::vector<int> map2;

	map2.push_back(-9);
	map2.push_back(-8);
	map2.push_back(-7);
	map2.push_back(-6);

	vec.insert(vec.begin(), map2.begin(), map2.end());

	return get_vector_content_std(vec);
}

std::string vector_test_4_ft() {
	
	ft::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vec.pop_back();
	vec.pop_back();

	ft::vector<int> map2;

	map2.push_back(-9);
	map2.push_back(-8);
	map2.push_back(-7);
	map2.push_back(-6);

	vec.insert(vec.begin(), map2.begin(), map2.end());

	return get_vector_content_ft(vec);
}

//############ TEST 5 #################

std::string vector_test_5_std() {
	
	std::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vec.erase(vec.begin());

	vec.at(2) = 1111;

	return get_vector_content_std(vec);
}

std::string vector_test_5_ft() {
	
	ft::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vec.erase(vec.begin());

	vec.at(2) = 1111;

	return get_vector_content_ft(vec);
}

//############ TEST 6 #################

std::string vector_test_6_std() {
	
	std::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vec.erase(vec.begin());

	vec[0] = 999;

	std::vector<int> vec2(vec);

	vec2.erase(vec2.begin());

	return get_vector_content_std(vec2);
}

std::string vector_test_6_ft() {
	
	ft::vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vec.erase(vec.begin());

	vec[0] = 999;

	ft::vector<int> vec2(vec);

	vec2.erase(vec2.begin());

	return get_vector_content_ft(vec2);
}

void vector_tester() {
	std::cout << "- - - VECTOR - - -" << std::endl;
	print_outputs_result(1, compare_vector_test_output(1, &vector_test_1_std, &vector_test_1_ft));
	print_outputs_result(2, compare_vector_test_output(2, &vector_test_2_std, &vector_test_2_ft));
	print_outputs_result(3, compare_vector_test_output(3, &vector_test_3_std, &vector_test_3_ft));
	print_outputs_result(4, compare_vector_test_output(4, &vector_test_4_std, &vector_test_4_ft));
	print_outputs_result(5, compare_vector_test_output(5, &vector_test_5_std, &vector_test_5_ft));
	print_outputs_result(6, compare_vector_test_output(6, &vector_test_6_std, &vector_test_6_ft));
}

/* -------------- STACK TESTER -------------- */


void stack_tester() {
	
}

/* -------------- MAP TESTER -------------- */
void map_tester() {

}

int main ()
{
	//atexit(&check_leaks);

	vector_tester();

	stack_tester();

	return 0;
}
