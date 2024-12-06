#!/usr/bin/env python3

from collections import defaultdict
from functools import cmp_to_key

def gen_rules():
    import fileinput

    rules = defaultdict(set)
    updates = []

    for line in fileinput.input():
        if "|" in line:
            ns = [int(x) for x in line.strip().split('|')]
            rules[ns[1]].add(ns[0])

        elif "," in line:
            updates.append([int(x) for x in line.strip().split(',')])

    return rules, updates

def check_order(rules, update):

    seen = set()
    present = set(update)

    for x in update:
        if not all(preceder in seen for preceder in rules[x] & present):
            return False
        seen.add(x)

    return True

def reorder(rules, update):
    def cmp(a, b):
        if b in rules[a]:
            return 1
        elif a in rules[b]:
            return -1
        return 0

    return sorted(update, key=cmp_to_key(cmp))

def middle(update):
    return update[len(update)//2]

if __name__=="__main__":

    rules, updates = gen_rules()

    part1 = 0
    part2 = 0

    for update in updates:
        if check_order(rules, update):
            # print("GOOD", update)
            part1 += middle(update)
        else:
            new = reorder(rules, update)
            # print("REORDER ", new)
            part2 += middle(new)

    print("Part1:", part1)
    print("Part2:", part2)
