import random
from typing import *


def choose(m: int, xs: List[int]) -> List[int]:
    """
    Randomly choose m out of xs
    """
    assert m <= len(xs)

    ret = xs[:m]

    for i in range(m, len(xs)):
        idx = random.randint(0, i)  # inclusive

        if idx < m:
            ret[idx] = xs[i]

    return ret


if __name__ == "__main__":
    xs = [1, 2, 3, 4, 5]
    print(choose(3, xs))
