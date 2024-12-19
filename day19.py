
with open("input.txt") as file:
    data = file.read().split("\n\n")
    d1 = data[0]
    d2 = data[1]
    d1 = [x.strip() for x in d1.split(",")]
    d2 = d2.split("\n")


import functools
@functools.lru_cache(None)
def can_match(design):
    if not design:
        return 1
    return sum(can_match(design[len(p):]) for p in d1 if design.startswith(p))


lst = [can_match(x) for x in d2]


print("Part 1:", sum(x > 0 for x in lst))
print("Part 2:", sum(lst))
