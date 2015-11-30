#ifndef VARIABLE_INSTANCE_H__
#define VARIABLE_INSTANCE_H__

class SymbolicRange;

class VariableInstance {
private:
    Variable * var;
    Instruction * instr;
    SymbolicRange * symRange;
public:
    // TODO: design functions
    Variable * getVariable();
    Instruction * getInstruction();
    SymbolicRange * getSymbolicRange();
};

#endif
