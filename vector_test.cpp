/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:13:51 by ebassi            #+#    #+#             */
/*   Updated: 2022/12/01 16:38:30 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include "vector.hpp"

#define _vector	ft::vector
const std::string GREEN = "\x1B[1;32m";
const std::string REDD = "\x1B[1;31m";
const std::string YELLOW = "\x1B[1;33m";
const std::string WHITE = "\x1B[1;39m";
const std::string RESET = "\033[0m";

volatile static time_t g_start1;
volatile static time_t g_start2;
volatile static time_t g_end1;
volatile static time_t g_end2;

time_t timer() {
	struct timeval start = {};
	gettimeofday(&start, nullptr);
	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return msecs_time;
}


int _ratio = 10000;
int _allocator_used = 0;

void printElement(std::string t) {
	if (t == "OK")
	    t = GREEN + t + RESET;
	else if (t == "FAILED") t = REDD + t + RESET;
	std::cout << std::left << std::setw(30) << std::setfill(' ') << t;
}


std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	FILE* pipe = popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	} catch (...) { pclose(pipe); throw; }
	pclose(pipe);
	return result;
}

std::string get_leak_string(std::string s) {
	std::string tmp;
	int idx = s.find("total leaked bytes");
	for (; s[idx] != '\n' ; --idx) {}
	int edx = idx + 1;
	for (; s[edx] != '\n' ; ++edx) {}

	return s.substr(++idx, edx - 101);
}

int leaks_test(pid_t pid) {
	std::string a = "leaks ";
	a += std::to_string(static_cast<int>(pid));
	std::string s = get_leak_string(exec(a.c_str()));

	if (s.find("0 leaks for 0 total leaked bytes") != std::string::npos) {
		printElement(GREEN + "CLEAR" + RESET);
		return (0);
	}
	else {
	    printElement(REDD + "LEAKS" + RESET);
	    return (1);
	}
}

template <class T>
int run_vector_unit_test(std::string test_name, std::vector<int> (func1)(std::vector<T>), std::vector<int> (func2)(_vector<T>)) {
    int    result;
    int    leaks;
    time_t t1;
    time_t t2;
    std::vector<int > res1;
    std::vector<int > res2;
    std::vector<int> vector;
    _vector<int> my_vector;

	printElement(test_name);
	res1 = func1(vector);
	res2 = func2(my_vector);
	if (res1 == res2) {
	    printElement("OK");
	    result = 0;
	}
	else {
		std::cout << std::endl << "nostro: " << res2.at(0) << std::endl;
		std::cout << "tester: " << res1.at(0) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(1) << std::endl;
		std::cout << "tester: " << res1.at(1) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(2) << std::endl;
		std::cout << "tester: " << res1.at(2) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(3) << std::endl;
		std::cout << "tester: " << res1.at(3) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(4) << std::endl;
		std::cout << "tester: " << res1.at(4) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(5) << std::endl;
		std::cout << "tester: " << res1.at(5) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(6) << std::endl;
		std::cout << "tester: " << res1.at(6) << std::endl << std:: endl;
		std::cout << "nostro: " << res2.at(7) << std::endl;
		std::cout << "tester: " << res1.at(7) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(8) << std::endl;
		std::cout << "tester: " << res1.at(8) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(9) << std::endl;
		std::cout << "tester: " << res1.at(9) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(10) << std::endl;
		std::cout << "tester: " << res1.at(10) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(11) << std::endl;
		std::cout << "tester: " << res1.at(11) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(12) << std::endl;
		std::cout << "tester: " << res1.at(12) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(13) << std::endl;
		std::cout << "tester: " << res1.at(13) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(14) << std::endl;
		std::cout << "tester: " << res1.at(14) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(15) << std::endl;
		std::cout << "tester: " << res1.at(15) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(16) << std::endl;
		std::cout << "tester: " << res1.at(16) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(17) << std::endl;
		std::cout << "tester: " << res1.at(17) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(18) << std::endl;
		std::cout << "tester: " << res1.at(18) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(19) << std::endl;
		std::cout << "tester: " << res1.at(19) << std::endl << std::endl;
		std::cout << "nostro: " << res2.at(20) << std::endl;
		std::cout << "tester: " << res1.at(20) << std::endl << std::endl;
	    printElement("FAILED");
	    result = 1;
	}
	t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
	(t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
	(t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
	// leaks = leaks_test(getpid());
	leaks = 0;
	std::cout << std::endl;

	return !(!result && !leaks);
}

template <class T, class A>
int run_vector_allocator_unit_test(std::string test_name, void (func)(_vector<T, A>)) {
    _vector<T, A> my_vector;

    printElement(test_name);
    func(my_vector);
    if (_allocator_used) {
        printElement("OK");
        std::cout << std::endl;
        return (0);
    }
    else {
        printElement("FAILED");
        std::cout << std::endl;
        return (1);
    }
}


template <typename T>
std::vector<int> iterator_test(std::vector<T> vector) {
    typename std::vector<T>::iterator it;
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
        vector.push_back(i);
    it = vector.begin();
    // g_start1 = timer();
    v.push_back(*(++it));
    v.push_back(*(--it));
    v.push_back(*(it + 1));
    it += 1;
    v.push_back(*(it - 1));
    it -= 1;
    v.push_back(*it);
    // g_end1 = timer();
    return v;
}

template <typename T>
std::vector<int> iterator_test(_vector<T> vector) {
    typename _vector<T>::iterator it;
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
        vector.push_back(i);
    it = vector.begin();
    // g_start2 = timer();
    v.push_back(*(++it));
    v.push_back(*(--it));
    v.push_back(*(it + 1));
    it += 1;
    v.push_back(*(it - 1));
    it -= 1;
    v.push_back(*it);
    // g_end2 = timer();
    return v;
}

template <typename T>
void	printVector(_vector<T> vector)
{
	typename ft::vector<T>::iterator	iter;
	if (vector.empty())
		std::cout << "VUOTO" << std::endl;
	else
	{
		iter = vector.begin();
		while (iter != vector.end())
			std::cout << *iter++ << std::endl;
	}
}

template <typename T>
std::vector<int> push_back_test(std::vector<T> vector) {
    std::vector<int> v;
    // g_start1 = timer();
    for (int i = 0; i < 5500 * _ratio; ++i)
        vector.push_back(i);
    // g_end1 = timer();
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> push_back_test(_vector<T> vector) {
    std::vector<int> v;
    // g_start2 = timer();
    for (int i = 0; i < 5500 * _ratio; ++i) {
        vector.push_back(i);
    }
    // g_end2 = timer();
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> insert_test_1(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(2600 * _ratio, 1);
    // g_start1 = timer();
    v.push_back(*(vector.insert(vector.end() - 800 * _ratio, 44)));
    // g_end1 = timer();
    v.push_back(vector.size());
    v.push_back(vector.capacity());

    return v;
}

template <typename T>
std::vector<int> insert_test_1(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(2600 * _ratio, 1);
    // g_start2 = timer();
    v.push_back(*(vector.insert(vector.end() - 800 * _ratio, 44)));
    // g_end2 = timer();
    v.push_back(vector.size());
    v.push_back(vector.capacity());

    return v;
}

template <typename T>
std::vector<int> constructor_test(std::vector<T> vector) {
    std::vector<int> v;
    std::vector<int> tmp0(vector);
    std::vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
    tmp = tmp2;
    std::vector<int> tmp3(tmp);
    // g_start1 = timer();
    std::vector<int> tmp4(tmp.begin(), tmp.end());
    // g_end1 = timer();
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { std::vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
    return v;
}

template <typename T>
std::vector<int> constructor_test(_vector<T> vector) {
    std::vector<int> v;
	_vector<int> tmp0(vector);
    _vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
    tmp = tmp2;
    _vector<int> tmp3(tmp);
    // g_start2 = timer();
    _vector<int> tmp4(tmp.begin(), tmp.end());
    // g_end2 = timer();
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { _vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
    return v;
}

template <typename T>
std::vector<int> empty_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    // g_start1 = timer();
    v.push_back(vector.empty());
    // g_end1 = timer();
    return v;
}

template <typename T>
std::vector<int> empty_test(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    // g_start2 = timer();
    v.push_back(vector.empty());
    // g_end2 = timer();
    return v;
}

template <typename T>
std::vector<int> insert_std_test(std::vector<T> vector) {
	std::vector<int> v;
	std::vector<int> tmp;
	tmp.assign(2600 * _ratio, 1);
	vector.assign(4200 * _ratio, 7);
	// g_start1 = timer();
	vector.insert(vector.begin(), tmp.begin(), tmp.end());
	// g_end1 = timer();
	for (size_t i = 0; i < tmp.size(); ++i) {
		v.push_back(vector[i]);
	}
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	return v;
}

template <typename T>
std::vector<int> insert_std_test(_vector<T> vector) {
	std::vector<int> v;
	std::vector<int> tmp;
	tmp.assign(2600 * _ratio, 1);
	vector.assign(4200 * _ratio, 7);
	// g_start2 = timer();
	vector.insert(vector.begin(), tmp.begin(), tmp.end());
	// g_end2 = timer();
	for (size_t i = 0; i < tmp.size(); ++i) {
		v.push_back(vector[i]);
	}
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	return v;
}

template <typename T>
std::vector<int> assign_test(std::vector<T> vector) {
    std::vector<int> v;
    std::vector<int> tmp, tmp2;
    vector.assign(3, 3);
    tmp.assign(4000 * _ratio, 1);
    tmp2.assign(4 * _ratio, 1);
    // g_start1 = timer();
    vector.assign(tmp.begin(), tmp.end());
    v.push_back(vector[1]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.assign(tmp2.begin(), tmp2.end());
    // g_end1 = timer();
    v.push_back(vector[444]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> assign_test(_vector<T> vector) {
    std::vector<int> v;
    _vector<int> tmp, tmp2;
    vector.assign(3, 3);
    tmp.assign(4000 * _ratio, 1);
    tmp2.assign(4 * _ratio, 1);
    // g_start2 = timer();
    vector.assign(tmp.begin(), tmp.end());
    v.push_back(vector[1]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.assign(tmp2.begin(), tmp2.end());
    // g_end2 = timer();
    v.push_back(vector[444]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> resize_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(9900 * _ratio, 1);
    // g_start1 = timer();
    vector.resize(5000 * _ratio);
    vector.reserve(5000 * _ratio);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(7000 * _ratio);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(15300 * _ratio, T());
    v.push_back(vector.size());
    // v.push_back(vector.capacity());
    v.push_back(vector[65]);
    // g_end1 = timer();
    return v;
}

template <typename T>
std::vector<int> resize_test(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(9900 * _ratio, 1);
    // g_start2 = timer();
    vector.resize(5000 * _ratio);
    vector.reserve(5000 * _ratio);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(7000 * _ratio);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(15300 * _ratio, T());
    v.push_back(vector.size());
    // v.push_back(vector.capacity());
    v.push_back(vector[65]);
    // g_end2 = timer();
    return v;
}

template <typename T>
std::vector<int> insert_test_2(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    // g_start1 = timer();
    vector.insert(vector.end() - 50, 4200 * _ratio , 2);
    // g_end1 = timer();
    v.push_back(vector[2121]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> insert_test_2(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    // g_start2 = timer();
    vector.insert(vector.end() - 50, 4200 * _ratio , 2);
    // g_end2 = timer();
    v.push_back(vector[2121]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };
};

template <typename T>
std::vector<int> insert_test_3(std::vector<T> vector) {
    std::vector<int> v;
    std::vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
    // g_start1 = timer();
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    // g_end1 = timer();
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());

    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    std::vector<A> vv;
    std::vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }

    return v;
}

template <typename T>
std::vector<int> insert_test_3(_vector<T> vector) {
    std::vector<int> v;
    _vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
    // g_start2 = timer();
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    // g_end2 = timer();
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());

    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    _vector<A> vv;
    _vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }

    return v;
}

template <typename T>
std::vector<int> erase_test_2(std::vector<T> vector) {
    std::vector<int> v;
    for (int i = 0; i < 9900 * _ratio; ++i)
        vector.push_back(i);
    // g_start1 = timer();
    v.push_back(*(vector.erase(vector.begin() + 8 * _ratio, vector.end() - 1500 * _ratio)));
    // g_end1 = timer();
    v.push_back(*(vector.begin() + 82 * _ratio));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> erase_test_2(_vector<T> vector) {
    std::vector<int> v;
    for (int i = 0; i < 9900 * _ratio; ++i)
        vector.push_back(i);
    // g_start2 = timer();
    v.push_back(*(vector.erase(vector.begin() + 8 * _ratio, vector.end() - 1500 * _ratio)));
    // g_end2 = timer();
    v.push_back(*(vector.begin() + 82 * _ratio));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> erase_test_1(std::vector<T> vector) {
    std::vector<int> v;
    for (int i = 0; i < 9900 * _ratio; ++i)
        vector.push_back(i);
    g_start1 = timer();
    v.push_back(*(vector.erase(vector.begin() + 8 * _ratio)));
    g_end1 = timer();
    v.push_back(*(vector.begin() + 82 * _ratio));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> erase_test_1(_vector<T> vector) {
    std::vector<int> v;
    for (int i = 0; i < 9900 * _ratio; ++i)
        vector.push_back(i);
    g_start2 = timer();
    v.push_back(*(vector.erase(vector.begin() + 8 * _ratio)));
    g_end2 = timer();
    v.push_back(*(vector.begin() + 82 * _ratio));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> swap_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1100 * _ratio, 11);
    std::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
    g_start1 = timer();
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    vector.swap(tmp);
    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	v.push_back(1);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.swap(tmp3);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::swap(vector, tmp2);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::swap(vector, tmp4);
    // g_end1 = timer();
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> swap_test(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(1100 * _ratio, 11);
    _vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
    // g_start2 = timer();
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    vector.swap(tmp);
    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	v.push_back(1);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.swap(tmp3);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::swap(vector, tmp2);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::swap(vector, tmp4);
    // g_end2 = timer();
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> rbegin_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    g_start1 = timer();
    v.push_back(*vector.rbegin());
    v.push_back(*(vector.rbegin() + 1));
    g_end1 = timer();
    return v;
}

template <typename T>
std::vector<int> rbegin_test(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    g_start2 = timer();
    v.push_back(*vector.rbegin());
    v.push_back(*(vector.rbegin() + 1));
    g_end2 = timer();
    return v;
}

template <typename T>
std::vector<int> clear_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(5000 * _ratio, 1);
    g_start1 = timer();
    vector.clear();
    g_end1 = timer();
    v.push_back(vector.capacity());
    v.push_back(vector.size());
    return v;
}

template <typename T>
std::vector<int> clear_test(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(5000 * _ratio, 1);
    g_start2 = timer();
    vector.clear();
    g_end2 = timer();
    v.push_back(vector.capacity());
    v.push_back(vector.size());
    return v;
}

int main() {

    exit(run_vector_unit_test<int>("swap()", swap_test, swap_test));
}
