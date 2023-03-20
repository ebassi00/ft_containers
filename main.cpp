#include "set.hpp"

#define T1 int

int		main(void)
{
	ft::set<T1> st;
	ft::set<T1>::iterator it = st.begin();
	ft::set<T1>::const_iterator cit = st.begin();

	ft::set<T1>::reverse_iterator rit(it);

	ft::set<T1>::const_reverse_iterator crit(rit);
	ft::set<T1>::const_reverse_iterator crit_(it);
	ft::set<T1>::const_reverse_iterator crit_2(cit);

	(void)crit;
	(void)crit_;
	(void)crit_2;
	/* error expected
	ft::set<T1>::reverse_iterator rit_(crit);
	ft::set<T1>::reverse_iterator rit2(cit);
	ft::set<T1>::iterator it2(rit);
	ft::set<T1>::const_iterator cit2(crit);
	*/

	std::cout << "OK" << std::endl;
	return (0);
}