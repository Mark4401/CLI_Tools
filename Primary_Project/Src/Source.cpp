#include"internal.h"
#include"CommandlineProcess.h"

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

		cout << "> " << n << ": " << flag << endl;

		n++; // Go to next argument
	}
}

void nullProc()
{
	cout << "Hello World!\n";

	//argPars(argc, argv);

	while (true)
	{
		// Ask if user wants to try again
		string again;
		cout << "\nWould you like to try again? (Y or N): ";
		cin >> again;
		cin.ignore(); // Clear newline from input buffer

		if (again != "Y" && again != "y")
		{
			cout << "Session ended!\n";
			break;
		}
		else
		{
			string input;
			cout << "\nEnter arguments: ";
			getline(cin, input); // Read entire line of input

			// Split input into tokens
			vector<string> tokens;
			stringstream ss(input);
			string token;

			while (ss >> token)
				tokens.push_back(token);

			// Convert to char* array
			vector<char*> argv;
			for (string& arg : tokens)
				argv.push_back(&arg[0]);

			int argc = static_cast<int>(argv.size());

			// Parse the arguments
			argPars(argc, argv.data());
		}

	}
}

int main(int argc, char* argv[])
{
	flagParams result = commandProcess(argc, argv);
	
	cout << "Count: " << result.count << ", Last flag: " << result.arg_list << endl;

	return 0;
}