#include "map.hpp"
#include "iterator.hpp"
#include "rb_tree.hpp"

int		main(void)
{
	ft::map<int, int> m;

	// insert range test
	m.insert(ft::make_pair(1, 1));
	m.insert(ft::make_pair(2, 2));
	m.insert(ft::make_pair(3, 3));
	m.insert(ft::make_pair(4, 4));
	m.insert(ft::make_pair(5, 5));

	// print m and m2 content
	ft::map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		std::cout << "m content: " << it->first << " " << it->second << std::endl;
		it++;
	}
	std::cout << m.empty() << std::endl;
}