#pragma once
#include <type_traits>

namespace ft {

	template<typename> struct is_integral {
		static const bool value = false;
	};

	template<> struct is_integral<bool> {
		static const bool value = true;
	};

	template<> struct is_integral<char> {
		static const bool value = true;
	};

	template<> struct is_integral<char16_t> {
		static const bool value = true;
	};

	template<> struct is_integral<char32_t> {
		static const bool value = true;
	};

	template<> struct is_integral<wchar_t> : std::true_type {
		static const bool value = true;
	};

	template<> struct is_integral<signed char> : std::true_type {
		static const bool value = true;
	};

	template<> struct is_integral<short int> : std::true_type {
		static const bool value = true;
	};

	template<> struct is_integral<int> : std::true_type {
		static const bool value = true;
	};

	template<> struct is_integral<long int> : std::true_type {
		static const bool value = true;
	};

	template<> struct is_integral<long long int> : std::true_type {
		static const bool value = true;
	};

	template<> struct is_integral<unsigned char> : std::true_type {
		static const bool value = true;
	};

	template<> struct is_integral<unsigned short int> : std::true_type {
		static const bool value = true;
	};

	template<> struct is_integral<unsigned int> : std::true_type {
		static const bool value = true;
	};

	template<> struct is_integral<unsigned long int> : std::true_type {
		static const bool value = true;
	};

	template<> struct is_integral<unsigned long long int> : std::true_type {
		static const bool value = true;
	};

}
