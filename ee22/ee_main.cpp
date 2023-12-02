/*! \file	ee_main.cpp
	\brief	Expression Evaluator application.
	\author	Garth Santor
	\date	2021-11-01
	\copyright	Garth Santor, Trinh Han

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2017.11.23
	Added Python-style power operator '**'

Version 2016.10.29
	Added help command.

Version 2014.11.27
	Added: setp to set the real number precision.

Version 2012.11.13
	C++ 11 cleanup

Version 2010.11.23
	Alpha release.

=============================================================

Copyright Garth Santor / Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor / Trinh Han, Canada.
The program(s) may be used and /or copied only with
the written permission of Garth Santor / Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement / contract under which
the program(s) have been supplied.
============================================================= */

#include <gats/ConsoleApp.hpp>
#include <ee/expression_evaluator.hpp>
#include <ee/function.hpp>
#include <ee/real.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;




MAKEAPP(ee) {
	cout << "Expression Evaluator, (c) 1998-2023 Garth Santor\n";
	for (unsigned count = 0; ; ++count) {
		cout << "> ";
		string command;
		if (!getline(cin, command) || command.empty())
			break;

		cout << "[" << count << "] = " << 42 << endl;
	}

	return EXIT_SUCCESS;
}
