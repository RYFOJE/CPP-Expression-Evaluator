/*! \file	marker_05_integer_parenthesis.cpp
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
#include <ee/RPNEvaluator.hpp>
#include <ee/expression_evaluator.hpp>
#include <ee/pseudo_operation.hpp>
#include <ee/integer.hpp>
#include <ee/operator.hpp>

constexpr unsigned GROUP_COUNT = 6;
constexpr double GROUP_WEIGHT = 5.0 / GROUP_COUNT;


GATS_TEST_CASE_WEIGHTED(05a_parser_single_parenthesis, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_PARENTHESIS
	GATS_CHECK(parse_test(
		// Test: (2)
		TokenList({ make<LeftParenthesis>(), make<Integer>(2), make<RightParenthesis>() }),
		TokenList({ make<Integer>(2) })
	));
#endif
}



GATS_TEST_CASE_WEIGHTED(05b_parser_double_parenthesis, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_PARENTHESIS
	GATS_CHECK(parse_test(
		// Test: ((2))
		TokenList({ make<LeftParenthesis>(), make<LeftParenthesis>(), make<Integer>(2), make<RightParenthesis>(), make<RightParenthesis>() }),
		TokenList({ make<Integer>(2) })
	));
#endif
}



GATS_TEST_CASE_WEIGHTED(05c_parser_multi_parenthesis, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_PARENTHESIS && TEST_BINARY_OPERATOR
	GATS_CHECK(parse_test(
		// Test: (3+4)*5
		TokenList({ make<LeftParenthesis>(), make<Integer>(3), make<Addition>(), make<Integer>(4), make<RightParenthesis>(), make<Multiplication>(), make<Integer>(5) }),
		TokenList({ make<Integer>(3), make<Integer>(4), make<Addition>(), make<Integer>(5), make<Multiplication>() })
	));
#endif
}



GATS_TEST_CASE_WEIGHTED(05d_evaluator_single_parenthesis, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_PARENTHESIS
	auto result = ExpressionEvaluator().evaluate("(2)");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(2));
#endif
}



GATS_TEST_CASE_WEIGHTED(05e_evaluator_double_parenthesis, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_PARENTHESIS
	auto result = ExpressionEvaluator().evaluate("((2))");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(2));
#endif
}



GATS_TEST_CASE_WEIGHTED(05f_evaluator_multi_parenthesis, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_PARENTHESIS && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("(3+4)*5");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(35));

	result = ExpressionEvaluator().evaluate("((1+2)*3)-4*(2-3)");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(13));

	result = ExpressionEvaluator().evaluate("(2**3)**4");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(4096));
#endif
}
