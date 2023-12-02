/*! \file	ut_parser_main.cpp
	\brief	Parser unit test.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Parser unit test for Expression Evaluator Project.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2015.11.05
	Visual Studio 2015
	TEST_xxxx macros

Version 2014.10.31
	Visual Studio 2013

Version 2012.11.16
	Added BitAnd, BitNot, BitOr, BitXor, BitShiftLeft, BitShiftRight

Version 2012.11.15
	Added BinaryInteger, Binary <function>

Version 2012.11.13
	C++ 11 cleanup

Version 2009.12.01
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

// unit test library
#include <gats/TestApp.hpp>

// Parser system
#include <ee/parser.hpp>
#include <ee/function.hpp>
#include <ee/integer.hpp>
#include <ee/operator.hpp>
#include <ee/pseudo_operation.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>

#include "ut_test_phases.hpp"

#pragma region test_support
//=================================================================================================
// MACRO Framework
//=================================================================================================


/*! Performs parser test case

	1. Tokenizes the expression.
	2. Checks that returned token list matches correct list.

	\param expression [in] The expression to tokenize.
	*/
[[nodiscard]] bool parse_test(TokenList const& infixTokenList, TokenList const & correct) {
	TokenList postfixTokenList = Parser().parse(infixTokenList);
	bool ok = true;
	ok = ok && (correct.size() == postfixTokenList.size());
	size_t n = std::min(correct.size(), postfixTokenList.size());
	for (size_t i = 0; i < n; ++i) {
		bool match = correct[i] == postfixTokenList[i];
		GATS_CHECK_MESSAGE(match, "Token [" << i << "] = " << postfixTokenList[i]->str() << " should be " << correct[i]->str());
		ok = ok && match;
	}
	return ok;
}

#pragma endregion


