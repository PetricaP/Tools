#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <string>

struct GuardPair {
    std::string topGuard;
    std::string bottomGuard;
};

class Generator {
private:
    std::string m_FileName;
    std::string m_ClassName;
public:
	explicit Generator(std::string fileName);
    static std::string ParseClassName(const std::string &fileName);
    GuardPair GenerateHeaderGuards();
    std::string GenerateConstructor();
    std::string GenerateDestructor();
    std::string GenerateCopyConstructor();
    std::string GenerateMoveConstructor();
    std::string GenerateCopyAssignmentOperator();
    std::string GenerateMoveAssignmentOperator();
};

#endif
