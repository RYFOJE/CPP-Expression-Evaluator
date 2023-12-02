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
#include <ee/RPNEvaluator.hpp>
#include <ee/expression_evaluator.hpp>
#include <ee/real.hpp>
#include <ee/operator.hpp>
#include <ee/function.hpp>
#include <ee/pseudo_operation.hpp>
#include <ee/variable.hpp>
#include <ee/boolean.hpp>



GATS_TEST_CASE_WEIGHTED(12a_express_result, 5.0) {
#if TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR && TEST_RESULT
	ExpressionEvaluator ee;
	auto result = ee.evaluate("1+1");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
	result = ee.evaluate("2+2");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("4"));

	result = ee.evaluate("result(1)*result(2)");
	GATS_CHECK(value_of<Integer>(result) == Integer::value_type("8"));
#endif
}
