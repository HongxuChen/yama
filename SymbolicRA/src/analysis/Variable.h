#ifndef SRA_VARIABLE_H__
#define SRA_VARIABLE_H__

/**
 * This class is mostly a wrapper of 
 * LLVM::Value
 */
class Variable {
  // TODO: define the class Variable
public:
    Value * getValue(); 
    Variable(Value *v) : value(v) {}
private:
    Value * value;
};

#endif
