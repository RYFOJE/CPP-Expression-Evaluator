#pragma once
/*!	\file	gats/ConsoleApp.hpp
	\brief	ConsoleApp framework declarations.
	\author	Garth Santor
	\date	2021-10-30
	\copyright	Garth Santor, Trinh Han

=============================================================
ConsoleApp class declaration.
	#define GATS_WIDE_CONSOLE_APP for wmain+wstring+wchar_t.
	defaults to main+string+char

	gats::ConsoleApp
	MAKEAPP()

=============================================================
Revision History
-------------------------------------------------------------
Version 2021.10.30
	C++ 20 Version
	Moved to namespace gats
	Moved to <gats/ConsoleApp.hpp>
	Added option for main+char vs. wmain+wchar_t
	Made Windows-specific extensions Windows-only


Version 2021.08.24
	C++ 17 Version
	Moved to namespace gats::win32

Version 2019.01.05
	C++ 11 Version

Version 2017.02.25
	Alpha release.

=============================================================
Copyright 2017-21, Garth Santor & Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/


#if defined(_WIN32)
#include <gats/win32/debug.hpp>
#include <gats/win32/ConsoleEnhanced.hpp>
#endif
#include <string>
#include <vector>


namespace gats {

	/*!	ConsoleApp is the base-class of the framework.
	*/
	class ConsoleApp {
	// TYPES
	public:
#if defined(GATS_WIDE_CONSOLE_APP)
		using char_type = wchar_t;
		using string_type = std::wstring;
#else
		using char_type = char;
		using string_type = std::string;
#endif
	private:
		using Args = std::vector<string_type>;

	// ATTRIBUTES
	private:
		static ConsoleApp*	thisApp_sm;
		Args				args_m;

		bool wrapupCalled_m = false;
		bool autoRestoreWindowStateOnExit_m = false;
	protected:

#if defined(_WIN32)
		gats::win32::ConsoleEnhanced::State	initialState_m;
		gats::win32::ConsoleEnhanced console;
#endif

	// OPERATIONS
	protected:
		ConsoleApp(bool autoRestoreWindowStateOnExit = false);
		virtual ~ConsoleApp();

		[[noreturn]] virtual void setup() {}
		[[nodiscard]] virtual int execute();
		[[noreturn]] virtual void wrapup() {}

		/*!	Access the command-line arguments container.
		*/
		[[nodiscard]] Args const& get_args() const { return args_m; }
	public:
		[[nodiscard]] static int main(int argc, char_type* argv[]);
	};


} // end-of-namespace gats


#define MAKEAPP(name)\
	class name : public gats::ConsoleApp {\
		int execute() override;\
} name##_g;\
int name ::execute()


#pragma endregion
