/*! \file	marker_03_integer_binary.cpp
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

constexpr unsigned GROUP_COUNT = 16;
constexpr double GROUP_WEIGHT = 20.0 / GROUP_COUNT;


GATS_TEST_CASE_WEIGHTED(03a_parser_binary_addition, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_BINARY_OPERATOR
	GATS_CHECK(parse_test(
		// Test: 4+2
		TokenList({ make<Integer>(4), make<Addition>(), make<Integer>(2) }),
		TokenList({ make<Integer>(4), make<Integer>(2), make<Addition>() })
	));
#endif
}

GATS_TEST_CASE_WEIGHTED(03b_parser_order_of_operation_a_m, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_BINARY_OPERATOR
	GATS_CHECK(parse_test(
		// Test: 4+2*3
		TokenList({ make<Integer>(4), make<Addition>(), make<Integer>(2), make<Multiplication>(), make<Integer>(3) }),
		TokenList({ make<Integer>(4), make<Integer>(2), make<Integer>(3), make<Multiplication>(), make<Addition>() })
	));
#endif
}



GATS_TEST_CASE_WEIGHTED(03c_parser_order_of_operation_m_a, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_PARSER && TEST_BINARY_OPERATOR
	GATS_CHECK(parse_test(
		// Test: 4*2+3
		TokenList({ make<Integer>(4), make<Multiplication>(), make<Integer>(2), make<Addition>(), make<Integer>(3) }),
		TokenList({ make<Integer>(4), make<Integer>(2), make<Multiplication>(), make<Integer>(3), make<Addition>() })
	));
#endif
}



GATS_TEST_CASE_WEIGHTED(03d_test_multiply_Integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Integer>(4), make<Multiplication>() });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(12));
#endif
}



GATS_TEST_CASE_WEIGHTED(03e_test_divide_Integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Integer>(45), make<Integer>(3), make<Division>() });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(15));
#endif
}



GATS_TEST_CASE_WEIGHTED(03f_test_addition_Integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Integer>(4), make<Addition>() });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(7));
#endif
}



GATS_TEST_CASE_WEIGHTED(03g_test_subtraction_Integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Integer>(4), make<Subtraction>() });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(-1));
#endif
}



GATS_TEST_CASE_WEIGHTED(03h_test_modulus_Integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Integer>(12), make<Integer>(5), make<Modulus>() });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(2));
#endif
}



GATS_TEST_CASE_WEIGHTED(03i_test_power_Integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Integer>(4), make<Power>() });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type(81));

	result = RPNEvaluator().evaluate({ make<Integer>(7), make<Integer>(2), make<Power>(), make<Negation>() });
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("-49"));
#endif
}



GATS_TEST_CASE_WEIGHTED(03j_EE_addition_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_RPN && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("2+3");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("5"));
#endif
}



GATS_TEST_CASE_WEIGHTED(03k_EE_subtraction_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("2-3");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("-1"));
#endif
}



GATS_TEST_CASE_WEIGHTED(03l_EE_multiplication_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("2*3");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("6"));
#endif
}



GATS_TEST_CASE_WEIGHTED(03m_EE_division_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("21/3");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("7"));
	result = ExpressionEvaluator().evaluate("23/3");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("7"));
#endif
}



GATS_TEST_CASE_WEIGHTED(03n_EE_modulo_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("21%3");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("0"));
	result = ExpressionEvaluator().evaluate("23%3");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
#endif
}



GATS_TEST_CASE_WEIGHTED(03o_EE_power_operator_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("5**2");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("25"));

	result = ExpressionEvaluator().evaluate("123**123");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("114374367934617190099880295228066276746218078451850229775887975052369504785666896446606568365201542169649974727730628842345343196581134895919942820874449837212099476648958359023796078549041949007807220625356526926729664064846685758382803707100766740220839267"));

	result = ExpressionEvaluator().evaluate("-7**2");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("-49"));
#endif
}



GATS_TEST_CASE_WEIGHTED(03p_EE_order_integer, GROUP_WEIGHT) {
#if TEST_INTEGER && TEST_EE && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("2*3+4");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("10"));
	result = ExpressionEvaluator().evaluate("21/3-5");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
	result = ExpressionEvaluator().evaluate("2+3*4");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("14"));
	result = ExpressionEvaluator().evaluate("2-32/4");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("-6"));

	result = ExpressionEvaluator().evaluate("4!!");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("620448401733239439360000"));
	result = ExpressionEvaluator().evaluate("2*4!-4");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("44"));

	result = ExpressionEvaluator().evaluate("20*3-32/4");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("52"));
	result = ExpressionEvaluator().evaluate("(21+5)/(7+6)");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
	result = ExpressionEvaluator().evaluate("(5+6*7)*(4+3)/(1+(5+6*7))");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("6"));
	result = ExpressionEvaluator().evaluate("(4 + 2 * 5) / (1 + 3 * 2)");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
#endif
}
