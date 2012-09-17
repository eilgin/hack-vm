#include "codewriter.h"

CodeWriter::CodeWriter(ostream &os):m_out(os)
{
	ret_eq=0; ret_gt=0; ret_lt=0;
	ret_addr_call=0;
	
	writeInit();
}

void CodeWriter::setFileName(string fileName)
{
	m_fileName = fileName;
}

void CodeWriter::writeInit()
{
	m_out << "@256" << endl;
	m_out << "D=A" << endl;
	m_out << "@SP" << endl;
	m_out << "M=D" << endl;
	
	// Start executing Sys.init (call Sys.init) : compiler specific
	m_out << "@RET_CALL_" << ret_addr_call << endl; // push return-addr
	m_out << "D=A" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=D" << endl;
	
	m_out << "@LCL" << endl; // push LCL
	m_out << "D=M" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=D" << endl;

	m_out << "@ARG" << endl; // push ARG
	m_out << "D=M" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=D" << endl;

	m_out << "@THIS" << endl; // push THIS
	m_out << "D=M" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=D" << endl;

	m_out << "@THAT" << endl; // push THAT
	m_out << "D=M" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=D" << endl;

	m_out << "@0" << endl; // ARG = SP-n-5 (here, n=0)
	m_out << "D=A" << endl;
	m_out << "@SP" << endl;
	m_out << "D=M-D" << endl;
	m_out << "@5" << endl;
	m_out << "D=D-A" << endl;
	m_out << "@ARG" << endl;
	m_out << "M=D" << endl;
	
	m_out << "@SP" << endl; // LCL = SP
	m_out << "D=M" << endl;
	m_out << "@LCL" << endl;
	m_out << "M=D" << endl;
	
	m_out << "@Sys.init" << endl;
	m_out << "0;JMP" << endl;

	m_out << "(RET_CALL_" << ret_addr_call << ")" << endl;

	++ret_addr_call;



	//m_out << "@JUMP_CMP_TRUE" << endl; // comment when Sys.init exists!
	//m_out << "0;JMP" << endl;
	
	// routine that make @R15=true
	// might be replaced by the routines
	// EQ, LESS & GREATER
	m_out << "(IF_CMP_TRUE)" << endl;
	m_out << "@SP" << endl;
	m_out << "A=M" << endl;
	m_out << "M=-1" << endl; // -1=true
	m_out << "@R15" << endl;
	m_out << "A=M" << endl;
	m_out << "0;JMP" << endl;

	//m_out << "(JUMP_CMP_TRUE)" << endl;
}

