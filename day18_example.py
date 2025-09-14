from day18 import read_input, path_find


corrupted = read_input()

n_bytes = 12
n = 7

print(path_find(corrupted, n_bytes, n=n))
