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

/*
namespace helper {

	[[nodiscard]] bool is_integer(Operand::pointer_type const& lhs, Operand::pointer_type const& rhs) {
		return (is<Integer>(lhs) || is<Integer>(rhs));
	}

	[[nodiscard]] bool is_integer(Operand::pointer_type const& op) {
		return is<Integer>(op);
	}

	Real::pointer_type get_as_real(Operand::pointer_type operand) {

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

	Real::pointer_type get_as_real(Integer* operand) {

		Real converted(operand->str());
		return make_real<Real>(converted.value());

		throw std::runtime_error("Error: Wrong data type used with get_as_real");

	}

	Real::pointer_type get_as_real(Operand::pointer_type operand) {

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

	Real::pointer_type get_as_real(Integer* operand) {

		Real converted(operand->str());
		return make_real<Real>(converted.value());

		throw std::runtime_error("Error: Wrong data type used with get_as_real");

	}

}

*/

[[nodiscard]] Real::string_type Real::str() const {
	ostringstream oss;
	oss << /*"Real: " << */fixed << setprecision(numeric_limits<value_type>::digits10) << value_;
	return oss.str();
}


//Real::pointer_type get_as_real(Operand::pointer_type operand) {
//
//	if (is<Real>(operand)) {
//		Real::value_type value = value_of<Real>(operand);
//		return make_real<Real>(value);
//	}
//
//	else if (is<Integer>(operand)) {
//
//		Real converted(operand->str());
//		return make_real<Real>(converted.value());
//
//	}
//
//	throw std::runtime_error("Error: Wrong data type used with get_as_real");
//
//}


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
void Real::perform_subtraction(operand_stack_type& opStack) {};
void Real::perform_multiplication(operand_stack_type& opStack) {};
void Real::perform_division(operand_stack_type& opStack) {};
void Real::perform_modulus(operand_stack_type& opStack) {};
void Real::perform_power(operand_stack_type& opStack) {};


namespace helper {

	[[nodiscard]] bool is_real(Operand::pointer_type lhs, Operand::pointer_type rhs) {
		return (is<Real>(lhs) || is<Real>(rhs));
	}
	
}