#pragma once
/*! \file	expression_evaluator.hpp
	\brief	ExpressionEvaluator class declaration.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated

Version 2010.10.29
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

#include <ee/tokenizer.hpp>
#include <ee/parser.hpp>
#include <ee/RPNEvaluator.hpp>
#include <ee/function.hpp>


class ExpressionEvaluator {
public:
	using expression_type = Token::string_type;
	using result_type = Token::pointer_type;
private:
	Tokenizer		tokenizer_m;
	Parser			parser_m;
	RPNEvaluator	rpn_m;
public:
	[[nodiscard]] result_type evaluate(expression_type const& expr);
};
