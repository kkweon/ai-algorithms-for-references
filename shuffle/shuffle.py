import random

def shuffle(xs):
    for i in range(len(xs) - 1, 0, -1):
        idx = random.randint(0, i)
        xs[i], xs[idx] = xs[idx], xs[i]
