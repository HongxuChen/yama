#!/usr/bin/env bash

LLVM_SUFFIX="-3.7"
CLANG="clang${LLVM_SUFFIX}"

SRC=$1
OUT_DIR=Output
PREFIX=${SRC%%.*}
BC=${OUT_DIR}/${PREFIX}.bc
SSA_BC=${OUT_DIR}/${PREFIX}.essa.bc
OPT="opt${LLVM_SUFFIX}"
LOAD="-load ../build/bin/librange.so"


${CLANG} -c -emit-llvm ${SRC} -o ${BC}
${OPT} -instnamer -mem2reg -break-crit-edges ${BC} -o ${BC}
${OPT} ${LOAD} -vssa ${BC} -o ${SSA_BC}

declare -a OPT_ARRARY=(ra-intra-cousot ra-intra-crop ra-inter-cousot ra-inter-crop)
for PASS in "${OPT_ARRARY[@]}"; do
  echo "===${PASS}==="
  ${OPT} ${LOAD} -${PASS} ${SSA_BC} -o /dev/null
done