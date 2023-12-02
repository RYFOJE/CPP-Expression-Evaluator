/*!	\file	UI_Prototype_main.cpp
	\brief	Demonstrates the 'ee' user interface.
	\author	Garth Santor
	\date	2022-11-06
	\copyright	Garth Santor, Trinh Han

=============================================================

A mock-up of the user interface of the 'ee' application.

=============================================================
Revision History
-------------------------------------------------------------

Version 2022.11.06
	Visual Studio 2022 validated

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 validated

Version 2016.10.29
	C++ 11 validated

Version 2014.10.29
	Updated copyright.

Version 2012.11.13
	Updated copyright.

Version 2009.11.26
	Alpha release.


=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/

#include <iostream>
#include <string>
using namespace std;

int main() {
	cout << "Expression Evaluator, (c) 1998-2022 Garth Santor\n";
	for (unsigned count = 0; ; ++count) {
		cout << "> ";
		string command;
		if (!getline(cin, command) || command.empty())
			break;

		cout << "[" << count << "] = " << 42 << endl;
	}
}
