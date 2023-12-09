/*!	\file	function.cpp
	\brief	Function class implementations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Function classes derived from Operation.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2016.11.02
	Added 'override' keyword where appropriate.

Version 2014.10.30
	Removed binary function

Version 2012.11.13
	C++ 11 cleanup

Version 2009.11.26
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


#include <ee/function.hpp>
#include <ee/integer.hpp>
#include <ee/real.hpp>


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
[[nodiscard]] static void prepare_datatypes(Operand::operand_stack_type& opStack) {

	Operand::pointer_type lhs = opStack.top();
	opStack.pop();
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	Operand::pointer_type newLhs;
	Operand::pointer_type newRhs;

	if (is<Real>(lhs) || is<Real>(rhs)) {
		newLhs = get_as_real(lhs);
		newRhs = get_as_real(rhs);
	}

	else {
		newLhs = lhs;
		newRhs = rhs;
	}

	opStack.push(newRhs);
	opStack.push(newLhs);



}

void Abs::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_abs(opStack);

}
void Arccos::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_arccos(opStack);

}
void Arcsin::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_arcsin(opStack);

}
void Arctan::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_arctan(opStack);

}
void Ceil::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_ceil(opStack);

}
void Cos::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_cos(opStack);
	
}
void Exp::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_exp(opStack);

}
void Floor::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_floor(opStack);
	
}
void Lb::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_lb(opStack);
	
}
void Ln::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_ln(opStack);

}
void Log::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_log(opStack);
	
}
void Result::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_result(opStack);

}
void Sin::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_sin(opStack);

}
void Sqrt::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_sqrt(opStack);

}
void Tan::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_tan(opStack);

}
void Arctan2::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_arctan2(opStack);

}
void Max::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_max(opStack);
	
}
void Min::perform(std::stack<Operand::pointer_type>& opStack) const {

	prepare_datatypes(opStack);

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_min(opStack);

}
void Pow::perform(std::stack<Operand::pointer_type>& opStack) const {

	// Get the right operand
	Operand::pointer_type rhs = opStack.top();
	opStack.pop();

	rhs->perform_pow(opStack);

}