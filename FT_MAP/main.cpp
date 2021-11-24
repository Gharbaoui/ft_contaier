#include <iostream>
#include <memory>
#include <vector>
#include <unistd.h>
#include <map>
#include "map.hpp"


#include <vector>
#include <unistd.h>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>

int main()
{
	bool cond;
        {
			std::map<int, std::string> m3;
			ft::map<int, std::string> ft_m3;

			std::vector<int> vec;
			std::vector<int> ft_vec;

			std::random_device randDev;
			std::mt19937 generator(randDev());
			std::uniform_int_distribution<int> distr(0, 1e8);

			for (size_t i = 0; i < 10; i++)
			{
				m3.insert(std::make_pair(i, "string1"));
				ft_m3.insert(ft::make_pair(i, "string1"));
			}

			for (size_t i = 0; i < 10; ++i)
			{
				int n = distr(generator);
				int ret1 = m3.erase(n);
				int ret2 = ft_m3.erase(n);

				if (ret1 != ret2)
				{
					std::cout << "got inside" << std::endl;
					cond = false;
					break;
				}
			}

			if (!m3.empty())
			{
				m3.erase(m3.begin(), m3.end());
				m3.erase(m3.begin(), m3.end());
			}
			if (!ft_m3.empty())
			{
				ft_m3.erase(ft_m3.begin(), ft_m3.end());
				ft_m3.erase(ft_m3.begin(), ft_m3.end());
			}
        }
}
