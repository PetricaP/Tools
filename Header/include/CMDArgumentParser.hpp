#ifndef CMDARGUMENTPARSER_HPP
#define CMDARGUMENTPARSER_HPP

#include "Generator.hpp"
#include <memory>
#include <sstream>

class CMDArgumentParser {
private:
    std::stringstream m_Prototypes;
    GuardPair m_GuardPair;
    bool m_X = false;
    int m_LineNumber = 0;
    std::string m_FileName;
    std::unique_ptr<Generator> m_Generator;
public:
    CMDArgumentParser(int argc, char *argv[]);
    void ParseOption(const std::string &arg);
    std::string GerPrototypes() const { return m_Prototypes.str(); }
    GuardPair GetGuardPair() const { return m_GuardPair; }
    std::string GetFileName() const { return m_FileName; }
    int GetLineNumber() const { return m_LineNumber; }
};

#endif // CMDARGUMENTPARSER_HPP
