#pragma once
/*!	\file	parser.cpp
	\brief	Parser class declaration.
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
#include <ee/token.hpp>

class Parser {
	Parser(Parser const&) = delete;
	Parser& operator = (Parser const&) = delete;
public:
	Parser() = default;
	[[nodiscard]] TokenList parse(TokenList const& infixTokens);
};
