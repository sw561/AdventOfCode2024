#!/usr/bin/env python3

from collections import defaultdict
import fileinput

def neighbours(m, p, q):
    for x, y in [(p-1, q), (p+1, q), (p, q-1), (p, q+1)]:
        if 0 <= x < len(m) and 0 <= y < len(m[x]):
            yield x, y

LEFT = 0
RIGHT = 1
UP = 0
DOWN = 1

def add_or_remove(s, a):
    (i, j, side) = a
    if (i, j, 1-side) in s:
        s.remove((i, j, 1-side))
    else:
        s.add(a)

def search_and_remove(faces, start, func):
    # Use func to find faces which are part of the same group and remove

    face = func(*start)
    while face in faces:
        faces.remove(face)
        face = func(*face)


def price(region):

    area = len(region)

    vertical_faces = set()
    horizontal_faces = set()

    for i, j in region:
        add_or_remove(vertical_faces, (i, j, LEFT))
        add_or_remove(vertical_faces, (i, j+1, RIGHT))
        add_or_remove(horizontal_faces, (i, j, UP))
        add_or_remove(horizontal_faces, (i+1, j, DOWN))

    part1 = area * (len(horizontal_faces) + len(vertical_faces))

    # Count sides

    h_sides = 0
    while horizontal_faces:
        face = horizontal_faces.pop()
        h_sides += 1

        for d in [-1,1]:
            search_and_remove(horizontal_faces, face,
                    (lambda i, j, side: (i, j+d, side))
                    )

    v_sides = 0
    while vertical_faces:
        face = vertical_faces.pop()
        v_sides += 1

        for d in [-1,1]:
            search_and_remove(vertical_faces, face,
                    (lambda i, j, side: (i+d, j, side))
                    )

    part2 = area * (h_sides + v_sides)

    return part1, part2


m = [line.strip() for line in fileinput.input()]

visited = [[False for _ in line] for line in m]

regions = defaultdict(list)

for i in range(len(m)):
    for j in range(len(m[i])):

        if visited[i][j]: continue

        # bfs from i,j
        to_check = [(i, j)]
        region = [(i, j)]
        visited[i][j] = True

        while to_check:
            p, q = to_check.pop()

            for pp, qq in neighbours(m, p, q):

                if visited[pp][qq]: continue
                if m[pp][qq] != m[i][j]: continue

                to_check.append((pp, qq))
                region.append((pp, qq))
                visited[pp][qq] = True

        regions[m[i][j]].append(region)

# print(regions)

part1 = 0
part2 = 0

for k, v in regions.items():
    for r in v:
        p1, p2 = price(r)
        part1 += p1
        part2 += p2

print(f"Part 1: {part1}")
print(f"Part 2: {part2}")

