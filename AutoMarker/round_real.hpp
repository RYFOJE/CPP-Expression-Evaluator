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

#include <ee/real.hpp>

inline Real::value_type round(Real::value_type x) {
	auto exp = pow(Real::value_type("10.0"), Real::value_type("990"));
	x *= exp;
	x += 0.5;
	x = floor(x);
	x /= exp;
	return x;
}



inline Real::value_type round(Token::pointer_type const& v) {
	return round(value_of<Real>(v));
}
