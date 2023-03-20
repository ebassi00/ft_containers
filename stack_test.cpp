#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include "vector.hpp"
#include "stack.hpp"
#include <stack>

#define _vector ft::vector
#define _stack ft::stack
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
int run_stack_unit_test(std::string test_name, std::vector<int> (func1)(std::stack<T>), std::vector<int> (func2)(_stack<T>)) {
    int    result;
    int    leaks;
    time_t t1;
	time_t t2;
	std::vector<int > res1;
	std::vector<int > res2;
	std::stack<int> stack;
	_stack<int> my_stack;

	printElement(test_name);
	res1 = func1(stack);
	res2 = func2(my_stack);
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

	return !(!result && !leaks);;
}


template <class T>
std::vector<int> constructor_test(std::stack<T> stk) {
	std::vector<int> v;
	std::deque<int> deque;
	for (int i = 0; i < 100 * _ratio; ++i)
		deque.push_back(i);
	for (int i = 100 * _ratio; i < 200 * _ratio; ++i)
		stk.push(i);
	g_start1 = timer();
	std::stack<int> stack(deque);
	std::stack<int> stack2(stk);
	std::stack<int> stack3;
	stack3 = stack2;
	g_end1 = timer();
	while (stack.size() > 0) {
		v.push_back(stack.top());
		stack.pop();
	}
	while (stack2.size() > 0) {
		v.push_back(stack2.top());
		stack2.pop();
	}
	return v;
}

template <class T>
std::vector<int> constructor_test(_stack<T> stk) {
	std::vector<int> v;
	_vector<int> deque;
	for (int i = 0; i < 100 * _ratio; ++i)
		deque.push_back(i);
	for (int i = 100 * _ratio; i < 200 * _ratio; ++i)
		stk.push(i);
	g_start2 = timer();
	_stack<int> stack(deque);
	_stack<int> stack2(stk);
	_stack<int> stack3;
	stack3 = stack2;
	g_end2 = timer();
	while (stack.size() > 0) {
		v.push_back(stack.top());
		stack.pop();
	}
	while (stack2.size() > 0) {
		v.push_back(stack2.top());
		stack2.pop();
	}
	return v;
}

int main() {

	exit(run_stack_unit_test<int>("constructor", constructor_test, constructor_test));
}
