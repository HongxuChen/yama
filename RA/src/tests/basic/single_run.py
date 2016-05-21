#! /usr/bin/env python
from __future__ import print_function

import os
import sys

# ----------------------
import subprocess

proj_name = 'yama'
proj_mode = 'Debug'
proj_path = os.path.expanduser('~/.CLion2016.1/system/cmake/generated/src-9c78f034/9c78f034/')
llvm_version = '3.7'
so_path = os.path.join(proj_path, 'Debug', 'lib/librange.so')


# ----------------------

def which(name):
    for path in os.getenv("PATH").split(os.path.pathsep):
        full_path = path + os.sep + name
        if os.path.exists(full_path):
            return full_path


def versioned(name, v=llvm_version):
    if v is None or v == '':
        return name
    else:
        return name + "-" + v


analysisTypes = [
    "-ra-inter-crop",
    "-ra-inter-cousot",
    "-ra-intra-crop",
    "-ra-intra-cousot"]


def print_help():
    print("./single_run.py <OPTION> <FILE.c>")
    print("\tOPTION:")
    print("\t-ra-inter-crop\t\t-\tInter-procedural analysis with CropDFS meet operator")
    print("\t-ra-inter-cousot\t-\tInter-procedural analysis with Cousot meet operator")
    print("\t-ra-intra-crop\t\t-\tIntra-procedural analysis with CropDFS meet operator")
    print("\t-ra-intra-cousot\t-\tIntra-procedural analysis with Cousot meet operator")


if len(sys.argv) < 3:
    print_help()
    sys.exit(1)

out_dir = "Output"
ra_analysis = sys.argv[1]
c_fname = sys.argv[2]
fname, ext = os.path.splitext(c_fname)
bc_name = fname + ".bc"
bc_essa_fname = fname + ".essa.bc"
CLANG = versioned("clang")
OPT = versioned("opt")
YOPT = OPT + " -load {}".format(so_path)

cmds = [
    "{clang} -c -emit-llvm {c_fname} -o {bc_name}".format(clang=CLANG, c_fname=c_fname, bc_name=bc_name),
    "{yopt} -instnamer -mem2reg -break-crit-edges -vssa {bc_name} -o {bc_essa_fname}".format(
        yopt=YOPT, bc_name=bc_name, bc_essa_fname=bc_essa_fname),
    "{yopt} {ra_analysis} {bc_essa_fname} -stats -o {devnull}".format(
        yopt=YOPT, ra_analysis=ra_analysis, bc_essa_fname=bc_essa_fname, devnull=os.devnull)
]

for cmd in cmds:
    print(cmd)
    subprocess.call(cmd.split(" "))
