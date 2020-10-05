#include <iostream>
#include "Function.hpp"
#include "Command.hpp"

#include <string_view>
#include <string>
#include <tuple>
#include <fstream>

static inline void trim_leading_spaces(std::string_view &code) {
	while (code.size() > 0
		   && (code[0] == ' '
			   || code[0] == '\n'
			   || code[0] == '\t'
			   )
		   ) code.remove_prefix(1);
}
	

std::tuple<int, std::vector<Command>> parse_helper(std::string_view &code) {
	const std::string_view code_ = code;
	
	std::tuple<int, std::vector<Command>> ret;
	int &argc = std::get<int>(ret);
	std::vector<Command> &cmds = std::get<std::vector<Command>>(ret);
	while (trim_leading_spaces(code), code.size() > 0) {
		switch (code[0]) {
			case 'a':
				argc = (argc < 1) ? 1 : argc;
				cmds.push_back(Command::push_a);
				code.remove_prefix(1);
				break;
			case 'b':
				argc = (argc < 2) ? 2 : argc;
				cmds.push_back(Command::push_b);
				code.remove_prefix(1);
				break;
			case 'c':
				argc = (argc < 3) ? 3 : argc;
				cmds.push_back(Command::push_c);
				code.remove_prefix(1);
				break;
			case 'd':
				argc = (argc < 4) ? 4 : argc;
				cmds.push_back(Command::push_e);
				code.remove_prefix(1);
				break;
			case 'e':
				argc = (argc < 5) ? 5 : argc;
				cmds.push_back(Command::push_e);
				code.remove_prefix(1);
				break;
			case 'f':
				argc = 6;
				cmds.push_back(Command::push_f);
				code.remove_prefix(1);
				break;
			case '+':
				cmds.push_back(Command::add);
				code.remove_prefix(1);
				break;
			case '-':
				cmds.push_back(Command::subtract);
				code.remove_prefix(1);
				break;
			case '*':
				cmds.push_back(Command::multiply);
				code.remove_prefix(1);
				break;
			case '/':
				cmds.push_back(Command::divide);
				code.remove_prefix(1);
				break;
			case '%':
				cmds.push_back(Command::mod);
				code.remove_prefix(1);
				break;
				
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				{
					long value = code[0] - '0';
					code.remove_prefix(1);
					while (code.size() > 0 && code[0] >= '0' && code[0] <= '9') {
						value = value * 10 + (code[0] - '0');
						code.remove_prefix(1);
					}
					cmds.push_back(Command::push_value(value));
				}
				break;
			
			case 'p':
				{
					code.remove_prefix(1);
					unsigned index = 0;
					while (code.size() > 0 && code[0] >= '0' && code[0] <= '9') {
						index = index * 10 + (code[0] - '0');
						code.remove_prefix(1);
					}
					cmds.push_back(Command::push_stack_index(index));
				}
				break;
			
			case 's':
				{
					code.remove_prefix(1);
					unsigned index = 0;
					while (code.size() > 0 && code[0] >= '0' && code[0] <= '9') {
						index = index * 10 + (code[0] - '0');
						code.remove_prefix(1);
					}
					cmds.push_back(Command::pop_stack_index(index));
				}
				break;
			case '{':
				{
					code.remove_prefix(1);
					auto [largc, lcmds] = parse_helper(code);
					trim_leading_spaces(code);
					
					if (code.size() < 1) {
						std::cerr << "Loop ended with EOF" << '\n';
					} else if (code[0] != '}') {
						std::cerr << "Unrecognized loop end: " << code[0] << '\n';
					} else code.remove_prefix(1);
					argc = (argc < largc) ? largc : argc;
					cmds.push_back(Command::while_loop(lcmds));
				}
				break;
			case '}':
				return ret;
				
			default:
				std::cerr << "Unrecognized command: " << code[0] << '\n';
				return ret;
		}
	}
	return ret;
}


int main(int argc, char **argv) {
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
	/*
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

			case 'p':{
				unsigned index;
				if (scanf("%u", &index) != 1) {
					printf("Unrecognized push number\n");
					return -1;
				}
				cmds.push_back(Command::push_stack_index(index));
				break;}
			case 's':{
				unsigned index;
				if (scanf("%u", &index) != 1) {
					printf("Unrecognized store/pop number\n");
					return -1;
				}
				cmds.push_back(Command::pop_stack_index(index));
				break;}
			default:
				printf("Unknown command: %c\n", cmd_name);
				return -1;
			}
		} else {
			printf("Unrecognized token\n");
			return -1;
		}
	}
	*/
	
	std::string line;
	
	if (argc < 2) {
		getline(std::cin, line);
	} else {
		std::ifstream file{argv[1]};
		if (!file.is_open()) {
			std::cerr << "Could not open file: " << argv[1] << std::endl;
			return -1;
		}
		getline(file, line);
	}
	
	std::string_view line_view = line;
	
	auto [paramcount, cmds] = parse_helper(line_view);

	Function function{std::move(cmds)};

	auto *func = function.get<6>();
	long args[6];

	printf("paramcount = %d\n", paramcount);
	if (paramcount == 0) {
		printf("%ld\n", func(0,0,0,0,0,0));
		return 0;
	}

	bool running = true;
	while (running) {
		std::cout << ">>> " << std::flush;
		for (int i = 0; i < paramcount; ++i) {
			std::cin >> args[i];
			if (!std::cin) {
				running = false;
				std::cout << '\n';
				break;
			}
		}
		if (running) {
			std::cout << func(args[0], args[1], args[2], args[3], args[4], args[5]) << '\n';
		}
	}
}
