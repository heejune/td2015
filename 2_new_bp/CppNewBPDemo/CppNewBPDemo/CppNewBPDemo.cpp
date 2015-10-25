// CppNewBPDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// sample originally from
// http://blogs.msdn.com/b/visualstudioalm/archive/2013/10/14/data-breakpoints.aspx
// http://blogs.msdn.com/cfs-file.ashx/__key/communityserver-components-postattachments/00-10-45-52-78/NativeBreakpointsSample.zip

#include "Object1.h"
#include "Object2.h"

void CleanUp(CObject1* pInObj1)
{
	pInObj1->AddRef();
	pInObj1->m_myint = 5;
}

void PrintObject(CObject1* pInObj1, CObject2* pInObj2)
{
	CObject1* pObj1 = pInObj1;
	CleanUp(pObj1);

	int result = pObj1->GetMyInt() + pInObj2->GetMyInt();
	std::cout << "Result = " << result << std::endl;
}

int main()
{
	CComPtr<CObject1> pObj1;
	pObj1.Attach(new CObject1(10));

	CComPtr<CObject2> pObj2 = new CObject2(22);
	pObj2.Attach(new CObject2(22));

	PrintObject(pObj1, pObj2);

	std::cout << "Test is done" << std::endl;
	
	return 0;
}

