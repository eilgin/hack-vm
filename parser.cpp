#include <cctype>
#include "parser.h"

using namespace std;

Parser::Parser(istringstream &iss):m_in(iss)
{
}

bool Parser::hasMoreCommands()
{
	return m_in.good();
}

void Parser::advance()
{
	if(hasMoreCommands())
	{
		// read line by line discarding white spaces
		// empty line and comments "//"
		string comment("//");
		string line;

		char *nowhere = new char[128];
		m_in.getline(nowhere, 128);
		line = nowhere;
		delete nowhere;
		
		// before we add this line to the buffer
		// we discard useless chars
		size_t found; // indicates the position of found whitespaces/comments
		
		// suppress comments
		found = line.find(comment);
		if (found != string::npos)
			line=line.substr(0, found);

		// we don't add a line unless it's not empty
		if (!line.empty())
		{
			// check if the line is a acceptable character
			/*int length = line.size();
			for (int i=0; i < length; i++)
			{
				char c = line[i];
				if (!ispunct(c) || !isalnum(c))
				{
					m_currentCommand = "";
					return;
				}
			}*/

			m_currentCommand = line;
		}
		else
			m_currentCommand = "";
	}
}

TYPE_COMMAND Parser::commandType()
{
	// check first if there's a cmd
	if (m_currentCommand.empty())
		return NO_COMMAND;


	TYPE_COMMAND cmd_t;

	// C_ARITHMETIC
	if (m_currentCommand.find("add") != string::npos
		|| m_currentCommand.find("sub") != string::npos
		|| m_currentCommand.find("neg") != string::npos
		|| m_currentCommand.find("eq") != string::npos
		|| m_currentCommand.find("gt") != string::npos
		|| m_currentCommand.find("lt") != string::npos
		|| m_currentCommand.find("and") != string::npos
		|| m_currentCommand.find("or") != string::npos
		|| m_currentCommand.find("not") != string::npos)
	{
		cmd_t = C_ARITHMETIC;
	}
	// C_PUSH
	else if (m_currentCommand.find("push") != string::npos)
	{
		cmd_t = C_PUSH;
	}
	// C_POP
	else if (m_currentCommand.find("pop") != string::npos)
	{
		cmd_t = C_POP;
	}
	// C_LABEL
	else if (m_currentCommand.find("label") != string::npos)
	{
		cmd_t = C_LABEL;
	}
	// C_IF
	else if (m_currentCommand.find("if-goto") != string::npos)
	{
		cmd_t = C_IF;
	}
	// C_GOTO
	else if (m_currentCommand.find("goto") != string::npos)
	{
		cmd_t = C_GOTO;
	}
	// C_FUNCTION
	else if (m_currentCommand.find("function") != string::npos)
	{
		cmd_t = C_FUNCTION;
	}
	// C_RETURN
	else if (m_currentCommand.find("return") != string::npos)
	{
		cmd_t = C_RETURN;
	}
	// C_CALL
	else if (m_currentCommand.find("call") != string::npos)
	{
		cmd_t = C_CALL;
	}

	return cmd_t;
}

string Parser::arg1()
{
	string sym;

	// first, we need to trim the currentcommand
	size_t trim = m_currentCommand.find_last_not_of(" ");
	m_currentCommand.erase(trim+1);

	// assume that commandType isn't RETURN or NO_CMD
	if (commandType() == C_ARITHMETIC)
	{
		return m_currentCommand;
	}
	else if (commandType() == C_LABEL
		|| commandType() == C_GOTO
		|| commandType() == C_IF)
	{
		sym = m_currentCommand;

		size_t delim_b = sym.find(" ");
		sym.erase(0, delim_b+1);

		// erase here only if there's more whitespaces
		size_t delim_e = sym.find(" ");
		if (delim_e != string::npos)
			sym.erase(delim_e);
	}
	else if (commandType() == C_PUSH
		|| commandType() == C_POP
		|| commandType() == C_CALL
		|| commandType() == C_FUNCTION)
	{
		sym = m_currentCommand;

		size_t delim_b = sym.find(" ");
		sym.erase(0, delim_b+1);

		size_t delim_e = sym.find(" ");
		sym.erase(delim_e);
	}

	return sym;
}

string Parser::arg2()
{
	string dest = m_currentCommand;

	size_t lastChar = dest.find_last_not_of(" ");
	size_t lastSpace = dest.find_last_of(" ");

	// if there's still spaces after the last char,
	// erase them, and try again to find the last space
	if (lastChar < lastSpace)
	{
		dest.erase(lastChar+1);
		lastSpace = dest.find_last_of(" ");
		dest = dest.substr(lastSpace+1, lastChar);
	}
	else
	{
		dest = dest.substr(lastSpace+1, lastChar);
	}

	return dest;
}