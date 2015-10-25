

#include "stdafx.h"
#include <Windows.h>
#include <stdexcept>
#include <strsafe.h>

#include <iostream>

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms680582(v=vs.85).aspx
struct MyException
{
	MyException()
		:err(GetLastError())
	{
		// Retrieve the system error message for the last-error code

		LPVOID lpMsgBuf;

		auto size = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		if (size)
		{
			errstr = std::wstring((wchar_t*)lpMsgBuf, size);

			LocalFree(lpMsgBuf);
		}
	}

	DWORD err;
	std::wstring errstr;
};

void make_exception()
{
	try
	{
		SetLastError(ERROR_ACCESS_DENIED);
		throw MyException();
	}
	catch (std::exception & e)
	{
		// swallow
	}
	catch (MyException & me)
	{
		// swallow
		std::wcout << L"Exeption reason: " << me.errstr.c_str() << std::endl;
	}
}