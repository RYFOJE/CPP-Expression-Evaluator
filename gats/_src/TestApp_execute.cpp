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
#include <chrono>
using namespace std;
using namespace std::chrono;
using namespace gats::win32;



namespace gats {
	/*!	'execute' overrides the application interface method to perform all test cases and log/report the results. */
	int TestApp::execute() {

		// pass/fail color code function
		auto setcolor = [=](auto passed, auto checked) {
			if (checked == 0)
				cout << bright(red);
			else {
				auto ratio = passed * 100 / checked;
				if (passed == checked && checked != 0)
					cout << bright(green);
				else if (ratio >= 80)
					cout << bright(yellow);
				else if (ratio >= 50)
					cout << yellow;
				else
					cout << bright(red);
			}
		};



		// restore console attributes on exit
		ScopedAttributeState sas;



		// sort the cases
		for (auto& testCaseGroup : cases()) {
			auto& testCases = testCaseGroup.second;
			sort(begin(testCases), end(testCases), [](case_pointer_type pLHS, case_pointer_type pRHS) { return *pLHS < *pRHS; });
		}



		// Initialize counts
		std::uintmax_t nCasesPassed{}, nChecked_m{}, nChecksPassed{}, nMaxChecked{};
		double score{}, maxScore{};



		// Run the cases
		for (auto& testCaseGroup : cases()) {
			for (auto& testCase : testCaseGroup.second) {
				cout << bright(yellow);
				currentCasePtr_sm = testCase;
				bool ranWithoutException = false;
				string exceptionMessage;
				auto start = high_resolution_clock::now();
				try {
					testCase->execute();
					ranWithoutException = true;

					nMaxChecked = std::max(nMaxChecked, testCase->nChecked_m);
				}
				catch (...) {
					exceptionMessage = "Unknown exception caught.";
				};
				auto stop = high_resolution_clock::now();
				auto elapsedTime = stop - start;
				testCase->elapsedTime_m = elapsedTime;

				// report exception trapped
				if (!ranWithoutException) {
					cout << testCase->name_m << ": ";
					cout << exceptionMessage << endl;
				}

				currentCasePtr_sm = nullptr;
				cout << white;
			}
		}
		auto nMaxCheckedDigits = (std::streamsize)floor(log10(nMaxChecked)) + 1;


		// Report the groups
		// ------------------------------------------------------
		for (auto& testCaseGroup : cases()) {

			// Group title
			cout << (bright(white) + background(blue));
			cout << "Group: " << (testCaseGroup.first.empty() ? "(ungrouped)" : testCaseGroup.first);
			cout << white << '\n';

			// Report the cases
			// --------------------------------------------------
			for (auto& testCase : testCaseGroup.second) {

				// Check for empty case
				bool passed = testCase->nPassed_m == testCase->nChecked_m && testCase->nChecked_m > 0;

				// report pass/fail
				double ratio = double(testCase->nPassed_m) / testCase->nChecked_m;
				if (testCase->nChecked_m == 0) ratio = 0.0;
				double percentage = ratio * 100.0;

				auto setColorLevel = [=]() {
					if (passed)
						cout << bright(green);
					else if (ratio >= 0.8)
						cout << bright(yellow);
					else if (ratio >= 0.5)
						cout << yellow;
					else
						cout << bright(red);
				};


				// time format
				auto timeCount = testCase->elapsedTime_m.count();
				string_type timeUnit = "ns";
				if (timeCount >= 1'000) {
					timeCount /= 1'000;
					timeUnit = "us";
				}
				if (timeCount >= 1'000) {
					timeCount /= 1'000;
					timeUnit = "ms";
				}
				if (timeCount >= 1'000) {
					timeCount /= 1'000;
					timeUnit = "s ";
				}


				setColorLevel();
				cout << (passed ? "Passed " : "Failed ");
				cout << setw(5) << setprecision(1) << fixed << percentage << "% ";

				cout << white;
				cout << "x" << testCase->weight_m << "=";
				setColorLevel();
				cout << std::setw(5) << std::setprecision(1) << std::fixed << ratio * testCase->weight_m;

				cout << white;
				cout << " (" << setw(nMaxCheckedDigits) << testCase->nPassed_m << "/" << setw(nMaxCheckedDigits) << testCase->nChecked_m << ")";

				cout << " " << setw(3) << right << timeCount << ' ' << timeUnit;
				cout << cyan;
				cout << " " << testCase->name_m;
				cout << endl;

				// log file record
				logFile_m << std::setw(5) << std::setprecision(1) << std::fixed << ratio * testCase->weight_m;
				logFile_m << "\t" << testCase->weight_m;
				logFile_m << "\t" << testCase->name_m;
				logFile_m << std::endl;

				// enumerate cases
				nCasesPassed += passed;
				nChecked_m += testCase->nChecked_m;
				nChecksPassed += testCase->nPassed_m;
				score += ratio * testCase->weight_m;
				maxScore += testCase->weight_m;
			}
		}



		// report summary
		double checkPercentage{ 100.0 * nChecksPassed / nChecked_m };

		setcolor(nChecksPassed, nChecked_m);
		std::ostringstream oss;
		oss << "\n" <<
			std::setprecision(1) << std::fixed <<
			nChecksPassed << "/" << nChecked_m << " checks passed (" << (nChecked_m ? checkPercentage : 0.0) << "%)\n";
		std::cout << oss.str();

		oss.str(""); oss.clear();

		size_t nTotalCases{};
		std::for_each(cases().cbegin(), cases().cend(), [&nTotalCases](auto& e) { nTotalCases += e.second.size(); });

		setcolor(nCasesPassed, nTotalCases);
		oss <<
			nCasesPassed << "/" << nTotalCases << " cases (" <<
			std::setprecision(1) << std::fixed << 
			(nTotalCases ? 100.0 * nCasesPassed / nTotalCases : 0.0) << "%)\n";
		std::cout << oss.str();

		oss.str("");  oss.clear();
		
		setcolor(score, maxScore);
		oss << "\nScore = " << score << " of " << maxScore << " (" << 
			std::setprecision(1) << std::fixed << 
			(maxScore > 0.0 ? score*100/maxScore : 0.0) << 
			"%)";
		std::cout << oss.str() << std::endl;
		logFile_m << oss.str() << std::endl;

		return EXIT_SUCCESS;
	}

} // end-of-namespace gats