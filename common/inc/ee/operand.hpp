#pragma once
/*!	\file	operand.hpp
	\brief	Operand class and utilities declarations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Operand class derived from Token and the 
supporting utilities.

	class Operand
	class NoCast
	DECL_OPERAND_PERFORM()
	DEF_OPERAND_PERFORM()
	make_operand()
	get_value()
	OperandList
	dereference()
	make_same()
	up_cast()

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.12.10
	make_operand changed to use a parameter pack

Version 2019.11.05
	C++ 17 cleanup

Version 2012.11.13
	C++ cleanup.

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

#include <ee/token.hpp>
#include <cassert>
#include <deque>
#include <stack>

/*! Operand token base class. */
class Operand : public Token {
public:
	DEF_POINTER_TYPE(Operand)
	using operand_list_type = std::deque<Operand::pointer_type>;
	using operand_stack_type = std::stack<Operand::pointer_type>;


	// OPERATORS
	virtual void perform_addition(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform addition not supported for this datatype"); };
	virtual void perform_subtraction(operand_stack_type& opStack)		{ throw std::runtime_error("Error: perform subtraction not supported for this datatype"); };
	virtual void perform_multiplication(operand_stack_type& opStack)	{ throw std::runtime_error("Error: perform multiplication not supported for this datatype"); };
	virtual void perform_division(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform division not supported for this datatype"); };
	virtual void perform_modulus(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform modulus not supported for this datatype"); };
	virtual void perform_power(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform power not supported for this datatype"); };
	virtual void perform_inequality(operand_stack_type& opStack)		{ throw std::runtime_error("Error: perform inequality not supported for this datatype"); };
	virtual void perform_equality(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform equality not supported for this datatype"); };
	virtual void perform_negation(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform negation not supported for this datatype"); };
	virtual void perform_not(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform not not supported for this datatype"); };
	virtual void perform_factorial(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform factorial not supported for this datatype"); };
	
	// COMPARAISON
	virtual void perform_less(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform less not supported for this datatype"); };;
	virtual void perform_less_equal(operand_stack_type& opStack)		{ throw std::runtime_error("Error: perform less equal supported for this datatype"); };;
	virtual void perform_greater(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform greater not supported for this datatype"); };;
	virtual void perform_greater_equal(operand_stack_type& opStack)		{ throw std::runtime_error("Error: perform greater equal not supported for this datatype"); };;

	// LOGICAL OPERATOR
	virtual void perform_and(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform and not supported for this datatype"); };
	virtual void perform_nand(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform nand not supported for this datatype"); };
	virtual void perform_nor(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform nor not supported for this datatype"); };
	virtual void perform_or(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform or not supported for this datatype"); };
	virtual void perform_xor(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform xor not supported for this datatype"); };
	virtual void perform_xnor(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform xnor not supported for this datatype"); };


	// FUNCTIONS
	virtual void perform_abs(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform abs not supported for this datatype"); };
	virtual void perform_arccos(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform arccos not supported for this datatype"); };
	virtual void perform_arcsin(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform arcsin not supported for this datatype"); };
	virtual void perform_arctan(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform arctan not supported for this datatype"); };
	virtual void perform_ceil(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform ceil not supported for this datatype"); };
	virtual void perform_cos(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform cos not supported for this datatype"); };
	virtual void perform_exp(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform exp not supported for this datatype"); };
	virtual void perform_floor(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform floor not supported for this datatype"); };
	virtual void perform_lb(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform lb not supported for this datatype"); };
	virtual void perform_ln(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform ln not supported for this datatype"); };
	virtual void perform_log(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform log not supported for this datatype"); };
	virtual void perform_result(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform result not supported for this datatype"); };
	virtual void perform_sin(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform sin not supported for this datatype"); };
	virtual void perform_sqrt(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform sqrt not supported for this datatype"); };
	virtual void perform_tan(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform tan not supported for this datatype"); };
	virtual void perform_arctan2(operand_stack_type& opStack)			{ throw std::runtime_error("Error: perform arctan2 not supported for this datatype"); };
	virtual void perform_max(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform max not supported for this datatype"); };
	virtual void perform_min(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform max not supported for this datatype"); };
	virtual void perform_pow(operand_stack_type& opStack)				{ throw std::runtime_error("Error: perform pow not supported for this datatype"); };


	// VARIABLES
	virtual void perform_assignment(operand_stack_type& opStack) { throw std::runtime_error("Error: assignment to a non-variable."); };


};


/*! Make a new smart-pointer managed Token object with constructor parameter. */
template <typename T, class... Args> inline Operand::pointer_type [[nodiscard]] make_operand(Args ... params) {
	return Operand::pointer_type(new T(params...));
}


/*! Gets the value from an operand. */
template <typename OPERAND_TYPE>
typename OPERAND_TYPE::value_type [[nodiscard]] value_of(Token::pointer_type const& operand) {
	assert(is<OPERAND_TYPE>(operand));
	return dynamic_cast<OPERAND_TYPE*>(operand.get())->value();
}


/*!	Type for a list of operands. */
using OperandList = Operand::operand_list_type;

