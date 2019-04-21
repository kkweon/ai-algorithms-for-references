from typing import *


def find_largest_k(xs: List[int], k: int) -> int:
    """
    >>> find_largest_k([1,2,3], 1)
    3
    >>> find_largest_k([1,1,3], 1)
    3
    >>> find_largest_k([1,1,3], 2)
    1
    >>> find_largest_k([1,1,1,3], 2)
    1
    >>> find_largest_k([1,1,1,3], 1)
    3
    >>> find_largest_k([1,1,3], 3)
    1
    >>> find_largest_k([3,1,2], 2)
    2
    >>> find_largest_k([3,2,1], 3)
    1
    >>> find_largest_k([3,2,1], 4)
    -1
    >>> find_largest_k([3,2,1], 0)
    -1
    >>> find_largest_k([3,2], 2)
    2
    >>> find_largest_k([], 1)
    -1
    >>> find_largest_k([1], 1)
    1
    """
    l, r = 0, len(xs) - 1

    while l <= r:
        w = l

        for i in range(l, r):
            if xs[i] > xs[r]:
                xs[w], xs[i] = xs[i], xs[w]
                w += 1

        xs[w], xs[r] = xs[r], xs[w]

        if w == k - 1: return xs[w]
        elif w < k - 1: l = w + 1
        else: r = w - 1

    return -1

if __name__ == "__main__":
    import doctest
    doctest.testmod()
