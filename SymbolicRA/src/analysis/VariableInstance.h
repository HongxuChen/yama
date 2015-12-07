#ifndef VARIABLE_INSTANCE_H__
#define VARIABLE_INSTANCE_H__

class SymbolicRange;

/*
 * TODO: this class might be removed,
 * as the LLVM Use class looks like
 * the right one to use.
 */
class VariableInstance {
private:
    Variable * var;
    Instruction * instr;
    SymbolicRange * symRange;
public:
    VariableInstance(Variable* v, Instruction* i) {
        var = v;
	instr = i;
    }

    // TODO: design functions
    Variable * getVariable();
    Instruction * getInstruction();
    SymbolicRange * getSymbolicRange();
};

#endif
