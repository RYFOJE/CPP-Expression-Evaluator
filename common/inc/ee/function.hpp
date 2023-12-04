#pragma once
/*!	\file	function.hpp
	\brief	Function classes declarations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Function classes derived from Operation.  
Includes the subclasses:
	OneArgFunction
		Abs
		Arccos
		Arcsin
		Arctan
		Ceil
		Cos
		Exp
		Floor
		Lb
		Ln
		Log
		Result
		Sin
		Sqrt
		Tan

	TwoArgFunction
		Arctan2
		Max
		Min
		Pow

	ThreeArgFunction

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2016.11.02
	Added 'override' keyword where appropriate.

Version 2014.10.30
	Removed binary function

Version 2012.11.13
	C++ 11 cleanup

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

#include <ee/operation.hpp>
#include <ee/integer.hpp>
#include <vector>

/*! Function token base class. */
class Function : public Operation { };

		/*! One argument function token base class. */
		class OneArgFunction : public Function {
		public:
			[[nodiscard]] virtual unsigned number_of_args() const override { return 1; }
		};

				/*! Absolute value function token. */
				class Abs : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! arc cosine function token. */
				class Arccos : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! arc sine function token. */
				class Arcsin : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! arc tangent function token.  Argument is the slope. */
				class Arctan : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! ceil function token. */
				class Ceil : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! cosine function token. */
				class Cos : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! exponential function token.  pow(e,x), where 'e' is the euler constant and 'x' is the exponent. */
				class Exp : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! floor function token. */
				class Floor : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! logarithm base 2 function token. */
				class Lb : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! natural logarithm function token. */
				class Ln : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! logarithm base 10 function token. */
				class Log : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! previous result token. Argument is the 1-base index of the result. */
				class Result : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! sine function token. */
				class Sin : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! Square root token. */
				class Sqrt : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! tangeant function. */
				class Tan : public OneArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};


		/*!	Two argument function token base class. */
		class TwoArgFunction : public Function {
		public:
			[[nodiscard]] virtual unsigned number_of_args() const override { return 2; }
		};

				/*! 2 parameter arc tangent function token.
					First argument is the change in Y, second argument is the change in X. */
				class Arctan2 : public TwoArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! Maximum of 2 elements function token. */
				class Max : public TwoArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! Minimum of 2 elements function token. */
				class Min : public TwoArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};

				/*! Pow function token.  First argument is the base, second the exponent. */
				class Pow : public TwoArgFunction {
				public:
					[[nodiscard]] virtual void perform(std::stack<Operand::pointer_type>& opStack) const override;
				};


		/*!	Three argument function token base class. */
		class ThreeArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 3; }
		};
