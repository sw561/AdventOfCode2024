#!/usr/bin/env python3

import fileinput
import re
from itertools import batched
import numpy as np

r = re.compile(r'\d+')

def generate_lines():
    for line in fileinput.input():
        x = re.findall(r, line)
        if x:
            yield [int(y) for y in x]

in_data = list(batched(generate_lines(), 3))

def solve(part2=False):

    ret = 0

    for (ax, ay), (bx, by), (px, py) in in_data:

        m = np.array([[ax, bx], [ay, by]])

        p = np.array([px, py])

        if part2:
            p[0] += 10000000000000
            p[1] += 10000000000000

        sol = np.linalg.solve(m, p)

        ra = round(sol[0])
        rb = round(sol[1])

        ppx = ax * ra + bx * rb
        ppy = ay * ra + by * rb

        if ppx - p[0] == 0 and  ppy - p[1] == 0:
            price = ra * 3 + rb
            ret += price
        else:
            price = -1

        # print(f"{ax} {ay} {bx} {by} : {p[0]} {p[1]} ---> {price}")

    return ret


part1 = solve()
part2 = solve(part2=True)

print("Part 1:", part1)
print("Part 2:", part2)
