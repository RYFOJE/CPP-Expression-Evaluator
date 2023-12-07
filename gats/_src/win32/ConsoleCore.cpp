#pragma once
/*	\file		ConsoleCore.cpp
	\author		Garth Santor
	\copyright	Garth Santor, Trinh Han
	\date		2021-08-30
	\brief		BasicConsole class implementation.

=========================================================================
ConsoleCore class implementation.

========================================================================================
Revision History
-------------------------------------------------------------

Version 2021.08.30
	C++ 17 version
	Moved to namespace gats::win32

Version 2015.03.20
	Alpha release.

==========================================================================================
Copyright 2015-21, Garth Santor & Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
========================================================================================*/


#include <gats/win32/ConsoleApp/ConsoleCore.hpp>
#include <Windows.h>
#include <memory>

namespace gats::win32 {

#pragma region Code Page Operations
	std::uint32_t ConsoleCore::GetInputCodePage() {
		return GetConsoleCP();
	}
	std::uint32_t ConsoleCore::GetOutputCodePage() {
		return GetConsoleOutputCP();
	}
	void ConsoleCore::SetInputCodePage(std::uint32_t wCodePageID) {
		THROW_IF_WIN32_ERROR(SetConsoleCP(wCodePageID));
	}
	void ConsoleCore::SetOutputCodePage(std::uint32_t wCodePageID) {
		THROW_IF_WIN32_ERROR(SetConsoleOutputCP(wCodePageID));
	}
#pragma endregion


#pragma region Control Handler Operations
	/*! SetConsoleCtrlHandler() function wrapper. */
	void ConsoleCore::SetCtrlHandler(PHANDLER_ROUTINE pHandler, bool add) {
		THROW_IF_WIN32_ERROR(SetConsoleCtrlHandler(pHandler, add));
	}
#pragma endregion

#pragma region Cursor Operations
	/** GetConsoleCursorInfo() function wrapper. */
	void ConsoleCore::GetCursorInfo(CONSOLE_CURSOR_INFO& _consoleCursorInfo) {
		THROW_IF_WIN32_ERROR(GetConsoleCursorInfo(hOutput(), &_consoleCursorInfo));
	}

	/** SetConsoleCursorInfo() function wrapper. */
	void ConsoleCore::SetCursorInfo(CONSOLE_CURSOR_INFO const& _consoleCursorInfo) {
		THROW_IF_WIN32_ERROR(SetConsoleCursorInfo(hOutput(), &_consoleCursorInfo));
	}

	/** GetCursorPosition() function adapter. */
	COORD ConsoleCore::GetCursorPosition() {
		auto sbi = GetScreenBufferInfo();
		return sbi.dwCursorPosition;
	}

	/** SetConsoleCursorPosition() function wrapper. */
	void ConsoleCore::SetCursorPosition(COORD _dwCursorPosition) {
		THROW_IF_WIN32_ERROR(SetConsoleCursorPosition(hOutput(), _dwCursorPosition));
	}
#pragma endregion


#pragma region Input Operations
	/*!	ReadConsoleInput() function wrapper. */
	std::uint32_t ConsoleCore::ReadInput(std::vector<INPUT_RECORD>& events) {
		DWORD nEventsRead;
		events.resize(events.capacity());
		THROW_IF_WIN32_ERROR(ReadConsoleInput(hInput(), events.data(), (DWORD)events.size(), &nEventsRead));
		events.resize(nEventsRead);
		return nEventsRead;
	}
#pragma endregion


#pragma region Mode Operations
	/*!	GetConsoleMode() function wrapper. */
	std::uint32_t ConsoleCore::GetMode() {
		DWORD mode;
		THROW_IF_WIN32_ERROR(GetConsoleMode(hInput(), &mode));
		return mode;
	}


	/*!	SetConsoleMode() function wrapper. */
	void ConsoleCore::SetMode(std::uint32_t mode) {
		THROW_IF_WIN32_ERROR(SetConsoleMode(hInput(), mode));
	}


#pragma endregion


#pragma region Output Operations
	/** FillConsoleOutputAttribute() function wrapper. */
	std::uint32_t ConsoleCore::FillOutputAttribute(std::uint16_t _attribute, std::uint32_t _nLength, COORD _writeCoord) {
		DWORD numberOfCharsWritten;
		THROW_IF_WIN32_ERROR(FillConsoleOutputAttribute(hOutput(), _attribute, _nLength, _writeCoord, &numberOfCharsWritten));
		return numberOfCharsWritten;
	}

	/** FillConsoleOutputCharacter() function wrapper. */
	std::uint32_t ConsoleCore::FillOutputCharacter(wchar_t _cCharacter, std::uint32_t _nLength, COORD _writeCoord) {
		DWORD numberOfCharsWritten;
		THROW_IF_WIN32_ERROR(FillConsoleOutputCharacterW(hOutput(), _cCharacter, _nLength, _writeCoord, &numberOfCharsWritten));
		return numberOfCharsWritten;
	}

	/** ReadConsoleOutput() function wrapper. */
	void ConsoleCore::ReadOutput(std::vector<CHAR_INFO>& _buffer, COORD _size, COORD _pos, SMALL_RECT& _readRegion) {
		_buffer.resize(_size.X * _size.Y);
		THROW_IF_WIN32_ERROR(ReadConsoleOutputW(hOutput(), _buffer.data(), _size, _pos, &_readRegion));
	}