void CodeWriter::writeArtithmetic(string command)
{	
	if (command.compare("add") == 0)
	{
		m_out << "@SP" << endl;
		m_out << "AM=M-1" << endl;
		m_out << "D=M" << endl;
		m_out << "A=A-1" << endl;
		m_out << "M=M+D" << endl; // ADD
	}
	else if (command.compare("sub") == 0)
	{
		m_out << "@SP" << endl;
		m_out << "AM=M-1" << endl;
		m_out << "D=M" << endl;
		m_out << "A=A-1" << endl;
		m_out << "M=M-D" << endl; // SUB
	}
	else if (command.compare("neg") == 0)
	{
		m_out << "@SP" << endl;
		m_out << "A=M-1" << endl;
		m_out << "M=-M" << endl; // NEG
	}
	else if (command.compare("eq") == 0)
	{
		// load return address in R15
		m_out << "@EQ_" << ret_eq << endl;
		m_out << "D=A"  << endl;
		m_out << "@R15" << endl;
		m_out << "M=D" << endl;
		
		// compute value
		m_out << "@SP" << endl;
		m_out << "AM=M-1" << endl;
		m_out << "D=M" << endl;
		m_out << "@SP" << endl;
		m_out << "AM=M-1" << endl;
		m_out << "D=M-D" << endl;

		m_out << "@IF_CMP_TRUE" << endl;
		m_out << "D;JEQ" << endl; // if true, goto COMPARE_TRUE routine
		m_out << "@SP" << endl; // else
		m_out << "A=M" << endl;
		m_out << "M=0" << endl; // Memory[A]=false	
		
		m_out << "(EQ_" << ret_eq << ")" << endl;
		m_out << "@SP" << endl;
		m_out << "M=M+1" << endl;

		++ret_eq;
	}
	else if (command.compare("gt") == 0)
	{
		// load return address in R15
		m_out << "@GT_" << ret_gt << endl;
		m_out << "D=A"  << endl;
		m_out << "@R15" << endl;
		m_out << "M=D" << endl;
		
		// compute value
		m_out << "@SP" << endl;
		m_out << "AM=M-1" << endl;
		m_out << "D=M" << endl;
		m_out << "@SP" << endl;
		m_out << "AM=M-1" << endl;
		m_out << "D=M-D" << endl;

		m_out << "@IF_CMP_TRUE" << endl;
		m_out << "D;JGT" << endl; // if x-y value is positive, where x=2nd "pop", y=1st
		m_out << "@SP" << endl; // else
		m_out << "A=M" << endl;
		m_out << "M=0" << endl; // Memory[A]=false	
		
		m_out << "(GT_" << ret_gt << ")" << endl;
		m_out << "@SP" << endl;
		m_out << "M=M+1" << endl;

		++ret_gt;
	}
	else if (command.compare("lt") == 0)
	{
		// load return address in R15
		m_out << "@LT_" << ret_lt << endl;
		m_out << "D=A"  << endl;
		m_out << "@R15" << endl;
		m_out << "M=D"  << endl;
		
		// compute value
		m_out << "@SP" << endl;
		m_out << "AM=M-1" << endl;
		m_out << "D=M" << endl;
		m_out << "@SP" << endl;
		m_out << "AM=M-1" << endl;
		m_out << "D=M-D" << endl;

		m_out << "@IF_CMP_TRUE" << endl;
		m_out << "D;JLT" << endl; // if x-y value is negative, where x=2nd "pop", y=1st
		m_out << "@SP" << endl; // else
		m_out << "A=M" << endl;
		m_out << "M=0" << endl; // Memory[A]=false	
		
		m_out << "(LT_" << ret_lt << ")" << endl;
		m_out << "@SP" << endl;
		m_out << "M=M+1" << endl;

		++ret_lt;
	}
	else if (command.compare("and") == 0)
	{
		m_out << "@SP" << endl;
		m_out << "AM=M-1" << endl;
		m_out << "D=M" << endl;
		m_out << "A=A-1" << endl;
		m_out << "M=M&D" << endl; // AND
	}
	else if (command.compare("or") == 0)
	{
		m_out << "@SP" << endl;
		m_out << "AM=M-1" << endl;
		m_out << "D=M" << endl;
		m_out << "A=A-1" << endl;
		m_out << "M=M|D" << endl; // OR
	}
	else if (command.compare("not") == 0)
	{
		m_out << "@SP" << endl;
		m_out << "AM=M+1" << endl;
		m_out << "A=A-1" << endl;
		m_out << "M=!M" << endl; // NOT
	}
}

