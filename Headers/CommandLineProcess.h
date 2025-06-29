#ifndef COMMAND_LINE_PROCESS_H
#define COMMAND_LINE_PROCESS_H

#include <iostream>
#include<string>

using namespace std;

enum class cmd_Flags {NEW, PRINT, EDIT, HELP, UNKNOWN, TERNIMATE};

class CommandLineProc
{

private:

public:

	cmd_Flags Preocess(int argc, char* argv[]);

	bool Authetication(cmd_Flags Flag);

	void deploy(cmd_Flags Flag);
};

#endif // !COMMAND_LINE_PROCESS_H
