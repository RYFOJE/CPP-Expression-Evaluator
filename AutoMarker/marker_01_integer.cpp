/*! \file	marker_01_integer.cpp
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
#include "test_parser.hpp"
#include <ee/integer.hpp>
#include <ee/RPNEvaluator.hpp>
#include <ee/expression_evaluator.hpp>

constexpr unsigned GROUP_COUNT = 5;
constexpr double GROUP_WEIGHT = 5 / GROUP_COUNT;


GATS_TEST_CASE_WEIGHTED(01a_parser_integers, GROUP_WEIGHT) {
#if TEST_INTEGER
	GATS_CHECK(parse_test(
		// Test: 42
		TokenList({ make<Integer>(42) }),
		TokenList({ make<Integer>(42) })));

	GATS_CHECK(parse_test(
		// Test: 0
		TokenList({ make<Integer>(0) }),
		TokenList({ make<Integer>(0) })));

	GATS_CHECK(parse_test(
		// Test: 0
		TokenList({ make<Integer>(Integer::value_type("1234567890123456789012345678901234567890")) }),
		TokenList({ make<Integer>(Integer::value_type("1234567890123456789012345678901234567890")) })
	));

	GATS_CHECK(parse_test(
		TokenList({ make<Integer>(23), make<Integer>(42) }),
		TokenList({ make<Integer>(23), make<Integer>(42) })
		));

	GATS_CHECK(parse_test(
		// Test: -42
		TokenList({ make<Integer>(-42) }),
		TokenList({ make<Integer>(-42) })));
#endif
}



GATS_TEST_CASE_WEIGHTED(01b_parser_too_many_operands, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN
	try {
		TokenList tl = { make<Integer>(3), make<Integer>(4) };
		auto t = RPNEvaluator().evaluate(tl);
		GATS_FAIL("Failed to throw exception");
	}
	catch( std::exception& e ) {
		GATS_CHECK( strcmp( e.what(), "Error: too many operands" ) == 0 );
	}
#endif
}


GATS_TEST_CASE_WEIGHTED(01c_RPN_single_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<Integer>(3) });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(3));

	result = RPNEvaluator().evaluate({ make<Integer>(42) });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(42));

	result = RPNEvaluator().evaluate({ make<Integer>(-42) });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(-42));

	result = RPNEvaluator().evaluate({ make<Integer>(Integer::value_type("1234567890123456789012345678901234567890")) });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("1234567890123456789012345678901234567890"));
#endif
}



GATS_TEST_CASE_WEIGHTED(01d_EE_integer_small, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE
	auto result = ExpressionEvaluator().evaluate("1000");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("1000"));

	result = ExpressionEvaluator().evaluate("42");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("42"));

	result = ExpressionEvaluator().evaluate("0");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("0"));

	result = ExpressionEvaluator().evaluate("-42");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("-42"));
#endif
}



GATS_TEST_CASE_WEIGHTED(01e_EE_integer_large, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE
	auto result = ExpressionEvaluator().evaluate("123456789012345678901234567890123456789012345678901234567890");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("123456789012345678901234567890123456789012345678901234567890"));
#endif
}
