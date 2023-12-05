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
#include <cassert>

#include <iostream>

void Power::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Assignment::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Addition::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void And::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Division::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Equality::perform(std::stack<Operand::pointer_type>& opStack) const {

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

}

void Modulus::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Nand::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Nor::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Or::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Subtraction::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Xor::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Xnor::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Identity::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Negation::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the top right operand
	Operand::pointer_type currOperand = opStack.top();
	opStack.pop();

	if (is<Real>(currOperand)) {
		// Negate the operand

		Real::value_type realValue = value_of<Real>(currOperand);
		Real::pointer_type realOperand = std::make_shared<Real>(-realValue);
		
		opStack.push(realOperand);
	}
	else if (is<Integer>(currOperand)) {
		// Negate the operand

		Integer::value_type realValue = value_of<Integer>(currOperand);
		Integer::pointer_type realOperand = std::make_shared<Integer>(-realValue);

		opStack.push(realOperand);
	}
	else {
		// Throw an exception
		throw std::exception("Invalid operand type for negation.");
	}

}

void Not::perform(std::stack<Operand::pointer_type>& opStack) const {

}

void Factorial::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the top right operand
	Operand::pointer_type currOperand = opStack.top();
	opStack.pop();

	if (is<Real>(currOperand)) {
		throw std::runtime_error("Error: Operand cannot be a Real");
	}

	// Get the numerical value and create a value to hold the running total
	Integer::value_type amount = value_of<Integer>(currOperand);
	Integer::value_type runningTotal(1);

	// Perform the factorial calculation
	for (int i = 1; i < amount; i++) {

		runningTotal *= i;

	}

	// Create an operand with the given value and add it to the operand stack
	opStack.push(make_operand<Integer>(runningTotal));

}
