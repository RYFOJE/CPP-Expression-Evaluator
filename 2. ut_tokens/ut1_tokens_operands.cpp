/*!	\file	ut1_tokens_operands.cpp
	\brief	Token types unit test.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Test the Operand tokens:
	Token
	Operand
	Integer
	Real
	Boolean
	Variable

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated
	Separated from ut_tokens.cpp

Version 2019.11.05
	C++ 17 cleanup

Version 2017.11.23
	Updated to Visual C++ 15.4.4
	New hierarchy tests.

Version 2014.10.29
	Updated to Visual C++ 12

Version 2012.11.16
	Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

Version 2012.11.15
	Added BinaryInteger, Binary <function>

Version 2012.11.13
	C++ 11 cleanup.

Version 2009.11.30
	Alpha release.


=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/

// unit test library
#include <gats/TestApp.hpp>

// Tokenizer system
#include <ee/boolean.hpp>
#include <ee/integer.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>

#include <string>
using namespace std;

#include "ut_test_phases.hpp"


// Test the Operand types
// ==============================
#if TEST_INTEGER
GATS_TEST_CASE(1_integer_test) {
	GATS_CHECK(Integer().value() == 0);
	GATS_CHECK(Integer(42).value() == 42);
	GATS_CHECK(
		Integer(Integer::value_type("123456789012345678901234567890")).value() ==
		Integer::value_type("123456789012345678901234567890"));

	auto i = make<Integer>();
	GATS_CHECK(is<Token>(i));
	GATS_CHECK(!is<Operation>(i));
	GATS_CHECK(is<Operand>(i));
#if TEST_BOOLEAN
	GATS_CHECK(!is<Boolean>(i));
#endif
#if TEST_REAL
	GATS_CHECK(!is<Real>(i));
#endif
#if TEST_VARIABLE
	GATS_CHECK(!is<Variable>(i));
#endif
	GATS_CHECK(is<Integer>(i));
}
#endif // TEST_INTEGER



#if TEST_REAL
GATS_TEST_CASE(1_real_test) {
	GATS_CHECK(Real().value() == 0.0);
	GATS_CHECK(Real(4.2).value() == 4.2);
	GATS_CHECK(
		Real(Real::value_type("12345678901234567890.1234567890")).value() ==
		Real::value_type("12345678901234567890.1234567890"));

	auto i = make<Real>();
	GATS_CHECK(is<Token>(i));
	GATS_CHECK(!is<Operation>(i));
	GATS_CHECK(is<Operand>(i));
#if TEST_BOOLEAN
	GATS_CHECK(!is<Boolean>(i));
#endif
#if TEST_INTEGER
	GATS_CHECK(!is<Integer>(i));
#endif
#if TEST_VARIABLE
	GATS_CHECK(!is<Variable>(i));
#endif
	GATS_CHECK(is<Real>(i));

	auto e = make<E>();
	GATS_CHECK(is<Token>(e));
	GATS_CHECK(!is<Operation>(e));
	GATS_CHECK(is<Operand>(e));
#if TEST_BOOLEAN
	GATS_CHECK(!is<Boolean>(e));
#endif
#if TEST_INTEGER
	GATS_CHECK(!is<Integer>(e));
#endif
#if TEST_VARIABLE
	GATS_CHECK(!is<Variable>(e));
#endif
	GATS_CHECK(is<Real>(e));
	GATS_CHECK(!is<Pi>(e));
	GATS_CHECK(is<E>(e));

	auto pi = make<Pi>();
	GATS_CHECK(is<Token>(pi));
	GATS_CHECK(!is<Operation>(pi));
	GATS_CHECK(is<Operand>(pi));
#if TEST_BOOLEAN
	GATS_CHECK(!is<Boolean>(pi));
#endif
#if TEST_INTEGER
	GATS_CHECK(!is<Integer>(pi));
#endif
#if TEST_VARIABLE
	GATS_CHECK(!is<Variable>(pi));
#endif
	GATS_CHECK(is<Real>(pi));
	GATS_CHECK(!is<E>(pi));
	GATS_CHECK(is<Pi>(pi));
}
#endif // TEST_REAL



#if TEST_BOOLEAN
GATS_TEST_CASE(1_boolean_test) {
	GATS_CHECK(Boolean(false).value() == false);
	GATS_CHECK(Boolean(true).value() == true);
	GATS_CHECK(False().value() == false);
	GATS_CHECK(True().value() == true);

	auto b = make<Boolean>(false);
	GATS_CHECK(is<Token>(b));
	GATS_CHECK(!is<Operation>(b));
	GATS_CHECK(is<Operand>(b));
	GATS_CHECK(is<Boolean>(b));
#if TEST_INTEGER
	GATS_CHECK(!is<Integer>(b));
#endif
#if TEST_VARIABLE
	GATS_CHECK(!is<Variable>(b));
#endif
#if TEST_REAL
	GATS_CHECK(!is<Real>(b));
#endif

	auto t = make<True>();
	GATS_CHECK(is<Token>(t));
	GATS_CHECK(!is<Operation>(t));
	GATS_CHECK(is<Operand>(t));
	GATS_CHECK(is<Boolean>(t));
#if TEST_INTEGER
	GATS_CHECK(!is<Integer>(t));
#endif
#if TEST_VARIABLE
	GATS_CHECK(!is<Variable>(t));
#endif
#if TEST_REAL
	GATS_CHECK(!is<Real>(t));
#endif
	GATS_CHECK(is<True>(t));
	GATS_CHECK(!is<False>(t));


	auto f = make<False>();
	GATS_CHECK(is<Token>(f));
	GATS_CHECK(!is<Operation>(f));
	GATS_CHECK(is<Operand>(f));
	GATS_CHECK(is<Boolean>(f));
#if TEST_INTEGER
	GATS_CHECK(!is<Integer>(f));
#endif
#if TEST_VARIABLE
	GATS_CHECK(!is<Variable>(f));
#endif
#if TEST_REAL
	GATS_CHECK(!is<Real>(f));
#endif
	GATS_CHECK(!is<True>(f));
	GATS_CHECK(is<False>(f));
}
#endif // TEST_BOOLEAN



#if TEST_VARIABLE
GATS_TEST_CASE(1_variable_test) {
	Integer::pointer_type pi(new Integer(4));
	auto v = make<Variable>();
	Variable::pointer_type pv = convert<Variable>(v);
	pv->set(convert<Operand>(pi));
	GATS_CHECK(pv->value()->str() == pi->str());

	GATS_CHECK(is<Token>(v));
	GATS_CHECK(!is<Operation>(v));
	GATS_CHECK(is<Operand>(v));
#if TEST_BOOLEAN
	GATS_CHECK(!is<Boolean>(v));
#endif
#if TEST_INTEGER
	GATS_CHECK(!is<Integer>(v));
#endif
#if TEST_REAL
	GATS_CHECK(!is<Real>(v));
#endif
	GATS_CHECK(is<Variable>(v));
}
#endif // TEST_VARIABLE
