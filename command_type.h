#ifndef _COMMAND_TYPE_H
#define _COMMAND_TYPE_H

// type of Commands
enum TYPE_COMMAND {
	C_ARITHMETIC,
	C_PUSH, C_POP,
	C_LABEL,
	C_GOTO, C_IF,
	C_FUNCTION,
	C_RETURN,
	C_CALL,
	NO_COMMAND
};

#endif
