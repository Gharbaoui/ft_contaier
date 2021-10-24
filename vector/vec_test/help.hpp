
template <typename T>
std::ostream	&operator<< (std::ostream &os, ft::vector<T> &v)
{
	int size = v.size();
	std::cout << "\033[1;34mft_vector\033[0m" << std::endl;
	for (int i = 0; i < size; ++i){
		os << v[i] << " ";
	}
	if (size)
		std::cout << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << "size: " << v.size() << std::endl;
	return os;
}

template <typename T>
std::ostream	&operator<< (std::ostream &os, std::vector<T> &v)
{
	int size = v.size();

	std::cout << "\033[1;34mstd_vector\033[0m" << std::endl;
	for (int i = 0; i < size; ++i){
		os << v[i] << " ";
	}
	if (size)
	std::cout << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << "size: " << v.size() << std::endl;
	return os;
}
