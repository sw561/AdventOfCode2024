#!/usr/bin/env python3

# Construct a graph of nodes.

# Start by reducing graph as much as possible.
#
# Pull out nodes which have more than one direction conncted to them

import sys
from collections import defaultdict

with open(sys.argv[1], 'r') as f:
    m = f.read().strip().split('\n')
    

for i, row in enumerate(m):
    m[i] = list(row)
    for j, col in enumerate(row):
        if col == "S":
            start = (i, j)
            m[i][j] = '.'
        elif col == "E":
            end = (i, j)
            m[i][j] = '.'

# print("\n".join("".join(row) for row in m))

nodes = set([start, end])

def is_node(m, i, j):
    return any(m[si][j] == "." for si in [i-1, i+1]) and\
        any(m[i][sj] == "." for sj in [j-1, j+1])

for i in range(len(m)):
    for j in range(len(m[0])):
        if m[i][j] == "#":
            continue
        if is_node(m, i, j):
            nodes.add((i, j))

# for i, row in enumerate(m):
#     for j, col in enumerate(m):
#         if (i, j) in nodes:
#             print("O", end='')
#         else:
#             print(m[i][j], end='')
#     print()

# Now search from each node in straight directions to see if we find more nodes
# and build an edge

# Each node is represented as (x, y, dx, dy)

# graph[x] = {y1: cost, y2: cost ...}
graph = defaultdict(dict)

for (node_x, node_y) in nodes:
    for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        nx, ny = node_x, node_y
        steps = 0

        while True:
            nx += dx
            ny += dy
            steps += 1

            if (nx, ny) in nodes:
                graph[(node_x, node_y, dx, dy)][(nx, ny, dx, dy)] = steps
                break
            elif m[nx][ny] == '#':
                break
            else:
                continue

    for ew_x, ew_y in [(0, 1), (0, -1)]:
        for ns_x, ns_y in [(1, 0), (-1, 0)]:
            graph[(node_x, node_y, ew_x, ew_y)][(node_x, node_y, ns_x, ns_y)] = 1000
            graph[(node_x, node_y, ns_x, ns_y)][(node_x, node_y, ew_x, ew_y)] = 1000

# for key, vals in graph.items():
#     print(key, vals)


# Now do a normal path finding algorithm
start = (start[0], start[1], 0, 1)

from heapq import *

h = [(0, start)]
visited = set()

while h:

    cost, node = heappop(h)
    if (node[0], node[1]) == end:
        print(cost)
        break
        
    visited.add(node)

    for n, steps in graph[node].items():
        if n in visited:
            continue

        heappush(h, (cost+steps, n))
    # print(visited)
    # print(h)
    # import pdb; pdb.set_trace()
        


        
        
    


