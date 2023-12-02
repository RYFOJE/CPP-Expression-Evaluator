/*!	\file	ut_tokenizer_main.cpp
	\brief	Test the tokenizer
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Tokenizer Unit Test for Expression Evaluator Project.
=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2017.11.23
	Updated to Visual C++ 15.4.4
	New hierarchy tests.
	Added Python-style power operator '**'.

Version 2015.11.05
	Visual Studio 2015
	TEST_xxxx macros

Version 2014.10.29
	Updated to Visual C++ 12
	Uses boost::multiprecision library.

Version 2012.11.16
	Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

Version 2012.11.15
	Added BinaryInteger tests.
	Added Binary function test.
	Added XNumericOverflow test.

Version 2012.11.13
	C++ 11 cleanup.

Version 2009.11.25
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
#include <ee/tokenizer.hpp>
#include <ee/boolean.hpp>
#include <ee/function.hpp>
#include <ee/integer.hpp>
#include <ee/operator.hpp>
#include <ee/pseudo_operation.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>

// std
#include <string>
using namespace std;

#include "ut_test_phases.hpp"


#if TEST_TOKENIZER

#pragma region test_support
// ==============================================================================
// TEST CASE SUPPORT
// ==============================================================================

/** Performs tokenizer test case

	1. Tokenizes the expression.
	2. Checks that returned token list matches correct list.

	@param expression [in] The expression to tokenize.
	*/
bool test(Tokenizer::string_type const& expression, TokenList const& correct) {
	Tokenizer tokenizer;
	TokenList tokens = tokenizer.tokenize(expression);
	bool ok = true;
	ok = ok && (correct.size() == tokens.size());
	size_t n = std::min(correct.size(), tokens.size());
	for (size_t i = 0; i < n; ++i) {
		bool match = correct[i] == tokens[i];
		GATS_CHECK_MESSAGE(match, "Token [" << i << "] = " << tokens[i]->str() << " should be " << correct[i]->str());
		ok = ok && match;
	}
	return ok;
};
#pragma endregion // test_support


#pragma region trivial_cases
// ==============================================================================
// Trivial Test Cases
// ==============================================================================
GATS_TEST_CASE(lexer_no_token) {
	GATS_CHECK(test("", TokenList({	})));
}


GATS_TEST_CASE(unknown_token) {
	try {
		Tokenizer tkn;
		TokenList tl = tkn.tokenize("@");
		GATS_FAIL("XBadCharacter exception not thrown");
	}
	catch (Tokenizer::XBadCharacter& e) {
		string s("Tokenizer::Bad character in expression.");
		string es(e.what());
		GATS_CHECK(s == es);
		GATS_CHECK(e.expression() == "@");
		GATS_CHECK(e.location() == 0);
	}
}
#pragma endregion


