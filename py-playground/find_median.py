from typing import *


def find_median(xs: List[int]) -> int:
    """
    >>> find_median([10,2,8,4,6,5,7,3,9,1])
    5.5

    >>> find_median([1,3,2])
    2

    >>> find_median([3,2,2,1])
    2.0

    >>> find_median([3,1])
    2.0

    >>> find_median([1])
    1

    >>> find_median([]) is None
    True
    """

    def find_lowest_k(k: int):
        lo = 0
        hi = len(xs) - 1

        while lo <= hi:
            w = lo
            for i in range(lo, hi):
                if xs[i] < xs[hi]:
                    xs[i], xs[w] = xs[w], xs[i]
                    w += 1
            xs[w], xs[hi] = xs[hi], xs[w]

            if w == k - 1:
                return w
            elif w < k - 1:
                lo = w + 1
            else:
                hi = w - 1
        return None

    i = find_lowest_k((len(xs) >> 1) + 1)
    if i is None:
        return None

    if len(xs) & 1:
        return xs[i]

    j = find_lowest_k(len(xs) >> 1)
    return 0.5 * (xs[i] + xs[j])
