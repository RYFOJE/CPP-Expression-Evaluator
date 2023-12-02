/*! \file	marker_07_real.cpp
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

constexpr unsigned GROUP_COUNT = 60;
constexpr double GROUP_WEIGHT = 10.0 / GROUP_COUNT;



GATS_TEST_CASE_WEIGHTED(07aa_Real_3_14, GROUP_WEIGHT){
#if TEST_RPN && TEST_REAL
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3.14")) });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("3.14"));
#endif
}



GATS_TEST_CASE_WEIGHTED(07ab_constant_Pi, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL
	auto result = RPNEvaluator().evaluate({ make<Pi>() });
	GATS_CHECK(value_of<Real>(result) == boost::math::constants::pi<Real::value_type>());
#endif
}



GATS_TEST_CASE_WEIGHTED(07ac_constant_E, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL
	auto result = RPNEvaluator().evaluate({ make<E>() });
	GATS_CHECK(value_of<Real>(result) == boost::math::constants::e<Real::value_type>());
#endif
}



GATS_TEST_CASE_WEIGHTED(07ad_negation_test_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_UNARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(3), make<Negation>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("-3.0"));
#endif
}



GATS_TEST_CASE_WEIGHTED(07ae_parser_function_1_arg_sin, GROUP_WEIGHT) {
#if TEST_PARSER && TEST_REAL && TEST_SINGLE_ARG_FUNCTION && TEST_PARENTHESIS
	GATS_CHECK(parse_test(
		// Test: sin(2.0)
		TokenList({ make<Sin>(), make<LeftParenthesis>(), make<Real>(2.0), make<RightParenthesis>() }),
		TokenList({ make<Real>(2.0), make<Sin>() })
		));
#endif
}

GATS_TEST_CASE_WEIGHTED(07af_parser_function_1_arg_cos, GROUP_WEIGHT) {
#if TEST_PARSER && TEST_REAL && TEST_SINGLE_ARG_FUNCTION && TEST_PARENTHESIS
	GATS_CHECK(parse_test(
		// Test: cos(2.0)
		TokenList({ make<Cos>(), make<LeftParenthesis>(), make<Real>(2.0), make<RightParenthesis>() }),
		TokenList({ make<Real>(2.0), make<Cos>() })
		));
#endif
}



GATS_TEST_CASE_WEIGHTED(07ag_parser_function_1_arg_tan, GROUP_WEIGHT) {
#if TEST_PARSER && TEST_REAL && TEST_SINGLE_ARG_FUNCTION && TEST_PARENTHESIS
	GATS_CHECK(parse_test(
		// Test: tan(2.0)
		TokenList({ make<Tan>(), make<LeftParenthesis>(), make<Real>(2.0), make<RightParenthesis>() }),
		TokenList({ make<Real>(2.0), make<Tan>() })
		));
#endif
}



GATS_TEST_CASE_WEIGHTED(07ah_parser_function_2_arg_pow, GROUP_WEIGHT) {
#if TEST_PARSER && TEST_REAL && TEST_MULTI_ARG_FUNCTION && TEST_PARENTHESIS
	GATS_CHECK(parse_test(
		// Test: pow(2.3,3.4)
		TokenList({ make<Pow>(), make<LeftParenthesis>(), make<Real>(2.3), make<ArgumentSeparator>(), make<Real>(3.4), make<RightParenthesis>() }),
		TokenList({ make<Real>(2.3), make<Real>(3.4), make<Pow>() })
		));
#endif
}



GATS_TEST_CASE_WEIGHTED(07ai_parser_function_expression, GROUP_WEIGHT) {
#if TEST_PARSER && TEST_REAL && TEST_MULTI_ARG_FUNCTION && TEST_PARENTHESIS
	GATS_CHECK(parse_test(
		// Test: atan2(2.1,4.2)-10.3
		TokenList({ make<Arctan2>(), make<LeftParenthesis>(), make<Real>(2.1), make<ArgumentSeparator>(), make<Real>(4.2), make<RightParenthesis>(), make<Subtraction>(), make<Real>(10.3) }),
		TokenList({ make<Real>(2.1), make<Real>(4.2), make<Arctan2>(), make<Real>(10.3), make<Subtraction>() })
		));
#endif
}

GATS_TEST_CASE_WEIGHTED(07aj_parser_function_argument_expression, GROUP_WEIGHT) {
#if TEST_PARSER && TEST_REAL && TEST_MULTI_ARG_FUNCTION && TEST_PARENTHESIS
	GATS_CHECK(parse_test(
		// Test: atan2(2.1,4.2-10.3)
		TokenList({ make<Arctan2>(), make<LeftParenthesis>(), make<Real>(2.1), make<ArgumentSeparator>(), make<Real>(4.2), make<Subtraction>(), make<Real>(10.3), make<RightParenthesis>() }),
		TokenList({ make<Real>(2.1), make<Real>(4.2), make<Real>(10.3), make<Subtraction>(), make<Arctan2>() })
		));
#endif
}

GATS_TEST_CASE_WEIGHTED(07ak_test_multiply_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(3.0), make<Real>(4.0), make<Multiplication>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("12.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07al_test_divide_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("45.0")), make<Real>(Real::value_type("3.0")), make<Division>() });
	GATS_CHECK(round(result) == round(Real::value_type("15.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07am_test_addition_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3.0")), make<Real>(Real::value_type("4.0")), make<Addition>() });
	GATS_CHECK(round(result) == round(Real::value_type("7.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07an_test_subtraction_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3.0")), make<Real>(Real::value_type("4.0")), make<Subtraction>() });
	GATS_CHECK(round(result) == round(Real::value_type("-1.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07ao_test_power_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3.0")), make<Real>(Real::value_type("4.0")), make<Power>() });
	GATS_CHECK(round(result) == round(Real::value_type("81")));
#endif
}



GATS_TEST_CASE_WEIGHTED(07ap_test_abs_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("4.0")), make<Abs>() });
	GATS_CHECK(round(result) == round(Real::value_type("4.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07aq_test_abs_Real_neg, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("-4.0")), make<Abs>() });
	GATS_CHECK(round(result) == round(Real::value_type("4.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07ar_test_acos_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Arccos>() });
	GATS_CHECK(round(result) == Real::value_type("0.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07as_test_asin_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Arcsin>() });
	GATS_CHECK(value_of<Real>(result) == boost::math::constants::half_pi<Real::value_type>());
#endif
}
GATS_TEST_CASE_WEIGHTED(07at_test_atan_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("0.0")), make<Arctan>() });
	GATS_CHECK(round(result) == Real::value_type("0.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07au_test_ceil_high_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("4.3")), make<Ceil>() });
	GATS_CHECK(round(result) == round(Real::value_type("5.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07av_test_ceil_low_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("-4.3")), make<Ceil>() });
	GATS_CHECK(round(result) == round(Real::value_type("-4.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07aw_test_cos_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("0.0")), make<Cos>() });
	GATS_CHECK(round(result) == round(Real::value_type("1.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07ax_test_exp, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Exp>() });
	GATS_CHECK(round(result) == round(boost::math::constants::e<Real::value_type>()));
#endif
}
GATS_TEST_CASE_WEIGHTED(07ay_test_floor_positive_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("4.3")), make<Floor>() });
	GATS_CHECK(round(result) == round(Real::value_type("4.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07az_test_floor__negative_Real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("-4.3")), make<Floor>() });
	GATS_CHECK(round(result) == round(Real::value_type("-5.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07ba_test_lb, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("8.0")), make<Lb>() });
	GATS_CHECK(round(value_of<Real>(result)) == round(Real::value_type("3.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bb_test_ln, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Ln>() });
	GATS_CHECK(round(value_of<Real>(result)) == boost::multiprecision::log(Real::value_type("1.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bc_test_sin, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("0.0")), make<Sin>() });
	GATS_CHECK(round(value_of<Real>(result)) == Real::value_type("0.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bd_test_sqrt, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("16.0")), make<Sqrt>() });
	GATS_CHECK(round(value_of<Real>(result)) == round(Real::value_type("4.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07be_test_tan, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Tan>() });
	GATS_CHECK(value_of<Real>(result) == tan(Real::value_type("1.0")));
#endif
}



GATS_TEST_CASE_WEIGHTED(07bf_test_arctan2, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("2.0")), make<Arctan2>() });
	GATS_CHECK(value_of<Real>(result) == atan2(Real::value_type("1.0"), Real::value_type("2.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bg_test_max_real_real_rhs, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("2.0")), make<Max>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bh_test_max_real_real_lhs, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("1.0")), make<Max>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bi_test_max_real_real_same, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("2.0")), make<Max>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bj_test_min_real_real_rhs, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("2.0")), make<Min>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bk_test_min_real_real_lhs, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("1.0")), make<Min>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bl_test_min_real_real_same, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("2.0")), make<Min>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bm_test_pow_real, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_MULTI_ARG_FUNCTION
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("3.0")), make<Pow>() });
	GATS_CHECK(value_of<Real>(result) == Real::value_type("8.0"));
#endif
}



GATS_TEST_CASE_WEIGHTED(07bn_EE_real_small, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL
	auto result = ExpressionEvaluator().evaluate("1234.5678");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("1234.5678"));
#endif
}



GATS_TEST_CASE_WEIGHTED(07bo_EE_real_large, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL
	auto result = ExpressionEvaluator().evaluate("123456789012345678901234567890123456789012345678901234567890.123456789012345678901234567890123456789012345678901234567890");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("123456789012345678901234567890123456789012345678901234567890.123456789012345678901234567890123456789012345678901234567890"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bp_EE_real_e, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL
	auto result = ExpressionEvaluator().evaluate("e");
	GATS_CHECK(value_of<Real>(result) == boost::math::constants::e<Real::value_type>());
	result = ExpressionEvaluator().evaluate("E");
	GATS_CHECK(value_of<Real>(result) == boost::math::constants::e<Real::value_type>());
#endif
}
GATS_TEST_CASE_WEIGHTED(07bq_EE_real_pi, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL
	auto result = ExpressionEvaluator().evaluate("pi");
	GATS_CHECK(value_of<Real>(result) == boost::math::constants::pi<Real::value_type>());
	result = ExpressionEvaluator().evaluate("Pi");
	GATS_CHECK(value_of<Real>(result) == boost::math::constants::pi<Real::value_type>());
	result = ExpressionEvaluator().evaluate("PI");
	GATS_CHECK(value_of<Real>(result) == boost::math::constants::pi<Real::value_type>());
#endif
}


GATS_TEST_CASE_WEIGHTED(07br_EE_identity_real, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_UNARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("+42.3");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("42.3"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bs_EE_negation_real, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_UNARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("-42.3");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("-42.3"));
#endif
}

GATS_TEST_CASE_WEIGHTED(07bt_EE_addition_real, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("2.2+3.3");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("5.5"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bu_EE_subtraction_real, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("2.2-3.3");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("-1.1"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bv_EE_multiplication_real, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("2.5*3.5");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("8.75"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bw_EE_division_real, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("5.5/1.1");
	GATS_CHECK(round(result) == round(Real::value_type("5.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bx_EE_power_operator_real, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("4.0 ** 0.5");
	GATS_CHECK(round(result) == round(Real::value_type("2.0")));
#endif
}


GATS_TEST_CASE_WEIGHTED(07by_EE_real_trig, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = ExpressionEvaluator().evaluate("cos(0.0)");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0"));

	result = ExpressionEvaluator().evaluate("arccos(1.0)");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("0.0"));

	result = ExpressionEvaluator().evaluate("sin(0.0)");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("0.0"));

	result = ExpressionEvaluator().evaluate("arcsin(1.0)");
	GATS_CHECK(value_of<Real>(result) == boost::math::constants::half_pi<Real::value_type>());

	result = ExpressionEvaluator().evaluate("tan(0.0)");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("0.0"));

	result = ExpressionEvaluator().evaluate("arctan(0.0)");
	GATS_CHECK(value_of<Real>(result) == Real::value_type("0.0"));
#endif
}
GATS_TEST_CASE_WEIGHTED(07bz_EE_abs, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = ExpressionEvaluator().evaluate("abs(4.0)");
	GATS_CHECK(round(result) == round(Real::value_type("4.0")));

	result = ExpressionEvaluator().evaluate("abs(-4.0)");
	GATS_CHECK(round(result) == round(Real::value_type("4.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07ca_EE_ceil, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = ExpressionEvaluator().evaluate("ceil(4.3)");
	GATS_CHECK(round(result) == round(Real::value_type("5.0")));
	result = ExpressionEvaluator().evaluate("ceil(-4.3)");
	GATS_CHECK(round(result) == round(Real::value_type("-4.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07cb_EE_exp, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = ExpressionEvaluator().evaluate("exp(1.0)");
	GATS_CHECK(value_of<Real>(result) == exp(Real::value_type("1.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07cc_EE_floor, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = ExpressionEvaluator().evaluate("floor(4.3)");
	GATS_CHECK(round(result) == round(Real::value_type("4.0")));
	result = ExpressionEvaluator().evaluate("floor(-4.3)");
	GATS_CHECK(round(result) == round(Real::value_type("-5.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07cd_EE_lb, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = ExpressionEvaluator().evaluate("lb(8.0)");
	GATS_CHECK(round(value_of<Real>(result)) == round(Real::value_type("3.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07ce_EE_ln, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = ExpressionEvaluator().evaluate("ln(1.0)");
	GATS_CHECK(round(value_of<Real>(result)) == boost::multiprecision::log(Real::value_type("1.0")));
#endif
}
GATS_TEST_CASE_WEIGHTED(07cf_EE_sqrt, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_SINGLE_ARG_FUNCTION
	auto result = ExpressionEvaluator().evaluate("sqrt(16.0)");
	GATS_CHECK(round(value_of<Real>(result)) == round(Real::value_type("4.0")));
#endif
}



GATS_TEST_CASE_WEIGHTED(07cg_EE_order_real, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("1.0/(1.0/32.0+1.0/48.0)");
	auto x = round(result);
	GATS_CHECK(x == round(Real::value_type("19.2")));
#endif
}

GATS_TEST_CASE_WEIGHTED(07ch_EE_order_real_function, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR && TEST_SINGLE_ARG_FUNCTION
	auto result = ExpressionEvaluator().evaluate("sin(1.0)**2+cos(1.0)**2");
	GATS_CHECK(round(result) == round(Real::value_type("1.0")));
#endif
}
