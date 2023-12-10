/*!	\file	parser.cpp
	\brief	Parser class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han
=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated
	Changed to GATS_TEST

Version 2014.10.31
	Visual C++ 2013

Version 2012.11.13
	C++ 11 cleanup

Version 2009.12.02
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

#include <ee/parser.hpp>
#include <ee/function.hpp>
#include <ee/operand.hpp>
#include <ee/operator.hpp>
#include <ee/pseudo_operation.hpp>
#include <stack>


[[nodiscard]] TokenList Parser::parse(TokenList const& infixTokens) {
	
	TokenList outputQ;
	std::stack<Token::pointer_type> opStack;

	for (auto& token : infixTokens) {
		
		if (is<Operand>(token))
			outputQ.push_back(token);

		else if (is<Function>(token))
			opStack.push(token);

		else if (is<ArgumentSeparator>(token)) {

			while (!opStack.empty() && !is<LeftParenthesis>(opStack.top())) {
				outputQ.push_back(opStack.top());
				opStack.pop();
			}
		}

		else if (is<LeftParenthesis>(token))
			opStack.push(token);

		else if (is<RightParenthesis>(token)) {

			while (!opStack.empty() && !is<LeftParenthesis>(opStack.top())) {
				outputQ.push_back(opStack.top());
				opStack.pop();
			}

			if (opStack.empty())
				throw std::runtime_error("Right Paranthesis, has no matching left parenthesis.");
			
			opStack.pop();

			if (!opStack.empty() && is<Function>(opStack.top())) {
				outputQ.push_back(opStack.top());
				opStack.pop();
			}
		} // Right Parenthesis

		else if (is<Operator>(token)) {

			while (!opStack.empty()) {

				if (!is<Operator>(opStack.top())) {
					break;
				}

				if (is<NonAssociative>(token)) {
					break;
				}

				Operator::pointer_type tokenCurrToken = convert<Operator>(token);
				Operator::pointer_type tokenTop = convert<Operator>(opStack.top());

				if (is<LAssocOperator>(token) && tokenCurrToken->precedence() > tokenTop->precedence()) {
					break;
				}

				if (is<RAssocOperator>(token) && tokenCurrToken->precedence() >= tokenTop->precedence()) {
					break;
				}

				outputQ.push_back(opStack.top());
				opStack.pop();
			}

			opStack.push(token);

		}

		else {
			throw std::runtime_error("Unknown Token");
		}

	} // for-each

	while (!opStack.empty()) {

		if (is<LeftParenthesis>(opStack.top())) {
			throw std::runtime_error("Missing right-pranthesis.");
		}

		outputQ.push_back(opStack.top());
		opStack.pop();

	}

	// The following line is just a placeholder until you have completed the parser.
	return outputQ;
}
