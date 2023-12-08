/*!	\file	integer.cpp
	\brief	Integer class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementations of the Integer class derived from Operand.

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

Version 2012.11.16
	Added Bit operators, Pow

Version 2012.11.15
	Added BinaryInteger, Binary <function>

Version 2012.11.13
	C++ 11 cleanup

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

#include <ee/integer.hpp>
#include <ee/function.hpp>
#include <ee/operator.hpp>
#include <ee/boolean.hpp>
#include <ee/real.hpp>
#include <array>

using namespace std;

namespace helper {

	[[nodiscard]] bool is_integer(Operand::pointer_type const& lhs, Operand::pointer_type const& rhs) {
		return (is<Integer>(lhs) || is<Integer>(rhs));
	}

	[[nodiscard]] bool is_integer(Operand::pointer_type const& op) {
		return is<Integer>(op);
	}

	[[nodiscard]] static Real::pointer_type get_as_real(Operand::pointer_type operand) {

		if (is<Real>(operand)) {
			Real::value_type value = value_of<Real>(operand);
			return make_real<Real>(value);
		}

		else if (is<Integer>(operand)) {

			Integer::pointer_type converted = convert<Integer>(operand);
			return make_real<Real>(converted->value().convert_to<Real::value_type>());

		}

		throw std::runtime_error("Error: Wrong data type used with get_as_real");

	}

	[[nodiscard]] static Real::pointer_type get_as_real(Integer* operand) {

		Real converted(operand->str());
		return make_real<Real>(converted.value());

		throw std::runtime_error("Error: Wrong data type used with get_as_real");

	}
}


[[nodiscard]] Integer::string_type Integer::str() const {
	return value().str();
}


void Integer::perform_addition(operand_stack_type& opStack) {
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	Operand::pointer_type result;

	if (helper::is_integer(lhs)) {

		result = make_operand<Integer>(value_of<Integer>(lhs) + this->value_);

	}
	
	else if (is<Real>(lhs))
		result = make_operand<Real>(value_of<Real>(lhs) + value_of<Real>(helper::get_as_real(this)));

	else
		throw std::runtime_error("Invalid operand type for addition.");

	opStack.push(result);
};

void Integer::perform_subtraction(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	Operand::pointer_type result;

	if (helper::is_integer(lhs)) {

		result = make_operand<Integer>(value_of<Integer>(lhs) - this->value_);

	}

	else if (helper::is_real(lhs))
		result = make_operand<Real>(value_of<Real>(lhs) - value_of<Real>(helper::get_as_real(this)));

	else
		throw std::runtime_error("Invalid operand type for addition.");

	opStack.push(result);

};
void Integer::perform_multiplication(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	Operand::pointer_type result;

	if (helper::is_integer(lhs))
		result = make_operand<Integer>(value_of<Integer>(lhs) * this->value_);

	else if (helper::is_real(lhs))
		result = make_operand<Real>(value_of<Real>(lhs) * value_of<Real>(helper::get_as_real(this)));

	else
		throw std::runtime_error("Invalid operand type for addition.");

	opStack.push(result);

};

void Integer::perform_division(operand_stack_type& opStack) {

	// Prevent division by zero
	if (this->value_ == 0)
		throw std::runtime_error("Error: Division by zero.");

	// Get the left operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	Operand::pointer_type result;

	// Check to see if the correct datatype has been passed
	if (helper::is_real(lhs)) {
		result = make_operand<Real>(value_of<Real>(lhs) / value_of<Real>(helper::get_as_real(this)));
	}

	else if (helper::is_integer(lhs)) {
		result = make_operand<Integer>(value_of<Integer>(lhs) / this->value_);
	}

	else
		throw std::runtime_error("Invalid operand type for addition.");

	opStack.push(result);

};
void Integer::perform_modulus(operand_stack_type& opStack) {

	// Get the left operand
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	Operand::pointer_type result;

	// Check to see if the correct datatype has been passed
	if (helper::is_integer(lhs)) {
		result = make_operand<Integer>(value_of<Integer>(lhs) % this->value_);
	}

	else
		throw std::runtime_error("Invalid operand type for addition.");

	opStack.push(result);

};

void Integer::perform_power(operand_stack_type& opStack) {};

void Integer::perform_equality(operand_stack_type& opStack) {};
void Integer::perform_negation(operand_stack_type& opStack) {

	Integer::value_type realValue = this->value();
	opStack.push(std::make_shared<Integer>(-realValue));

};
void Integer::perform_not(operand_stack_type& opStack) {};
void Integer::perform_factorial(operand_stack_type& opStack) {
	
	// Get the numerical value and create a value to hold the running total
	Integer::value_type amount = this->value_;
	Integer::value_type runningTotal(1);

	// Perform the factorial calculation
	for (int i = 1; i <= amount; i++) {

		runningTotal *= i;

	}

	// Create an operand with the given value and add it to the operand stack
	opStack.push(make_operand<Integer>(runningTotal));

};