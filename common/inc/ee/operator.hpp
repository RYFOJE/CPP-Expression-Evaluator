#pragma once
/*!	\file	operator.hpp
	\brief	Operator classes declarations and utilities.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Operator classes derived from Token and the
supporting utilities.

	enum class Precedence
	DEF_PRECEDENCE()
	class Operator
		class BinaryOperator
			class RAssocOperator
				class Power
				class Assignment
			class LAssocOperator
				class Addition
				class And
				class Division
				class Equality
				class Greater
				class GreaterEqual
				class Inequality
				class Less
				class LessEqual
				class Multiplication
				class Modulus
				class Nand
				class Nor
				class Or
				class Subtraction
				class Xor
				class Xnor
		class NonAssociative
			class UnaryOperator
				class Identity
				class Negation
				class Not
			class PostfixOperator
				class Factorial

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated
	Converted 'enum' to 'enum class'

Version 2019.11.05
	C++ 17 cleanup

Version 2016.11.02
	Added 'override' keyword where appropriate.

Version 2014.10.30
	Removed bitwise operators.

Version 2012.11.16
	Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

Version 2012.11.13
	C++ 11 cleanup

Version 2010.11.09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.

Version 2009.11.26
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

#include <ee/operand.hpp>
#include <ee/operation.hpp>


/*! Operator Precedence values. */
enum class Precedence { MIN = 0,
	ASSIGNMENT, LOGOR, LOGXOR, LOGAND, BITOR,
	BITXOR, BITAND, EQUALITY, RELATIONAL, BITSHIFT,
	ADDITIVE, MULTIPLICATIVE, UNARY, POWER, POSTFIX,
	MAX };



/*! Defines a precedence category method.  Used inside a class declaration. */
#define DEF_PRECEDENCE(category)\
	public: [[nodiscard]] Precedence precedence() const override { return Precedence::category; }



/*! Operator token base class. */
class Operator : public Operation {
public:
	DEF_POINTER_TYPE(Operator)
	[[nodiscard]] virtual Precedence precedence() const = 0;
};

		/*! Binary operator token base class. */
		class BinaryOperator : public Operator {
		public:
			[[nodiscard]] virtual unsigned number_of_args() const override { return 2; }
		};

				/*! Right-associative operator base class. */
				class RAssocOperator : public BinaryOperator { };

						/*! Power token. */
						class Power : public RAssocOperator {
						DEF_PRECEDENCE(POWER)
						};

						/*! Assignment token. */
						class Assignment : public RAssocOperator {
						DEF_PRECEDENCE(ASSIGNMENT)
						};


				/*! Left-associative operator base class. */
				class LAssocOperator : public BinaryOperator {};

						/*! Addition token. */
						class Addition : public LAssocOperator {
						DEF_PRECEDENCE(ADDITIVE)
						};

						/*! And token. */
						class And : public LAssocOperator {
						DEF_PRECEDENCE(LOGAND)
						};

						/*! Division token. */
						class Division : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
						};

						/*! Equality token. */
						class Equality : public LAssocOperator {
						DEF_PRECEDENCE(EQUALITY)
						};

						/*! Greater than token. */
						class Greater : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
						};

						/*! Greater than or equal to token. */
						class GreaterEqual : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
						};

						/*! Inequality operator token. */
						class Inequality : public LAssocOperator {
						DEF_PRECEDENCE(EQUALITY)
						};

						/*! Less than operator token. */
						class Less : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
						};

						/*! Less than equal-to operator token. */
						class LessEqual : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
						};

						/*! Multiplication operator token. */
						class Multiplication : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
						};

						/*! Modulus operator token. */
						class Modulus : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
						};

						/*! Nand operator token. */
						class Nand : public LAssocOperator {
						DEF_PRECEDENCE(LOGAND)
						};

						/*! Nor operator token. */
						class Nor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
						};

						/*! Or operator token. */
						class Or : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
						};

						/*! Subtraction operator token. */
						class Subtraction : public LAssocOperator {
						DEF_PRECEDENCE(ADDITIVE)
						};

						/*! XOR operator token. */
						class Xor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
						};

						/*! XNOR operator token. */
						class Xnor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
						};


		/*! Non-associative operator token base class. */
		class NonAssociative : public Operator { };

				/*! Unary operator token base class. */
				class UnaryOperator : public NonAssociative {
				public: [[nodiscard]] virtual unsigned number_of_args() const override { return 1; }
				DEF_PRECEDENCE(UNARY)
				};

						/*! Identity operator token. */
						class Identity : public UnaryOperator {
						};

						/*! Negation operator token. */
						class Negation : public UnaryOperator {
						};

						/*! Not operator token. */
						class Not : public UnaryOperator {
						};

				/*! Postfix Operator token base class. */
				class PostfixOperator : public UnaryOperator { };

						/*! Factorial token base class. */
						class Factorial : public PostfixOperator {
						};
