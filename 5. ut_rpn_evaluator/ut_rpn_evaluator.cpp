/*! \file	ut_rpn_evaluator.cpp
	\brief	RPN evaluator unit test.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Reverse-Polish Evaluator unit test for Expression Evaluator Project.

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

Version 2014.11.21
	Improved round() - reduced float point conversion errors.

Version 2014.10.31
	Visual Studio 2013
	Removed bit operations
	Added multiprecision.

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

#include <ee/RPNEvaluator.hpp>
#include <ee/boolean.hpp>
#include <ee/integer.hpp>
#include <ee/function.hpp>
#include <ee/operator.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>

#include <boost/math/constants/constants.hpp>

#include "ut_test_phases.hpp"


#if TEST_REAL
Real::value_type round(Real::value_type x) {
	auto exp = pow(Real::value_type("10.0"), Real::value_type("990"));
	x *= exp;
	x += 0.5;
	x = floor(x);
	x /= exp;
	return x;
}

Real::value_type round(Token::pointer_type const& v) {
	return round(value_of<Real>(v));
}
#endif


GATS_TEST_CASE(no_operand) {
	try {
		auto t = RPNEvaluator().evaluate(TokenList());
		GATS_FAIL("Failed to throw exception");
	}
	catch( std::exception& e ) {
		GATS_CHECK( strcmp( e.what(), "Error: insufficient operands" ) == 0 );
	}
}


#if TEST_INTEGER
	GATS_TEST_CASE(too_many_operand) {
		try {
			TokenList tl = { make<Integer>(3), make<Integer>(4) };
			auto t = RPNEvaluator().evaluate(tl);
			GATS_FAIL("Failed to throw exception");
		}
		catch( std::exception& e ) {
			GATS_CHECK( strcmp( e.what(), "Error: too many operands" ) == 0 );
		}
	}
#endif



#if TEST_VARIABLE
	GATS_TEST_CASE(unitialized_single_variable) {
		auto result = RPNEvaluator().evaluate({ make<Variable>() });

		GATS_CHECK(is<Variable>(result));
		Variable::pointer_type v = convert<Variable>(result);
		GATS_CHECK(v->value() == nullptr);
	}
	GATS_TEST_CASE(unitialized_variable_expression) {
		try {
			auto result = RPNEvaluator().evaluate({ make<Variable>(), make<Negation>() });
			GATS_FAIL("Failed to throw exception");
		}
		catch (std::exception& e) {
			GATS_CHECK(strcmp(e.what(), "Error: variable not initialized") == 0);
		}
	}
#endif


// literals
#if TEST_INTEGER
	GATS_TEST_CASE(Integer_3){
		auto result = RPNEvaluator().evaluate({ make<Integer>(3) });
		GATS_CHECK(value_of<Integer>(result) == Integer::value_type(3));
	}
#endif
#if TEST_REAL
	GATS_TEST_CASE(Real_3_14){
		auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3.14")) });
		GATS_CHECK(value_of<Real>(result) == Real::value_type("3.14"));
	}
#endif



// Constants
#if TEST_BOOLEAN
	GATS_TEST_CASE(constant_true) {
		auto result = RPNEvaluator().evaluate({ make<True>() });
		GATS_CHECK(value_of<True>(result) == true);
	}
	GATS_TEST_CASE(constant_false) {
		auto result = RPNEvaluator().evaluate({ make<False>() });
		GATS_CHECK(value_of<False>(result) == false);
	}
#endif
#if TEST_REAL
	GATS_TEST_CASE(constant_Pi) {
		auto result = RPNEvaluator().evaluate({ make<Pi>() });
		GATS_CHECK(value_of<Real>(result) == boost::math::constants::pi<Real::value_type>());
	}
	GATS_TEST_CASE(constant_E) {
		auto result = RPNEvaluator().evaluate({ make<E>() });
		GATS_CHECK(value_of<Real>(result) == boost::math::constants::e<Real::value_type>());
	}
#endif

// Identity
#if TEST_UNARY_OPERATOR
	#if TEST_INTEGER
		GATS_TEST_CASE(identity_test_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Identity>() });
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type(3));
		}
	#endif
	#if TEST_REAL
		GATS_TEST_CASE(identity_test_Real) {
			auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3")), make<Identity>() });
			GATS_CHECK(value_of<Real>(result) == Real::value_type("3.0"));
		}
	#endif


	// Negation
	#if TEST_INTEGER
		GATS_TEST_CASE(negation_test_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Negation>() });
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type(-3));
		}
	#endif
	#if TEST_REAL
		GATS_TEST_CASE(negation_test_Real) {
			auto result = RPNEvaluator().evaluate({ make<Real>(3), make<Negation>() });
			GATS_CHECK(value_of<Real>(result) == Real::value_type("-3.0"));
		}
	#endif


	// Factorial
	#if TEST_INTEGER
		GATS_TEST_CASE(factorial_test_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(5), make<Factorial>() });
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type(120));
		}
	#endif


	// Logical not
	#if TEST_BOOLEAN
		GATS_TEST_CASE(not_test_Boolean) {
			auto result = RPNEvaluator().evaluate({ make<Boolean>(true), make<Not>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
			result = RPNEvaluator().evaluate({ make<Boolean>(false), make<Not>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
		}
	#endif
#endif // TEST_UNARY_OPERATOR


#if TEST_BINARY_OPERATOR
	#if TEST_INTEGER
		GATS_TEST_CASE(test_multiply_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Integer>(4), make<Multiplication>() });
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type(12));
		}
		GATS_TEST_CASE(test_divide_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(45), make<Integer>(3), make<Division>() });
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type(15));
		}
		GATS_TEST_CASE(test_addition_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Integer>(4), make<Addition>() });
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type(7));
		}
		GATS_TEST_CASE(test_subtraction_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Integer>(4), make<Subtraction>() });
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type(-1));
		}
		GATS_TEST_CASE(test_modulus_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(12), make<Integer>(5), make<Modulus>() });
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type(2));
		}
		GATS_TEST_CASE(test_power_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Integer>(4), make<Power>() });
			GATS_CHECK(value_of<Integer>(result) == Integer::value_type(81));
		}
		#if TEST_VARIABLE
			GATS_TEST_CASE( assignment_test ) {
				auto result = RPNEvaluator().evaluate({ make<Variable>(), make<Integer>(4), make<Assignment>() });

				GATS_CHECK(is<Variable>(result));
				Variable::pointer_type v = convert<Variable>(result);
				GATS_CHECK( is<Integer>( v->value() ) );
				Integer::pointer_type i = convert<Integer>( v->value() );
				GATS_CHECK( i->value() == 4 );
			}
		#endif
	#endif  // TEST_INTEGER

	#if TEST_REAL
		GATS_TEST_CASE(test_multiply_Real) {
			auto result = RPNEvaluator().evaluate({ make<Real>(3.0), make<Real>(4.0), make<Multiplication>() });
			GATS_CHECK(value_of<Real>(result) == Real::value_type("12.0"));
		}
		GATS_TEST_CASE(test_divide_Real) {
			auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("45.0")), make<Real>(Real::value_type("3.0")), make<Division>() });
			GATS_CHECK(round(result) == round(Real::value_type("15.0")));
		}
		GATS_TEST_CASE(test_addition_Real) {
			auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3.0")), make<Real>(Real::value_type("4.0")), make<Addition>() });
			GATS_CHECK(round(result) == round(Real::value_type("7.0")));
		}
		GATS_TEST_CASE(test_subtraction_Real) {
			auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3.0")), make<Real>(Real::value_type("4.0")), make<Subtraction>() });
			GATS_CHECK(round(result) == round(Real::value_type("-1.0")));
		}
		GATS_TEST_CASE(test_power_Real) {
			auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3.0")), make<Real>(Real::value_type("4.0")), make<Power>() });
			GATS_CHECK(round(result) == round(Real::value_type("81")));
		}
	#endif	// TEST_REAL

	#if TEST_MIXED
		GATS_TEST_CASE(test_multiply_Integer_Real) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Real>(4.0), make<Multiplication>() });
			GATS_CHECK(value_of<Real>(result) == Real::value_type("12.0"));
		}
		GATS_TEST_CASE(test_multiply_Real_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Real>(3.0), make<Integer>(4), make<Multiplication>() });
			GATS_CHECK(value_of<Real>(result) == Real::value_type("12.0"));
		}
		GATS_TEST_CASE(test_divide_Integer_Real) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Real>(6.0), make<Division>() });
			GATS_CHECK(round(result) == round(Real::value_type("0.5")));
		}
		GATS_TEST_CASE(test_divide_Real_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Real>(3.0), make<Integer>(6), make<Division>() });
			GATS_CHECK(round(result) == round(Real::value_type("0.5")));
		}
		GATS_TEST_CASE(test_addition_Integer_Real) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Real>(Real::value_type("4.2")), make<Addition>() });
			GATS_CHECK(round(result) == round(Real::value_type("7.2")));
		}
		GATS_TEST_CASE(test_addition_Real_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("3.3")), make<Integer>(4), make<Addition>() });
			GATS_CHECK(round(result) == round(Real::value_type("7.3")));
		}
		GATS_TEST_CASE(test_subtraction_Integer_Real) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(3), make<Real>(Real::value_type("0.5")), make<Subtraction>() });
			GATS_CHECK(round(result) == round(Real::value_type("2.5")));
		}
		GATS_TEST_CASE(test_subtraction_Real_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("4.25")), make<Integer>(4), make<Subtraction>() });
			GATS_CHECK(round(result) == round(Real::value_type("0.25")));
		}
		GATS_TEST_CASE(test_neg_power_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(-4), make<Power>() });
			GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0") / Real::value_type("16.0"));
		}
		GATS_TEST_CASE(test_power_Integer_Real) {
			auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("3.0")), make<Power>() });
			GATS_CHECK(round(result) == round(Real::value_type("8.0")));
		}
		GATS_TEST_CASE(test_power_Real_Integer) {
			auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Integer>(3), make<Power>() });
			GATS_CHECK(round(result) == round(Real::value_type("8.0")));
		}

		#if TEST_VARIABLE
			GATS_TEST_CASE( assignment_to_constant_fail ) {
				try {
					auto t = RPNEvaluator().evaluate({ make<Pi>(), make<Integer>(4), make<Assignment>() });
					GATS_FAIL( "Failed to throw an 'assignment to a non-variable' exception." );
				}
				catch( std::exception const& ex ) {
					GATS_CHECK( std::string( ex.what() ) == std::string("Error: assignment to a non-variable.") );
				}
			}
		#endif // TEST_VARIABLE
	#endif	// TEST_MIXED

	#if TEST_BOOLEAN
		GATS_TEST_CASE(test_and) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<And>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<And>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<And>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
			result = RPNEvaluator().evaluate({ make<False>(), make<False>(), make<And>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
		}
		GATS_TEST_CASE(test_nand) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Nand>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
			result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<Nand>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Nand>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<False>(), make<False>(), make<Nand>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
		}
		GATS_TEST_CASE(test_nor) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Nor>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
			result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<Nor>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Nor>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
			result = RPNEvaluator().evaluate({ make<False>(), make<False>(), make<Nor>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
		}
		GATS_TEST_CASE(test_or) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Or>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<Or>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Or>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<False>(), make<False>(), make<Or>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
		}
		GATS_TEST_CASE(test_xor) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Xor>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
			result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<Xor>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Xor>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<False>(), make<False>(), make<Xor>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
		}
		GATS_TEST_CASE(test_equality_boolean) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Equality>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Equality>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
		}
		GATS_TEST_CASE(test_inequality_boolean) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Inequality>() });
			GATS_CHECK(value_of<Boolean>(result) != true);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Inequality>() });
			GATS_CHECK(value_of<Boolean>(result) != false);
		}
		GATS_TEST_CASE(test_greater_boolean) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Greater>() });
			GATS_CHECK(value_of<Boolean>(result) != true);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Greater>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
		}
		GATS_TEST_CASE(test_greater_equal_boolean) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<GreaterEqual>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<GreaterEqual>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
			result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<GreaterEqual>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
		}
		GATS_TEST_CASE(test_less_boolean) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<Less>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<Less>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<Less>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
		}
		GATS_TEST_CASE(test_less_equal_boolean) {
			auto result = RPNEvaluator().evaluate({ make<True>(), make<True>(), make<LessEqual>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<False>(), make<True>(), make<LessEqual>() });
			GATS_CHECK(value_of<Boolean>(result) == true);
			result = RPNEvaluator().evaluate({ make<True>(), make<False>(), make<LessEqual>() });
			GATS_CHECK(value_of<Boolean>(result) == false);
		}
		#if TEST_INTEGER
			// Equality
			GATS_TEST_CASE(test_equality_integer) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<Equality>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<Equality>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
			GATS_TEST_CASE(test_inequality_integer) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<Inequality>() });
				GATS_CHECK(value_of<Boolean>(result) != true);
				result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<Inequality>() });
				GATS_CHECK(value_of<Boolean>(result) != false);
			}
			GATS_TEST_CASE(test_greater_integer) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<Greater>() });
				GATS_CHECK(value_of<Boolean>(result) != true);
				result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<Greater>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
			GATS_TEST_CASE(test_greater_equal_integer) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<GreaterEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<GreaterEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(0), make<GreaterEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
			}
			GATS_TEST_CASE(test_less_integer) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<Less>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<Less>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(0), make<Less>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
			GATS_TEST_CASE(test_less_equal_integer) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(1), make<LessEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = RPNEvaluator().evaluate({ make<Integer>(0), make<Integer>(1), make<LessEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(0), make<LessEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
		#endif
		#if TEST_REAL
			GATS_TEST_CASE(test_equality_real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<Equality>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Real>(Real::value_type("1.0")), make<Equality>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
			GATS_TEST_CASE(test_inequality_real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<Inequality>() });
				GATS_CHECK(value_of<Boolean>(result) != true);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Real>(Real::value_type("1.0")), make<Inequality>() });
				GATS_CHECK(value_of<Boolean>(result) != false);
			}
			GATS_TEST_CASE(test_greater_real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<Greater>() });
				GATS_CHECK(value_of<Boolean>(result) != true);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Real>(Real::value_type("1.0")), make<Greater>() });
				GATS_CHECK(value_of<Boolean>(result) != false);
			}
			GATS_TEST_CASE(test_greater_equal_real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<GreaterEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("1.0")), make<GreaterEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("2.0")), make<GreaterEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
			GATS_TEST_CASE(test_less_real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<Less>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Real>(Real::value_type("1.0")), make<Less>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("0.1")), make<Real>(Real::value_type("1.0")), make<Less>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
			}
			GATS_TEST_CASE(test_less_equal_real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("1.0")), make<LessEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("1.0")), make<LessEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("2.0")), make<LessEqual>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
			}
		#endif

		#if TEST_MIXED
			GATS_TEST_CASE(test_equality_mixed) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("1.0")), make<Equality>() });
				GATS_CHECK(value_of<Boolean>(result) == true);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Integer>(1), make<Equality>() });
				GATS_CHECK(value_of<Boolean>(result) == false);
			}
			GATS_TEST_CASE(test_inequality_mixed) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("1.0")), make<Inequality>() });
				GATS_CHECK(value_of<Boolean>(result) != true);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Integer>(1), make<Inequality>() });
				GATS_CHECK(value_of<Boolean>(result) != false);
			}
			GATS_TEST_CASE(test_greater_mixed) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Real>(Real::value_type("1.0")), make<Greater>() });
				GATS_CHECK(value_of<Boolean>(result) != true);
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.1")), make<Integer>(1), make<Greater>() });
				GATS_CHECK(value_of<Boolean>(result) != false);
			}
			GATS_TEST_CASE(test_greater_equal_mixed) {
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
			}
			GATS_TEST_CASE(test_less_mixed) {
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
			}
			GATS_TEST_CASE(test_less_equal_mixed) {
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
			}
		#endif
	#endif // TEST_BOOLEAN
#endif // TEST_BINARY_OPERATOR


#if TEST_FUNCTION
	#if TEST_SINGLE_ARG
		#if TEST_INTEGER
			GATS_TEST_CASE(test_abs_Integer) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(4), make<Abs>() });
				GATS_CHECK(value_of<Integer>(result) == 4);
			}
			GATS_TEST_CASE(test_abs_Integer_neg) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(-4), make<Abs>() });
				GATS_CHECK(value_of<Integer>(result) == 4);
			}
		#endif
		#if TEST_REAL
			GATS_TEST_CASE(test_abs_Real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("4.0")), make<Abs>() });
				GATS_CHECK(round(result) == round(Real::value_type("4.0")));
			}
			GATS_TEST_CASE(test_abs_Real_neg) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("-4.0")), make<Abs>() });
				GATS_CHECK(round(result) == round(Real::value_type("4.0")));
			}
			GATS_TEST_CASE(test_acos_Real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Arccos>() });
				GATS_CHECK(round(result) == Real::value_type("0.0"));
			}
			GATS_TEST_CASE(test_asin_Real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Arcsin>() });
				GATS_CHECK(value_of<Real>(result) == boost::math::constants::half_pi<Real::value_type>());
			}
			GATS_TEST_CASE(test_atan_Real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("0.0")), make<Arctan>() });
				GATS_CHECK(round(result) == Real::value_type("0.0"));
			}
			GATS_TEST_CASE(test_ceil_high_Real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("4.3")), make<Ceil>() });
				GATS_CHECK(round(result) == round(Real::value_type("5.0")));
			}
			GATS_TEST_CASE(test_ceil_low_Real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("-4.3")), make<Ceil>() });
				GATS_CHECK(round(result) == round(Real::value_type("-4.0")));
			}
			GATS_TEST_CASE(test_cos_Real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("0.0")), make<Cos>() });
				GATS_CHECK(round(result) == round(Real::value_type("1.0")));
			}
			GATS_TEST_CASE(test_exp) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Exp>() });
				GATS_CHECK(round(result) == round(boost::math::constants::e<Real::value_type>()));
			}
			GATS_TEST_CASE(test_floor_positive_Real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("4.3")), make<Floor>() });
				GATS_CHECK(round(result) == round(Real::value_type("4.0")));
			}
			GATS_TEST_CASE(test_floor__negative_Real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("-4.3")), make<Floor>() });
				GATS_CHECK(round(result) == round(Real::value_type("-5.0")));
			}
			GATS_TEST_CASE(test_lb) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("8.0")), make<Lb>() });
				GATS_CHECK(round(value_of<Real>(result)) == round(Real::value_type("3.0")));
			}
			GATS_TEST_CASE(test_ln) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Ln>() });
				GATS_CHECK(round(value_of<Real>(result)) == boost::multiprecision::log(Real::value_type("1.0")));
			}
			GATS_TEST_CASE(test_sin) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("0.0")), make<Sin>() });
				GATS_CHECK(round(value_of<Real>(result)) == Real::value_type("0.0"));
			}
			GATS_TEST_CASE(test_sqrt) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("16.0")), make<Sqrt>() });
				GATS_CHECK(round(value_of<Real>(result)) == round(Real::value_type("4.0")));
			}
			GATS_TEST_CASE(test_tan) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Tan>() });
				GATS_CHECK(value_of<Real>(result) == tan(Real::value_type("1.0")));
			}
		#endif
	#endif //TEST_SINGLE_ARG
	#if TEST_MULTI_ARG
		#if TEST_INTEGER
			GATS_TEST_CASE(test_max_int_int_rhs) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(2), make<Max>() });
				GATS_CHECK(value_of<Integer>(result) == 2);
			}
			GATS_TEST_CASE(test_max_int_int_lhs) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(1), make<Max>() });
				GATS_CHECK(value_of<Integer>(result) == 2);
			}
			GATS_TEST_CASE(test_max_int_int_same) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(2), make<Max>() });
				GATS_CHECK(value_of<Integer>(result) == 2);
			}
			GATS_TEST_CASE(test_min_int_int_rhs) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(1), make<Integer>(2), make<Min>() });
				GATS_CHECK(value_of<Integer>(result) == 1);
			}
			GATS_TEST_CASE(test_min_int_int_lhs) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(1), make<Min>() });
				GATS_CHECK(value_of<Integer>(result) == 1);
			}
			GATS_TEST_CASE(test_min_int_int_same) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(2), make<Min>() });
				GATS_CHECK(value_of<Integer>(result) == 2);
			}
			GATS_TEST_CASE(test_pow_integer) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Integer>(3), make<Pow>() });
				GATS_CHECK(value_of<Integer>(result) == Integer::value_type(8));
			}
		#endif // TEST_INTEGER
		#if TEST_REAL
			GATS_TEST_CASE(test_arctan2) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("2.0")), make<Arctan2>() });
				GATS_CHECK(value_of<Real>(result) == atan2(Real::value_type("1.0"), Real::value_type("2.0")));
			}
			GATS_TEST_CASE(test_max_real_real_rhs) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("2.0")), make<Max>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
			}
			GATS_TEST_CASE(test_max_real_real_lhs) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("1.0")), make<Max>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
			}
			GATS_TEST_CASE(test_max_real_real_same) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("2.0")), make<Max>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
			}
			GATS_TEST_CASE(test_min_real_real_rhs) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Real>(Real::value_type("2.0")), make<Min>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0"));
			}
			GATS_TEST_CASE(test_min_real_real_lhs) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("1.0")), make<Min>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0"));
			}
			GATS_TEST_CASE(test_min_real_real_same) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("2.0")), make<Min>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
			}
			GATS_TEST_CASE(test_pow_real) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Real>(Real::value_type("3.0")), make<Pow>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("8.0"));
			}
		#endif // TEST_REAL
		#if TEST_MIXED
			GATS_TEST_CASE(test_max_real_int_rhs) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Integer>(2), make<Max>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
			}
			GATS_TEST_CASE(test_max_int_real_lhs) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("1.0")), make<Max>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
			}
			GATS_TEST_CASE(test_max_int_real_same) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Integer>(2), make<Max>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
			}
			GATS_TEST_CASE(test_min_real_int_rhs) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("1.0")), make<Integer>(2), make<Min>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0"));
			}
			GATS_TEST_CASE(test_min_int_real_lhs) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("1.0")), make<Min>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("1.0"));
			}
			GATS_TEST_CASE(test_min_int_real_same) {
				auto result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Integer>(2), make<Min>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("2.0"));
			}
			GATS_TEST_CASE(test_pow_mixed) {
				auto result = RPNEvaluator().evaluate({ make<Integer>(2), make<Real>(Real::value_type("3.0")), make<Pow>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("8.0"));
				result = RPNEvaluator().evaluate({ make<Real>(Real::value_type("2.0")), make<Integer>(3), make<Pow>() });
				GATS_CHECK(value_of<Real>(result) == Real::value_type("8.0"));
			}
		#endif // TEST_MIXED
	#endif // TEST_MULTI_ARG
#endif // TEST_FUNCTION