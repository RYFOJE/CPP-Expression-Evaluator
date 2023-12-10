/*!	\file	RPNEvaluator.cpp
	\brief	RPN Evaluator class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated
	Changed to GATS_TEST

Version 2012.11.13
	C++ 11 cleanup

Version 2009.12.10
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

#include <ee/RPNEvaluator.hpp>
#include <ee/integer.hpp>
#include <ee/operation.hpp>

#include <ee/variable.hpp>

#include <cassert>
#include <stack>


[[nodiscard]] Operand::pointer_type RPNEvaluator::evaluate( TokenList const& rpnExpression ) {
	
	// create a stack to store operands
	std::stack<Operand::pointer_type> opStack;

	for (auto& token : rpnExpression) {

		if (is<Operand>(token)) {
			opStack.push(convert<Operand>(token));
		}

		else {

			// Convert the token to an operation
			Operation::pointer_type currOperation = convert<Operation>(token);

			// Check if there are enough operands for the operation
			if (currOperation->number_of_args() > opStack.size()) {
				throw std::runtime_error("Insufficient # of operands for operation");
			}

			// Perform the operation of the current token
			currOperation->perform(opStack);

		} // end not operand
		
	} // End for rpnExpression

	if (opStack.size() > 1)
		throw std::runtime_error("Error: too many operands");

	if (opStack.empty())
		throw std::runtime_error("Error: insufficient operands");


	// The following line is just a placeholder until you have completed the parser.
	return opStack.top();
}

