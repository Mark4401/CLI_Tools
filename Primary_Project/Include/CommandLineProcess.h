#ifndef COMMAND_LINE_PROCESS_H
#define COMMAND_LINE_PROCESS_H

#include"Internal.h"

using namespace std;

struct flagParams
{
	int count;
	string arg_list;
};

flagParams commandProcess(int argumentCount, char* argumentList[]);

void PrintList(flagParams& list);
#endif // COMMAND_LINE_PROCESS_H
