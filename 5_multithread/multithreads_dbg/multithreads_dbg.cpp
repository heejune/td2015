// lambda-task-lifetime.cpp
// compile with: /EHsc
#include "stdafx.h"

#include <ppl.h>
#include <array>
#include <sstream>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace concurrency;

int fibonacci(int value)
{
	if (value < 2)
		return value;

	return fibonacci(value - 1) + fibonacci(value - 2);
}

void threads()
{
	auto param = []() {
		
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(1, 10);
		
		for (int i = 0; i < 10; ++i)
		{
			auto r = dist(mt);
			std::cout << "thread: " << std::this_thread::get_id() << " running..." << std::endl;
			std::this_thread::sleep_for(3s);
		}

		std::cout << "thread: " << std::this_thread::get_id() << " done..." << std::endl;
	};

	// https://think-async.com/Asio/TipsAndTricks

	auto work_thread_count = 10;
	std::vector<std::thread> threads;
	threads.reserve(work_thread_count);
	for (unsigned int i = 0; i < work_thread_count; ++i) 
	{
		threads.emplace_back([&]() 
		{ 
			for (int i = 0; i < 10; ++i)
			{
				std::cout << "thread: " << std::this_thread::get_id() << " running..." << std::endl;
				std::this_thread::sleep_for(3s);
			}
		});
	}

	std::for_each(threads.begin(), threads.end(),
		[](auto& thread) { thread.join(); });
}

int wmain()
{
	//threads();

	fibonacci(50);

	// Print each value from 1 to 5 in parallel.
	//parallel_for(1, 6, [](int value) {
	//	wstringstream ss;
	//	ss << value << L' ';
	//	wcout << ss.str();
	//});
}