#include "stdafx.h"
#include <Windows.h>

#include <memory>
#include <iostream>
#include <vector>

struct DataContext
{
	int member1;
	int memebr2;
};

void DoWork(void* context, void* args)
{
	context;
	// (DataContext*)context

	std::cout << std::hex << context << std::endl;

	// https://msdn.microsoft.com/en-us/library/75w45ekt.aspx

	// (int*)args, 10
	std::vector<int> myVector{ 1,2,3,4,5 };
	 
	// myVector, !

	__debugbreak();

}

void eval_test()
{
	std::shared_ptr<DataContext> data(new DataContext());

	int* param = new int[10];

	unsigned vars[10]{ 0,1,2,3,4,5,6,7,8,9 };

	DoWork(reinterpret_cast<void*>(data.get()), param);

	delete[] param;
}