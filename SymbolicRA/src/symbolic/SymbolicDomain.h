#ifndef SYMBOLIC_DOMAIN_H__
#define SYMBOLIC_DOMAIN_H__
class SymbolicExpr;

class SymbolicDomain {
    // TODO: main the set of symbolic expressions

    // check if the given expression is 
    // an affine function of an existing 
    // expression in the domain
    bool hasAffineExpr(SymbolicExpr expr);
public:
    // add a symbolic expression into 
    // the domain, creating new 
    // expression if necessary   
    bool addSymbolicExpr(SymbolicExpr expr);
    
};

#endif
