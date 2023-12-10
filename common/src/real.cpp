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

#include <iostream>

using namespace std;

[[nodiscard]] Real::string_type Real::str() const {
	ostringstream oss;
	oss << /*"Real: " << */fixed << setprecision(numeric_limits<value_type>::digits10) << value_;

	std::string str = oss.str();

	auto no_trailing_zeros = str.find_last_not_of('0');
	if (no_trailing_zeros != string::npos) {
		
		// Remove trailing zeros
		string trimmed = str.substr(0, no_trailing_zeros + 1);
		
		// If the decimal point is the last character remove it
		if (trimmed.back() == '.') {
			trimmed.pop_back();
		}
		
		return trimmed;
	}
	return str;
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

	if (is<Real>(lhs)) {
		Real::pointer_type lhs_real = helper::get_as_real(lhs);
		opStack.push(make_operand<Real>(value_of<Real>(lhs_real) + this->value_));
	}
	
	else
		throw std::runtime_error("Invalid operand type for addition.");
	
};
void Real::perform_subtraction(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	if (is<Real>(lhs)) {
		Real::pointer_type lhs_real = helper::get_as_real(lhs);
		opStack.push(make_operand<Real>(value_of<Real>(lhs_real) - this->value_));
	}

	else
		throw std::runtime_error("Invalid operand type for addition.");

};
void Real::perform_multiplication(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	if (is<Real>(lhs)) {
		Real::pointer_type lhs_real = helper::get_as_real(lhs);
		opStack.push(make_operand<Real>(value_of<Real>(lhs_real) * this->value_));
	}

	else
		throw std::runtime_error("Invalid operand type for addition.");

};
void Real::perform_division(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	if (is<Real>(lhs)) {
		Real::pointer_type lhs_real = helper::get_as_real(lhs);
		opStack.push(make_operand<Real>(value_of<Real>(lhs_real) / this->value_));
	}

	else
		throw std::runtime_error("Invalid operand type for addition.");
	
};
void Real::perform_power(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	// Make sure it is the right data type
	if (!(is<Real>(lhs)))
		throw std::runtime_error("Invalid operand type for subtraction.");

	Real::value_type result;

	if (this->value_ == 0)
		opStack.push(make_real<Real>(Real::value_type(1)));

	Real::pointer_type lhs_real = helper::get_as_real(lhs);	
	result = boost::multiprecision::pow(value_of<Real>(lhs_real), this->value_);
	
	opStack.push(make_real<Real>(result));
	
};

void Real::perform_abs(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(abs(this->value_)));

};
void Real::perform_arccos(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(acos(this->value_)));

};
void Real::perform_arcsin(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(asin(this->value_)));

};
void Real::perform_arctan(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(atan(this->value_)));

};
void Real::perform_ceil(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(ceil(this->value_)));

};
void Real::perform_cos(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(cos(this->value_)));

};
void Real::perform_exp(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(exp(this->value_)));
	
};
void Real::perform_floor(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(floor(this->value_)));

};
void Real::perform_lb(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(log2(this->value_)));

};
void Real::perform_ln(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(log(this->value_)));
	
};
void Real::perform_log(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(log(this->value_)));

};
void Real::perform_result(operand_stack_type& opStack) {};
void Real::perform_sin(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(sin(this->value_)));

};
void Real::perform_sqrt(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(sqrt(this->value_)));
	
};
void Real::perform_tan(operand_stack_type& opStack) {

	opStack.push(make_real<Real>(tan(this->value_)));

};
void Real::perform_arctan2(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	if (is<Real>(lhs)) {
		Real::pointer_type lhs_real = helper::get_as_real(lhs);
		opStack.push(make_real<Real>(atan2(value_of<Real>(lhs_real), this->value_)));
	}

	else
		throw std::runtime_error("Invalid operand type for addition.");

};
void Real::perform_max(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	opStack.push(this->value_ > value_of<Real>(lhs) ? make_real<Real>(this->value_) : lhs);

};
void Real::perform_min(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	opStack.push(this->value_ > value_of<Real>(lhs) ? lhs : make_real<Real>(this->value_));

};
void Real::perform_pow(operand_stack_type& opStack) {

	perform_power(opStack);

};

void Real::perform_equality(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	bool calculatedValue;

	if (is<Real>(lhs)) {
		calculatedValue = (value_of<Real>(lhs) == this->value_);
	}

	else {
		calculatedValue = true;
	}

	opStack.push(make_operand<Boolean>(calculatedValue));

};
void Real::perform_inequality(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	bool calculatedValue;

	if (is<Real>(lhs)) {
		calculatedValue = (value_of<Real>(lhs) != this->value_);
	}

	else {
		calculatedValue = true;
	}

	opStack.push(make_operand<Boolean>(calculatedValue));

};
void Real::perform_less(operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();

	bool calculatedValue;

	if (is<Real>(lhs)) {
		calculatedValue = (value_of<Real>(lhs) < this->value_);
	}

	else {
		calculatedValue = true;
	}

	opStack.push(make_operand<Boolean>(calculatedValue));

};
 void Real::perform_less_equal(operand_stack_type& opStack) {
 
	 Operand::pointer_type lhs = opStack.top();
	 opStack.pop();

	 bool calculatedValue;

	 if (is<Real>(lhs)) {
		 calculatedValue = (value_of<Real>(lhs) <= this->value_);
	 }

	 else {
		 calculatedValue = true;
	 }

	 opStack.push(make_operand<Boolean>(calculatedValue));

 };
 void Real::perform_greater(operand_stack_type& opStack) {
 
	 Operand::pointer_type lhs = opStack.top();
	 opStack.pop();

	 bool calculatedValue;

	 if (is<Real>(lhs)) {
		 calculatedValue = (value_of<Real>(lhs) > this->value_);
	 }

	 else {
		 calculatedValue = true;
	 }

	 opStack.push(make_operand<Boolean>(calculatedValue));
 
 };
 void Real::perform_greater_equal(operand_stack_type& opStack) {
 
	 Operand::pointer_type lhs = opStack.top();
	 opStack.pop();

	 bool calculatedValue;

	 if (is<Real>(lhs)) {
		 calculatedValue = (value_of<Real>(lhs) >= this->value_);
	 }

	 else {
		 calculatedValue = true;
	 }

	 opStack.push(make_operand<Boolean>(calculatedValue));
 
 };