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
#include <ee/variable.hpp>
#include <ee/operator.hpp>
#include <ee/integer.hpp>
#include <ee/boolean.hpp>
#include <ee/real.hpp>



constexpr unsigned GROUP_COUNT = 8;
constexpr double GROUP_WEIGHT = 5.0 / GROUP_COUNT;


GATS_TEST_CASE_WEIGHTED(11a_parser_variable, GROUP_WEIGHT) {
#if TEST_PARSER && TEST_INTEGER && TEST_VARIABLE && TEST_BINARY_OPERATOR
	GATS_CHECK(parse_test(
		// Test: x=2
		TokenList({ make<Variable>(), make<Assignment>(), make<Integer>(2) }),
		TokenList({ make<Variable>(), make<Integer>(2), make<Assignment>() })
		));
#endif
}

GATS_TEST_CASE_WEIGHTED(11b_parser_variable_variable, GROUP_WEIGHT) {
#if TEST_PARSER && TEST_VARIABLE && TEST_BINARY_OPERATOR
	GATS_CHECK(parse_test(
		// Test: x=y
		TokenList({ make<Variable>(), make<Assignment>(), make<Variable>() }),
		TokenList({ make<Variable>(), make<Variable>(), make<Assignment>() })
		));
#endif
}


GATS_TEST_CASE_WEIGHTED(11c_unitialized_single_variable, GROUP_WEIGHT) {
#if TEST_RPN && TEST_VARIABLE
	auto result = RPNEvaluator().evaluate({ make<Variable>() });

	GATS_CHECK(is<Variable>(result));
	Variable::pointer_type v = convert<Variable>(result);
	GATS_CHECK(v->value() == nullptr);
#endif
}


GATS_TEST_CASE_WEIGHTED(11d_unitialized_variable_expression, GROUP_WEIGHT) {
#if TEST_RPN && TEST_VARIABLE && TEST_UNARY_OPERATOR
	try {
		auto result = RPNEvaluator().evaluate({ make<Variable>(), make<Negation>() });
		GATS_FAIL("Failed to throw exception");
	}
	catch (std::exception& e) {
		GATS_CHECK(strcmp(e.what(), "Error: variable not initialized") == 0);
	}
#endif
}



GATS_TEST_CASE_WEIGHTED(11e_assignment_test, GROUP_WEIGHT) {
#if TEST_RPN && TEST_VARIABLE && TEST_BINARY_OPERATOR && TEST_INTEGER
	auto result = RPNEvaluator().evaluate({ make<Variable>(), make<Integer>(4), make<Assignment>() });

	GATS_CHECK(is<Variable>(result));
	Variable::pointer_type v = convert<Variable>(result);
	GATS_CHECK( is<Integer>( v->value() ) );
	Integer::pointer_type i = convert<Integer>( v->value() );
	GATS_CHECK( i->value() == 4 );
#endif
}


GATS_TEST_CASE_WEIGHTED(11f_assignment_to_constant_fail, GROUP_WEIGHT) {
#if TEST_RPN && TEST_REAL && TEST_BINARY_OPERATOR && TEST_VARIABLE
	try {
		auto t = RPNEvaluator().evaluate({ make<Pi>(), make<Integer>(4), make<Assignment>() });
		GATS_FAIL("Failed to throw an 'assignment to a non-variable' exception.");
	} catch (std::exception const& ex) {
		GATS_CHECK(std::string(ex.what()) == std::string("Error: assignment to a non-variable."));
	}
#endif
}


GATS_TEST_CASE_WEIGHTED(11g_EE_variable, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR && TEST_VARIABLE
	ExpressionEvaluator ee;
	auto result = ee.evaluate("x=4");
	auto var = convert<Variable>(result);
	auto val = var->value();
	GATS_CHECK(value_of<Integer>(val) == Integer::value_type("4"));
#endif
}


GATS_TEST_CASE_WEIGHTED(11h_EE_variable, GROUP_WEIGHT) {
#if TEST_EE && TEST_REAL && TEST_BINARY_OPERATOR && TEST_BOOLEAN && TEST_NAMED_OPERATOR && TEST_RELATIONAL_OPERATOR && TEST_VARIABLE
	ExpressionEvaluator ee;
	auto result = ee.evaluate("a = true");
	result = ee.evaluate("b = false");
	result = ee.evaluate("a and b == not(not a or not b)");
	GATS_CHECK(value_of<Boolean>(result) == true);
#endif
}
