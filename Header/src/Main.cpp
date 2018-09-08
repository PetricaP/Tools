#include "CMDArgumentParser.hpp"
#include <fstream>

int main(int argc, char *argv[]) {
    CMDArgumentParser parser(argc, argv);
    std::string prototypes = parser.GerPrototypes();
    GuardPair guardPair = parser.GetGuardPair();
    std::string fileName = parser.GetFileName();
    std::ifstream input(fileName);
    int lineNumber = parser.GetLineNumber();
    int count = 0;
    std::string line;
    std::stringstream newFile;
    newFile << guardPair.topGuard;
    while (std::getline(input, line)) {
        ++count;
        newFile << line << '\n';
        if (lineNumber == 0) {
            if (line.find("public:") != std::string::npos) {
                newFile << prototypes;
            }
        } else {
            if (count == lineNumber) {
                newFile << prototypes;
            }
        }
    }
    input.close();
    newFile << guardPair.bottomGuard;
    std::ofstream output(fileName);
    output << newFile.str();
    output.close();
}
