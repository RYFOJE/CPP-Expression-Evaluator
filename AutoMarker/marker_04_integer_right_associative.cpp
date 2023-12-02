/*! \file	marker_04_integer_right_associative.cpp
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
#include <ee/operator.hpp>
#include <ee/integer.hpp>
#include <ee/RPNEvaluator.hpp>
#include <ee/expression_evaluator.hpp>


constexpr unsigned GROUP_COUNT = 3;
constexpr double GROUP_WEIGHT = 5.0 / GROUP_COUNT;


GATS_TEST_CASE_WEIGHTED(04a_EE_modulo_named_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_BINARY_OPERATOR && TEST_NAMED_OPERATOR
	auto result = ExpressionEvaluator().evaluate("23 mod 3");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));

	result = ExpressionEvaluator().evaluate("15 mod 6 * 3");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("9"));
#endif
}



GATS_TEST_CASE_WEIGHTED(04b_EE_order_integer_right_associative, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_BINARY_OPERATOR && TEST_RIGHT_ASSOCIATIVE_OPERATOR
	auto result = ExpressionEvaluator().evaluate("4**3**2");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("262144"));
#endif
}



GATS_TEST_CASE_WEIGHTED(04c_parser_order_of_operation_right_assoc, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_BINARY_OPERATOR && TEST_RIGHT_ASSOCIATIVE_OPERATOR
	GATS_CHECK(parse_test(
		// Test: 2**3**4
		TokenList({ make<Integer>(2), make<Power>(), make<Integer>(3), make<Power>(), make<Integer>(4) }),
		TokenList({ make<Integer>(2), make<Integer>(3), make<Integer>(4), make<Power>(), make<Power>() })
	));

	GATS_CHECK(parse_test(
		// Test: -2**8
		TokenList({ make<Negation>(), make<Integer>(2), make<Power>(), make<Integer>(8) }),
		TokenList({ make<Integer>(2), make<Integer>(8), make<Power>(), make<Negation>() })
	));
#endif
}

