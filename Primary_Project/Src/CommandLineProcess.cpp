#include"CommandLineProcess.h"

using namespace std;

flagParams commandProcess(int argumentCount, char* argumentList[])
{
	flagParams argResult;

	argResult.count = argumentCount;
	
	if (argumentCount > 0)
		//cout << "no arguments entered!\n";

		// this process makes sure that any array always starts at 1 and not at an NULL i.e value! 
		argResult.arg_list = string(argumentList[argumentCount - 1]);
	else
		argResult.arg_list = "NaN";

	return argResult;
		
}

void PrintList(flagParams& list)
{
	cout << ">: " << list.count << "Flag type: " << list.arg_list;
}

