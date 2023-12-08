/*	\file		XError.cpp
	\author		Garth Santor
	\copyright	Garth Santor, Trinh Han
	\date		2021-08-25
	\brief		Win32 Error system implementations.

=========================================================================
XError class implementation.

Implements:
	XError
	ErrorDesciption()

=========================================================================
Revision History
-------------------------------------------------------------

Version 2021.08.25
	C++ 17 version.

Version 2019.01.19
	Production version.

Version 2015.01.01
	Alpha release.

=========================================================================

Copyright 2015-21, Garth Santor & Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=========================================================================*/


#include <gats/win32/XError.hpp>
#include <sstream>



namespace gats::win32 {


	/* ErrorDescription creates a formatted standard string from a Win32 error code. */
	std::wstring ErrorDescription(DWORD dwMessageID) {
		LPWSTR msg;
		auto c = FormatMessageW(
			/* flags */			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
			/* source*/			NULL,
			/* message ID */	dwMessageID,
			/* language */		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			/* buffer */		(LPWSTR)&msg,
			/* size */			0,
			/* args */			NULL
		);

		std::wstring strMsg = (c == 0)
			? L"unknown"
			: msg;
		LocalFree(msg);
		return strMsg;
	}



	/* XError constructor. */
	XError::XError(int line, file_type file) : code_(GetLastError()), line_(line), file_(file) {}



	/* Gets the full error message for the contained code. */
	XError::string_type XError::message() const {
		std::wostringstream oss;
		oss << "Error: " << code() << '\n';
		oss << ErrorDescription(code()) << '\n';
		oss << "In: " << file() << '\n';
		oss << "Line: " << line() << '\n';
		return oss.str();
	}

} // End-of-namespace gats::win32