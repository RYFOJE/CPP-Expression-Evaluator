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

constexpr unsigned GROUP_COUNT = 16;
constexpr double GROUP_WEIGHT = 5.0 / GROUP_COUNT;




GATS_TEST_CASE_WEIGHTED(10a_EE_equal_bool, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("true == true");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("false == true");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(10b_EE_not_equal_bool, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR
	auto result = ExpressionEvaluator().evaluate("true != true");
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = ExpressionEvaluator().evaluate("false != true");
	GATS_CHECK(value_of<Boolean>(result) != false);
#endif
}

GATS_TEST_CASE_WEIGHTED(10c_EE_equal_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_INTEGER
	auto result = ExpressionEvaluator().evaluate("1 == 1");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("1 == 2");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(10d_EE_not_equal_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_INTEGER
	auto result = ExpressionEvaluator().evaluate("1 != 1");
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = ExpressionEvaluator().evaluate("1 != 2");
	GATS_CHECK(value_of<Boolean>(result) != false);
#endif
}
GATS_TEST_CASE_WEIGHTED(10e_EE_less_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_INTEGER
	auto result = ExpressionEvaluator().evaluate("1 < 1");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("1 < 2");
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}
GATS_TEST_CASE_WEIGHTED(10f_EE_less_equal_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_INTEGER
	auto result = ExpressionEvaluator().evaluate("1 <= 1");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("1 <= 2");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("3 <= 2");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(10g_EE_greater_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_INTEGER
	auto result = ExpressionEvaluator().evaluate("1 > 1");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("2 > 1");
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}
GATS_TEST_CASE_WEIGHTED(10h_EE_greater_equal_integer, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_INTEGER
	auto result = ExpressionEvaluator().evaluate("1 >= 1");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("2 >= 1");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("2 >= 3");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}

GATS_TEST_CASE_WEIGHTED(10i_EE_equal_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_REAL
	auto result = ExpressionEvaluator().evaluate("1.0 == 1.0");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("1.0 == 2.0");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(10j_EE_not_equal_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_REAL
	auto result = ExpressionEvaluator().evaluate("1.0 != 1.0");
	GATS_CHECK(value_of<Boolean>(result) != true);
	result = ExpressionEvaluator().evaluate("1.0 != 2.0");
	GATS_CHECK(value_of<Boolean>(result) != false);
#endif
}
GATS_TEST_CASE_WEIGHTED(10k_EE_less_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_REAL
	auto result = ExpressionEvaluator().evaluate("1.0 < 1.0");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("1.0 < 2.0");
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}
GATS_TEST_CASE_WEIGHTED(10l_EE_less_equal_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_REAL
	auto result = ExpressionEvaluator().evaluate("1.0 <= 1.0");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("1.0 <= 2.0");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("2.01 <= 2.0");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}
GATS_TEST_CASE_WEIGHTED(10m_EE_greater_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_REAL
	auto result = ExpressionEvaluator().evaluate("1.0 > 1.0");
	GATS_CHECK(value_of<Boolean>(result) == false);
	result = ExpressionEvaluator().evaluate("2.0 > 1.0");
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}
GATS_TEST_CASE_WEIGHTED(10n_EE_greater_equal_real, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_REAL
	auto result = ExpressionEvaluator().evaluate("1.0 >= 1.0");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("2.0 >= 1.0");
	GATS_CHECK(value_of<Boolean>(result) == true);
	result = ExpressionEvaluator().evaluate("1.99 >= 2.0");
	GATS_CHECK(value_of<Boolean>(result) == false);
#endif
}



GATS_TEST_CASE_WEIGHTED(10o_EE_order_bool, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR
	ExpressionEvaluator ee;
	auto result = ee.evaluate("true and not true");
	GATS_CHECK(value_of<Boolean>(result) == false);

	result = ee.evaluate("true and false == not(not true or not false)");
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}


GATS_TEST_CASE_WEIGHTED(10p_EE_relational, GROUP_WEIGHT) {
#if TEST_BOOLEAN && TEST_EE && TEST_RELATIONAL_OPERATOR && TEST_BINARY_OPERATOR && TEST_INTEGER
	ExpressionEvaluator ee;
	auto result = ee.evaluate("4 < 5 and 5 == 5");
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}
