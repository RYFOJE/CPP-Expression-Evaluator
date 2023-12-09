/*!	\file	real.hpp
	\brief	Real classes implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementations of the Real classes derived from Operand.  Includes
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

#include <ee/real.hpp>
#include <ee/boolean.hpp>
#include <ee/function.hpp>
#include <ee/operator.hpp>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

[[nodiscard]] Real::string_type Real::str() const {
	ostringstream oss;
	oss << /*"Real: " << */fixed << setprecision(numeric_limits<value_type>::digits10) << value_;
	return oss.str();
}

namespace helper {

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

	[[nodiscard]] static Real::pointer_type get_as_real(Integer* operand) {

		Real converted(operand->str());
		return make_real<Real>(converted.value());

		throw std::runtime_error("Error: Wrong data type used with get_as_real");

	}

	[[nodiscard]] bool is_real(const Operand::pointer_type lhs, const Operand::pointer_type rhs) {
		return (is<Real>(lhs) || is<Real>(rhs));
	}

	[[nodiscard]] bool is_real(const Operand::pointer_type op) {
		return (is<Real>(op));
	}

}

void Real::perform_negation(operand_stack_type& opStack) {

	opStack.push(make_operand<Real>(-this->value_));

};
void Real::perform_addition(operand_stack_type& opStack) {
	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	Operand::pointer_type result;

	if (is<Real>(lhs))
		result = make_operand<Real>(value_of<Real>(lhs) + this->value_);

	else if (is<Real>(lhs))
		result = make_operand<Real>(value_of<Real>(lhs) + this->value_);

	else
		throw std::runtime_error("Invalid operand type for addition.");

	opStack.push(result);

};
void Real::perform_subtraction(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	// Make sure it is the right data type
	if (!(is<Real>(lhs) || is<Integer>(lhs)))
		throw std::runtime_error("Invalid operand type for subtraction.");

	Real::pointer_type lhs_real = helper::get_as_real(lhs);

	opStack.push(make_real<Real>(value_of<Real>(lhs_real) - this->value_));

};
void Real::perform_multiplication(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	// Make sure it is the right data type
	if (!(is<Real>(lhs) || is<Integer>(lhs)))
		throw std::runtime_error("Invalid operand type for subtraction.");

	Real::pointer_type lhs_real = helper::get_as_real(lhs);

	opStack.push(make_real<Real>(value_of<Real>(lhs_real) * this->value_));

};
void Real::perform_division(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	// Make sure it is the right data type
	if (!(is<Real>(lhs) || is<Integer>(lhs)))
		throw std::runtime_error("Invalid operand type for subtraction.");

	Real::pointer_type lhs_real = helper::get_as_real(lhs);

	opStack.push(make_real<Real>(value_of<Real>(lhs_real) / this->value_));
	
};
void Real::perform_power(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	Real::value_type result;

	if (this->value_ == 0){
		make_real<Real>(Real::value_type(1));
		return;
	}

	// Make sure it is the right data type
	if (!(is<Real>(lhs) || is<Integer>(lhs)))
		throw std::runtime_error("Invalid operand type for subtraction.");

	Real::pointer_type lhs_real = helper::get_as_real(lhs);
	
	result = pow(value_of<Real>(lhs_real), this->value_);
	
	opStack.push(make_real<Real>(result));
	
};


