/*! \file	ut_expression_evaluator.cpp
	\brief	ExpressionEvaluator unit test.
	\author	Garth Santor
	\date	2021-11-01
	\copyright	Garth Santor, Trinh Han

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2017.11.23
	Added Python-style power operator '**'.

Version 2014.11.21
	Improved round() - reduced float point conversion errors.

Version 2014.11.03
	Visual C++ 2013
	Removed bit operations.
	Added boost::multiprecision

Version 2012.11.16
	Added tests for Bit operators

Version 2012.11.15
	Added XNumericOverflow.
	Added tests for BinaryInteger, Binary <function>

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
#include "ut_test_phases.hpp"

#include <ee/expression_evaluator.hpp>
#include <ee/integer.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>
#include <ee/boolean.hpp>



#if TEST_REAL
	[[nodiscard]] Real::value_type round(Real::value_type x) {
		auto exp = pow(Real::value_type("10.0"), Real::value_type("990"));
		x *= exp;
		x += 0.5;
		x = floor(x);
		x /= exp;
		return x;
	}

	[[nodiscard]] Real::value_type round(Token::pointer_type const& v) {
		return round(value_of<Real>(v));
	}
#endif

// error cases
GATS_TEST_CASE( unknown_token ) {
	try {
		ExpressionEvaluator::result_type result = ExpressionEvaluator().evaluate("@");
		GATS_FAIL("Failed to throw exception");
	}
	catch( Tokenizer::XBadCharacter& e ) {
		std::string s( "Tokenizer::Bad character in expression." );
		std::string es( e.what() );
		GATS_CHECK( s == es );
		GATS_CHECK( e.expression() == "@" );
		GATS_CHECK( e.location() == 0 );
	}
	catch( ... ) {
		GATS_FAIL("Didn't catch Tokenizer::BadCharacter");
	}
}

GATS_TEST_CASE( empty_expression ) {
	try {
		ExpressionEvaluator::result_type result = ExpressionEvaluator().evaluate("");
		GATS_FAIL("Failed to throw exception");
	}
	catch( std::exception& e ) {
		GATS_CHECK( strcmp( e.what(), "Error: insufficient operands" ) == 0 );
	}
	catch( ... ) {
		GATS_FAIL( "Caught wrong exception" );
	}
}


#if TEST_INTEGER
	GATS_TEST_CASE(EE_integer_small) {
		auto result = ExpressionEvaluator().evaluate("1000");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("1000"));
	}
	GATS_TEST_CASE(EE_integer_large) {
		auto result = ExpressionEvaluator().evaluate("123456789012345678901234567890123456789012345678901234567890");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("123456789012345678901234567890123456789012345678901234567890"));
	}

	#if TEST_UNARY_OPERATOR
		GATS_TEST_CASE(EE_identity_integer) {
			auto result = ExpressionEvaluator().evaluate("+42");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("42"));
		}
		GATS_TEST_CASE(EE_negation_integer) {
			auto result = ExpressionEvaluator().evaluate("-42");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("-42"));
		}
		GATS_TEST_CASE(EE_factorial) {
			auto result = ExpressionEvaluator().evaluate("5!");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("120"));
			result = ExpressionEvaluator().evaluate("100!");
			GATS_CHECK(value_of<Integer>(result) ==
				Integer::value_type("93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000"));
		}
	#endif // TEST_UNARY_OPERATOR
	#if TEST_BINARY_OPERATOR
		GATS_TEST_CASE(EE_addition_integer) {
			auto result = ExpressionEvaluator().evaluate("2+3");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("5"));
		}
		GATS_TEST_CASE(EE_subtraction_integer) {
			auto result = ExpressionEvaluator().evaluate("2-3");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("-1"));
		}
		GATS_TEST_CASE(EE_multiplication_integer) {
			auto result = ExpressionEvaluator().evaluate("2*3");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("6"));
		}
		GATS_TEST_CASE(EE_division_integer) {
			auto result = ExpressionEvaluator().evaluate("21/3");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("7"));
			result = ExpressionEvaluator().evaluate("23/3");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("7"));
		}
		GATS_TEST_CASE(EE_modulo_integer) {
			auto result = ExpressionEvaluator().evaluate("21%3");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("0"));
			result = ExpressionEvaluator().evaluate("23%3");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
			#if TEST_NAMED_OPERATOR
				result = ExpressionEvaluator().evaluate("23 mod 3");
				GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
			#endif // TEST_NAMED_OPERATOR
		}
		GATS_TEST_CASE(EE_power_operator_integer) {
			auto result = ExpressionEvaluator().evaluate("5**2");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("25"));

			result = ExpressionEvaluator().evaluate("123**123");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("114374367934617190099880295228066276746218078451850229775887975052369504785666896446606568365201542169649974727730628842345343196581134895919942820874449837212099476648958359023796078549041949007807220625356526926729664064846685758382803707100766740220839267"));
		}
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_INTEGER

#if TEST_REAL
	GATS_TEST_CASE(EE_real_small) {
		auto result = ExpressionEvaluator().evaluate("1234.5678");
		GATS_CHECK(value_of<Real>(result) == Real::value_type("1234.5678"));
	}
	GATS_TEST_CASE(EE_real_large) {
		auto result = ExpressionEvaluator().evaluate("123456789012345678901234567890123456789012345678901234567890.123456789012345678901234567890123456789012345678901234567890");
		GATS_CHECK(value_of<Real>(result) == Real::value_type("123456789012345678901234567890123456789012345678901234567890.123456789012345678901234567890123456789012345678901234567890"));
	}
	GATS_TEST_CASE(EE_real_e) {
		auto result = ExpressionEvaluator().evaluate("e");
		GATS_CHECK(value_of<Real>(result) == boost::math::constants::e<Real::value_type>());
		result = ExpressionEvaluator().evaluate("E");
		GATS_CHECK(value_of<Real>(result) == boost::math::constants::e<Real::value_type>());
	}
	GATS_TEST_CASE(EE_real_pi) {
		auto result = ExpressionEvaluator().evaluate("pi");
		GATS_CHECK(value_of<Real>(result) == boost::math::constants::pi<Real::value_type>());
		result = ExpressionEvaluator().evaluate("Pi");
		GATS_CHECK(value_of<Real>(result) == boost::math::constants::pi<Real::value_type>());
		result = ExpressionEvaluator().evaluate("PI");
		GATS_CHECK(value_of<Real>(result) == boost::math::constants::pi<Real::value_type>());
	}
	#if TEST_UNARY_OPERATOR
		GATS_TEST_CASE(EE_identity_real) {
			auto result = ExpressionEvaluator().evaluate("+42.3");
			GATS_CHECK(value_of<Real>(result) == Real::value_type("42.3"));
		}
		GATS_TEST_CASE(EE_negation_real) {
			auto result = ExpressionEvaluator().evaluate("-42.3");
			GATS_CHECK(value_of<Real>(result) == Real::value_type("-42.3"));
		}
	#endif // TEST_UNARY_OPERATOR
	#if TEST_BINARY_OPERATOR
		GATS_TEST_CASE(EE_addition_real) {
			auto result = ExpressionEvaluator().evaluate("2.2+3.3");
			GATS_CHECK(value_of<Real>(result) == Real::value_type("5.5"));
		}
		GATS_TEST_CASE(EE_subtraction_real) {
			auto result = ExpressionEvaluator().evaluate("2.2-3.3");
			GATS_CHECK(value_of<Real>(result) == Real::value_type("-1.1"));
		}
		GATS_TEST_CASE(EE_multiplication_real) {
			auto result = ExpressionEvaluator().evaluate("2.5*3.5");
			GATS_CHECK(value_of<Real>(result) == Real::value_type("8.75"));
		}
		GATS_TEST_CASE(EE_division_real) {
			auto result = ExpressionEvaluator().evaluate("5.5/1.1");
			GATS_CHECK(round(result) == round(Real::value_type("5.0")));
		}
		GATS_TEST_CASE(EE_power_operator_real) {
			auto result = ExpressionEvaluator().evaluate("4.0 ** 0.5");
			GATS_CHECK(round(result) == round(Real::value_type("2.0")));
		}
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_REAL


#if TEST_MIXED && TEST_INTEGER && TEST_REAL
	#if TEST_BINARY_OPERATOR
		GATS_TEST_CASE(EE_mixed_addition) {
			auto result = ExpressionEvaluator().evaluate("1+3.3");
			GATS_CHECK(round(result) == round(Real::value_type("4.3")));
		}

		GATS_TEST_CASE(EE_mixed_division) {
			auto result = ExpressionEvaluator().evaluate("5/2.0");
			GATS_CHECK(round(result) == round(Real::value_type("2.5")));

			result = ExpressionEvaluator().evaluate("5.0/2");
			GATS_CHECK(round(result) == round(Real::value_type("2.5")));
		}


	#endif // TEST_BINARY_OPERATOR
#endif // TEST_MIXED && TEST_INTEGER && TEST_REAL

#if TEST_BOOLEAN
	GATS_TEST_CASE(EE_bool_true) {
		auto result = ExpressionEvaluator().evaluate("true");
		GATS_CHECK(value_of<Boolean>(result) == true);
		result = ExpressionEvaluator().evaluate("True");
		GATS_CHECK(value_of<Boolean>(result) == true);
		result = ExpressionEvaluator().evaluate("TRUE");
		GATS_CHECK(value_of<Boolean>(result) == true);
	}
	GATS_TEST_CASE(EE_bool_false) {
		auto result = ExpressionEvaluator().evaluate("false");
		GATS_CHECK(value_of<Boolean>(result) == false);
		result = ExpressionEvaluator().evaluate("False");
		GATS_CHECK(value_of<Boolean>(result) == false);
		result = ExpressionEvaluator().evaluate("FALSE");
		GATS_CHECK(value_of<Boolean>(result) == false);
	}

	#if TEST_BINARY_OPERATOR
		#if TEST_NAMED_OPERATOR
			GATS_TEST_CASE(EE_and) {
				auto result = ExpressionEvaluator().evaluate("true and true");
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("true and false");
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false and true");
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false and false");
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
			GATS_TEST_CASE(EE_or) {
				auto result = ExpressionEvaluator().evaluate("true or true");
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("true or false");
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("false or true");
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("false or false");
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
			GATS_TEST_CASE(EE_xor) {
				auto result = ExpressionEvaluator().evaluate("true xor true");
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("true xor false");
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("false xor true");
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("false xor false");
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
			GATS_TEST_CASE(EE_nand) {
				auto result = ExpressionEvaluator().evaluate("true nand true");
				GATS_CHECK(value_of<Boolean>(result) == !true);
				result = ExpressionEvaluator().evaluate("true nand false");
				GATS_CHECK(value_of<Boolean>(result) == !false);
				result = ExpressionEvaluator().evaluate("false nand true");
				GATS_CHECK(value_of<Boolean>(result) == !false);
				result = ExpressionEvaluator().evaluate("false nand false");
				GATS_CHECK(value_of<Boolean>(result) == !false);
			}
			GATS_TEST_CASE(EE_nor) {
				auto result = ExpressionEvaluator().evaluate("true nor true");
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("true nor false");
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false nor true");
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false nor false");
				GATS_CHECK(value_of<Boolean>(result) == true);
			}
			GATS_TEST_CASE(EE_xnor) {
				auto result = ExpressionEvaluator().evaluate("true xnor true");
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("true xnor false");
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false xnor true");
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = ExpressionEvaluator().evaluate("false xnor false");
				GATS_CHECK(value_of<Boolean>(result) == true);
			}
		#endif // TEST_NAMED_OPERATOR
		#if TEST_RELATIONAL_OPERATOR
			GATS_TEST_CASE(EE_equal_bool) {
				auto result = ExpressionEvaluator().evaluate("true == true");
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = ExpressionEvaluator().evaluate("false == true");
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
			GATS_TEST_CASE(EE_not_equal_bool) {
				auto result = ExpressionEvaluator().evaluate("true != true");
				GATS_CHECK(value_of<Boolean>(result) != true);
				result = ExpressionEvaluator().evaluate("false != true");
				GATS_CHECK(value_of<Boolean>(result) != false);
			}

			#if TEST_INTEGER
				GATS_TEST_CASE(EE_equal_integer) {
					auto result = ExpressionEvaluator().evaluate("1 == 1");
					GATS_CHECK(value_of<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("1 == 2");
					GATS_CHECK(value_of<Boolean>(result) == false);
				}
				GATS_TEST_CASE(EE_not_equal_integer) {
					auto result = ExpressionEvaluator().evaluate("1 != 1");
					GATS_CHECK(value_of<Boolean>(result) != true);
					result = ExpressionEvaluator().evaluate("1 != 2");
					GATS_CHECK(value_of<Boolean>(result) != false);
				}
				GATS_TEST_CASE(EE_less_integer) {
					auto result = ExpressionEvaluator().evaluate("1 < 1");
					GATS_CHECK(value_of<Boolean>(result) == false);
					result = ExpressionEvaluator().evaluate("1 < 2");
					GATS_CHECK(value_of<Boolean>(result) == true);
				}
				GATS_TEST_CASE(EE_less_equal_integer) {
					auto result = ExpressionEvaluator().evaluate("1 <= 1");
					GATS_CHECK(value_of<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("1 <= 2");
					GATS_CHECK(value_of<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("3 <= 2");
					GATS_CHECK(value_of<Boolean>(result) == false);
				}
				GATS_TEST_CASE(EE_greater_integer) {
					auto result = ExpressionEvaluator().evaluate("1 > 1");
					GATS_CHECK(value_of<Boolean>(result) == false);
					result = ExpressionEvaluator().evaluate("2 > 1");
					GATS_CHECK(value_of<Boolean>(result) == true);
				}
				GATS_TEST_CASE(EE_greater_equal_integer) {
					auto result = ExpressionEvaluator().evaluate("1 >= 1");
					GATS_CHECK(value_of<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("2 >= 1");
					GATS_CHECK(value_of<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("2 >= 3");
					GATS_CHECK(value_of<Boolean>(result) == false);
				}

			#endif // TEST_INTEGER
			#if TEST_REAL
				GATS_TEST_CASE(EE_equal_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 == 1.0");
					GATS_CHECK(value_of<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("1.0 == 2.0");
					GATS_CHECK(value_of<Boolean>(result) == false);
				}
				GATS_TEST_CASE(EE_not_equal_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 != 1.0");
					GATS_CHECK(value_of<Boolean>(result) != true);
					result = ExpressionEvaluator().evaluate("1.0 != 2.0");
					GATS_CHECK(value_of<Boolean>(result) != false);
				}
				GATS_TEST_CASE(EE_less_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 < 1.0");
					GATS_CHECK(value_of<Boolean>(result) == false);
					result = ExpressionEvaluator().evaluate("1.0 < 2.0");
					GATS_CHECK(value_of<Boolean>(result) == true);
				}
				GATS_TEST_CASE(EE_less_equal_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 <= 1.0");
					GATS_CHECK(value_of<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("1.0 <= 2.0");
					GATS_CHECK(value_of<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("2.01 <= 2.0");
					GATS_CHECK(value_of<Boolean>(result) == false);
				}
				GATS_TEST_CASE(EE_greater_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 > 1.0");
					GATS_CHECK(value_of<Boolean>(result) == false);
					result = ExpressionEvaluator().evaluate("2.0 > 1.0");
					GATS_CHECK(value_of<Boolean>(result) == true);
				}
				GATS_TEST_CASE(EE_greater_equal_real) {
					auto result = ExpressionEvaluator().evaluate("1.0 >= 1.0");
					GATS_CHECK(value_of<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("2.0 >= 1.0");
					GATS_CHECK(value_of<Boolean>(result) == true);
					result = ExpressionEvaluator().evaluate("1.99 >= 2.0");
					GATS_CHECK(value_of<Boolean>(result) == false);
				}

			#endif // TEST_REAL
		#endif // TEST_RELATIONAL_OPERATOR
	#endif // TEST_BINARY_OPERATOR
#endif // TEST_BOOLEAN



#if TEST_FUNCTION
	#if TEST_SINGLE_ARG
		#if TEST_INTEGER
			GATS_TEST_CASE(EE_abs_integer) {
				auto result = ExpressionEvaluator().evaluate("abs(4)");
				GATS_CHECK(value_of<Integer>(result) == 4);

				result = ExpressionEvaluator().evaluate("abs(-4)");
				GATS_CHECK(value_of<Integer>(result) == 4);
			}

		#endif // TEST_INTEGER
		#if TEST_REAL
			GATS_TEST_CASE(EE_real_trig) {
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
			}
			GATS_TEST_CASE(EE_abs) {
				auto result = ExpressionEvaluator().evaluate("abs(4.0)");
				GATS_CHECK(round(result) == round(Real::value_type("4.0")));

				result = ExpressionEvaluator().evaluate("abs(-4.0)");
				GATS_CHECK(round(result) == round(Real::value_type("4.0")));
			}
			GATS_TEST_CASE(EE_ceil) {
				auto result = ExpressionEvaluator().evaluate("ceil(4.3)");
				GATS_CHECK(round(result) == round(Real::value_type("5.0")));
				result = ExpressionEvaluator().evaluate("ceil(-4.3)");
				GATS_CHECK(round(result) == round(Real::value_type("-4.0")));
			}
			GATS_TEST_CASE(EE_exp) {
				auto result = ExpressionEvaluator().evaluate("exp(1.0)");
				GATS_CHECK(value_of<Real>(result) == exp(Real::value_type("1.0")));
			}
			GATS_TEST_CASE(EE_floor) {
				auto result = ExpressionEvaluator().evaluate("floor(4.3)");
				GATS_CHECK(round(result) == round(Real::value_type("4.0")));
				result = ExpressionEvaluator().evaluate("floor(-4.3)");
				GATS_CHECK(round(result) == round(Real::value_type("-5.0")));
			}
			GATS_TEST_CASE(test_lb) {
				auto result = ExpressionEvaluator().evaluate("lb(8.0)");
				GATS_CHECK(round(value_of<Real>(result)) == round(Real::value_type("3.0")));
			}
			GATS_TEST_CASE(test_ln) {
				auto result = ExpressionEvaluator().evaluate("ln(1.0)");
				GATS_CHECK(round(value_of<Real>(result)) == boost::multiprecision::log(Real::value_type("1.0")));
			}
			GATS_TEST_CASE(test_sqrt) {
				auto result = ExpressionEvaluator().evaluate("sqrt(16.0)");
				GATS_CHECK(round(value_of<Real>(result)) == round(Real::value_type("4.0")));
			}

		#endif // TEST_REAL
	#endif // TEST_SINGLE_ARG



#endif // TEST_FUNCTIONS

#if TEST_INTEGER && TEST_BINARY_OPERATOR && TEST_UNARY_OPERATOR
	GATS_TEST_CASE(EE_order_integer) {
		auto result = ExpressionEvaluator().evaluate("2*3+4");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("10"));
		result = ExpressionEvaluator().evaluate("21/3-5");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
		result = ExpressionEvaluator().evaluate("2+3*4");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("14"));
		result = ExpressionEvaluator().evaluate("2-32/4");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("-6"));

		#if TEST_RIGHT_ASSOCIATIVE_OPERATOR
			result = ExpressionEvaluator().evaluate("4**3**2");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("262144"));
		#endif // TEST_RIGHT_ASSOCIATIVE_OPERATOR

		result = ExpressionEvaluator().evaluate("4!!");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("620448401733239439360000"));
		result = ExpressionEvaluator().evaluate("2*4!-4");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("44"));

		result = ExpressionEvaluator().evaluate("20*3-32/4");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("52"));
		result = ExpressionEvaluator().evaluate("(21+5)/(7+6)");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
		result = ExpressionEvaluator().evaluate("(5+6*7)*(4+3)/(1+(5+6*7))");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("6"));
		result = ExpressionEvaluator().evaluate("(4 + 2 * 5) / (1 + 3 * 2)");
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
		#if TEST_NAMED_OPERATOR
			result = ExpressionEvaluator().evaluate("(15 mod 6)*3");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("9"));
		#endif // TEST_NAMED_OPERATOR
	}
#endif // TEST_INTEGER && TEST_BINARY_OPERATOR && TEST_UNARY_OPERATOR



#if TEST_REAL && TEST_BINARY_OPERATOR && TEST_UNARY_OPERATOR
	GATS_TEST_CASE(EE_order_real) {
		auto result = ExpressionEvaluator().evaluate("1.0/(1.0/32.0+1.0/48.0)");
		auto x = round(result);
		GATS_CHECK(x == round(Real::value_type("19.2")));
		#if TEST_FUNCTION && TEST_SINGLE_ARG
			result = ExpressionEvaluator().evaluate("sin(1.0)**2+cos(1.0)**2");
			GATS_CHECK(round(result) == round(Real::value_type("1.0")));
		#endif //TEST_FUNCTION && TEST_SINGLE_ARG
	}
#endif // TEST_REAL && TEST_BINARY_OPERATOR && TEST_UNARY_OPERATOR




#if TEST_BOOLEAN && TEST_UNARY_OPERATOR && TEST_BINARY_OPERATOR && TEST_NAMED_OPERATOR
	GATS_TEST_CASE(EE_order_bool) {
	ExpressionEvaluator ee;
	auto result = ee.evaluate("true and not true");
	GATS_CHECK(value_of<Boolean>(result) == false);

	result = ee.evaluate("true and false == not(not true or not false)");
	GATS_CHECK(value_of<Boolean>(result) == true);
}
#endif // TEST_BOOLEAN && TEST_UNARY_OPERATOR && TEST_BINARY_OPERATOR && TEST_NAMED_OPERATOR


#if TEST_BOOLEAN && TEST_RELATIONAL_OPERATOR && TEST_INTEGER && TEST_BINARY_OPERATOR && TEST_NAMED_OPERATOR
	GATS_TEST_CASE(EE_relational) {
		ExpressionEvaluator ee;
		auto result = ee.evaluate("4 < 5 and 5 == 5");
		GATS_CHECK(value_of<Boolean>(result) == true);
	}
#endif // TEST_BOOLEAN && TEST_RELATIONAL_OPERATOR && TEST_INTEGER && TEST_BINARY_OPERATOR && TEST_NAMED_OPERATOR


#if TEST_VARIABLE && TEST_INTEGER && TEST_BINARY_OPERATOR

	#if TEST_MIXED
		GATS_TEST_CASE(EE_variable_mixed) {
			ExpressionEvaluator ee;
			auto result = ee.evaluate("x=12");
			result = ee.evaluate("y=12.0");
			result = ee.evaluate("x * 3 / (4+x)");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));

			result = ee.evaluate("y*3/(4+y)");
			GATS_CHECK(value_of<Real>(result) == Real::value_type("2.25"));
		}
	#endif // TEST_MIXED

	#if TEST_RESULT
		GATS_TEST_CASE(express_result) {
			ExpressionEvaluator ee;
			auto result = ee.evaluate("1+1");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("2"));
			result = ee.evaluate("2+2");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("4"));

			result = ee.evaluate("result(1)*result(2)");
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type("8"));
		}
	#endif // TEST_RESULT
#endif // TEST_VARIABLE

