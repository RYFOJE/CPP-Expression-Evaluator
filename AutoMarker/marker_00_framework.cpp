/*! \file	marker_00_framework.cpp
	\brief	Expression Evaluator marking application.
	\author	Garth Santor
	\date	2021-11-07
	\copyright	Garth Santor

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.07
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

#include <gats/TestApp.hpp>
#include "ut_test_phases.hpp"
#include <ee/parser.hpp>
#include <ee/RPNEvaluator.hpp>
#include <ee/expression_evaluator.hpp>



GATS_TEST_CASE_WEIGHTED(00a_parser_empty, 1.25) {
#if TEST_PARSER
	TokenList infixTokenList, postfixTokenList;
	TokenList result = Parser().parse( infixTokenList );
	GATS_CHECK(result.size() == postfixTokenList.size());
#endif
}



GATS_TEST_CASE_WEIGHTED(00b_rpn_evaluator_empty, 1.25) {
#if TEST_RPN
	try {
		auto t = RPNEvaluator().evaluate(TokenList());
		GATS_FAIL("Failed to throw exception");
	}
	catch( std::exception& e ) {
		GATS_CHECK( strcmp( e.what(), "Error: insufficient operands" ) == 0 );
	}
#endif
}



GATS_TEST_CASE_WEIGHTED(00c_expression_evaluator_unknown_token, 1.25) {
#if TEST_EE
	try {
		ExpressionEvaluator::result_type result = ExpressionEvaluator().evaluate("@");
		GATS_FAIL("Failed to throw exception");
	} catch (Tokenizer::XBadCharacter& e) {
		std::string s("Tokenizer::Bad character in expression.");
		std::string es(e.what());
		GATS_CHECK(s == es);
		GATS_CHECK(e.expression() == "@");
		GATS_CHECK(e.location() == 0);
	} catch (...) {
		GATS_FAIL("Didn't catch Tokenizer::BadCharacter");
	}
#endif
}



GATS_TEST_CASE_WEIGHTED(00d_expression_evaluator_empty_expression, 1.25) {
#if TEST_EE
	try {
		ExpressionEvaluator::result_type result = ExpressionEvaluator().evaluate("");
		GATS_FAIL("Failed to throw exception");
	} catch (std::exception& e) {
		GATS_CHECK(strcmp(e.what(), "Error: insufficient operands") == 0);
	} catch (...) {
		GATS_FAIL("Caught wrong exception");
	}
#endif
}