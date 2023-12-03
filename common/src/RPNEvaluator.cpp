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

			Operation::pointer_type currOperation = convert<Operation>(token);

			if (currOperation->number_of_args() > opStack.size()) {
				throw std::runtime_error("Insufficient # of operands for operation");
			}

			// Pop the correct number of operands from the operand stack
			for (int i = 0; i < currOperation->number_of_args(); i++) {

				std::stack<Operand::pointer_type> opToPass;

				// Get the rightmost element and add it to the list of operands to pass
				opToPass.push(convert<Operand>(opStack.top()));
				opStack.pop();



				break; // TODO REMOVE THIS AND ADD CODE FOR THIS
				
			}

		} // end not operand
	} // End for rpnExpression

	if (opStack.size() > 1)
		throw std::runtime_error("Error: too many operands");

	if (opStack.empty())
		throw std::runtime_error("Error: insufficient operands");




		/*
		// if token is an operand, push it to the stack
		if (token->isOperand()) {
			opStack.push(std::dynamic_pointer_cast<Operand>(token));
		}
		// if token is an operator, pop two operands from the stack, apply the operator, and push the result back to the stack
		else if (token->isOperator()) {
			Operand::pointer_type op2 = opStack.top();
			opStack.pop();
			Operand::pointer_type op1 = opStack.top();
			opStack.pop();
			opStack.push(std::dynamic_pointer_cast<Operation>(token)->perform(op1, op2));
		}
		// if token is a function, pop one operand from the stack, apply the function, and push the result back to the stack
		else if (token->isFunction()) {
			Operand::pointer_type op1 = opStack.top();
			opStack.pop();
			opStack.push(std::dynamic_pointer_cast<Function>(token)->perform(op1));
		}
		// if token is a variable, push it to the stack
		else if (token->isVariable()) {
			opStack.push(std::dynamic_pointer_cast<Variable>(token));
		}
		// if token is a left parenthesis, push it to the stack
		else if (token->isLeftParen()) {
			opStack.push(std::dynamic_pointer_cast<LeftParen>(token));
		}
		// if token is a right parenthesis, pop operands from the stack until a left parenthesis is encountered
		else if (token->isRightParen()) {
			while (!opStack.empty() && !opStack.top()->isLeftParen()) {
				Operand::pointer_type op2 = opStack.top();
				opStack.pop();
				Operand::pointer_type op1 = opStack.top();
				opStack.pop();
				opStack.push(std::dynamic_pointer_cast<Operation>(op2)->perform(op1, op2));
			}
			// pop the left parenthesis from the stack
			opStack.pop();
		}
		// if token is a comma, pop operands from the stack until a left parenthesis is encountered
		else if (token->isComma()) {
			while (!opStack.empty() && !opStack.top()->isLeftParen()) {
				Operand::pointer_type op2 = opStack.top();
				opStack.pop();
	*/

	// The following line is just a placeholder until you have completed the parser.
	return opStack.top();
}

