from cs50 import get_int

while True:
    n = get_int("Dimension: ")
    if n > 0:
        break

for i in range(n):
    print("#" * n)
