#include"internal.h"
#include"CommandlineProcess.h"
#include"DialogLookUp.h"

using namespace std;

int main(int argc, char* argv[])
{
	flagParams result = commandProcess(argc, argv);
	
	PrintList(result);
	RequestLoop();

	SceneStart();

	return 0;
}