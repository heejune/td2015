#include "stdafx.h"
#include <string>

struct MyCustomType
{
	int _value;
	std::string text;
};

void natvisdemo()
{
	MyCustomType type;

	type._value = 123;
	type.text = "hello natvis!";
}

// more info
// http://blogs.msdn.com/b/vcblog/archive/2015/09/28/debug-visualizers-in-visual-c-2015.aspx