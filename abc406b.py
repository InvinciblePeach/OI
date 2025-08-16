n, k = map(int, input().split())
a = map(int, input().split())
nw = 1
for i in a:
    nw *= i
    if nw >= 10**k: nw = 1
print(nw)
