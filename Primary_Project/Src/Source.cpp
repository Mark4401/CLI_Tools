#include"internal.h"
#include"CommandlineProcess.h"

using namespace std;

int main(int argc, char* argv[])
{
	flagParams result = commandProcess(argc, argv);
	
	PrintList(result);
	RequestLoop();

	return 0;
}