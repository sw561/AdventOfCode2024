#!/usr/bin/env python3

import sys

with open(sys.argv[1], 'r') as f:
    s = f.read()

keys = []
locks = []

for i, block in enumerate(s.split('\n\n')):

    # print(block)
    block = block.split('\n')

    if block[0][0] == ".":
        # Key

        heights = []
        for col in range(5):
            lowest = 5
            while block[lowest][col] == '#':
                lowest -= 1

            heights.append(5 - lowest)

        # print("Key", heights)
        keys.append(heights)

    else:
        # Lock
        heights = []
        for col in range(5):
            highest = 1
            while block[highest][col] == '#':
                highest += 1

            heights.append(highest - 1)

        # print("Lock", heights)
        locks.append(heights)


compatible = 0
for lock in locks:
    for key in keys:
        if all(x <= 5 for x in map(sum, zip(lock, key))):
            compatible += 1

print(compatible)


