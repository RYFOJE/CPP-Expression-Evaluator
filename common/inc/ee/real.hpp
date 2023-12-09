#pragma once
/*!	\file	real.hpp
	\brief	Real classes declarations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Real classes derived from Operand.  Includes
the subclasses Pi and E.


=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.26
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2014.10.29
	C++ 11 refactor.
	Switched value_type to boost::multiprecision::cpp_dec_float_100

Version 2012.11.13
	C++ 11 cleanup

Version 2010.11.09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.

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

#include <ee/operand.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>


/*! Real number token. */
class Real : public Operand {
public:
	DEF_POINTER_TYPE(Real)
	using value_type = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<1000, int32_t, void>>;
private:
	value_type	value_;
public:
	
	Real(value_type value = value_type(0)) : value_(value) { }
	Real(Token::string_type str) : value_(value_type(str)) { }
	[[nodiscard]] value_type	value() const { return value_; };
	[[nodiscard]] string_type	str() const override;


	// OPERATIONS
	virtual void perform_addition(operand_stack_type& opStack) override;
	virtual void perform_subtraction(operand_stack_type& opStack) override;
	virtual void perform_multiplication(operand_stack_type& opStack) override;
	virtual void perform_division(operand_stack_type& opStack) override;
	virtual void perform_power(operand_stack_type& opStack) override;
	virtual void perform_negation(operand_stack_type& opStack) override;
	virtual void perform_equality(operand_stack_type& opStack) override;
	virtual void perform_inequality(operand_stack_type& opStack) override;
	virtual void perform_less_equal(operand_stack_type& opStack) override;
	virtual void perform_less(operand_stack_type& opStack) override;
	virtual void perform_greater(operand_stack_type& opStack) override;
	virtual void perform_greater_equal(operand_stack_type& opStack) override;

	// FUNCTIONS
	virtual void perform_abs(operand_stack_type& opStack) override;
	virtual void perform_arccos(operand_stack_type& opStack) override;
	virtual void perform_arcsin(operand_stack_type& opStack) override;
	virtual void perform_arctan(operand_stack_type& opStack) override;
	virtual void perform_ceil(operand_stack_type& opStack) override;
	virtual void perform_cos(operand_stack_type& opStack) override;
	virtual void perform_exp(operand_stack_type& opStack) override;
	virtual void perform_floor(operand_stack_type& opStack) override;
	virtual void perform_lb(operand_stack_type& opStack) override;
	virtual void perform_ln(operand_stack_type& opStack) override;
	virtual void perform_log(operand_stack_type& opStack) override;
	virtual void perform_result(operand_stack_type& opStack) override;
	virtual void perform_sin(operand_stack_type& opStack) override;
	virtual void perform_sqrt(operand_stack_type& opStack) override;
	virtual void perform_tan(operand_stack_type& opStack) override;
	virtual void perform_arctan2(operand_stack_type& opStack) override;
	virtual void perform_max(operand_stack_type& opStack) override;
	virtual void perform_min(operand_stack_type& opStack) override;
	virtual void perform_pow(operand_stack_type& opStack) override;

};


/*! Pi constant token. */
class Pi : public Real {
public:
	Pi() : Real(boost::math::constants::pi<value_type>()) { }
};


/*! Euler constant token. */
class E : public Real {
public:
	E() : Real(boost::math::constants::e<value_type>()) { }
};


/*! Make a new smart-pointer managed Token object with constructor parameter. */
template <typename T, class... Args> inline Real::pointer_type [[nodiscard]] make_real(Args ... params) {
	return Real::pointer_type(new T(params...));
}

namespace helper {

	[[nodiscard]] bool is_real(const Operand::pointer_type lhs, const Operand::pointer_type rhs);
	[[nodiscard]] bool is_real(const Operand::pointer_type op);

}
