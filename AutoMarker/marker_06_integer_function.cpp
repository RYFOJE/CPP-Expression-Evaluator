/*! \file	marker_06_integer_function.cpp
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

constexpr unsigned GROUP_COUNT = 13;
constexpr double GROUP_WEIGHT = 10.0 / GROUP_COUNT;



GATS_TEST_CASE_WEIGHTED(06a_parser_function_1_arg_abs, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_PARENTHESIS && TEST_SINGLE_ARG_FUNCTION
	GATS_CHECK(parse_test(
		// Test: abs(2)
		TokenList({ make<Abs>(), make<LeftParenthesis>(), make<Integer>(2), make<RightParenthesis>() }),
		TokenList({ make<Integer>(2), make<Abs>() })
	));
#endif
}



GATS_TEST_CASE_WEIGHTED(06b_parser_function_2_arg_max, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_PARENTHESIS && TEST_MULTI_ARG_FUNCTION
	GATS_CHECK(parse_test(
		// Test: max(2,4)
		TokenList({ make<Max>(), make<LeftParenthesis>(), make<Integer>(2), make<ArgumentSeparator>(), make<Integer>(4), make<RightParenthesis>() }),
		TokenList({ make<Integer>(2), make<Integer>(4), make<Max>() })
		));
#endif
}



GATS_TEST_CASE_WEIGHTED(06c_parser_function_2_arg_min, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_PARENTHESIS && TEST_MULTI_ARG_FUNCTION
	GATS_CHECK(parse_test(
		// Test: min(2,4)
		TokenList({ make<Min>(), make<LeftParenthesis>(), make<Integer>(2), make<ArgumentSeparator>(), make<Integer>(4), make<RightParenthesis>() }),
		TokenList({ make<Integer>(2), make<Integer>(4), make<Min>() })
		));
#endif
}



GATS_TEST_CASE_WEIGHTED(06d_test_abs_Integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Integer>(4), make<Abs>() });
	GATS_CHECK(value_of<Integer>(result) == 4);
#endif
}



GATS_TEST_CASE_WEIGHTED(06e_test_abs_Integer_neg, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Integer>(-4), make<Abs>() });
	GATS_CHECK(value_of<Integer>(result) == 4);
#endif
}



GATS_TEST_CASE_WEIGHTED(06f_test_max_int_int_rhs, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(2), make<Max>() });
	GATS_CHECK(value_of<Integer>(result) == 2);
#endif
}



GATS_TEST_CASE_WEIGHTED(06g_test_max_int_int_lh, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(1), make<Max>() });
	GATS_CHECK(value_of<Integer>(result) == 2);
#endif
}



GATS_TEST_CASE_WEIGHTED(06h_test_max_int_int_same, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(2), make<Max>() });
	GATS_CHECK(value_of<Integer>(result) == 2);
#endif
}



GATS_TEST_CASE_WEIGHTED(06i_test_min_int_int_rhs, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(2), make<Min>() });
	GATS_CHECK(value_of<Integer>(result) == 1);
#endif
}



GATS_TEST_CASE_WEIGHTED(06j_test_min_int_int_lhs, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(1), make<Min>() });
	GATS_CHECK(value_of<Integer>(result) == 1);
#endif
}



GATS_TEST_CASE_WEIGHTED(06k_test_min_int_int_same, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(2), make<Min>() });
	GATS_CHECK(value_of<Integer>(result) == 2);
#endif
}
GATS_TEST_CASE_WEIGHTED(06l_test_pow_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(3), make<Pow>() });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(8));
#endif
}



GATS_TEST_CASE_WEIGHTED(06m_EE_abs_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_MULTI_ARG_FUNCTION
	auto result = ExpressionEvaluator().evaluate("abs(4)");
	GATS_CHECK(value_of<Integer>(result) == 4);

	result = ExpressionEvaluator().evaluate("abs(-4)");
	GATS_CHECK(value_of<Integer>(result) == 4);
#endif
}