#if TEST_PARSER
	GATS_TEST_CASE( parser_empty ) {
		TokenList infixTokenList, postfixTokenList;
		TokenList result = Parser().parse( infixTokenList );
		GATS_CHECK(result.size() == postfixTokenList.size());
	}



	#if TEST_INTEGER
		GATS_TEST_CASE(parser_single_number) {
			GATS_CHECK(parse_test(
				// Test: 42
				TokenList({ make<Integer>(42) }),
				TokenList({ make<Integer>(42) })));
		}



		#if TEST_UNARY_OPERATOR
			GATS_TEST_CASE(parser_single_negative) {
				GATS_CHECK(parse_test(
					// Test: -42
					TokenList({ make<Negation>(), make<Integer>(42) }),
					TokenList({ make<Integer>(42), make<Negation>() })));
			}
		#endif // TEST_UNARY



		#if TEST_BINARY_OPERATOR
			GATS_TEST_CASE(parser_binary_addition) {
				GATS_CHECK(parse_test(
					// Test: 4+2
					TokenList({ make<Integer>(4), make<Addition>(), make<Integer>(2) }),
					TokenList({ make<Integer>(4), make<Integer>(2), make<Addition>() })
					));
			}

			GATS_TEST_CASE(parser_order_of_operation_a_m) {
				GATS_CHECK(parse_test(
					// Test: 4+2*3 --> 4 2 3 * +
					TokenList({ make<Integer>(4), make<Addition>(), make<Integer>(2), make<Multiplication>(), make<Integer>(3) }),
					TokenList({ make<Integer>(4), make<Integer>(2), make<Integer>(3), make<Multiplication>(), make<Addition>() })
					));
			}

			GATS_TEST_CASE(parser_order_of_operation_m_a) {
				GATS_CHECK(parse_test(
					// Test: 4*2+3
					TokenList({ make<Integer>(4), make<Multiplication>(), make<Integer>(2), make<Addition>(), make<Integer>(3) }),
					TokenList({ make<Integer>(4), make<Integer>(2), make<Multiplication>(), make<Integer>(3), make<Addition>() })
					));
			}

			#if TEST_RIGHT_ASSOCIATIVE_OPERATOR
				GATS_TEST_CASE(parser_order_of_operation_right_assoc) {
					GATS_CHECK(parse_test(
						// Test: 2#3#4
						TokenList({ make<Integer>(2), make<Power>(), make<Integer>(3), make<Power>(), make<Integer>(4) }),
						TokenList({ make<Integer>(2), make<Integer>(3), make<Integer>(4), make<Power>(), make<Power>() })
						));
				}

			#endif // TEST_RIGHT_ASSOCIATIVE_OPERATOR

		#endif // TEST_BINARY_OPERATOR


		#if TEST_PARENTHESIS

			GATS_TEST_CASE(parser_single_parenthesis) {
				GATS_CHECK(parse_test(
					// Test: (2)
					TokenList({ make<LeftParenthesis>(), make<Integer>(2), make<RightParenthesis>() }),
					TokenList({ make<Integer>(2) })
					));
			}

			GATS_TEST_CASE(parser_double_parenthesis) {
				GATS_CHECK(parse_test(
					// Test: ((2))
					TokenList({ make<LeftParenthesis>(), make<LeftParenthesis>(), make<Integer>(2), make<RightParenthesis>(), make<RightParenthesis>() }),
					TokenList({ make<Integer>(2) })
					));
			}

			GATS_TEST_CASE(parser_multi_parenthesis) {
				GATS_CHECK(parse_test(
					// Test: (3+4)*5
					TokenList({ make<LeftParenthesis>(), make<Integer>(3), make<Addition>(), make<Integer>(4), make<RightParenthesis>(), make<Multiplication>(), make<Integer>(5) }),
					TokenList({ make<Integer>(3), make<Integer>(4), make<Addition>(), make<Integer>(5), make<Multiplication>() })
					));
			}

		#endif // TEST_PARENTHESIS

		#if TEST_FUNCTION && TEST_PARENTHESIS
			#if TEST_SINGLE_ARG

				GATS_TEST_CASE(parser_function_1_arg_abs) {
					GATS_CHECK(parse_test(
						// Test: abs(2)
						TokenList({ make<Abs>(), make<LeftParenthesis>(), make<Integer>(2), make<RightParenthesis>() }),
						TokenList({ make<Integer>(2), make<Abs>() })
						));
				}

			#endif // TEST_SINGLE_ARG

			#if TEST_MULTI_ARG

				GATS_TEST_CASE(parser_function_2_arg_max) {
					GATS_CHECK(parse_test(
						// Test: max(2,4)
						TokenList({ make<Max>(), make<LeftParenthesis>(), make<Integer>(2), make<ArgumentSeparator>(), make<Integer>(4), make<RightParenthesis>() }),
						TokenList({ make<Integer>(2), make<Integer>(4), make<Max>() })
						));
				}

				GATS_TEST_CASE(parser_function_2_arg_min) {
					GATS_CHECK(parse_test(
						// Test: min(2,4)
						TokenList({ make<Min>(), make<LeftParenthesis>(), make<Integer>(2), make<ArgumentSeparator>(), make<Integer>(4), make<RightParenthesis>() }),
						TokenList({ make<Integer>(2), make<Integer>(4), make<Min>() })
						));
				}

			#endif // TEST_MULTI_ARG
		#endif // TEST_FUNCTION && TEST_PARENTHESIS
	#endif // TEST_INTEGER



	#if TEST_REAL
		#if TEST_FUNCTION && TEST_PARENTHESIS
			#if TEST_SINGLE_ARG

				GATS_TEST_CASE(parser_function_1_arg_sin) {
					GATS_CHECK(parse_test(
						// Test: sin(2.0)
						TokenList({ make<Sin>(), make<LeftParenthesis>(), make<Real>(2.0), make<RightParenthesis>() }),
						TokenList({ make<Real>(2.0), make<Sin>() })
						));
				}

				GATS_TEST_CASE(parser_function_1_arg_cos) {
					GATS_CHECK(parse_test(
						// Test: cos(2.0)
						TokenList({ make<Cos>(), make<LeftParenthesis>(), make<Real>(2.0), make<RightParenthesis>() }),
						TokenList({ make<Real>(2.0), make<Cos>() })
						));
				}

				GATS_TEST_CASE(parser_function_1_arg_tan) {
					GATS_CHECK(parse_test(
						// Test: tan(2.0)
						TokenList({ make<Tan>(), make<LeftParenthesis>(), make<Real>(2.0), make<RightParenthesis>() }),
						TokenList({ make<Real>(2.0), make<Tan>() })
						));
				}

			#endif // TEST_SINGLE_ARG


			#if TEST_MULTI_ARG

				GATS_TEST_CASE(parser_function_2_arg_pow) {
					GATS_CHECK(parse_test(
						// Test: pow(2.3,3.4)
						TokenList({ make<Pow>(), make<LeftParenthesis>(), make<Real>(2.3), make<ArgumentSeparator>(), make<Real>(3.4), make<RightParenthesis>() }),
						TokenList({ make<Real>(2.3), make<Real>(3.4), make<Pow>() })
						));
				}

				GATS_TEST_CASE(parser_function_expression) {
					GATS_CHECK(parse_test(
						// Test: atan2(2.1,4.2)-10.3
						TokenList({ make<Arctan2>(), make<LeftParenthesis>(), make<Real>(2.1), make<ArgumentSeparator>(), make<Real>(4.2), make<RightParenthesis>(), make<Subtraction>(), make<Real>(10.3) }),
						TokenList({ make<Real>(2.1), make<Real>(4.2), make<Arctan2>(), make<Real>(10.3), make<Subtraction>() })
						));
				}

				GATS_TEST_CASE(parser_function_argument_expression) {
					GATS_CHECK(parse_test(
						// Test: atan2(2.1,4.2-10.3)
						TokenList({ make<Arctan2>(), make<LeftParenthesis>(), make<Real>(2.1), make<ArgumentSeparator>(), make<Real>(4.2), make<Subtraction>(), make<Real>(10.3), make<RightParenthesis>() }),
						TokenList({ make<Real>(2.1), make<Real>(4.2), make<Real>(10.3), make<Subtraction>(), make<Arctan2>() })
						));
				}

			#endif // TEST_MULTI_ARG
		#endif // TEST_FUNCTION
	#endif // TEST_REAL


	#if TEST_VARIABLE
		#if TEST_BINARY_OPERATOR

			GATS_TEST_CASE(parser_variable) {
				GATS_CHECK(parse_test(
					// Test: x=2
					TokenList({ make<Variable>(), make<Assignment>(), make<Integer>(2) }),
					TokenList({ make<Variable>(), make<Integer>(2), make<Assignment>() })
					));
			}

			GATS_TEST_CASE(parser_variable_variable) {
				GATS_CHECK(parse_test(
					// Test: x=y
					TokenList({ make<Variable>(), make<Assignment>(), make<Variable>() }),
					TokenList({ make<Variable>(), make<Variable>(), make<Assignment>() })
					));
			}

		#endif // TEST_BINARY_OPERATOR
	#endif // TEST_VARIABLE



#endif // TEST_PARSER

