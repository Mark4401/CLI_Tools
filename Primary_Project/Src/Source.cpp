#include"internal.h"

using namespace std;

void argPars(int argc, char* argv[])
{
	int n = 0;
	bool AllArgsPassed = false;


	while (!AllArgsPassed)
	{
		if (n >= argc)
		{
			AllArgsPassed = true;
			break;
		}

		string flag(argv[n]);

		cout << n << ": " << flag << endl;

		n++; // Go to next argument
	}
}

int main(int argc, char* argv[])
{
	cout << "Hello World!\n";

	argPars(argc, argv);

	return 0;
}