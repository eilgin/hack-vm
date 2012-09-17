#ifndef _PARSER_H
#define _PARSER_H

#include <sstream>
#include <string>
#include "command_type.h"

using std::istringstream;
using std::string;

class Parser {
public:
	/**
	Opens the input file and gets ready
	to parse it
	*/
	Parser(istringstream &iss);
	/**
	Are there more commands in the input ?
	*/
	bool hasMoreCommands();
	/**
	Reads the next command from the input
	and makes it the current command.
	Should be called only if hasMoreCommands()
	is true.
	Initially there is no current command
	*/
	void advance();
	/**
	Returns the type of the current
	VM command
	*/
	TYPE_COMMAND commandType();
	/**
	Returns the 1st argument
	of VM command.
	In case of C_ARITHMETIC,
	the command itself (add, sub,...)
	is returned.
	Should not be called if the 
	current cmd is C_RETURN
	*/
	string arg1();
	/**
	Returns the 2nd argument
	of VM command.
	Should be called only if the 
	current cmd is C_PUSH, C_POP,
	C_FUNCTION, C_CALL
	*/
	string arg2();

private:
	istringstream &m_in;
	string m_currentCommand;
};

#endif
