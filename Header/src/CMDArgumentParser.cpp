#include "CMDArgumentParser.hpp"
#include <fstream>
#include <iostream>
#include <string>

CMDArgumentParser::CMDArgumentParser(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Please specify file name" << std::endl;
		exit(1);
	} else {
		GuardPair guardPair;
		for (int i = 1; i < argc; ++i) {
			std::string arg = argv[i];
			if (m_X) {
				m_LineNumber = strtol(arg.c_str(), nullptr, 10);
				m_X = false;
			} else if (arg[0] == '-') {
				if (m_FileName.empty()) {
					std::cout << "First argument is the file name" << '\n';
					exit(1);
				}
				ParseOption(arg);
			} else {
				m_FileName = arg;
				m_Generator = std::make_unique<Generator>(m_FileName);
			}
		}
	}
}

void CMDArgumentParser::ParseOption(const std::string &arg) {
	int l = arg.length();
	for (int j = 1; j < l; ++j) {
		switch (arg[j]) {
		case 'x': // line number
			m_X = true;
			break;
		case 'g': // default constructor
			m_GuardPair = m_Generator->GenerateHeaderGuards();
			break;
		case 'c': // default constructor
			m_Prototypes << "    " << m_Generator->GenerateConstructor();
			break;
		case 'd': // destructor
			m_Prototypes << "    " << m_Generator->GenerateDestructor();
			break;
		case 'm': // move constructor
			m_Prototypes << "    " << m_Generator->GenerateMoveConstructor();
			break;
		case 'n': // move assignment operator
			m_Prototypes << "    "
									 << m_Generator->GenerateMoveAssignmentOperator();
			break;
		case 'k': // copy constructor
			m_Prototypes << "    " << m_Generator->GenerateCopyConstructor();
			break;
		case 'a': // copy assignment operator
			m_Prototypes << "    "
									 << m_Generator->GenerateCopyAssignmentOperator();
			break;
		default:
			std::cout << "Unknown option: " << arg[j] << '\n';
			exit(1);
		}
	}
}