void CodeWriter::writePushPop(TYPE_COMMAND command, string segment, int index)
{
	if (command == C_PUSH)
	{
		if (segment.compare("constant") == 0)
		{
			m_out << "@" << index << endl;
			m_out << "D=A" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M+1" << endl;
			m_out << "A=A-1" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("argument") == 0)
		{
			m_out << "@" << index << endl; // not an actual function ARG
			m_out << "D=A" << endl;
			m_out << "@ARG" << endl;
			m_out << "A=M+D" << endl;
			m_out << "D=M" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M+1" << endl;
			m_out << "A=A-1" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("local") == 0)
		{
			m_out << "@" << index << endl; // not an actual function ARG
			m_out << "D=A" << endl;
			m_out << "@LCL" << endl;
			m_out << "A=M+D" << endl;
			m_out << "D=M" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M+1" << endl;
			m_out << "A=A-1" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("static") == 0)
		{
			m_out << "@" << m_fileName << "." << index << endl;
			m_out << "D=M" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M+1" << endl;
			m_out << "A=A-1" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("this") == 0)
		{
			m_out << "@" << index << endl; // not an actual function ARG
			m_out << "D=A" << endl;
			m_out << "@THIS" << endl;
			m_out << "A=M+D" << endl;
			m_out << "D=M" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M+1" << endl;
			m_out << "A=A-1" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("that") == 0)
		{
			m_out << "@" << index << endl; // not an actual function ARG
			m_out << "D=A" << endl;
			m_out << "@THAT" << endl;
			m_out << "A=M+D" << endl;
			m_out << "D=M" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M+1" << endl;
			m_out << "A=A-1" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("pointer") == 0)
		{
			m_out << "@" << index+3 << endl; // pointer address start at 3 (THIS)
			m_out << "D=M" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M+1" << endl;
			m_out << "A=A-1" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("temp") == 0)
		{
			m_out << "@" << index+5 << endl; // temp address start at 5
			m_out << "D=M" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M+1" << endl;
			m_out << "A=A-1" << endl;
			m_out << "M=D" << endl;
		}
	}
	else if (command == C_POP)
	{
		if (segment.compare("argument") == 0)
		{
			m_out << "@" << index << endl;
			m_out << "D=A" << endl;
			m_out << "@ARG" << endl;
			m_out << "D=M+D" << endl;
			m_out << "@R14" << endl;
			m_out << "M=D" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M-1" << endl;
			m_out << "D=M" << endl;

			m_out << "@R14" << endl;
			m_out << "A=M" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("local") == 0)
		{
			m_out << "@" << index << endl;
			m_out << "D=A" << endl;
			m_out << "@LCL" << endl;
			m_out << "D=M+D" << endl;
			m_out << "@R14" << endl;
			m_out << "M=D" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M-1" << endl;
			m_out << "D=M" << endl;

			m_out << "@R14" << endl;
			m_out << "A=M" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("static") == 0)
		{
			m_out << "@SP" << endl;
			m_out << "AM=M-1" << endl;
			m_out << "D=M" << endl;
			m_out << "@" << m_fileName << "." << index << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("this") == 0)
		{
			m_out << "@" << index << endl;
			m_out << "D=A" << endl;
			m_out << "@THIS" << endl;
			m_out << "D=M+D" << endl;
			m_out << "@R14" << endl;
			m_out << "M=D" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M-1" << endl;
			m_out << "D=M" << endl;

			m_out << "@R14" << endl;
			m_out << "A=M" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("that") == 0)
		{
			m_out << "@" << index << endl;
			m_out << "D=A" << endl;
			m_out << "@THAT" << endl;
			m_out << "D=M+D" << endl;
			m_out << "@R14" << endl;
			m_out << "M=D" << endl;

			m_out << "@SP" << endl;
			m_out << "AM=M-1" << endl;
			m_out << "D=M" << endl;

			m_out << "@R14" << endl;
			m_out << "A=M" << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("pointer") == 0)
		{
			m_out << "@SP" << endl;
			m_out << "AM=M-1" << endl;
			m_out << "D=M" << endl;
			m_out << "@" << index+3 << endl;
			m_out << "M=D" << endl;
		}
		else if (segment.compare("temp") == 0)
		{
			m_out << "@SP" << endl;
			m_out << "AM=M-1" << endl;
			m_out << "D=M" << endl;
			m_out << "@" << index+5 << endl;
			m_out << "M=D" << endl;
		}
	}
}

void CodeWriter::writeLabel(string label)
{
	// write functionName$label or
	// vmFileName&label if there's no funcName
	if (m_funcName.empty())
	{
		m_out << "(" << m_fileName << "$" << label << ")" << endl;
	}
	else
	{
		m_out << "(" << m_funcName << "$" << label << ")" << endl;
	}
}

void CodeWriter::writeGoto(string label)
{
	if (m_funcName.empty())
	{
		m_out << "@" << m_fileName << "$" << label << endl;
	}
	else
	{
		m_out << "@" << m_funcName << "$" << label << endl;
	}
	
	m_out << "0;JMP" << endl;
}

void CodeWriter::writeIf(string label)
{
	// decrement SP value by 1
	m_out << "@SP" << endl;
	m_out << "AM=M-1" << endl;
	m_out << "D=M" << endl;

	if (m_funcName.empty())
	{
		m_out << "@" << m_fileName << "$" << label << endl;
	}
	else
	{
		m_out << "@" << m_funcName << "$" << label << endl;
	}
	
	m_out << "D;JNE" << endl;
}

