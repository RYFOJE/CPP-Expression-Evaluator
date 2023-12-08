/*!	\file	operator.cpp
	\brief	Operator classes implementations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementation of the Operator class derived from Token and the
supporting utilities.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2012.11.13
	C++ 11 cleanup

Version 0.1.0: 2010-11-08
	Added exception for assignment to a non-variable.

Version 2009.12.14
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

#include <ee/operator.hpp>
#include <ee/operand.hpp>
#include <ee/integer.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>
#include <ee/boolean.hpp>
#include <cassert>

#include <iostream>

void Power::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type op = opStack.top();
	opStack.pop();
	
	op->perform_power(opStack);

}

void Assignment::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Addition::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_addition(opStack);

}

void And::perform(std::stack<Operand::pointer_type>& opStack) const {

	//// Get the right operand
	//Operand::pointer_type rhs = opStack.top();
	//opStack.pop();

	//// Get the left operand
	//Operand::pointer_type lhs = opStack.top();
	//opStack.pop();

	//if (helper::is_bool(lhs, rhs)) {

	//	Boolean::value_type rhsValue = value_of<Boolean>(rhs);
	//	Boolean::value_type lhsValue = value_of<Boolean>(lhs);
	//	opStack.push(make_operand<Boolean>(lhsValue && rhsValue));

	//}
	//else {
	//	// Throw an exception
	//	throw std::exception("Invalid operand type for negation.");
	//}

}

void Division::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_division(opStack);

	//// Get the left operand
	//Operand::pointer_type lhs = opStack.top();
	//opStack.pop();

	//// TODO FIX THIS AS IT DOES NOT WORK WITH MIXED DATA TYPES
	//if (helper::is_real(lhs, rhs)) {

	//	// Convert both to real and make sure they are

	//	Real::value_type rhsValue = value_of<Real>(helper::get_as_real(rhs));
	//	Real::value_type lhsValue = value_of<Real>(helper::get_as_real(lhs));
	//	opStack.push(make_operand<Real>(lhsValue / rhsValue));
	//}

	//else {

	//	Integer::value_type rhsValue = value_of<Integer>(rhs);
	//	Integer::value_type lhsValue = value_of<Integer>(lhs);
	//	opStack.push(make_operand<Integer>(lhsValue / rhsValue));

	//}

}

void Equality::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_equality(opStack);

	//// Get the left operand
	//Operand::pointer_type lhs = opStack.top();
	//opStack.pop();

	//if (helper::is_bool(lhs, rhs)) {

	//	Boolean::value_type rhsValue = value_of<Boolean>(rhs);
	//	Boolean::value_type lhsValue = value_of<Boolean>(lhs);
	//	opStack.push(make_operand<Real>(lhsValue || rhsValue));

	//}
	//else if (helper::is_real(lhs, rhs)) {
	//	// Throw an exception
	//	throw std::exception("Invalid operand type for negation.");
	//}

	//else if (helper::is_integer(lhs, rhs)) {
	//	// Throw an exception
	//	throw std::exception("Invalid operand type for negation.");
	//}

	//else {
	//	// Throw an exception
	//	throw std::exception("Invalid operand type for negation.");
	//}

}

void Greater::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void GreaterEqual::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Inequality::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Less::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void LessEqual::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Multiplication::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_multiplication(opStack);

	//// Get the left operand
	//Operand::pointer_type lhs = opStack.top();
	//opStack.pop();

	//// TODO FIX THIS AS IT DOES NOT WORK WITH MIXED DATA TYPES
	//if (helper::is_real(lhs, rhs)) {

	//	// Convert both to real and make sure they are

	//	Real::value_type rhsValue = value_of<Real>(helper::get_as_real(rhs));
	//	Real::value_type lhsValue = value_of<Real>(helper::get_as_real(lhs));
	//	opStack.push(make_operand<Real>(lhsValue * rhsValue));
	//}

	//else {

	//	Integer::value_type rhsValue = value_of<Integer>(rhs);
	//	Integer::value_type lhsValue = value_of<Integer>(lhs);
	//	opStack.push(make_operand<Integer>(lhsValue * rhsValue));

	//}

}

void Modulus::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_modulus(opStack);

	//// Get the left operand
	//Operand::pointer_type lhs = opStack.top();
	//opStack.pop();

	//// TODO FIX THIS AS IT DOES NOT WORK WITH MIXED DATA TYPES
	//if (helper::is_real(lhs, rhs)) {
	//	throw std::runtime_error("Error: Cannot perform modulo on Real number");
	//}

	//else {

	//	Integer::value_type rhsValue = value_of<Integer>(rhs);
	//	Integer::value_type lhsValue = value_of<Integer>(lhs);
	//	opStack.push(make_operand<Integer>(lhsValue % rhsValue));

	//}

}

void Nand::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Nor::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Or::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	// Get the left operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	if (helper::is_bool(lhs, rhs)) {
		
		Boolean::value_type rhsValue = value_of<Boolean>(rhs);
		Boolean::value_type lhsValue = value_of<Boolean>(lhs);
		opStack.push(make_operand<Boolean>(lhsValue || rhsValue));

	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}

}

void Subtraction::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_subtraction(opStack);

	//// Get the left operand
	//Operand::pointer_type lhs = opStack.top();
	//opStack.pop();

	//// TODO FIX THIS AS IT DOES NOT WORK WITH MIXED DATA TYPES
	//if (helper::is_real(lhs, rhs)) {

	//	// Convert both to real and make sure they are

	//	Real::value_type rhsValue = value_of<Real>(helper::get_as_real(rhs));
	//	Real::value_type lhsValue = value_of<Real>(helper::get_as_real(lhs));
	//	opStack.push(make_operand<Real>(lhsValue - rhsValue));
	//}

	//else {

	//	Integer::value_type rhsValue = value_of<Integer>(rhs);
	//	Integer::value_type lhsValue = value_of<Integer>(lhs);
	//	opStack.push(make_operand<Integer>(lhsValue - rhsValue));

	//}

}

void Xor::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Xnor::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Identity::perform(std::stack<Operand::pointer_type>& opStack) const {
	//TODO Check to see if this is supposed to be empty
}

void Negation::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the top right operand
	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_negation(opStack);

	//if (is<Real>(currOperand)) {
	//	// Negate the operand

	//	Real::value_type realValue = value_of<Real>(currOperand);
	//	Real::pointer_type realOperand = std::make_shared<Real>(-realValue);
	//	
	//	opStack.push(realOperand);
	//}
	//else if (is<Integer>(currOperand)) {
	//	// Negate the operand

	//	Integer::value_type realValue = value_of<Integer>(currOperand);
	//	Integer::pointer_type realOperand = std::make_shared<Integer>(-realValue);

	//	opStack.push(realOperand);
	//}
	//else {
	//	// Throw an exception
	//	throw std::exception("Invalid operand type for negation.");
	//}

}

void Not::perform(std::stack<Operand::pointer_type>& opStack) const {

	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_not(opStack);

	/*if (helper::is_bool(currOperand)) {

		Boolean::value_type boolValue = value_of<Boolean>(currOperand);
		Boolean::pointer_type boolOperand = std::make_shared<Boolean>(!boolValue);

		opStack.push(boolOperand);

	}
	else {

		throw std::exception("Invalid operand type for not.");

	}*/

}

void Factorial::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the top right operand
	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_factorial(opStack);

	//if (is<Real>(currOperand)) {
	//	throw std::runtime_error("Error: Operand cannot be a Real");
	//}

	//// Get the numerical value and create a value to hold the running total
	//Integer::value_type amount = value_of<Integer>(currOperand);
	//Integer::value_type runningTotal(1);

	//// Perform the factorial calculation
	//for (int i = 1; i <= amount; i++) {

	//	runningTotal *= i;

	//}

	//// Create an operand with the given value and add it to the operand stack
	//opStack.push(make_operand<Integer>(runningTotal));

}
