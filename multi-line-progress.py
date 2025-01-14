#!/usr/bin/env python3

import time

# def show(s1, s2):
#     print(f"[1A\r{s1}[K[B\r{s2}[K", end='')

used = 0

def show(s):
    global used
    if used:
        parg = f"[{len(s)-1}A\r[0J{'\n'.join(s)}"
    else:
        parg = f"\r[0J{'\n'.join(s)}"
        used = 1

    print(parg, end='')

print("HALLO")

for s in zip(["msg1", "hello world", "greetings", "a very long message indeed", "one"],
        [f"Line {x}" for x in range(12, 0, -1)]):
    show(s+("qowiejo",))
    time.sleep(1)

# print("[1A")

# print("Line two")

print()