void CodeWriter::writeCall(string functionName, int numArgs)
{
	m_out << "@RET_CALL_" << ret_addr_call << endl; // push return-addr
	m_out << "D=A" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=D" << endl;
	
	m_out << "@LCL" << endl; // push LCL
	m_out << "D=M" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=D" << endl;

	m_out << "@ARG" << endl; // push ARG
	m_out << "D=M" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=D" << endl;

	m_out << "@THIS" << endl; // push THIS
	m_out << "D=M" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=D" << endl;

	m_out << "@THAT" << endl; // push THAT
	m_out << "D=M" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=D" << endl;

	m_out << "@" << numArgs << endl; // ARG = SP-n-5
	m_out << "D=A" << endl;
	m_out << "@SP" << endl;
	m_out << "D=M-D" << endl;
	m_out << "@5" << endl;
	m_out << "D=D-A" << endl;
	m_out << "@ARG" << endl;
	m_out << "M=D" << endl;
	
	m_out << "@SP" << endl; // LCL = SP
	m_out << "D=M" << endl;
	m_out << "@LCL" << endl;
	m_out << "M=D" << endl;
	
	m_out << "@" << functionName << endl; // goto func
	m_out << "0;JMP" << endl;

	m_out << "(RET_CALL_" << ret_addr_call << ")" << endl;

	++ret_addr_call;
}

void CodeWriter::writeReturn()
{
	m_out << "@LCL" << endl;
	m_out << "D=M" << endl;
	m_out << "@R13" << endl; // R13 -> FRAME
	m_out << "M=D" << endl;  // FRAME=LCL

	m_out << "@5" << endl;
	m_out << "D=A" << endl;
	m_out << "@R13" << endl;
	m_out << "A=M-D" << endl; // FRAME-5
	m_out << "D=M" << endl;   // *(FRAME-5)
	m_out << "@R14" << endl;  // R14 -> RET
	m_out << "M=D" << endl;   // RET= *(FRAME-5)

	m_out << "@SP" << endl;
	m_out << "A=M-1" << endl;
	m_out << "D=M" << endl;  // pop()
	m_out << "@ARG" << endl;
	m_out << "A=M" << endl;
	m_out << "M=D" << endl;  // *ARG=pop()
	m_out << "D=A+1" << endl; // ARG+1
	m_out << "@SP" << endl;
	m_out << "M=D" << endl; // SP = ARG+1

	m_out << "@R13" << endl;
	m_out << "A=M-1" << endl;
	m_out << "D=M" << endl; // *(FRAME-1)
	m_out << "@THAT" << endl;
	m_out << "M=D" << endl;

	m_out << "@2" << endl; // THIS = *(FRAME-2)
	m_out << "D=A" << endl;
	m_out << "@R13" << endl;
	m_out << "A=M-D" << endl;
	m_out << "D=M" << endl;
	m_out << "@THIS" << endl;
	m_out << "M=D" << endl;

	m_out << "@3" << endl; // ARG = *(FRAME-3)
	m_out << "D=A" << endl;
	m_out << "@R13" << endl;
	m_out << "A=M-D" << endl;
	m_out << "D=M" << endl;
	m_out << "@ARG" << endl;
	m_out << "M=D" << endl;

	m_out << "@4" << endl; // LCL = *(FRAME-4)
	m_out << "D=A" << endl;
	m_out << "@R13" << endl;
	m_out << "A=M-D" << endl;
	m_out << "D=M" << endl;
	m_out << "@LCL" << endl;
	m_out << "M=D" << endl;

	m_out << "@R14" << endl; // goto RET
	m_out << "A=M" << endl;
	m_out << "0;JMP" << endl;
}

void CodeWriter::writeFunction(string functionName, int numLocals)
{
	// store the new function's name
	m_funcName = functionName;

	m_out << "(" << m_funcName << ")" << endl;
	m_out << "@" << numLocals << endl;
	m_out << "D=A" << endl;
	m_out << "(LOOP_" << m_funcName << ")" << endl;
	m_out << "D=D-1" << endl;
	m_out << "@SP" << endl;
	m_out << "AM=M+1" << endl;
	m_out << "A=A-1" << endl;
	m_out << "M=0" << endl;
	m_out << "@LOOP_" << m_funcName << endl;
	m_out << "D;JGT" << endl;
	// decrement SP (numLocals=0 means 0 MOVEMENT for SP)
	m_out << "@SP" << endl;
	m_out << "M=M-1" << endl;
}