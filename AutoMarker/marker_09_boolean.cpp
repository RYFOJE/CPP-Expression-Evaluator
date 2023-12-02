/*! \file	marker_09_boolean.cpp
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
#include <ee/boolean.hpp>
#include <ee/integer.hpp>
#include <ee/real.hpp>

constexpr unsigned GROUP_COUNT = 40;
constexpr double GROUP_WEIGHT = 5.0 / GROUP_COUNT;


GATS_TEST_CASE_WEIGHTED(09aa_constant_true, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>() });
	GATS_CHECK(value_of<True>(result) == true);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ab_constant_false, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<False>() });
	GATS_CHECK(value_of<False>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ac_not_test_Boolean, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<Boolean>(true), make<Not>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Boolean>(false), make<Not>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ad_test_and, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<And>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<And>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<And>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<False>(), make<False>(), make<And>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ae_test_nand, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Nand>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<Nand>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Nand>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<False>(), make<False>(), make<Nand>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}



GATS_TEST_CASE_WEIGHTED(09af_test_nor, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Nor>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<Nor>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Nor>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<False>(), make<False>(), make<Nor>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ag_test_or, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Or>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<Or>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Or>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<False>(), make<False>(), make<Or>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ah_test_xor, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Xor>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<Xor>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Xor>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<False>(), make<False>(), make<Xor>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ai_test_equality_boolean, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Equality>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Equality>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09aj_test_inequality_boolean, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Inequality>() });
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Inequality>() });
	GATS_CHECK(value_of<Boolean>(result) != false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ak_test_greater_boolean, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Greater>() });
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Greater>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09al_test_greater_equal_boolean, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}



GATS_TEST_CASE_WEIGHTED(09am_test_less_boolean, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09an_test_less_equal_boolean, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ao_test_equality_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<Equality>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<Equality>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ap_test_inequality_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<Inequality>() });
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<Inequality>() });
	GATS_CHECK(value_of<Boolean>(result) != false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09aq_test_greater_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<Greater>() });
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<Greater>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ar_test_greater_equal_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(0), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}



GATS_TEST_CASE_WEIGHTED(09as_test_less_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(0), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09at_test_less_equal_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(0), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09au_test_equality_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<Equality>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Real>(Real::value_type("1.0")), make<Equality>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09av_test_inequality_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<Inequality>() });
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Real>(Real::value_type("1.0")), make<Inequality>() });
	GATS_CHECK(value_of<Boolean>(result) != false);
#endif
}



GATS_TEST_CASE_WEIGHTED(09aw_test_greater_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<Greater>() });
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Real>(Real::value_type("1.0")), make<Greater>() });
	GATS_CHECK(value_of<Boolean>(result) != false);
#endif
}
GATS_TEST_CASE_WEIGHTED(09ax_test_greater_equal_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("1.0")), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("2.0")), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(09ay_test_less_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Real>(Real::value_type("1.0")), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("0.1")), make<Real>(Real::value_type("1.0")), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}
GATS_TEST_CASE_WEIGHTED(09az_test_less_equal_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("1.0")), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("2.0")), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}



GATS_TEST_CASE_WEIGHTED(09ba_test_equality_mixed, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR && TEST_INTEGER && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("1.0")), make<Equality>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Integer>(1), make<Equality>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(09bb_test_inequality_mixed, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR && TEST_INTEGER && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("1.0")), make<Inequality>() });
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Integer>(1), make<Inequality>() });
	GATS_CHECK(value_of<Boolean>(result) != false);
#endif
}
GATS_TEST_CASE_WEIGHTED(09bc_test_greater_mixed, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR && TEST_INTEGER && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("1.0")), make<Greater>() });
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Integer>(1), make<Greater>() });
	GATS_CHECK(value_of<Boolean>(result) != false);
#endif
}
GATS_TEST_CASE_WEIGHTED(09bd_test_greater_equal_mixed, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR && TEST_INTEGER && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Integer>(1), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Integer>(1), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Integer>(2), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("1.0")), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("1.0")), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("2.0")), make<GreaterEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(09be_test_less_mixed, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR && TEST_INTEGER && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("1.0")), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Integer>(0), make<Real>(Real::value_type("1.0")), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("1.0")), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Integer>(1), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Integer>(1), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("0.1")), make<Integer>(1), make<Less>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}
GATS_TEST_CASE_WEIGHTED(09bf_test_less_equal_mixed, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR && TEST_INTEGER && TEST_MIXED
	auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Integer>(1), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Integer>(1), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Integer>(2), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("1.0")), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("1.0")), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("2.0")), make<LessEqual>() });
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}



GATS_TEST_CASE_WEIGHTED(09bg_EE_bool_true, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR && TEST_INTEGER && TEST_MIXED
	auto result = ExpressionEvaluator().evaluate("true");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("True");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("TRUE");
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}
GATS_TEST_CASE_WEIGHTED(09bh_EE_bool_false, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR && TEST_INTEGER && TEST_MIXED
	auto result = ExpressionEvaluator().evaluate("false");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("False");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("FALSE");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}

GATS_TEST_CASE_WEIGHTED(09bi_EE_and, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_NAMED_OPERATOR && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("true and true");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("true and false");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("false and true");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("false and false");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(09bj_EE_or, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_NAMED_OPERATOR && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("true or true");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("true or false");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("false or true");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("false or false");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(09bk_EE_xor, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_NAMED_OPERATOR && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("true xor true");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("true xor false");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("false xor true");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("false xor false");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(09bl_EE_nand, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_NAMED_OPERATOR && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("true nand true");
	GATS_CHECK(value_of<Boolean>(result) == !true);
	result = ExpressionEvaluator().evaluate("true nand false");
	GATS_CHECK(value_of<Boolean>(result) == !false);
	result = ExpressionEvaluator().evaluate("false nand true");
	GATS_CHECK(value_of<Boolean>(result) == !false);
	result = ExpressionEvaluator().evaluate("false nand false");
	GATS_CHECK(value_of<Boolean>(result) == !false);
#endif
}
GATS_TEST_CASE_WEIGHTED(09bm_EE_nor, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_NAMED_OPERATOR && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("true nor true");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("true nor false");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("false nor true");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("false nor false");
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}
GATS_TEST_CASE_WEIGHTED(09bn_EE_xnor, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_NAMED_OPERATOR && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("true xnor true");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("true xnor false");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("false xnor true");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("false xnor false");
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}

