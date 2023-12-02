#pragma once
/*!	\file	pseudo_operation.hpp
	\brief	PseudoOperation classes declarations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the PseudoOperation classes derived from Token.

	class PseduoOperation
		class Parenthesis
			class LeftParenthesis
			class RightParenthesis
		class ArgumentSeparator

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.26
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

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

#include <ee/token.hpp>


/*! Pseudo-operation token base class. */
class PseudoOperation : public Token { };

		/*! Parenthesis operation token base class. */
		class Parenthesis : public PseudoOperation { };

				/*! Left-parenthesis token. */
				class LeftParenthesis : public Parenthesis { };

				/*! Right-parenthesis token. */
				class RightParenthesis : public Parenthesis { };

		/*! Argument-separator operation token. */
		class ArgumentSeparator : public PseudoOperation { };
