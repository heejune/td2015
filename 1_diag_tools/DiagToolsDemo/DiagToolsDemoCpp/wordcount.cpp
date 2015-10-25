// Example from the following link:
// http://www.artima.com/samples/cpp11NotesSample.pdf

#include "stdafx.h"

#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map> 
#include <future>

using WordCountMapType = std::unordered_map < std::string, std::size_t >;  // << === using, unordered_map

WordCountMapType wordsInFile(const char * const fileName)
{
	std::ifstream file(fileName);
	WordCountMapType wordCounts;
	for (std::string word; file >> word;) {
		++wordCounts[word];
	}

	return wordCounts;
}

template<typename MapIt>
void showCommonWords(MapIt begin, MapIt end, const std::size_t n)
{
	std::vector<MapIt> wordIters;
	wordIters.reserve(std::distance(begin, end));

	for (auto i = begin; i != end; ++i) wordIters.push_back(i);

	auto sortedRangeEnd = wordIters.begin() + n;

	std::partial_sort(wordIters.begin(), sortedRangeEnd, wordIters.end(),
		[](MapIt it1, MapIt it2)
	{ return it1->second > it2->second; });

	for (auto it = wordIters.cbegin();
	it != sortedRangeEnd;
		++it) {
		std::printf(" %-10s%10Iu\n", (*it)->first.c_str(),
			(*it)->second);	// %-10s%10zu
	}
}

void do_wordcount(std::vector<std::string> files)
{
	std::vector<std::future<WordCountMapType>> futures;

	//for (int argNum = 1; argNum < argc; ++argNum) {
	//	futures.push_back(
	//		std::async([=] { return wordsInFile(argv[argNum]); })
	//		);
	//}

	std::for_each(std::begin(files), std::end(files), [&](const std::string& e) {
		futures.push_back(
			std::async([=] { return wordsInFile(e.c_str()); })
			);
	});

	WordCountMapType wordCounts;

	for (auto& f : futures) {
		const auto wordCountInfoForFile = f.get();				// move map returned by wordInFile

		for (const auto& wordInfo : wordCountInfoForFile) {
			wordCounts[wordInfo.first] += wordInfo.second;
		}
	}

	std::cout << wordCounts.size() << " words found. Most common:\n";

	const std::size_t maxWordsToShow = 20;
	showCommonWords(wordCounts.begin(), wordCounts.end(),
		std::min(wordCounts.size(),
			maxWordsToShow));
}

// STL's approach: http://blogs.msdn.com/b/vcblog/archive/2013/01/18/jumping-into-c.aspx?PageIndex=1#comments
//http://sdrv.ms/UCieo5
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <regex>

void do_wordcount_slow(std::vector<std::string> files)
{
	const std::regex word_regex("\\w+");

	std::map<std::string, unsigned long long> word_freq;

	//for (int argi = 1; argi < argc; ++argi) {
	std::for_each(std::begin(files), std::end(files), [&](const std::string& e) {
		std::ifstream file(e);

		if (!file) {
			std::cerr << "ERROR: Couldn't open \"" << e << "\"." << std::endl;
			return;
		}

		for (std::string line; std::getline(file, line);) {
			for (std::sregex_token_iterator i(line.begin(), line.end(), word_regex), end; i != end; ++i) {
				++word_freq[*i];
			}
		}
	});

	std::cout << word_freq.size() << " unique words." << std::endl;

	for (const auto& p : word_freq) {
		std::cout << p.first << ": " << p.second << std::endl;
	}
}