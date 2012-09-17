#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <boost/filesystem.hpp>

#include "parser.h"
#include "codewriter.h"

using namespace std;
using namespace boost::filesystem;

/* this function use a path class, read the content
and map the data to his path
*/
pair<path, string> assoc_file_to_content(path p)
{
	ifstream in(p.string());

	// read data as a block
	stringbuf sbuf;
	in >> &sbuf;

	// create a string from buffer data
	string buf( sbuf.str() );

	return pair<path, string>(p, buf);
}

int main(int argc, char **argv)
{
	// verify that there's only 1 argument
	if (argc != 2)
	{
		cout << "usage: " << argv[0] << " filename.vm OR directory" << endl;
		exit(1);
	}
	
	string in_ext_type = ".vm";
	string out_ext_type = ".asm";
	path p (argv[1]);
	map<path, string> input_files;

	/*
	first, we test the existence of the pathname. then,
	whether it's a file or a directory, we associate
	the path to the content of each JACK file found
	in order to facilitate their manipulation after
	*/
	try
	{
		if (exists(p))
		{
			if (is_regular_file(p) && p.extension() == in_ext_type)
			{			
				input_files.insert( assoc_file_to_content(p) );
			}
			else if (is_directory(p))
			{
				// we do the same as for one file except we search every files
				// with "in_ext_type" in one directory
				vector<path> vec;
				copy(directory_iterator(p), directory_iterator(), back_inserter(vec));

				typedef vector<path>::iterator path_iter;
				for (path_iter it(vec.begin()), it_end(vec.end()); it != it_end; ++it)
				{
					path p = *it;

					if (p.extension() == in_ext_type)
					{
						input_files.insert( assoc_file_to_content(p) );
					}
					
				}
			}
			else
			{
				cout << p << " exists, but is neither a regular file nor a directory " << endl;
			}
		}
		else
		{
			cout << p << " does not exist" << endl;
		}
	}
	catch(const filesystem_error& e)
	{
		cout << e.what() << endl;
	}

	// initialize the Writer module
	if ( is_directory(p) )
	{
		p /= p.stem().string() + out_ext_type ;
	}
	else
	{
		p.replace_extension( out_ext_type );
	}
	
	ofstream out( p.string() );

	// initialize the analyzer, one parser is created
	// for every file that has been found
	CodeWriter cw(cout);

	for (map<path, string>::iterator it = input_files.begin(), it_end = input_files.end();
		it != it_end; ++it)
	{
		path path = it->first;
		string vmfile = it->second;

		istringstream in( vmfile );
		Parser p = Parser(in);
		// informs the code writer
		cw.setFileName( path.stem().string() );

		while (p.hasMoreCommands())
		{
			p.advance();
			TYPE_COMMAND cmd_t = p.commandType();

			if (cmd_t == NO_COMMAND)
			{
				continue;
			}
			
			string arg1, arg2;

			if (cmd_t != C_RETURN)
				arg1 = p.arg1();
			if (cmd_t == C_PUSH
				|| cmd_t == C_POP
				|| cmd_t == C_FUNCTION
				|| cmd_t == C_CALL)
			{
				arg2 = p.arg2();
			}

			// translate vm code into hack code
			if (cmd_t == C_ARITHMETIC)
				cw.writeArtithmetic(arg1);
			else if (cmd_t == C_PUSH || cmd_t == C_POP)
			{
				int index = atoi(arg2.c_str());
				cw.writePushPop(cmd_t, arg1, index);
			}
			else if (cmd_t == C_LABEL)
			{
				cw.writeLabel(arg1);
			}
			else if (cmd_t == C_GOTO)
			{
				cw.writeGoto(arg1);
			}
			else if (cmd_t == C_IF)
			{
				cw.writeIf(arg1);
			}
			else if (cmd_t == C_CALL)
			{
				int numArgs = atoi(arg2.c_str());
				cw.writeCall(arg1, numArgs);
			}
			else if (cmd_t == C_RETURN)
			{
				cw.writeReturn();
			}
			else if (cmd_t == C_FUNCTION)
			{
				int numLocals = atoi(arg2.c_str());
				cw.writeFunction(arg1, numLocals);
			}
		}
	}

	// close the output file
	out.close();

	return 0;
}