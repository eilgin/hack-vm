#ifndef _CODEWRITER_H
#define _CODEWRITER_H

#include <ostream>
#include <string>
#include <stack>
#include "command_type.h"

using std::ostream;
using std::string;
using std::stack;
using std::endl;

class CodeWriter {
public:
	/**
	Opens the output file and gets ready
	to write into it
	*/
	CodeWriter(ostream &os);
	/**
	Informs the code writer that the translation
	of a new VM file is started
	*/
	void setFileName(string fileName);
	/**
	Writes the assembly code that is the
	translation of the given arithmetic command
	*/
	void writeArtithmetic(string command);
	/**
	Writes the assembly code that is the
	translation of the given command,
	where command is either C_PUSH or C_POP
	*/
	void writePushPop(TYPE_COMMAND command, string segment, int index);
	/**
	Writes the assembly code that effects
	the VM initialization, also called
	bootstrap code. This code must be placed
	at the beginning of the output file
	*/
	void writeInit();
	/**
	Writes the assembly code that effects
	the label command
	*/
	void writeLabel(string lbl);
	/**
	Writes the assembly code that effects
	the goto command
	*/
	void writeGoto(string strGoto);
	/**
	Writes the assembly code that effects
	the if-goto command
	*/
	void writeIf(string strIf);
	/**
	Writes the assembly code that effects
	the call command
	*/
	void writeCall(string functionName, int numArgs);
	/**
	Writes the assembly code that effects
	the return command
	*/
	void writeReturn();
	/**
	Writes the assembly code that effects
	the function command
	*/
	void writeFunction(string functionName, int numLocals);

private:
	ostream &m_out;
	string m_fileName, m_funcName;

	unsigned int ret_eq, ret_gt, ret_lt, ret_addr_call;
	//stack<int> m_stack;
};

#endif