#if TEST_INTEGER
	// ==============================================================================
	// Integer Test Cases
	// ==============================================================================
	GATS_TEST_CASE(lexer_single_integer_1234) {
		GATS_CHECK(test("1234", TokenList({ make<Integer>(1234) })));
	}

	GATS_TEST_CASE(lexer_single_integer_0) {
		GATS_CHECK(test("0", TokenList({ make<Integer>(0) })));
	}

	GATS_TEST_CASE(lexer_single_integer_big) {
		GATS_CHECK(test("1234567890123456789012345678901234567890", TokenList({ make<Integer>(Integer::value_type("1234567890123456789012345678901234567890")) })));
	}

	GATS_TEST_CASE(lexer_two_integers) {
		GATS_CHECK(test("23 42", TokenList({ make<Integer>(23), make<Integer>(42) })));
	}


	#if TEST_UNARY_OPERATOR
		GATS_TEST_CASE(lexer_operator_identity) {
			GATS_CHECK(test("++2", TokenList({
				make<Identity>(), make<Identity>(), make<Integer>(2)
			})));
		}

		GATS_TEST_CASE(lexer_operator_negation) {
			GATS_CHECK(test("--2", TokenList({
				make<Negation>(), make<Negation>(), make<Integer>(2)
			})));
		}

		GATS_TEST_CASE(lexer_operator_factorial) {
			GATS_CHECK(test("42!", TokenList({ make<Integer>(42), make<Factorial>() })));
		}
	#endif // TEST_UNARY_OPERATOR


	#if TEST_BINARY_OPERATOR
		GATS_TEST_CASE(lexer_single_operator_multiplication) {
			GATS_CHECK(test("1*2", TokenList({
				make<Integer>(1), make<Multiplication>(), make<Integer>(2)
			})));
		}
		GATS_TEST_CASE(lexer_single_operator_division) {
			GATS_CHECK(test("1/2", TokenList({
				make<Integer>(1), make<Division>(), make<Integer>(2)
			})));
		}
		GATS_TEST_CASE(lexer_single_operator_modulus) {
			GATS_CHECK(test("1%2", TokenList({
				make<Integer>(1), make<Modulus>(), make<Integer>(2)
			})));
		}
		GATS_TEST_CASE(lexer_single_operator_addition) {
			GATS_CHECK(test("1+2", TokenList({
				make<Integer>(1), make<Addition>(), make<Integer>(2)
			})));
		}
		GATS_TEST_CASE(lexer_single_operator_subtraction) {
			GATS_CHECK(test("1-2", TokenList({
				make<Integer>(1), make<Subtraction>(), make<Integer>(2)
			})));
		}
		GATS_TEST_CASE(lexer_single_operator_power) {
			GATS_CHECK(test("1**2", TokenList({
				make<Integer>(1), make<Power>(), make<Integer>(2)
			})));
		}
		GATS_TEST_CASE(lexer_combined_1) {
			GATS_CHECK(test("1+2*3/4%5", TokenList({
				make<Integer>(1),
				make<Addition>(),
				make<Integer>(2),
				make<Multiplication>(),
				make<Integer>(3),
				make<Division>(),
				make<Integer>(4),
				make<Modulus>(),
				make<Integer>(5)
			})));
		}

		#if TEST_NAMED_OPERATOR
			GATS_TEST_CASE(lexer_single_operator_modulus_name) {
				GATS_CHECK(test("1 mod 2", TokenList({
					make<Integer>(1), make<Modulus>(), make<Integer>(2)
				})));
			}
		#endif // TEST_NAMED_OPERATOR
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_INTEGER





#if TEST_PARENTHESIS
	#if TEST_INTEGER
		GATS_TEST_CASE(lexer_single_operator_parenthesis) {
			GATS_CHECK(test("(42)", TokenList({
				make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
			})));
		}
	#endif // TEST_INTEGER

	#if TEST_UNARY_OPERATOR
		GATS_TEST_CASE(lexer_operator_identity_parenthesis) {
			GATS_CHECK(test("+(++2", TokenList({
				make<Identity>(), make<LeftParenthesis>(), make<Identity>(), make<Identity>(), make<Integer>(2)
			})));
		}

		GATS_TEST_CASE(lexer_operator_negation_parenthesis) {
			GATS_CHECK(test("-(--2", TokenList({
				make<Negation>(), make<LeftParenthesis>(), make<Negation>(), make<Negation>(), make<Integer>(2)
			})));
		}
	#endif // TEST_UNARY_OPERATOR

	#if TEST_BINARY_OPERATOR
		GATS_TEST_CASE(lexer_combined_2) {
			GATS_CHECK(test("-(-3--4)-5", TokenList({
				make<Negation>(),
				make<LeftParenthesis>(),
				make<Negation>(),
				make<Integer>(3),
				make<Subtraction>(),
				make<Negation>(),
				make<Integer>(4),
				make<RightParenthesis>(),
				make<Subtraction>(),
				make<Integer>(5)
			})));
		}
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_PARENTHESIS



#if TEST_FUNCTION && TEST_INTEGER
	GATS_TEST_CASE(lexer_single_operator_separator) {
		GATS_CHECK(test("1,2", TokenList({
			make<Integer>(1), make<ArgumentSeparator>(), make<Integer>(2)
		})));
	}

	GATS_TEST_CASE(lexer_func_abs) {
		GATS_CHECK(test("abs(42)", TokenList({
			make<Abs>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
		})));
	}
#endif // TEST_FUNCTION