	/* WriteConsoleOutput() wrapper. */
	void ConsoleCore::WriteOutput(std::vector<CHAR_INFO> const& _buffer, COORD _bufferSize, COORD _pos, SMALL_RECT& _writeRegion) {
		THROW_IF_WIN32_ERROR(WriteConsoleOutput(hOutput(), _buffer.data(), _bufferSize, _pos, &_writeRegion));
	}

#pragma endregion


#pragma region Title Operations
	/** GetConsoleTitle() function wrappers. */
	void ConsoleCore::GetTitle(std::string& _consoleTitle) {
		size_t const SIZE = 0xFFFF;
		auto p = std::unique_ptr<char, std::default_delete<char[]>>(new char[SIZE]);
		THROW_IF_WIN32_ERROR(GetConsoleTitleA(p.get(), SIZE));
		_consoleTitle = p.get();
	}
	void ConsoleCore::GetTitle(std::wstring& _consoleTitle) {
		size_t const SIZE = 0x7FFF;
		auto p = std::unique_ptr<wchar_t, std::default_delete<wchar_t[]>>(new wchar_t[SIZE]);
		THROW_IF_WIN32_ERROR(GetConsoleTitleW(p.get(), SIZE));
		_consoleTitle = p.get();
	}
	std::wstring ConsoleCore::GetTitle() {
		std::wstring title;
		GetTitle(title);
		return title;
	}

	/** SetConsoleTitle() function wrappers. */
	void ConsoleCore::SetTitle(char const* _szConsoleTitle) {
		THROW_IF_WIN32_ERROR(SetConsoleTitleA(_szConsoleTitle));
	}
	void ConsoleCore::SetTitle(wchar_t const* _szConsoleTitle) {
		THROW_IF_WIN32_ERROR(SetConsoleTitleW(_szConsoleTitle));
	}
	void ConsoleCore::SetTitle(std::string const& _consoleTitle) {
		THROW_IF_WIN32_ERROR(SetConsoleTitleA(_consoleTitle.c_str()));
	}
	void ConsoleCore::SetTitle(std::wstring const& _consoleTitle) {
		THROW_IF_WIN32_ERROR(SetConsoleTitleW(_consoleTitle.c_str()));
	}
#pragma endregion



#pragma region Screen Buffer Operations
	// GetConsoleScreenBufferInfo() wrapper functions.
	void ConsoleCore::GetScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO& _consoleScreenBufferInfo) {
		assert(hOutput() != INVALID_HANDLE_VALUE);
		THROW_IF_WIN32_ERROR(GetConsoleScreenBufferInfo(hOutput(), &_consoleScreenBufferInfo));
	}
	CONSOLE_SCREEN_BUFFER_INFO ConsoleCore::GetScreenBufferInfo() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetScreenBufferInfo(csbi);
		return csbi;
	}

	/** GetConsoleScreenBufferInfoEx() wrapper functions. */
	void ConsoleCore::GetScreenBufferInfoEx(CONSOLE_SCREEN_BUFFER_INFOEX& _consoleScreenBufferInfoEx) {
		_consoleScreenBufferInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		THROW_IF_WIN32_ERROR(GetConsoleScreenBufferInfoEx(hOutput(), &_consoleScreenBufferInfoEx));
	}
	CONSOLE_SCREEN_BUFFER_INFOEX ConsoleCore::GetScreenBufferInfoEx() {
		CONSOLE_SCREEN_BUFFER_INFOEX csbix;
		GetScreenBufferInfoEx(csbix);
		return csbix;
	}

	/**	Query the current text attribute. */
	void GetTextAttribute(Attribute& attribute) {
		CONSOLE_SCREEN_BUFFER_INFOEX csbi{ 0 };
		ConsoleCore::GetScreenBufferInfoEx(csbi);
		attribute = csbi.wAttributes;
	}
	Attribute ConsoleCore::GetTextAttribute() {
		CONSOLE_SCREEN_BUFFER_INFOEX csbi{ 0 };
		ConsoleCore::GetScreenBufferInfoEx(csbi);
		return csbi.wAttributes;
	}

	/** SetConsoleScreenBufferInfoEx() wrapper function. */
	void ConsoleCore::SetScreenBufferInfoEx(CONSOLE_SCREEN_BUFFER_INFOEX& _consoleScreenBufferInfoEx) {
		_consoleScreenBufferInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		THROW_IF_WIN32_ERROR(SetConsoleScreenBufferInfoEx(hOutput(), &_consoleScreenBufferInfoEx));
	}

	/** SetConsoleScreenBufferSize() wrapper function. */
	void ConsoleCore::SetScreenBufferSize(COORD _size) {
		THROW_IF_WIN32_ERROR(SetConsoleScreenBufferSize(hOutput(), _size));
	}

	/*!	SetConsoleTextAttribute() wrapper function. */
	void ConsoleCore::SetTextAttribute(Attribute _attribute) {
		THROW_IF_WIN32_ERROR(SetConsoleTextAttribute(hOutput(), _attribute.mask_));
	}


	/** SetConsoleWindowInfo() wrapper functions. */
	void ConsoleCore::SetWindowInfo(BOOL _bAbsolute, SMALL_RECT const& _consoleWindow) {
		THROW_IF_WIN32_ERROR(SetConsoleWindowInfo(hOutput(), _bAbsolute, &_consoleWindow));
	}



#pragma region ScopedAttributeState class
	ScopedAttributeState::ScopedAttributeState() : attribute_m(ConsoleCore::GetTextAttribute()) { }
	ScopedAttributeState::~ScopedAttributeState() {
		ConsoleCore::SetTextAttribute(attribute_m);
	}
#pragma endregion


} // end-of-namespace gats::win32

#pragma endregion