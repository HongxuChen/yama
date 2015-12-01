#ifndef SYM_TABLE_H__
#define SYM_TABLE_H__
#include <map>

class Variable;
class SymbolicRange;

class SymTable {
public:
    static SymTable * instance;
    static SymTable * getInstance();
    
    void putRange(Variable* V, SymbolicRange *R); 
    SymbolicRange * getRange(Variable* V); 
    bool isInTable(Variable * V);    
private:
    SymTable();
    std::map<Variable *, SymbolicRange*> * table;
};
#endif
