/*! \file	expression_evaluator.cpp
	\brief	ExpressionEvaluator class implementation.
	\author	Garth Santor
	\date	2021-11-01
	\copyright	Garth Santor, Trinh Han

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated

Version 2010.10.31
	Alpha release.

=============================================================

Copyright Garth Santor / Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor / Trinh Han, Canada.
The program(s) may be used and /or copied only with
the written permission of Garth Santor / Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement / contract under which
the program(s) have been supplied.
============================================================= */

#include <ee/expression_evaluator.hpp>
#include <ee/tokenizer.hpp>
#include <ee/parser.hpp>
#include <ee/RPNEvaluator.hpp>
#include <ee/function.hpp>

#if defined(SHOW_STEPS)
#include <iostream>
#endif

[[nodiscard]] ExpressionEvaluator::result_type ExpressionEvaluator::evaluate( ExpressionEvaluator::expression_type const& expr ) {
	TokenList infixTokens = tokenizer_m.tokenize(expr);
#if defined(SHOW_STEPS)
	{ using namespace std;
	cout << "Lexer output" << endl;
	copy(infixTokens.begin(), infixTokens.end(), ostream_iterator<Token::pointer_type>(cout, " "));
	std::cout << std::endl;
	}
#endif

	TokenList postfixTokens = parser_m.parse(infixTokens);
#if defined(SHOW_STEPS)
	{ using namespace std;
	cout << "Parser output" << endl;
	copy(postfixTokens.begin(), postfixTokens.end(), ostream_iterator<Token::pointer_type>(cout, " "));
	std::cout << std::endl;
	}
#endif

	Operand::pointer_type result = rpn_m.evaluate(postfixTokens);
	return result;
}
