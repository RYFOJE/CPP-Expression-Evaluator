/*! \file	marker_02_integer_unary.cpp
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


constexpr unsigned GROUP_COUNT = 6;
constexpr double GROUP_WEIGHT = 10.0 / GROUP_COUNT;



GATS_TEST_CASE_WEIGHTED(02a_parser_unary_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_UNARY_OPERATOR
	GATS_CHECK(parse_test(
		// Test: -42
		TokenList({ make<Negation>(), make<Integer>(42) }),
		TokenList({ make<Integer>(42), make<Negation>() })));

	GATS_CHECK(parse_test(
		// Test: - - 42
		TokenList({ make<Negation>(), make<Negation>(), make<Integer>(42) }),
		TokenList({ make<Integer>(42), make<Negation>(), make<Negation>() })));

	GATS_CHECK(parse_test(
		// Test: + + 42
		TokenList({ make<Identity>(), make<Identity>(), make<Integer>(42) }),
		TokenList({ make<Integer>(42), make<Identity>(), make<Identity>() })));

	GATS_CHECK(parse_test(
		// Test: 42!
		TokenList({ make<Integer>(42), make<Factorial>() }),
		TokenList({ make<Integer>(42), make<Factorial>() })
	));
#endif
}



GATS_TEST_CASE_WEIGHTED(02b_integer_rpn_identity, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_UNARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Identity>() });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(3));
#endif
}



GATS_TEST_CASE_WEIGHTED(02c_integer_rpn_factorial, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_UNARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Integer>(5), make<Factorial>() });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(120));
#endif
}



GATS_TEST_CASE_WEIGHTED(02d_EE_identity_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_UNARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("+42");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("42"));
#endif
}



GATS_TEST_CASE_WEIGHTED(02e_EE_negation_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_UNARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("-42");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("-42"));
#endif
}



GATS_TEST_CASE_WEIGHTED(02f_EE_factorial, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_UNARY_OPERATOR && TEST_POSTFIX_OPERATOR
	auto result = ExpressionEvaluator().evaluate("5!");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("120"));
	result = ExpressionEvaluator().evaluate("100!");
	GATS_CHECK(value_of<Integer>(result) ==
		Integer::value_type("93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000"));
#endif
}
