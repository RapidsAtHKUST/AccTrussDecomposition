with open('numbers1.txt') as ifs:
    numbers1 = ifs.readlines()
    mset = set()
    for l in numbers1:
        mset.add(l.strip())

with open('numbers2.txt') as ifs:
    numbers2 = ifs.readlines()
    mset2 = set()

    for l in numbers2:
        mset2.add(l.strip())

print(len(mset & mset2))
print(mset & mset2)