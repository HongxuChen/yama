/*
 * This is the main entry of the 
 * symbolic range analysis.
 */


#include "VariableInstance.h"
#include "../symbolic/SymbolicRange.h"
#include "../symbolic/SymbolicExpr.h"
#include "../symbolic/AtomicSymbol.h"

using namespace std;
// need also use namespace llvm;

/*
 * Algorithm 1 in the paper
 */
SymbolicRange computeUseRange(VariableInstance vInst) {
    Variable * V = vInst->getVariable();
    computeDefRange(V);

    Instruction * P = vInst->getInstruction(); 

    // TODO: think about the copy of SymbolicRange
    return refineDefRange(V, P); 
}

// TODO: implement this function based 
// on the supported kinds of instructions 
// in Figure 3
void extractOperands(Variable* variable, vector<Variable*>& vec) {
    Value * val = variable->getValue();

    if (isa<User>(val)) {
	User * user = dynamic_cast<User*>(val);

	
	if (user.isBinaryOp()){
	    // solvable types:
	    // llvm::Instruction::Add
	    // llvm::Instruction::Sub
	    // llvm::Instruction::Mul
	    // llvm::Instruction::Div
	    // llvm::Instruction::Rem 
	    // (what about urem vs. srem?)
	    
            // there are exactly two operands
	    llvm::User::const_op_iterator opIte;
	    for (opIte = user->op_begin(); opIte != user->op_end(); ++opIte) {
	        Value * opPtr = (*opIte)->get();
	        vec.push_back(new Variable(opPtr));
	    }
	} 
    } else if (isa<llvm::PHINode>(val)) {
	PHINode * phiNode = dynamic_cast<PHINode*>(val);
	// TODO: deal with a phi node
    } else if (isa<llvm::LoadInst(val)) {
	// Load(A, I), where A is a contant aggregate 
	// (TODO: how to determine the type of A...?)
    } // else if val is a user input or cannot be resolved
    // TODO: how to determine val is provided by user...?
}

// TODO: implement this function based 
// on the suppored kinds of predicate 
// instructions in Figure 4
void extractOperands(Predicate* pred, vector<Variable*>& vec) {
    // if the predicate can be supported 
    // by the rules in Figure 4
    extractOperandsFromInstruction(pred, vec);
}

void extractOperandsFromInstruction(Instruction* instr, vector<Variable*>& vec) {
    if (isa<User>(instr)) {
	User* user = dynamic_cast<User*>(instr);

	llvm::User::const_op_iterator opIte;
	for (opIte = user->op_begin(); opIte != user->op_end(); ++opIte) {
	    Value* opPtr =  (*opIte)->get();
	    vec.push_back(new Variable(opPtr));
	}
    }
}

// TODO: implement this function based 
// on the calculation rules in Figure 3
SymbolicRange * computeDefRangeWithOps(Variable * variable,
		vector<Variable*> operands) {
}


/*
 * Algorithm 2 (1)
 */
void computeDefRange(Variable * variable) {
    SymTable * symTable = SymTable.getInstance();
    if (!symTable->isInTable(variable)) {
    	return;
    }   

    // emplace?
    NewValSet.insert(variable);

    SymbolicRange * universe = new SymbolicRange(
	        *(BottomSymbol.getInstance()), 
	        *(TopSymbol.getInstance()) );

    symTable->putRange(variable, universe);

    vector<Variable*> operands = extractOperands(variable);
    vector<Variable*>::iterator opIte;
    for (opIte = operands.begin(); opIte != operands.end();
		    opIte++) {
	// Instruction * def = getDefinition(*opIte);
	Value * defVal = (*opIte)->getValue();
	computeUseRange(*opIte, def);
    }

    // TODO: compute def range for 
    // variable using ranges of the 
    // operands, based on Figure 3
    SymbolicRange * defRange = 
	    computeDefRangeWithOps(variable, operands);
    
    symTable->putRange(variable, defRange);

    updateDefRange(variable);

    NewValSet.erase(variable);
}

/*
 * Algorithm 2 (2)
 */
void updateDefRange(Variable * V) {
    SymTable * symTable = SymTable.getInstance();
    set<Variable*>::iterator newValIte;
    for (newValIte = NewValSet.begin(); newValIte != NewValSet.end(); newValIte++) {
	Variable * W = *newValIte;
	// TODO: check if the range of W 
	// depends on the range of V
	vector<Variable*> operands = extractOperands(W);
	vector<Variable*>::iterator opIte;
	for (opIte = operands.begin(); opIte != operands.end(); opIte++) {
            // Instruction * def = getDefinition(*opIte);
	    Value * defVal = (*opIte)->getValue();
	    computeUseRange(*opIte, def);
	}

        SymbolicRange * defRange = 
	    computeDefRangeWithOps(W, operands);
        
	// TODO: think about the design of intersect
	SymbolicRange * wRange = symTable->getRange(W);
	bool updated = wRange->intersect(defRange);
        if (updated) {
	    updateDefRange(W);
	}
    } 
}

// TODO: implement this functions based 
// on the two rules mentioned in the 
// paper: 1) immediate dominator and 2) 
// reachable from only one of the 
// branches of the predicate
set<Predicate*> extractPredicates(Variable * V, Instruction * P) {

}

/*
 * Algorithm 3
 */
void refineDefRange(Variable * V, Instruction * P) {
    SymTable * symTable = SymTable.getInstance();
    SymbolicRange *defRange = symTable->getRange(V);
    set<Predicate*> predicates = extractPredicates(V, P);
    
    set<Predicate*>::iterator predIte;
    for (predIte = predicates.begin(); predIte != predicates.end(); predIte++) {
	vector<Variable*> operands = extractOperands(*predIte);
	computeUseRange(operands[1], *predIte);
        normalizeAndRefine(V, P, *predIte, operands);
    }
}

/*
 * Normalize the operands of the 
 * predicate and refine the range based 
 * on Figure 4
 */
void normalizeAndRefine(Variable * V, Instruction * P,
		Predicate * pred, vector<Variable*> operands) {
}

int main() {
    // 1. get the pattern matching results
    
    // 2. extract interesting variables
    
    // 3. perform symbolic range analysis
    
    // 4. report warnings

    return 0;
}

