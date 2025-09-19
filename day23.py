#!/usr/bin/env python

import fileinput
from collections import defaultdict

links = defaultdict(set)

for line in fileinput.input():
    a, b = line.strip().split('-')

    links[a].add(b)
    links[b].add(a)

count = 0

for first in sorted(links.keys()):
    for second in links[first]:
        if second <= first:
            continue

        for third in links[first] & links[second]:
            if third <= second:
                continue

            if any(s[0] == "t" for s in [first, second, third]):
                # print(first, second, third)
                count += 1

print(count)



constructed_fully_linked = []
constructed_fully_linked_nodes = set()


for first in sorted(links.keys()):
    if first in constructed_fully_linked_nodes:
        continue

    for second in links[first]:
        if second in constructed_fully_linked_nodes:
            continue

        nodes = set([first, second])
        
        for candidate in links[first] & links[second]:
            if links[candidate] >= nodes:
                nodes.add(candidate)

        constructed_fully_linked.append(nodes)
        constructed_fully_linked_nodes |= nodes

        # print(nodes)


longest = max(constructed_fully_linked, key=len)
print(",".join(sorted(longest)))

