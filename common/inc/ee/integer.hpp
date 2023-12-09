#pragma once
/*!	\file	integer.hpp
	\brief	Integer class declaration.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Integer class derived from Operand.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2014.10.29
	C++ 11 refactor.
	Converted Integer::value_type to boost::multiprecision::cpp_int
	Removed BinaryInteger

Version 2012.11.15
	Added BinaryInteger.

Version 2012.11.13
	C++ 11 cleanup.

Version 2010.11.09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.
	Switched __int64 to long long.

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
#include <boost/multiprecision/cpp_int.hpp>


/*! Integer token. */
class Integer : public Operand {
public:
	using value_type = boost::multiprecision::cpp_int;
	DEF_POINTER_TYPE(Integer)
private:
	value_type	value_;
public:
	Integer( value_type value = 0 )
		: value_( value ) { }

	Integer(Token::string_type str) : value_(value_type(str)) { }

	[[nodiscard]]	value_type	value() const { return value_; }
	[[nodiscard]]	string_type	str() const override;


	// OPERATORS

	virtual void perform_addition(operand_stack_type& opStack) override;
	virtual void perform_subtraction(operand_stack_type& opStack) override;
	virtual void perform_multiplication(operand_stack_type& opStack) override;
	virtual void perform_division(operand_stack_type& opStack) override;
	virtual void perform_modulus(operand_stack_type& opStack) override;
	virtual void perform_power(operand_stack_type& opStack) override;
	virtual void perform_pow(operand_stack_type& opStack) override;
	virtual void perform_equality(operand_stack_type& opStack) override;
	virtual void perform_inequality(operand_stack_type& opStack) override;
	virtual void perform_negation(operand_stack_type& opStack) override;
	virtual void perform_factorial(operand_stack_type& opStack) override;

	// FUNCTIONS
	virtual void perform_abs(operand_stack_type& opStack) override;
	virtual void perform_max(operand_stack_type& opStack) override;
	virtual void perform_min(operand_stack_type& opStack) override;

	// COMPARATOR
	virtual void perform_less(operand_stack_type& opStack) override;
	virtual void perform_less_equal(operand_stack_type& opStack) override;
	virtual void perform_greater(operand_stack_type& opStack) override;
	virtual void perform_greater_equal(operand_stack_type& opStack) override;

};

/*! Make a new smart-pointer managed Token object with constructor parameter. */
template <typename T, class... Args> inline Integer::pointer_type [[nodiscard]] make_integer(Args ... params) {
	return Integer::pointer_type(new T(params...));
}

namespace helper {

	[[nodiscard]] bool is_integer(Operand::pointer_type const& lhs, Operand::pointer_type const& rhs);
	[[nodiscard]] bool is_integer(Operand::pointer_type const& op);
	

}