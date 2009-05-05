#include <queue>
#include <iostream>
#include "fsm.h"

////////////////////////////////////////////////////////////////////////////////

int main()
{
	FSM microwave;

	char input;
	Event e;

    std::cout << "Hello Microwave!\n\n"
        << "To open microwave door type 'o'\n"
        << "To close microwave door type 'c'\n"
        << "To add one minute type '+'\n"
        << "To subtract one minute type '-'\n"
        << "To wait one minute type 'w'\n\n";

	while (std::cin >> input)
	{
		switch (input)
		{
		case 'o':
			e = OPEN_DOOR;
			break;
		case 'c':
			e = CLOSE_DOOR;
			break;
		case '+':
			e = ADD_TIME;
			break;
		case '-':
			e = SUB_TIME;
			break;
		case 'w':
			e = DO_NOTHING;
			break;
		default:
			continue;
		}

		microwave.ProcessEvent(e);
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
