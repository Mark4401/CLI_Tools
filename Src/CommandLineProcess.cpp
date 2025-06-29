#include"CommandLineProcess.h"

cmd_Flags CommandLineProc::Preocess(int argc, char* argv[])
{
	if (argc < 2) return cmd_Flags::HELP;

	if (argv[1] == string("-new") || argv[1] == string("-n"))
		return cmd_Flags::NEW;
	
	if (argv[1] == string("-help") || argv[1] == string("-h"))
		return cmd_Flags::HELP;

	if (argv[1] == string("-edit") || argv[1] == string("-d"))
		return cmd_Flags::EDIT;
	
	if (argv[1] == string("-print") || argv[1] == string("-p"))
		return cmd_Flags::PRINT;
	
	if (argv[1] == string("-terminate") || argv[1] == string("-t"))
		return cmd_Flags::TERNIMATE;


	return cmd_Flags::UNKNOWN;
}

bool CommandLineProc::Authetication(cmd_Flags Flag)
{
	switch (Flag)
	{
		case cmd_Flags::NEW:
			return true;

		case cmd_Flags::PRINT:
			return true;

		case cmd_Flags::EDIT:
			return true;

		case cmd_Flags::HELP:
			return true;

		case cmd_Flags::UNKNOWN:
			return true;

		case cmd_Flags::TERNIMATE:
			return true;
	}
	return true;
}

void CommandLineProc::deploy(cmd_Flags Flag)
{
	switch (Flag) {
		case cmd_Flags::NEW:
			std::cout << "Creating a new invoice...\n";
			break;
		
		case cmd_Flags::PRINT:
			std::cout << "Printing invoice...\n";
			break;
		
		case cmd_Flags::EDIT:
			std::cout << "Editing In progress...\n";
			break;

		case cmd_Flags::HELP:
			std::cout << "Usage:\n  --new | -n    Create a new invoice\n"
				<< "  --print | -p  Print invoice\n"
				<< "  --help | -h   Show help\n";
			break;
		
		case cmd_Flags::TERNIMATE:
			std::cout << "Ending Tool!";
			break;

		case cmd_Flags::UNKNOWN:

		default:
			std::cout << "Unknown command. Use --help for usage.\n";
			break;
	}
}
