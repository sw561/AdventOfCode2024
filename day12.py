#!/usr/bin/env python3

from collections import defaultdict

def read_input():
    import fileinput

    m = []

    for line in fileinput.input():
        m.append(line.strip())

    return m

def neighbours(m, p, q):
    for x, y in [(p-1, q), (p+1, q), (p, q-1), (p, q+1)]:
        if 0 <= x < len(m) and 0 <= y < len(m[x]):
            yield x, y

def price(region):
    vertical_faces = defaultdict(lambda: -1)
    horizontal_faces = defaultdict(lambda: -1)

    for i, j in region:
        vertical_faces[(i, j)] *= -1
        vertical_faces[(i+1, j)] *= -1
        horizontal_faces[(i, j)] *= -1
        horizontal_faces[(i, j+1)] *= -1

    n_faces = sum(1 for v in vertical_faces.values() if v == 1) +\
        sum(1 for v in horizontal_faces.values() if v == 1)

    area = len(region)

    return area * n_faces

def price_part2(region):
    return 0

m = read_input()

visited = [[False for _ in line] for line in m]

regions = defaultdict(list)

for i in range(len(m)):
    for j in range(len(m[i])):

        if visited[i][j]: continue

        # bfs from i,j
        region = set()

        to_check = [(i, j)]

        while to_check:
            p, q = to_check.pop()
            if visited[p][q]: continue
            visited[p][q] = True
            region.add((p, q))

            for pp, qq in neighbours(m, p, q):

                if m[pp][qq] != m[i][j]: continue

                to_check.append((pp, qq))

        regions[m[i][j]].append(region)

# print(regions)

part1 = 0
part2 = 0

for k, v in regions.items():
    for r in v:
        part1 += price(r)
        part2 += price_part2(r)

print(f"Part 1: {part1}")
print(f"Part 2: {part2}")

