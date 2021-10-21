#ifndef IS_INTEGRAL
#define IS_INTEGRAL
// helpers
namespace ft{
template <bool val>
struct ft_type{
	static const bool value = val;
};

// helpers end
template <typename T>
struct	is_integral : ft_type<false>{};

template <>
struct is_integral<bool> : ft_type<true> {};

template <>
struct is_integral<char> : ft_type<true> {};

template <>
struct is_integral<signed char> : ft_type<true> {};

template <>
struct is_integral<unsigned char> : ft_type<true> {};

template <>
struct is_integral<unsigned short> : ft_type<true> {};

template <>
struct is_integral<char16_t> : ft_type<true> {};

template <>
struct is_integral<char32_t> : ft_type<true> {};

template <>
struct is_integral<wchar_t> : ft_type<true> {};

template <>
struct is_integral<short> : ft_type<true> {};

template <>
struct is_integral<int> : ft_type<true> {};

template <>
struct is_integral<unsigned int> : ft_type<true> {};

template <>
struct is_integral<long> : ft_type<true> {};

template <>
struct is_integral<unsigned long> : ft_type<true> {};

template <>
struct is_integral<long long> : ft_type<true> {};

template <>
struct is_integral<unsigned long long> : ft_type<true> {};

template <>
struct is_integral<float> : ft_type<true> {};

template <>
struct is_integral<double> : ft_type<true> {};

template <>
struct is_integral<long double> : ft_type<true> {};
};
#endif
