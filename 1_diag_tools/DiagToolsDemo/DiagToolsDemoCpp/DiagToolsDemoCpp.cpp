// DiagToolsDemoCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>

// http://www.gutenberg.org/ebooks/search/?sort_order=downloads

void do_wordcount(std::vector<std::string> files);
void do_wordcount_slow(std::vector<std::string> files, bool show);

std::vector<int> get_primes(int max);

void demo_memory_usage();

int main()
{
	// cpu usage demo
	//std::vector<std::string> files{ "pg1342.txt", "pg2701.txt", "pg6130.txt" };
	std::vector<std::string> files{ "pg1342.txt" };
	do_wordcount(files);
	do_wordcount_slow(files, false);

	std::vector<int> primes;
	primes = get_primes(100000);
	std::cout << primes.size();

	// memory usage demo
	//demo_memory_usage();

	return 0;
}

