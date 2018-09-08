#include "Generator.hpp"
#include <algorithm>

Generator::Generator(std::string fileName)
    : m_FileName(std::move(fileName)) {
    m_ClassName = ParseClassName(m_FileName);
}

std::string Generator::ParseClassName(const std::string &fileName) {

    int index1 = fileName.find_last_of('/');
    int index2 = fileName.find_last_of('.');
    std::string className = fileName.substr(index1 + 1,
                                            index2 - index1 - 1);
    return className;
}

std::string Generator::GenerateConstructor()
{
    std::string constructor = m_ClassName + "();\n";
    return constructor;
}

std::string Generator::GenerateDestructor() {
    std::string destructor = "~" + m_ClassName + "();\n";
    return destructor;
}

std::string Generator::GenerateCopyConstructor() {
    std::string copyCosntructor = m_ClassName + "(const " + m_ClassName +
                                  "& other) = default;\n";
    return copyCosntructor;
}

std::string Generator::GenerateMoveConstructor() {
    std::string copyCosntructor = m_ClassName + "(" + m_ClassName +
                                  "&& other) noexcept(true) = default;\n";
    return copyCosntructor;
}

std::string Generator::GenerateCopyAssignmentOperator() {
    std::string copyCosntructor = m_ClassName + " &operator=(const " +
                                  m_ClassName + "& other) = default;\n";
    return copyCosntructor;
}

std::string Generator::GenerateMoveAssignmentOperator() {
    std::string copyCosntructor = m_ClassName + " &operator=(" + m_ClassName +
                                  "&& other) noexcept(true) = default;\n";
    return copyCosntructor;
}

GuardPair Generator::GenerateHeaderGuards() {
    GuardPair guardPair;
    std::string definition = m_FileName;
    size_t index = definition.find('/');
    if (index != std::string::npos) {
        definition = definition.substr(index + 1, std::string::npos);
    }
    int l = definition.length();
    for (int i = 0; i < l; ++i) {
        definition[i] = toupper(definition[i]);
    }
    std::replace(definition.begin(), definition.end(), '/', '_');
    std::replace(definition.begin(), definition.end(), '.', '_');
    guardPair.topGuard = "#ifndef " + definition + "\n#define " + definition + "\n\n";
    guardPair.bottomGuard = "\n#endif // " + definition + "\n";
    return guardPair;
}
