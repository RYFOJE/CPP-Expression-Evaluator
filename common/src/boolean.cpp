/*!	\file	boolean.hpp
	\brief	Boolean classes implementations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementations of the Booleans classes derived from Operand.  Includes
the subclasses True and False.
=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019-11-05
	C++ 17 cleanup

Version 2012-11-13
	C++ 11 cleanup

Version 2009-11-26
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

#include <ee/boolean.hpp>
#include <ee/function.hpp>
#include <algorithm>


/*! Print a boolean token's value. */
Boolean::string_type Boolean::str() const {
	return value_ ? string_type("True") : string_type("False");
}


namespace helper {

	[[nodiscard]] bool is_bool(Operand::pointer_type const& lhs, Operand::pointer_type const& rhs) {

		return is<Boolean>(lhs) && is<Boolean>(rhs);

	}
	
	[[nodiscard]] bool is_bool(Operand::pointer_type const& op) {

		return is<Boolean>(op);

	}
	
}


void Boolean::perform_not(operand_stack_type& opStack) {

	opStack.push(make_bool(!this->value_));

}
void Boolean::perform_and(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();


	if (is<Boolean>(lhs)) {

		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(lhsValue && this->value_));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}

}
void Boolean::perform_nand(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();


	if (is<Boolean>(lhs)) {

		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(!(lhsValue && this->value_)));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}

}
void Boolean::perform_nor(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();


	if (is<Boolean>(lhs)) {

		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(!(lhsValue || this->value_)));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}

}
void Boolean::perform_or(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();
	

	if (is<Boolean>(lhs)) {
		
		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(lhsValue || this->value_));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}
	
}
void Boolean::perform_xor(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();


	if (is<Boolean>(lhs)) {

		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(lhsValue != this->value_));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}

}
void Boolean::perform_xnor(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();


	if (is<Boolean>(lhs)) {

		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(!(lhsValue != this->value_)));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}

}


void Boolean::perform_inequality(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();


	if (is<Boolean>(lhs)) {

		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(lhsValue != this->value_));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}
}
void Boolean::perform_equality(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();


	if (is<Boolean>(lhs)) {

		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(lhsValue == this->value_));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}
}
void Boolean::perform_greater(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();


	if (is<Boolean>(lhs)) {

		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(lhsValue < this->value_));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}

}
void Boolean::perform_less(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();


	if (is<Boolean>(lhs)) {

		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(lhsValue > this->value_));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}

}
void Boolean::perform_less_equal(operand_stack_type& opStack) {

	// Get the right operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();


	if (is<Boolean>(lhs)) {

		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(lhsValue >= this->value_));

	}
	else {
		// Throw an exception
		throw std::runtime_error("Invalid operand type for negation.");
	}

}