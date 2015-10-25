// DiagToolsDemoCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>

// http://www.gutenberg.org/ebooks/search/?sort_order=downloads

void do_wordcount(std::vector<std::string> files);
void do_wordcount_slow(std::vector<std::string> files);

std::vector<int> get_primes(int max);

void demo_memory_usage();

int main()
{
	// memory usage demo
	demo_memory_usage();

	// cpu usage demo
	//std::vector<std::string> files{ "pg1342.txt", "pg2701.txt", "pg6130.txt" };
	std::vector<std::string> files{ "pg1342.txt" };
	do_wordcount(files);
	do_wordcount_slow(files);

	std::vector<int> primes;
	primes = get_primes(10000);
	std::cout << primes.size();

    return 0;
}

