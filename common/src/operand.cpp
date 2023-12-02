/*!	\file	operand.cpp
	\brief	Operand class and utilities implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementations of the Operand class derived from Token and the
supporting utilities.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2017.12.12
	Added an exception to dereference when there is no value stored in the variable.

Version 2012.11.13
	C++ 11 cleanup

Version 2009.12.14
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

#include <ee/operand.hpp>
#include <ee/boolean.hpp>
#include <ee/integer.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>
