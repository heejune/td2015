
#include "stdafx.h"
#include <Windows.h>

void show_vars()
{
	SetLastError(ERROR_ACCESS_DENIED);

	// $err
	// $err, hr		<== format specifiers...
	// more format specifiers
	// https://msdn.microsoft.com/en-us/library/75w45ekt.aspx

	SetLastError(ERROR_SUCCESS);

	// $env 
	// $cmdline

}