#!/usr/bin/env python

def combo_oberand_display(x):
    if x <= 3: return x
    return chr(ord('A') + x - 4)

opcodes = {
    0: 'A = A / 2^',
    1: 'B ^= ',
    2: 'B <-%8 ',
    3: 'jump if A nonzero',
    4: 'B ^= C',
    5: 'out',
    6: 'B = A / 2^',
    7: 'C = A / 2^'
}

def str_8_(x):
    # Represent a number in 8 bit format
    if x == 0:
        return ""
    return "".join([str_8_(x // 8), "{}".format(x % 8)])

def str_8(x):
    if x == 0: return '0'
    return str_8_(x)

p = 0
A = 44348299
B = 0
C = 0
program = [2,4,1,5,7,5,1,6,0,3,4,2,5,5,3,0]

# A = 729
# B = 0
# C = 0
# program = [0,1,5,4,3,0]

def combo_oberand(x):
    if x <= 3: return x
    elif x == 4: return A
    elif x == 5: return B
    elif x == 6: return C


def step():
    global A, B, C, p
    op = program[p]
    operand = program[p+1]

    if op == 0:
        num = A
        den = 1 << combo_oberand(operand)
        A = num // den
        p += 2
    elif op == 1:
        B ^= operand
        p += 2
    elif op == 2:
        B = combo_oberand(operand) % 8
        p += 2
    elif op == 3:
        if A != 0:
            p = operand
        else:
            p += 2
    elif op == 4:
        B ^= C
        B %= 8
        p += 2
    elif op == 5:
        print("OUT: ", combo_oberand(operand) % 8)
        p += 2
    elif op == 6:
        num = A
        den = 1 << combo_oberand(operand)
        B = num // den
        p += 2
    elif op == 7:
        num = A
        den = 1 << combo_oberand(operand)
        C = (num // den) % 8
        p += 2
    else:
        raise Exception("Unrecognized opcode")



def arrow(p, i):
    if p == i: return "--->"
    return "    "

def display():
    print(" ".join(f"{k}: {str_8(v)}" for k, v in zip('ABC', [A, B, C])))

    for i in range(0, len(program), 2):
        a = program[i]
        if a == 4:
            print(f"{arrow(p, i)} {opcodes[a]}")
            continue
        b = program[i+1]
        if a in [1, 3]:
            print(f"{arrow(p, i)} {opcodes[a]} {str_8(b)}")
        else:
            print(f"{arrow(p, i)} {opcodes[a]} {combo_oberand_display(b)}")

while p < len(program):
    display()
    input()
    print("--------------")
    step()

