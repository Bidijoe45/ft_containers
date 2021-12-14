#pragma once
#include <type_traits>

namespace ft {

	template<typename> struct is_integral : std::false_type {};

	template<> struct is_integral<bool> : std::true_type {};
	template<> struct is_integral<char> : std::true_type {};
	template<> struct is_integral<char16_t> : std::true_type {};
	template<> struct is_integral<char32_t> : std::true_type {};
	template<> struct is_integral<wchar_t> : std::true_type {};
	template<> struct is_integral<signed char> : std::true_type {};
	template<> struct is_integral<short int> : std::true_type {};
	template<> struct is_integral<int> : std::true_type {};
	template<> struct is_integral<long int> : std::true_type {};
	template<> struct is_integral<long long int> : std::true_type {};
	template<> struct is_integral<unsigned char> : std::true_type {};
	template<> struct is_integral<unsigned short int> : std::true_type {};
	template<> struct is_integral<unsigned int> : std::true_type {};
	template<> struct is_integral<unsigned long int> : std::true_type {};
	template<> struct is_integral<unsigned long long int> : std::true_type {};

}
