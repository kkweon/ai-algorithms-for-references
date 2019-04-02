from typing import *

def merge(xs, aux, lo, mid, hi):
    for i in range(lo, hi + 1):
        aux[i] = xs[i]

    i = lo
    j = mid + 1

    for k in range(lo, hi + 1):

        if mid < i:
            xs[k] = aux[j]
            j += 1
        elif hi < j:
            xs[k] = aux[i]
            i += 1
        elif aux[j] < aux[i]:
            xs[k] = aux[j]
            j += 1
        else:
            xs[k] = aux[i]
            i += 1

def mergesort(xs: List[int]) -> List[int]:
    """
    >>> xs = [3,2,1]
    >>> mergesort(xs)
    [1, 2, 3]

    >>> xs = [3,2,2,1]
    >>> mergesort(xs)
    [1, 2, 2, 3]

    >>> xs = [1]
    >>> mergesort(xs)
    [1]

    >>> xs = []
    >>> mergesort(xs)
    []
    """
    n = len(xs)
    size = 1

    aux = [0] * n

    while size < n:
        lo = 0
        while lo < n - size:
            merge(xs, aux, lo, lo + size - 1, min(lo + 2 * size - 1, n - 1))
            lo += 2 * size
        size *= 2

    return xs
