#!/usr/bin/env bash

FILE=$1
PREFIX=${FILE%%.*}
BC=${PREFIX}.bc
SSA_BC=${PREFIX}.essa.bc
OPT="opt -load ${HOME}/RESEARCH/yama/RA/src/build/bin/librange.so"

clang -c -emit-llvm ${FILE} -o $BC
$OPT -instnamer -mem2reg -break-crit-edges $BC -o $BC
$OPT -vssa $BC -o ${SSA_BC}
$OPT -client-ra ${SSA_BC} -o /dev/null
