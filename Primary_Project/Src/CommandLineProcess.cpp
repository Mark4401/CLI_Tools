#include"CommandLineProcess.h"

using namespace std;

void userRequest()
{
	const int MAX_INPUT_LEN = 256;
	char inputLine[MAX_INPUT_LEN];

	cout << "> ";
	cin.getline(inputLine, MAX_INPUT_LEN);

	cout << "\n";

	flagParams EntryArgs;
	EntryArgs.count = 1;

	char* token = strtok(inputLine, " ");

	while (token != nullptr && EntryArgs.count < MAX_LIST_LIMIT)
	{
		EntryArgs.argList[EntryArgs.count] = token;
		EntryArgs.count++;
		token = strtok(nullptr, " ");
	}

	PrintList(EntryArgs);
}

void RequestLoop()
{
	while (true)
	{
		cout << "\nWould you like to try again? (Y or N): ";
		char response;
		cin >> response;
		cin.ignore(); // clear trailing newline

		if (response != 'Y' && response != 'y')
		{
			cout << "Session ended!\n";
			break;
		}
		else
		{
			userRequest();
		}
	}
}

flagParams commandProcess(int argumentCount, char* argumentList[])
{
	flagParams argResult;

	argResult.count = 0;

	for (int i = 0; i < argumentCount && i < MAX_LIST_LIMIT; i++)
	{
		argResult.argList[i] = argumentList[i];
		argResult.count++;
	}
		
	// Accurate: warn only if more than 15 were passed
	if (argumentCount > MAX_LIST_LIMIT)
	{
		cout << "\nOnly the first " << (MAX_LIST_LIMIT - 1) << " arguments will be processed. "
			<< (argumentCount - MAX_LIST_LIMIT) << " ignored.\n\n";
	}

	return argResult;
}

void PrintList(flagParams& list)
{
	if (list.count <= 1)
	{
		cout << "No Arguments added!\nOnly the EXE name.\n";
		return;
	}

	int n = 1;
	
	while (n < list.count)
	{
		string flag = list.argList[n];
		
		cout << "> " << n << " | Flag: " << flag << endl;
		
		n++;
	}

	// Inform user if they hit the upper limit (could mean some args were ignored)
	if (list.count == MAX_LIST_LIMIT)
	{
		cout << "\nLimit reached: only first " << (MAX_LIST_LIMIT - 1)
			<< " arguments were printed.\n\n";
	}
}

