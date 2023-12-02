/*!	\file	ut0_simple_tokens.cpp
	\brief	Token unit test - basic Tokens.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Test the simple tokens:
	Token
	PseudoOperations

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated
	Separated from ut_tokens.cpp

Version 2019.11.05
	C++ 17 cleanup

Version 2017.11.23
	Updated to Visual C++ 15.4.4
	New hierarchy tests.

Version 2014.10.29
	Updated to Visual C++ 12

Version 2012.11.16
	Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

Version 2012.11.15
	Added BinaryInteger, Binary <function>

Version 2012.11.13
	C++ 11 cleanup.

Version 2009.11.30
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

// unit test library
#include <gats/TestApp.hpp>

// Tokenizer system
#include <ee/token.hpp>
#include <ee/pseudo_operation.hpp>

#include <string>
using namespace std;

#include "ut_test_phases.hpp"


// Test the root type of the Token hierarchy.
GATS_TEST_CASE(0a_token_test) {
	auto tkn = make<Token>();
	GATS_CHECK(is<Token>(tkn));
	GATS_CHECK_EQUAL(tkn->str(), "<Token>");
}


// Test the PseudoOperation types
// ==============================
#if TEST_PARENTHESIS
GATS_TEST_CASE(0b_left_parenthesis_token_test) {
	auto tkn = make<LeftParenthesis>();
	GATS_CHECK(is<Token>(tkn));
	GATS_CHECK(is<PseudoOperation>(tkn));
	GATS_CHECK(is<Parenthesis>(tkn));
	GATS_CHECK(is<LeftParenthesis>(tkn));
	GATS_CHECK(!is<RightParenthesis>(tkn));
	GATS_CHECK_EQUAL(tkn->str(), "<LeftParenthesis>");
}
GATS_TEST_CASE(0b_right_parenthesis_token_test) {
	auto tkn = make<RightParenthesis>();
	GATS_CHECK(is<Token>(tkn));
	GATS_CHECK(is<PseudoOperation>(tkn));
	GATS_CHECK(is<Parenthesis>(tkn));
	GATS_CHECK(!is<LeftParenthesis>(tkn));
	GATS_CHECK(is<RightParenthesis>(tkn));
	GATS_CHECK_EQUAL(tkn->str(), "<RightParenthesis>");
}
#endif
#if TEST_FUNCTION && TEST_MULTI_ARG
GATS_TEST_CASE(0c_separator_token_test) {
	auto tkn = make<ArgumentSeparator>();
	GATS_CHECK(is<Token>(tkn));
	GATS_CHECK(is<PseudoOperation>(tkn));
	GATS_CHECK(!is<Parenthesis>(tkn));
	GATS_CHECK(is<ArgumentSeparator>(tkn));
	GATS_CHECK_EQUAL(tkn->str(), "<ArgumentSeparator>");
}
#endif