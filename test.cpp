#include <cstdio>
#include "Function.hpp"
#include "Command.hpp"


int main(void) {
/*
	Function sq{{
		Command::push_a,
		Command::push_a,
		Command::multiply
	}};

	long (*square)(long) = sq.get<1>();

	long input;
	while (std::scanf("%ld", &input) == 1) {
		std::printf("%ld: %ld\n", input, (*square)(input));
	}
*/
	std::vector<Command> cmds;
	int argc = 0;
	while (true) {
		char cmd_name;
		if (long value; scanf("%ld", &value) == 1) {
			cmds.push_back(Command::push_value(value));
		} else if (scanf(" %c", &cmd_name) == 1) {
			if (cmd_name == 'Q') break;
			switch (cmd_name) {
			case 'a':
				argc = (argc < 1) ? 1 : argc;
				cmds.push_back(Command::push_a);
				break;
			case 'b':
				argc = (argc < 2) ? 2 : argc;
				cmds.push_back(Command::push_b);
				break;
			case 'c':
				argc = (argc < 3) ? 3 : argc;
				cmds.push_back(Command::push_c);
				break;
			case 'd':
				argc = (argc < 4) ? 4 : argc;
				cmds.push_back(Command::push_e);
				break;
			case 'e':
				argc = (argc < 5) ? 5 : argc;
				cmds.push_back(Command::push_e);
				break;
			case 'f':
				argc = 6;
				cmds.push_back(Command::push_f);
				break;
			case '+':
				cmds.push_back(Command::add);
				break;
			case '-':
				cmds.push_back(Command::subtract);
				break;
			case '*':
				cmds.push_back(Command::multiply);
				break;
			case '/':
				cmds.push_back(Command::divide);
				break;
			case '%':
				cmds.push_back(Command::mod);
				break;
			default:
				printf("Unknown command: %c\n", cmd_name);
				return -1;
			}
		} else {
			printf("Unrecognized token\n");
			return -1;
		}
	}

	Function function{std::move(cmds)};

	auto *func = function.get<6>();
	long args[6];

	printf("argc = %d\n", argc);
	if (argc == 0) {
		printf("%ld\n", func(0,0,0,0,0,0));
		return 0;
	}

	bool running = true;
	while (running) {
		printf(">>> ");
		fflush(stdout);
		for (int i = 0; i < argc; ++i) {
			if (scanf("%ld", &args[i]) != 1) {
				running = false;
				printf("\n");
				break;
			}
		}
		if (running) {
			printf("%ld\n", func(args[0], args[1], args[2], args[3], args[4], args[5]));
		}
	}
}
