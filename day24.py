#!/usr/bin/env python3

import fileinput

inits = True
max_z = 0

h_file = open("day24.h", 'w')
d_file = open("day24.d", 'w')

for line in fileinput.input():

    if line.strip() == "":
        inits = False

    elif inits:
        wire, value = line.strip().split(': ')
        
        h_file.write(f"int {wire}(){{ return {value}; }}\n")
        d_file.write(f"int {wire}();\n")

    else:
        ins, out = line.strip().split(' -> ')
        g1, op, g2 = ins.split()

        cpp_op = {"AND": "&",
            "XOR": "^",
            "OR": "|"}
        h_file.write(f"int {out}(){{ return {g1}() {cpp_op[op]} {g2}(); }}\n")
        d_file.write(f"int {out}();\n")

        if out[0] == "z":
            max_z = max(max_z, int(out[1:]))


h_file.write(f"int max_z = {max_z};\n")

h_file.write(
"""
int z(int index) {
switch(index) {
"""
)
for i in range(max_z+1):
    h_file.write(f"case {i}: return z{i:02d}();\n")

h_file.write("}\n")
h_file.write("return 0;\n")

h_file.write("}\n")

h_file.close()
d_file.close()
