#!/usr/bin/env python3

import fileinput
import re
from itertools import batched
import numpy as np

def solve(a, b, p, part2=False):

    (ax, ay) = a
    (bx, by) = b

    m = np.array([[ax, bx], [ay, by]])

    p = np.array(p)

    if part2:
        p[0] += 10000000000000
        p[1] += 10000000000000

    sol = np.linalg.solve(m, p)

    sol = np.fromiter(map(round, sol), dtype=int)

    # pp is where we end up
    pp = m.dot(np.array(sol))

    if not np.any(pp - p):
        return sol.dot([3, 1])
    else:
        return 0


r = re.compile(r'\d+')
def generate_lines():
    for line in fileinput.input():
        x = re.findall(r, line)
        if x:
            yield [int(y) for y in x]

part1 = 0
part2 = 0
for data in batched(generate_lines(), 3):
    part1 += solve(*data)
    part2 += solve(*data, part2=True)

print("Part 1:", part1)
print("Part 2:", part2)
