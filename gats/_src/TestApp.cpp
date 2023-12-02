/*!	\file	TestApp.cpp
	\brief	TestApp framework implementations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=========================================================================
TestApp framework implementations.
	TestApp class declaration.
	TestApp::TestCase class declaration.
	TestApp::TestCase::check_equal template implemenation.
	TestApp::TestCase::check_close_epsilon template implemenation.
	GATS_TEST_CASE()
	GATS_TEST_CASE_WEIGHTED()
	GATS_CHECK()
	GATS_CHECK_MESSAGE()
	GATS_CHECK_EQUAL()
	GATS_CHECK_WITHIN()
	GATS_CHECK_THROW()

=========================================================================
Revision History
-------------------------------------------------------------

Version 2021.10.29
	Added:
		TestApp::current_case()

Version 2021.09.23
	Fixed pass-count in GATS_CHECK_THROW
	Changed stream type from wide to standard.
	Added:
		char_type, ostream_type, ostringstream_type
		GATS_CHECK_MESSAGE
		filename to check failure report.
		GATS_TEST_CASE_WEIGHTED
		Weighted score
	Refactored internal macro names to 'DETAILED_ ...'
	Replaced some CHECK macros internals with methods
	Formatting: placed quotes around case name in output.

Version 2021.08.29
	Alpha release.

=========================================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=========================================================================*/


#include <gats/TestApp.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <filesystem>
#include <string>


namespace gats {
// ----------------------------------------------------------------------------
// TestApp::TestCase
// ----------------------------------------------------------------------------

	/*!	TestCase constructor registers the test case with the TestApp */
	TestApp::TestCase::TestCase(string_type const& name, string_type const& group, double weight) : name_m(name), group_m(group), weight_m(weight) {
		auto& cases = TestApp::cases();
		cases[group_m].push_back(this);
	}



	/*!	Outputs the location of GATS_CHECK_xxx() macro call. */
	void TestApp::TestCase::output_check_location(ostream_type& os, std::filesystem::path file, int line) {
		os << file.filename().string() << " (" << line << "): error in \"" << name_m << "\": ";
	}



	/*! Checks a condition, logging and reporting a failure to achieve that condition. */
	void TestApp::TestCase::check(bool condition, const char_type* const condStr, const char* file, int line) {
		++nChecked_m;
		if (condition == false) {
			ostringstream_type oss;
			output_check_location(oss, file, line);
			oss << condStr << "\n";
			display() << oss.str();
			//log() << oss.str();
		} else
			++nPassed_m;
	}



	/*! Checks a condition, logging and reporting a failure to achieve that condition with a user supplied message. */
	void TestApp::TestCase::check_message(bool condition, const string_type& message, const char* const file, int line) {
		++nChecked_m;
		if (condition == false) {
			ostringstream_type oss;
			output_check_location(oss, file, line);
			oss << message << "\n";
			display() << oss.str();
			//log() << oss.str();
		} else
			++nPassed_m;
	}



// ----------------------------------------------------------------------------
// TestApp
// ----------------------------------------------------------------------------

	//! Classifier instances for TestApp
	TestApp::case_groups_pointer_type	TestApp::casesPtr_sm;
	TestApp::ofstream_type				TestApp::logFile_m;
	TestApp::case_pointer_type			TestApp::currentCasePtr_sm = nullptr;
	TestApp::string_type const			TestApp::TestCase::defaultGroup_csm{};


	//! Global TestConsoleApp instance <<singleton>>
	TestApp testConsoleApp_g;



	/*!	Returns a reference to the cases container. */
	TestApp::case_groups_type& TestApp::cases() {
		if (!casesPtr_sm)
			casesPtr_sm.reset(new case_groups_type);
		return *casesPtr_sm;
	}



	/*!	Get a reference to the cases container. */
	TestApp::case_pointer_type TestApp::current_case(const char* file, int line) {
		using namespace std;
		if (currentCasePtr_sm == nullptr) {
			throw std::runtime_error("Check invoked without enclosing test case: "s + file + "(" + to_string(line) + ")");
		}
		return currentCasePtr_sm;
	}


	/*!	'setup' overrides the application method to register a logfile for storing test results. */
	void TestApp::setup() {
		using namespace std;
		std::filesystem::path filename = "gats-test-log-file.txt";
		logFile_m.open(filename);
		if (!logFile_m) {
			throw std::runtime_error("Could not open: "s + filename.string());
		}
	}

} // end-of-namespace gats