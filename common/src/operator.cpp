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


[[nodiscard]] static Real::pointer_type get_as_real(Operand::pointer_type operand) {

		if (is<Real>(operand)) {
			Real::value_type value = value_of<Real>(operand);
			return make_real<Real>(value);
		}

		else if (is<Integer>(operand)) {

			Real converted(operand->str());
			return make_real<Real>(converted.value());

		}

		throw std::runtime_error("Error: Wrong data type used with get_as_real");

	}

/**
 * @brief			Get the operator for the perform and modify the operands to their correct data types
 * @param opStack	The operand stack
*/
[[nodiscard]] void prepare_datatypes(Operand::operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	Operand::pointer_type newLhs;
	Operand::pointer_type newRhs;

	if (is<Real>(lhs) || is<Real>(rhs) ){
		newLhs = get_as_real(lhs);
		newRhs = get_as_real(rhs);
	}

	// If any of the variables are not initialized
	else if (is<Variable>(lhs) || is<Variable>(rhs)) {

		Variable::pointer_type lVar = helper::make_variable(lhs);
		Variable::pointer_type rVar = helper::make_variable(rhs);

		if (!(helper::is_var_initialized(lVar) && helper::is_var_initialized(lVar))) {
			throw std::runtime_error("Error: Variable not initialized");
		}

	}

	else {
		newLhs = lhs;
		newRhs = rhs;
	}

	opStack.push(newRhs);
	opStack.push(newLhs);



}
[[nodiscard]] void prepare_single_operand(Operand::operand_stack_type& opStack) {

	/*
	Operand::pointer_type op = opStack.top();
	opStack.pop();

	Operand::pointer_type newOp;

	// If not assigning to a variable
	if (is<Variable>(op)) {

		Variable::pointer_type var = helper::make_variable(op);

		if (!helper::is_var_initialized(var)) {
			throw std::runtime_error("Error: Variable not initialized");
		}

		newOp = make_operand<Operand>(op);

	}

	opStack.push(newOp);
	*/

}


void Power::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type op = opStack.top();
	opStack.pop();
	
	op->perform_power(opStack);

}
void Factorial::perform(std::stack<Operand::pointer_type>& opStack) const {



	// Get the right operand
	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_factorial(opStack);

}
void Addition::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_addition(opStack);

}
void Division::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_division(opStack);

}
void Multiplication::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_multiplication(opStack);

}
void Subtraction::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_subtraction(opStack);

}
void Modulus::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_modulus(opStack);

}

void Identity::perform(std::stack<Operand::pointer_type>& opStack) const {
	//TODO Check to see if this is supposed to be empty
}
void Negation::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_negation(opStack);

}
void Assignment::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();
	
	// Get the left operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	opStack.push(rhs);

	lhs->perform_assignment(opStack);
	
}

void And::perform(std::stack<Operand::pointer_type>& opStack) const {

	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_and(opStack);

}
void Nand::perform(std::stack<Operand::pointer_type>& opStack) const {

	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_nand(opStack);

}
void Nor::perform(std::stack<Operand::pointer_type>& opStack) const {

	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_nor(opStack);

}
void Or::perform(std::stack<Operand::pointer_type>& opStack) const {

	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_or(opStack);

	//// Get the right operand
	//Operand::pointer_type rhs = opStack.top();
	//opStack.pop();

	//// Get the left operand
	//Operand::pointer_type lhs = opStack.top();
	//opStack.pop();

	//if (helper::is_bool(lhs, rhs)) {
	//	
	//	Boolean::value_type rhsValue = value_of<Boolean>(rhs);
	//	Boolean::value_type lhsValue = value_of<Boolean>(lhs);
	//	opStack.push(make_operand<Boolean>(lhsValue || rhsValue));

	//}
	//else {
	//	// Throw an exception
	//	throw std::exception("Invalid operand type for negation.");
	//}

}
void Xor::perform(std::stack<Operand::pointer_type>& opStack) const {

	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_xor(opStack);

}
void Xnor::perform(std::stack<Operand::pointer_type>& opStack) const {

	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_xnor(opStack);

}
void Not::perform(std::stack<Operand::pointer_type>& opStack) const {

	Operand::pointer_type op = opStack.top();
	opStack.pop();

	op->perform_not(opStack);

}

void Equality::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_equality(opStack);

}
void Inequality::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_inequality(opStack);

}
void Greater::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_greater(opStack);

}
void GreaterEqual::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_greater_equal(opStack);

}
void Less::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_less(opStack);

}
void LessEqual::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_less_equal(opStack);

}