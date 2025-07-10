#ifndef COMMAND_LINE_PROCESS_H
#define COMMAND_LINE_PROCESS_H

#include"Internal.h"
//#include <string>

using namespace std;

/// <summary>
/// Max amount of flags able to be processed while adding 1 for exclusion of 0 or 1 for the EXE name!
/// </summary>
const int MAX_LIST_LIMIT = 16;

struct flagParams
{
	int count;
	string argList[MAX_LIST_LIMIT];
};


flagParams commandProcess(int argumentCount, char* argumentList[]);

void PrintList(flagParams& list);
void RequestLoop();


#endif // COMMAND_LINE_PROCESS_H
