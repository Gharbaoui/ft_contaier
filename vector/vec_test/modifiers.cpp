#ifndef OUTER
#include <iostream>
#include "vector.hpp"
#include <vector>
#include "help.hpp"

int main()
{
	std::cout << "\033[1;32mclear  test\033[0m" << std::endl << std::endl;
	ft::vector<double> ft_vec(23, 56);
	std::vector<double> st_vec(23, 56);

	std::cout << "\033[1;36mbefore clear\033[0m" << std::endl;
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;
	std::cout << "\033[1;36mafter clear\033[0m" << std::endl;
	ft_vec.clear();
	st_vec.clear();
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;
	
	// just fill with some values
	srand(time(NULL));
	for (int i = 0; i < 20; ++i){
		int val = rand() % 100;
		ft_vec.push_back(val);
		st_vec.push_back(val);
	}

	std::cout << "\033[1;32minsert with iterator and value test\033[0m" << std::endl << std::endl;
	ft_vec.insert(ft_vec.begin(), -998);
	std::cout << ft_vec << std::endl;
	st_vec.insert(st_vec.begin(), -998);
	std::cout << st_vec << std::endl;

	std::cout << "\033[1;32minsert with iterator , count and value test\033[0m" << std::endl << std::endl;
	ft_vec.insert(ft_vec.begin() + 5, 4 , 111);
	std::cout << ft_vec << std::endl;
	st_vec.insert(st_vec.begin() + 5, 4, 111);
	std::cout << st_vec << std::endl;

	std::cout << "\033[1;32minsert with one element iterators test\033[0m" << std::endl << std::endl;
	ft::vector<int> f_holder(5, 666);
	std::vector<int> s_holder(5, 666);
	f_holder[2] = s_holder[2] = -84;	
	ft_vec.insert(ft_vec.begin() + 5, f_holder.begin(), f_holder.end());
	st_vec.insert(st_vec.begin() + 5, s_holder.begin(), s_holder.end());
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;

	{
		std::cout << "\033[1;32minsert with range iterators  test\033[0m" << std::endl << std::endl;
		ft::vector<int> new_f_holder(10, 99);
		std::vector<int> new_s_holder(10, 99);
		new_f_holder[2] = new_s_holder[2] = -66;

		ft::vector<int> new_ft_vec(5, 7888);
		std::vector<int> new_st_vec(5, 7888);

		new_ft_vec.insert(new_ft_vec.begin() + 2, new_f_holder.begin(), new_f_holder.end());
		new_st_vec.insert(new_st_vec.begin() + 2, new_s_holder.begin(), new_s_holder.end());

		std::cout << new_ft_vec << std::endl;
		std::cout << new_st_vec << std::endl;
	}

	std::cout << "\033[1;32merase one element test\033[0m" << std::endl << std::endl;
	ft_vec.erase(ft_vec.begin() + 7);
	st_vec.erase(st_vec.begin() + 7);
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;

	std::cout << "\033[1;32merase range test\033[0m" << std::endl << std::endl;
	ft_vec.erase(ft_vec.begin() + 9, ft_vec.begin() + 12);
	st_vec.erase(st_vec.begin() + 9, st_vec.begin() + 12);
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;

	std::cout << "\033[1;32mpush_back test\033[0m" << std::endl << std::endl;
	std::cout << "|    before push back    |" << std::endl;
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;
	std::cout << "|    after push back    |" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		int val = rand()  % 100;
		ft_vec.push_back(val);
		st_vec.push_back(val);
	}
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;

	{
		std::cout << "\033[1;32mpush_back on empty vector test\033[0m" << std::endl << std::endl;
		ft::vector<int> ft_vec;
		std::vector<int> st_vec;

		std::cout << "|    before push back    |" << std::endl;
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
		std::cout << "|    after push back    |" << std::endl;
		for (int i = 0; i < 10; ++i)
		{
			int val = rand()  % 100;
			ft_vec.push_back(val);
			st_vec.push_back(val);
		}
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
	}
	std::cout << "\033[1;32mpop_back  test\033[0m" << std::endl << std::endl;
	std::cout << "|    before pop back    |" << std::endl;
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;
	std::cout << "|    after pop back    |" << std::endl;
	int size = ft_vec.size();
	for (int i = 0; i < size; ++i)
	{
		ft_vec.pop_back();
		st_vec.pop_back();
	}
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;
	
	std::cout << "\033[1;32mpop_back empty vector  test\033[0m" << std::endl << std::endl;
	std::cout << "|    before pop back    |" << std::endl;
	std::cout << ft_vec << std::endl;
	std::cout << "|    after pop back    |" << std::endl;
	ft_vec.pop_back();
	std::cout << ft_vec << std::endl;
	
	{
		std::cout << "\033[1;32mresize more than size and smaller than capacity  test\033[0m" << std::endl << std::endl;
		ft::vector<double> ft_vec(23, 56);
		std::vector<double> st_vec(23, 56);
		ft_vec.push_back(23);
		st_vec.push_back(23);
	
		std::cout << "|    before resize    |" << std::endl;
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
		std::cout << "|    after resize    |" << std::endl;
		ft_vec.resize(40, -99);
		st_vec.resize(40, -99);
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;

		std::cout << "\033[1;32mresize smaller than size test\033[0m" << std::endl << std::endl;
		std::cout << "|    before resize    |" << std::endl;
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
		std::cout << "|    after resize    |" << std::endl;
		ft_vec.resize(30, -99);
		st_vec.resize(30, -99);
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
		std::cout << "\033[1;32mresize more than capacity  test\033[0m" << std::endl << std::endl;
		std::cout << "|    before resize    |" << std::endl;
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
		std::cout << "|    after resize    |" << std::endl;
		ft_vec.resize(100, -1);
		st_vec.resize(100, -1);
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
	}

	{
		std::cout << "\033[1;32mresize more than size and smaller than capacity (one param) test\033[0m" << std::endl << std::endl;
		ft::vector<double> ft_vec(23);
		std::vector<double> st_vec(23);
		ft_vec.push_back(23);
		st_vec.push_back(23);
	
		std::cout << "|    before resize    |" << std::endl;
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
		std::cout << "|    after resize    |" << std::endl;
		ft_vec.resize(40);
		st_vec.resize(40);
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;

		std::cout << "\033[1;32mresize smaller than size (one param) test\033[0m" << std::endl << std::endl;
		std::cout << "|    before resize    |" << std::endl;
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
		std::cout << "|    after resize    |" << std::endl;
		ft_vec.resize(30);
		st_vec.resize(30);
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
		std::cout << "\033[1;32mresize more than capacity (one param)  test\033[0m" << std::endl << std::endl;
		std::cout << "|    before resize    |" << std::endl;
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
		std::cout << "|    after resize    |" << std::endl;
		ft_vec.resize(100);
		st_vec.resize(100);
		std::cout << ft_vec << std::endl;
		std::cout << st_vec << std::endl;
	}
	
	std::cout << "\033[1;32mswap  test\033[0m" << std::endl << std::endl;
	ft::vector<float> f_a1(12, 78);
	ft::vector<float> f_a2(2, 12);

	std::vector<float> s_a1(12, 78);
	std::vector<float> s_a2(2, 12);

	std::cout << "\033[1;40mft before swap\033[0m" << std::endl;
	std::cout << f_a1 << std::endl;
	std::cout << f_a2 << std::endl;
	std::cout << "\033[1;40mft after swap\033[0m" << std::endl;
	f_a2.swap(f_a1);
	std::cout << f_a1 << std::endl;
	std::cout << f_a2 << std::endl;
	
	std::cout << "\033[1;40mstd before swap\033[0m" << std::endl;
	std::cout << s_a1 << std::endl;
	std::cout << s_a2 << std::endl;
	std::cout << "\033[1;40mstd after swap\033[0m" << std::endl;
	s_a2.swap(s_a1);
	std::cout << s_a1 << std::endl;
	std::cout << s_a2 << std::endl;
}

#endif


#ifdef OUTER
#include <vector>
# include <iostream>
# include <iterator>
# include <ctime>
# include <iomanip>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include "vector.hpp"


# define BLUE "\e[0;34m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[1;33m"
# define RESET "\e[0m"

# define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
# define TIME_FAC 3 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)


time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return(msecs_time);
}
#endif
