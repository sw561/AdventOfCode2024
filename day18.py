

def read_input():
    import fileinput

    data = dict()

    for i, line in enumerate(fileinput.input()):
        x, y = map(int, line.split(','))

        data[(x, y)] = i

    return data

def show_map(data, n_bytes, n=71):

    n_max = len(data) + 8
    
    for j in range(n):
        for i in range(n):
            if data.get((i, j), n_max) < n_bytes:
                print('#',end='')
            else:
                print('.',end='')
                
        print()

def valid(i, j, n, data, n_bytes, n_max):
    return (0 <= i < n and
            0 <= j < n and
            data.get((i, j), n_max) >= n_bytes
           )

def gen_neighbours(i, j):
    return [(i-1,j),
            (i+1,j),
            (i,j-1),
            (i,j+1)
            ]

def path_find(data, n_bytes, n=71):

    pos = (0, 0)

    least_steps = [[-1]*n for _ in range(n)]

    n_max = len(data)
    
    to_consider = set([pos])
    least_steps[0][0] = 0
    steps_so_far = 0
    while to_consider and least_steps[n-1][n-1] == -1:
        steps_so_far += 1
        new_to_consider = set()
        for (i, j) in to_consider:
            for (ni, nj) in gen_neighbours(i, j):
                if not valid(ni, nj, n, data, n_bytes, n_max):
                    continue

                if least_steps[ni][nj] == -1:
                    least_steps[ni][nj] = steps_so_far
                    new_to_consider.add((ni, nj))

        to_consider = new_to_consider

    # for j in range(7): print([least_stepsi[j] for least_stepsi in least_steps])

    return least_steps[n-1][n-1]

def bisection(f, left, right):
    # Find smallest x s.t. f(x) == -1
    #
    while right - left > 1:

        m = (left + right) // 2
        if f(m) == -1:
            right = m
        else:
            left = m

    return right
        


if __name__=="__main__":
    
    corrupted = read_input()

    n_bytes = 1024
    n = 71

    print(path_find(corrupted, n_bytes, n=n))

    first = bisection(
        lambda n_bytes: path_find(corrupted, n_bytes, n=n),
        1024,
        len(corrupted)
        )

    # print(first)

    print(",".join(map(str, list(corrupted.keys())[first-1])))

