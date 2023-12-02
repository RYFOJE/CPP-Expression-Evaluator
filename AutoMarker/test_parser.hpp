#pragma once
/*! \file	marker_00_framework.cpp
	\brief	Expression Evaluator marking application.
	\author	Garth Santor
	\date	2021-11-07
	\copyright	Garth Santor

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.07
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

#include <ee/token.hpp>
#include <ee/parser.hpp>
#include <gats/TestApp.hpp>



/*! Performs tokenizer test case

	1. Tokenizes the expression.
	2. Checks that returned token list matches correct list.

	\param expression [in] The expression to tokenize.
	*/
inline [[nodiscard]] bool parse_test(TokenList const& infixTokenList, TokenList const& correct) {
	TokenList postfixTokenList = Parser().parse(infixTokenList);
	bool ok = true;
	ok = ok && (correct.size() == postfixTokenList.size());
	size_t n = std::min(correct.size(), postfixTokenList.size());
	for (size_t i = 0; i < n; ++i) {
		bool match = correct[i] == postfixTokenList[i];
		GATS_CHECK_MESSAGE(match, "Token [" << i << "] = " << postfixTokenList[i]->str() << " should be " << correct[i]->str());
		ok = ok && match;
	}
	return ok;
}
