/*!	\file	ut2_tokens_operations.cpp
	\brief	Token types unit test.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

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
#include <ee/function.hpp>
#include <ee/integer.hpp>
#include <ee/operator.hpp>
#include <ee/pseudo_operation.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>

#include <string>
using namespace std;

#include "ut_test_phases.hpp"



// Test the Operation types
// ==============================
#if TEST_UNARY_OPERATOR
GATS_TEST_CASE(2_Identity_operator_test) {
	auto tkn = make<Identity>();
	GATS_CHECK(!is<Operand>(tkn));
	GATS_CHECK(!is<PseudoOperation>(tkn));
	GATS_CHECK(is<Operation>(tkn));

	GATS_CHECK(is<Operator>(tkn));
#if TEST_FUNCTION
	GATS_CHECK(!is<Function>(tkn));
#endif

	GATS_CHECK(is<NonAssociative>(tkn));
#if TEST_BINARY_OPERATOR
	GATS_CHECK(!is<BinaryOperator>(tkn));
#endif
	GATS_CHECK(is<UnaryOperator>(tkn));

	GATS_CHECK(is<Identity>(tkn));
	GATS_CHECK(!is<Negation>(tkn));

	// Can be only one of the following.
#if TEST_BOOLEAN
	GATS_CHECK(!is<Not>(tkn));
#endif
#if TEST_POSTFIX_OPERATOR
	GATS_CHECK(!is<PostfixOperator>(tkn));
#endif
}


GATS_TEST_CASE(2_Negation_operator_test) {
	auto tkn = make<Negation>();
	GATS_CHECK(!is<Operand>(tkn));
	GATS_CHECK(!is<PseudoOperation>(tkn));
	GATS_CHECK(is<Operation>(tkn));

	GATS_CHECK(is<Operator>(tkn));
#if TEST_FUNCTION
	GATS_CHECK(!is<Function>(tkn));
#endif

	GATS_CHECK(is<NonAssociative>(tkn));
#if TEST_BINARY_OPERATOR
	GATS_CHECK(!is<BinaryOperator>(tkn));
#endif
	GATS_CHECK(is<UnaryOperator>(tkn));

	GATS_CHECK(!is<Identity>(tkn));
	GATS_CHECK(is<Negation>(tkn));

	// Can be only one of the following.
#if TEST_BOOLEAN
	GATS_CHECK(!is<Not>(tkn));
#endif
#if TEST_POSTFIX_OPERATOR
	GATS_CHECK(!is<PostfixOperator>(tkn));
#endif
}



#if TEST_BOOLEAN
GATS_TEST_CASE(2_Not_operator_test) {
	auto tkn = make<Not>();
	GATS_CHECK(!is<Operand>(tkn));
	GATS_CHECK(!is<PseudoOperation>(tkn));
	GATS_CHECK(is<Operation>(tkn));

	GATS_CHECK(is<Operator>(tkn));
#if TEST_FUNCTION
	GATS_CHECK(!is<Function>(tkn));
#endif

	GATS_CHECK(is<NonAssociative>(tkn));
#if TEST_BINARY_OPERATOR
	GATS_CHECK(!is<BinaryOperator>(tkn));
#endif
	GATS_CHECK(is<UnaryOperator>(tkn));


	GATS_CHECK(!is<Identity>(tkn));
	GATS_CHECK(!is<Negation>(tkn));
	GATS_CHECK(is<Not>(tkn));

#if TEST_POSTFIX_OPERATOR
	GATS_CHECK(!is<PostfixOperator>(tkn));
#endif
}
#endif
#if TEST_POSTFIX_OPERATOR
GATS_TEST_CASE(2_Factorial_operator_test) {
	auto tkn = make<Factorial>();
	GATS_CHECK(!is<Operand>(tkn));
	GATS_CHECK(!is<PseudoOperation>(tkn));
	GATS_CHECK(is<Operation>(tkn));

	GATS_CHECK(is<Operator>(tkn));
#if TEST_FUNCTION
	GATS_CHECK(!is<Function>(tkn));
#endif

	GATS_CHECK(is<NonAssociative>(tkn));
#if TEST_BINARY_OPERATOR
	GATS_CHECK(!is<BinaryOperator>(tkn));
#endif
	GATS_CHECK(is<UnaryOperator>(tkn));

	GATS_CHECK(!is<Identity>(tkn));
	GATS_CHECK(!is<Negation>(tkn));

#if TEST_BOOLEAN
	GATS_CHECK(!is<Not>(tkn));
#endif
#if TEST_POSTFIX_OPERATOR
	GATS_CHECK(is<PostfixOperator>(tkn));
	GATS_CHECK(is<Factorial>(tkn));
#endif
}
#endif


//#if TEST_BINARY_OPERATOR
//typedef boost::mpl::list<Addition, And, Division
//#if TEST_RELATIONAL_OPERATOR
//	, Equality, Greater, GreaterEqual, Inequality, Less, LessEqual
//#endif
//	, Modulus, Multiplication
//#if TEST_BOOLEAN
//	, Nand, Nor, Or
//#endif
//	, Subtraction
//#if TEST_BOOLEAN
//	, Xnor, Xor
//#endif
//> lassoc_binary_test_types;
//GATS_TEST_CASE(LAssoc_binary_operator_test, T, lassoc_binary_test_types) {
//	auto tkn = make<T>();
//	GATS_CHECK(!is<Operand>(tkn));
//	GATS_CHECK(!is<PseudoOperation>(tkn));
//	GATS_CHECK(is<Operation>(tkn));
//
//	GATS_CHECK(is<Operator>(tkn));
//#if TEST_FUNCTION
//	GATS_CHECK(!is<Function>(tkn));
//#endif
//
//	GATS_CHECK(!is<NonAssociative>(tkn));
//	GATS_CHECK(!is<UnaryOperator>(tkn));
//
//	GATS_CHECK(is<BinaryOperator>(tkn));
//#if TEST_RIGHT_ASSOCIATIVE_OPERATOR
//	GATS_CHECK(!is<RAssocOperator>(tkn));
//	GATS_CHECK(is<LAssocOperator>(tkn));
//#endif
//	GATS_CHECK(is<T>(tkn));
//
//	// Can be only one of the following.
//	auto sum = is<Addition>(tkn) + is<And>(tkn) + is<Division>(tkn) + is<Modulus>(tkn) + is<Multiplication>(tkn) + is<Subtraction>(tkn)
//#if TEST_RELATIONAL_OPERATOR
//		+ is<Equality>(tkn) + is<Greater>(tkn) + is<GreaterEqual>(tkn) + is<Inequality>(tkn) + is<Less>(tkn) + is<LessEqual>(tkn)
//#endif
//#if TEST_BOOLEAN
//		+ is<Nand>(tkn) + is<Nor>(tkn) + is<Or>(tkn) + is<Xnor>(tkn) + is<Xor>(tkn)
//#endif
//		;
//
//	GATS_CHECK_EQUAL(sum, 1);
//}
//
//
//#if TEST_RIGHT_ASSOCIATIVE_OPERATOR
//typedef boost::mpl::list<Assignment, Power> rassoc_binary_test_types;
//GATS_TEST_CASE_TEMPLATE(RAssoc_binary_operator_test, T, rassoc_binary_test_types) {
//	auto tkn = make<T>();
//	GATS_CHECK(!is<Operand>(tkn));
//	GATS_CHECK(!is<PseudoOperation>(tkn));
//	GATS_CHECK(is<Operation>(tkn));
//
//	GATS_CHECK(is<Operator>(tkn));
//#if TEST_FUNCTION
//	GATS_CHECK(!is<Function>(tkn));
//#endif
//	GATS_CHECK(!is<NonAssociative>(tkn));
//#if TEST_UNARY_OPERATOR
//	GATS_CHECK(!is<UnaryOperator>(tkn));
//#endif
//	GATS_CHECK(is<BinaryOperator>(tkn));
//
//	GATS_CHECK(is<RAssocOperator>(tkn));
//	GATS_CHECK(!is<LAssocOperator>(tkn));
//
//	GATS_CHECK(is<T>(tkn));
//
//	// Can be only one of the following.
//	GATS_CHECK(is<Assignment>(tkn) + is<Power>(tkn) == 1);
//}
//#endif
//#endif
//
//#if TEST_POSTFIX_OPERATOR
//GATS_TEST_CASE(postfix_operator_test) {
//	auto tkn = make<Factorial>();
//	GATS_CHECK(!is<Operand>(tkn));
//	GATS_CHECK(!is<PseudoOperation>(tkn));
//	GATS_CHECK(is<Operation>(tkn));
//
//	GATS_CHECK(is<Operator>(tkn));
//#if TEST_FUNCTION
//	GATS_CHECK(!is<Function>(tkn));
//#endif
//	GATS_CHECK(is<NonAssociative>(tkn));
//	GATS_CHECK(!is<BinaryOperator>(tkn));
//
//	GATS_CHECK(is<UnaryOperator>(tkn));
//
//	GATS_CHECK(is<PostfixOperator>(tkn));
//	GATS_CHECK(is<Factorial>(tkn));
//}
//#endif

//#if TEST_FUNCTION
//#if TEST_SINGLE_ARG
//typedef boost::mpl::list<Abs, Arccos, Arcsin, Arctan, Ceil, Cos, Exp, Floor, Lb, Ln, Log, Result, Sin, Sqrt, Tan> single_arg_function_test_types;
//GATS_TEST_CASE_TEMPLATE(Single_arg_function_test, T, single_arg_function_test_types) {
//	auto tkn = make<T>();
//	GATS_CHECK(!is<Operand>(tkn));
//	GATS_CHECK(!is<PseudoOperation>(tkn));
//	GATS_CHECK(is<Operation>(tkn));
//
//	GATS_CHECK(!is<Operator>(tkn));
//	GATS_CHECK(is<Function>(tkn));
//	GATS_CHECK(is<OneArgFunction>(tkn));
//	GATS_CHECK(!is<TwoArgFunction>(tkn));
//
//	GATS_CHECK(is<T>(tkn));
//
//	// Can be only one of the following.
//	GATS_CHECK(
//		is<Abs>(tkn) + is<Arccos>(tkn) + is<Arcsin>(tkn) + is<Arctan>(tkn) +
//		is<Ceil>(tkn) + is<Cos>(tkn) + is<Exp>(tkn) + is<Floor>(tkn) +
//		is<Lb>(tkn) + is<Ln>(tkn) + is<Log>(tkn) + is<Result>(tkn) +
//		is<Sin>(tkn) + is<Sqrt>(tkn) + is<Tan>(tkn)
//		== 1);
//}
//#endif
//#if TEST_MULTI_ARG
//typedef boost::mpl::list<Arctan2, Max, Min, Pow> double_arg_function_test_types;
//GATS_TEST_CASE() {
//	auto tkn = make<T>();
//	GATS_CHECK(!is<Operand>(tkn));
//	GATS_CHECK(!is<PseudoOperation>(tkn));
//	GATS_CHECK(is<Operation>(tkn));
//
//	GATS_CHECK(!is<Operator>(tkn));
//	GATS_CHECK(is<Function>(tkn));
//	GATS_CHECK(!is<OneArgFunction>(tkn));
//	GATS_CHECK(is<TwoArgFunction>(tkn));
//
//	GATS_CHECK(is<T>(tkn));
//
//	// Can be only one of the following.
//	GATS_CHECK(
//		is<Arctan2>(tkn) + is<Max>(tkn) + is<Min>(tkn) + is<Pow>(tkn)
//		== 1);
//}
//#endif
#endif
