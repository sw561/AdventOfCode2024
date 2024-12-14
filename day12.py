#!/usr/bin/env python3

from collections import defaultdict

def debug(*args, **kwargs):
    return 0 # print(*args, **kwargs)

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
    def add_or_remove(s, p):
        if p in s:
            s.remove(p)
        else:
            s.add(p)
    vertical_faces = set()
    horizontal_faces = set()

    for i, j in region:
        add_or_remove(vertical_faces, (i, j))
        add_or_remove(vertical_faces, (i+1, j))
        add_or_remove(horizontal_faces, (i, j))
        add_or_remove(horizontal_faces, (i, j+1))

    n_faces = len(vertical_faces) + len(horizontal_faces)

    area = len(region)

    return area * n_faces

LEFT = 0
RIGHT = 1
UP = 0
DOWN = 1

def price_part2(region):

    def add_or_remove(s, a):
        (i, j, side) = a
        if (i, j, 1-side) in s:
            s.remove((i, j, 1-side))
        else:
            s.add(a)

    vertical_faces = set()
    horizontal_faces = set()

    for i, j in region:
        add_or_remove(vertical_faces, (i, j, LEFT))
        add_or_remove(vertical_faces, (i, j+1, RIGHT))
        add_or_remove(horizontal_faces, (i, j, UP))
        add_or_remove(horizontal_faces, (i+1, j, DOWN))

    debug(region)

    debug("horizontal_faces:", horizontal_faces)

    # Count sides

    h_sides = 0
    while horizontal_faces:
        (i, j, side) = horizontal_faces.pop()
        h_sides += 1
        side_list = [(i, j, side)]

        ci, cj = i, j

        # Search right and left
        while (i, j+1, side) in horizontal_faces:
            j += 1
            horizontal_faces.remove((i, j, side))
            side_list.append((i, j, side))

        i, j = ci, cj
        while (i, j-1, side) in horizontal_faces:
            j -= 1
            horizontal_faces.remove((i, j, side))
            side_list.append((i, j, side))

        debug("Horizontal", side_list)

    debug("vertical_faces:", vertical_faces)
    v_sides = 0
    while vertical_faces:
        (i, j, side) = vertical_faces.pop()
        v_sides += 1
        side_list = [(i, j, side)]

        ci, cj = i, j
        # Search up and down
        while (i+1, j, side) in vertical_faces:
            i += 1
            vertical_faces.remove((i, j, side))
            side_list.append((i, j, side))

        i, j = ci, cj
        while (i-1, j, side) in vertical_faces:
            i -= 1
            vertical_faces.remove((i, j, side))
            side_list.append((i, j, side))

        debug("Vertical", side_list)

    area = len(region)

    n_sides = h_sides + v_sides

    debug("area, n_sides, area * n_sides:", area, n_sides, area * n_sides)

    return area * n_sides


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
        debug("k:", k)
        part1 += price(r)
        part2 += price_part2(r)

print(f"Part 1: {part1}")
print(f"Part 2: {part2}")

