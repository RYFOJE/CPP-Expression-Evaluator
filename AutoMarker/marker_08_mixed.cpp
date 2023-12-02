/*! \file	marker_08_mixed.cpp
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
#include <ee/real.hpp>
#include <ee/operator.hpp>
#include <ee/function.hpp>
#include <ee/pseudo_operation.hpp>
#include "round_real.hpp"

constexpr unsigned GROUP_COUNT = 20;
constexpr double GROUP_WEIGHT = 5.0 / GROUP_COUNT;


GATS_TEST_CASE_WEIGHTED(08a_test_multiply_Integer_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Real>(4.0), make<Multiplication>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("12.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(08b_test_multiply_Real_Integer, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(3.0), make<Integer>(4), make<Multiplication>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("12.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(08c_test_divide_Integer_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Real>(6.0), make<Division>() });
	GATS_CHECK(round(result) == round(Real::value_type("0.5")));
#endif
}
GATS_TEST_CASE_WEIGHTED(08d_test_divide_Real_Integer, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(3.0), make<Integer>(6), make<Division>() });
	GATS_CHECK(round(result) == round(Real::value_type("0.5")));
#endif
}
GATS_TEST_CASE_WEIGHTED(08e_test_addition_Integer_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Real>(Real::value_type("4.2")), make<Addition>() });
	GATS_CHECK(round(result) == round(Real::value_type("7.2")));
#endif
}
GATS_TEST_CASE_WEIGHTED(08f_test_addition_Real_Integer, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3.3")), make<Integer>(4), make<Addition>() });
	GATS_CHECK(round(result) == round(Real::value_type("7.3")));
#endif
}
GATS_TEST_CASE_WEIGHTED(08g_test_subtraction_Integer_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Real>(Real::value_type("0.5")), make<Subtraction>() });
	GATS_CHECK(round(result) == round(Real::value_type("2.5")));
#endif
}
GATS_TEST_CASE_WEIGHTED(08h_test_subtraction_Real_Integer, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("4.25")), make<Integer>(4), make<Subtraction>() });
	GATS_CHECK(round(result) == round(Real::value_type("0.25")));
#endif
}
GATS_TEST_CASE_WEIGHTED(08i_test_neg_power_Integer, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(-4), make<Power>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0") / Real::value_type("16.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(08j_test_power_Integer_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("3.0")), make<Power>() });
	GATS_CHECK(round(result) == round(Real::value_type("8.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(08k_test_power_Real_Integer, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Integer>(3), make<Power>() });
	GATS_CHECK(round(result) == round(Real::value_type("8.0")));
#endif
}



GATS_TEST_CASE_WEIGHTED(08l_test_max_real_int_rhs, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_MULTI_ARG_FUNCTION && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Integer>(2), make<Max>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(08m_test_max_int_real_lhs, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_MULTI_ARG_FUNCTION && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("1.0")), make<Max>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(08n_test_max_int_real_same, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_MULTI_ARG_FUNCTION && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Integer>(2), make<Max>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(08o_test_min_real_int_rhs, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_MULTI_ARG_FUNCTION && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Integer>(2), make<Min>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(08p_test_min_int_real_lhs, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_MULTI_ARG_FUNCTION && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("1.0")), make<Min>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(08q_test_min_int_real_same, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_MULTI_ARG_FUNCTION && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Integer>(2), make<Min>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(08r_test_pow_mixed, GROUP_WEIGHT) {
#if TEST_RPN && TEST_INTEGER && TEST_REAL && TEST_MULTI_ARG_FUNCTION && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("3.0")), make<Pow>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("8.0"));
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Integer>(3), make<Pow>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("8.0"));
#endif
}



GATS_TEST_CASE_WEIGHTED(08s_EE_mixed_addition, GROUP_WEIGHT) {
#if TEST_EE && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = ExpressionEvaluator().evaluate("1+3.3");
	GATS_CHECK(round(result) == round(Real::value_type("4.3")));
#endif
}

GATS_TEST_CASE_WEIGHTED(08t_EE_mixed_division, GROUP_WEIGHT) {
#if TEST_EE && TEST_INTEGER && TEST_REAL && TEST_BINARY_OPERATOR && TEST_MIXED
	auto result = ExpressionEvaluator().evaluate("5/2.0");
	GATS_CHECK(round(result) == round(Real::value_type("2.5")));

	result = ExpressionEvaluator().evaluate("5.0/2");
	GATS_CHECK(round(result) == round(Real::value_type("2.5")));
#endif
}