#if TEST_REAL
	// ==============================================================================
	// Real Test Cases
	// ==============================================================================
	GATS_TEST_CASE(lexer_single_real) {
		GATS_CHECK(test("1234.56", TokenList({ make<Real>(Real::value_type("1234.56")) })));
	}

	GATS_TEST_CASE(lexer_single_real_small) {
		GATS_CHECK(test("0.000000000000000000000000000000000000004", TokenList({ make<Real>(Real::value_type("0.000000000000000000000000000000000000004")) })));
	}

	GATS_TEST_CASE(lexer_single_real_big) {
		GATS_CHECK(test("1234567890123456789012345678901234567890.1234567890123456789012345678901234567890",
			TokenList({ make<Real>(Real::value_type("1234567890123456789012345678901234567890.1234567890123456789012345678901234567890")) })));
	}


	GATS_TEST_CASE(lexer_single_pi) { 
		GATS_CHECK(test("pi", TokenList({ make<Pi>() }))); 
	}
	GATS_TEST_CASE(lexer_single_Pi) { 
		GATS_CHECK(test("Pi", TokenList({ make<Pi>() }))); 
	}
	GATS_TEST_CASE(lexer_single_PI) { 
		GATS_CHECK(test("PI", TokenList({ make<Pi>() }))); 
	}
	GATS_TEST_CASE(lexer_single_e) { 
		GATS_CHECK(test("e", TokenList({ make<E>() }))); 
	}
	GATS_TEST_CASE(lexer_single_E) { 
		GATS_CHECK(test("E", TokenList({ make<E>() }))); 
	}

	#if TEST_FUNCTION
		#if TEST_SINGLE_ARG
			GATS_TEST_CASE(lexer_func_arccos) {
				GATS_CHECK(test("arccos(42)", TokenList({
					make<Arccos>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_arcsin) {
				GATS_CHECK(test("arcsin(42)", TokenList({
					make<Arcsin>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_arctan) {
				GATS_CHECK(test("arctan(42)", TokenList({
					make<Arctan>(), make<LeftParenthesis>(), make<Integer>(42), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_ceil) {
				GATS_CHECK(test("ceil(4.2)", TokenList({
					make<Ceil>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_cos) {
				GATS_CHECK(test("cos(4.2)", TokenList({
					make<Cos>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_exp) {
				GATS_CHECK(test("exp(4.2)", TokenList({
					make<Exp>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_floor) {
				GATS_CHECK(test("floor(4.2)", TokenList({
					make<Floor>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_lb) {
				GATS_CHECK(test("lb(4.2)", TokenList({
					make<Lb>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_ln) {
				GATS_CHECK(test("ln(4.2)", TokenList({
					make<Ln>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_log) {
				GATS_CHECK(test("log(4.2)", TokenList({
					make<Log>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_sin) {
				GATS_CHECK(test("sin(4.2)", TokenList({
					make<Sin>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_sqrt) {
				GATS_CHECK(test("sqrt(4.2)", TokenList({
					make<Sqrt>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_tan) {
				GATS_CHECK(test("tan(4.2)", TokenList({
					make<Tan>(), make<LeftParenthesis>(), make<Real>(Real::value_type("4.2")), make<RightParenthesis>()
				})));
			}
		#endif // TEST_SINGLE_ARG

		#if TEST_MULTI_ARG
			GATS_TEST_CASE(lexer_func_arctan2) {
				GATS_CHECK(test("arctan2(42,123.3)", TokenList({
					make<Arctan2>(), make<LeftParenthesis>(), make<Integer>(42), make<ArgumentSeparator>(),
					make<Real>(Real::value_type("123.3")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_max) {
				GATS_CHECK(test("max(42,123.3)", TokenList({
					make<Max>(), make<LeftParenthesis>(), make<Integer>(42), make<ArgumentSeparator>(),
					make<Real>(Real::value_type("123.3")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_min) {
				GATS_CHECK(test("min(42,123.3)", TokenList({
					make<Min>(), make<LeftParenthesis>(), make<Integer>(42), make<ArgumentSeparator>(),
					make<Real>(Real::value_type("123.3")), make<RightParenthesis>()
				})));
			}
			GATS_TEST_CASE(lexer_func_pow) {
				GATS_CHECK(test("pow(42,123.3)", TokenList({
					make<Pow>(), make<LeftParenthesis>(), make<Integer>(42), make<ArgumentSeparator>(),
					make<Real>(Real::value_type("123.3")), make<RightParenthesis>()
				})));
			}
		#endif // TEST_MULTI_ARG
	#endif // TEST_FUNCTION
#endif // TEST_REAL


#if TEST_BOOLEAN
	// ==============================================================================
	// Boolean Test Cases
	// ==============================================================================
	GATS_TEST_CASE(lexer_single_true) { GATS_CHECK(test("true", TokenList({ make<Boolean>(true) }))); }
	GATS_TEST_CASE(lexer_single_false) { GATS_CHECK(test("false", TokenList({ make<Boolean>(false) }))); }


	#if TEST_UNARY_OPERATOR
		GATS_TEST_CASE(lexer_bool_operator_not) {
			GATS_CHECK(test("not false", TokenList({
				make<Not>(), make<False>()
			})));
		}
	#endif // TEST_UNARY_OPERATOR


	#if TEST_BINARY_OPERATOR
		GATS_TEST_CASE(lexer_bool_operator_and) {
			GATS_CHECK(test("true and false", TokenList({
				make<True>(), make<And>(), make<False>()
			})));
		}

		GATS_TEST_CASE(lexer_bool_operator_or) {
			GATS_CHECK(test("true or false", TokenList({
				make<True>(), make<Or>(), make<False>()
			})));
		}

		GATS_TEST_CASE(lexer_bool_operator_xor) {
			GATS_CHECK(test("true xor false", TokenList({
				make<True>(), make<Xor>(), make<False>()
			})));
		}

		GATS_TEST_CASE(lexer_bool_operator_nand) {
			GATS_CHECK(test("true nand false", TokenList({
				make<True>(), make<Nand>(), make<False>()
			})));
		}

		GATS_TEST_CASE(lexer_bool_operator_nor) {
			GATS_CHECK(test("true nor false", TokenList({
				make<True>(), make<Nor>(), make<False>()
			})));
		}

		GATS_TEST_CASE(lexer_bool_operator_xnor) {
			GATS_CHECK(test("true xnor false", TokenList({
				make<True>(), make<Xnor>(), make<False>()
			})));
		}


		#if TEST_RELATIONAL_OPERATOR && TEST_INTEGER
			GATS_TEST_CASE(lexer_bool_operator_equality) {
				GATS_CHECK(test("3 == 2", TokenList({
					make<Integer>(3), make<Equality>(), make<Integer>(2)
				})));
			}

			GATS_TEST_CASE(lexer_bool_operator_inequality) {
				GATS_CHECK(test("3 != 2", TokenList({
					make<Integer>(3), make<Inequality>(), make<Integer>(2)
				})));
			}

			GATS_TEST_CASE(lexer_bool_operator_greater) {
				GATS_CHECK(test("3 > 2", TokenList({
					make<Integer>(3), make<Greater>(), make<Integer>(2)
				})));
			}
			GATS_TEST_CASE(lexer_bool_operator_greaterequal) {
				GATS_CHECK(test("3 >= 2", TokenList({
					make<Integer>(3), make<GreaterEqual>(), make<Integer>(2)
				})));
			}
			GATS_TEST_CASE(lexer_bool_operator_less) {
				GATS_CHECK(test("3 < 2", TokenList({
					make<Integer>(3), make<Less>(), make<Integer>(2)
				})));
			}
			GATS_TEST_CASE(lexer_bool_operator_lessequal) {
				GATS_CHECK(test("3 <= 2", TokenList({
					make<Integer>(3), make<LessEqual>(), make<Integer>(2)
				})));
			}
		#endif // TEST_RELATIONAL_OPERATOR && TEST_INTEGER
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_BOOLEAN


#if TEST_VARIABLE
	GATS_TEST_CASE(lexer_single_Variable) {
		GATS_CHECK(test("variable", TokenList({ make<Variable>() })));
	}

	GATS_TEST_CASE(def_ctor_variable) {
		Variable::pointer_type p(new Variable);
		GATS_CHECK(p->value() == 0);
		GATS_CHECK(p->str() == "Variable: null");
	}

	GATS_TEST_CASE(variable_match) {
		Tokenizer tkr;
		TokenList tl = tkr.tokenize("a");
		Token::pointer_type p = tl.front();
		tl.clear();
		tl = tkr.tokenize("a");
		GATS_CHECK(p.get() == tl.front().get());
	}


	#if TEST_BINARY_OPERATOR && TEST_INTEGER
		GATS_TEST_CASE(lexer_single_operator_assignment) {
			GATS_CHECK(test("a=2", TokenList({
				make<Variable>(), make<Assignment>(), make<Integer>(2)
			})));
		}
	#endif // TEST_BINARY_OPERATOR && TEST_INTEGER

	#if TEST_FUNCTION && TEST_SINGLE_ARG
		GATS_TEST_CASE(lexer_func_result) {
			GATS_CHECK(test("result(4)", TokenList({
				make<Result>(), make<LeftParenthesis>(), make<Integer>(4), make<RightParenthesis>()
			})));
		}
	#endif // TEST_FUNCTION && TEST_SINGLE_ARG
#endif // TEST_VARIABLE

#endif // TEST_TOKENIZER
