/*!	\file	variable.cpp
	\brief	Variable class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementation of the Variable class derived from Operand.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.26
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

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

#include <ee/variable.hpp>

[[nodiscard]] Token::string_type Variable::str() const {
	if (!value_m)
		return Token::string_type("Variable: null");
	return value_m->str();
}

namespace helper {

	/**
	 * @brief			Make a variable from an operand.
	 * @param value		The operand to convert
	 * @return			The converted operand as a variable.
	*/
	Variable::pointer_type make_variable(Operand::pointer_type const& value) {
		Variable::pointer_type var = std::make_shared<Variable>();
		var->set(value);
		return var;
	}
	
	/**
	 * @brief			Verify if a variable is initialized.
	 * @param var		The variable to check.
	 * @return			True if the variable is initialized. Else false.
	*/
	[[nodiscard]] bool is_var_initialized(Variable::pointer_type var) {

		return var->value() != nullptr;

	};

}

void Variable::perform_assignment(operand_stack_type& opStack) {
	// pop the value from the stack
	Operand::pointer_type value = opStack.top();
	opStack.pop();

	// push the variable onto the stack
	opStack.push(helper::make_variable(value));

}

void Variable::perform_result(operand_stack_type& opStack) {

	// push the variable onto the stack
	opStack.push(this->value());

}

