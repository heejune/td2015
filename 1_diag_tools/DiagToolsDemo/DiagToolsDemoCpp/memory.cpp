
#include "stdafx.h"

#include <string>
#include <map>
#include <vector>
#include <iostream>

struct UserContext
{
	unsigned long id;
};

#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include <algorithm>

// http://stackoverflow.com/questions/19515557/fast-generate-a-large-set-of-random-strings-from-number-and-alphabet
void make_random(
	std::vector<std::string>& strs, 
	const size_t N_STRS,	// # of string
	const size_t S_LEN)		// # of char for each string
{
	static const char alphabet[] =
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789";

	std::random_device rd;
	std::default_random_engine rng(rd());
	std::uniform_int_distribution<> dist(0, sizeof(alphabet) / sizeof(*alphabet) - 2);

	strs.reserve(N_STRS);

	// insert strings into vector
	std::generate_n(
		std::back_inserter(strs), strs.capacity(),
		[&] { 
				// make random string
				std::string str;
				str.reserve(S_LEN);
				std::generate_n(std::back_inserter(str), S_LEN,
				[&]() { return alphabet[dist(rng)]; });
				return str; 
	});
	
	// for output
	//std::copy(strs.begin(), strs.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

void internal_function()
{
	UserContext* ContextArrays = new UserContext[100];

	// make leak
	//delete[] ContextArrays;
}

void leak_demo()
{
	for (int i = 0; i < 100; i++)
	{
		internal_function();
	}
}

void demo_memory_usage()
{
	// structure
	std::wcout << L"Size of UserContext=" << sizeof(UserContext);

	UserContext* ContextArrays = new UserContext[100];

	__debugbreak();

	//delete[] ContextArrays;

	std::vector<std::string> strings;
	make_random(strings, 1000, 30);

	__debugbreak();

	leak_demo();
	
	__debugbreak();
}