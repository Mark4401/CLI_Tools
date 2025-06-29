#include <iostream>
#include"CommandLineProcess.h"

using namespace std;

int main(int argc, char* argv[])
{
	CommandLineProc Proc;

	cmd_Flags command = Proc.Preocess(argc, argv);

	if (!Proc.Authetication(command))
	{
		cerr << "Invalid command or arguments.\n";

		return -1;
	}

	Proc.deploy(command);

	return 0;
}