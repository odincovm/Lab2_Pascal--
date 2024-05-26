#include "HierarchicalList.h"
#include "SyntacsisControler.h"
#include <iostream>
#include <fstream>
#include <string>



class Compiler {
private:
    // „лены класса
    ifstream inputFile;
    HierarchicalList program;
    SyntacsisControler ctrl;

    // ћетоды
    void parse();
    void generateMachineCode();
    void writeMachineCode();

public:
    Compiler(const string& inputFile);
    void compile();
}; 

