#!/usr/bin/env python3

# Each loop removes last three bits of A and then outputs based on value in A.
#
# So to constuct a quine, start by determining three bits of A to output last
# value in program. Then construct (x << 3) + y to get next three bits etc.


import fileinput
import re
import subprocess

r = re.compile(r'\d+')
for line in fileinput.input():
    if line.startswith("Program: "):
        x = re.findall(r, line)
        program = [int(y) for y in x]

# print(program)

def create_input(a=0, b=0, c=0):
    s = f"Register A: {a}\n"
    s += "Register B: {b}\n"
    s += "Register C: {c}\n"
    s += "\n"
    s += "Program: {}\n".format(",".join(map(str, program)))
    return s

def run_program(inp):
    r = subprocess.check_output("./day17", input=inp.encode())

    return [int(x) for x in r.split(b',')]


x = run_program(create_input(a=44348299))

def attempt(a, program, i):
    for a_end in range(8):
        new_a = a * 8 + a_end
        ret = run_program(create_input(a=new_a))
        # print("new_a, ret:", new_a, ret)
        if any(r < 0 for r in ret):
            import pdb; pdb.set_trace()

        if ret == program[i:]:
            if i == 0:
                return new_a

            a_ret = attempt(new_a, program, i-1)
            if a_ret is not None:
                return a_ret

    return None

a = attempt(0, program, len(program)-1)

print("Part 2:", a)
assert run_program(create_input(a=a)) == program



