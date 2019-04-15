from typing import *


def find_kth_lowest_in_2_arrays(xs: List[int], ys: List[int], k: int) -> int:
    """
    >>> find_kth_lowest_in_2_arrays([1,5,6],[2,4,7], 1)
    1
    >>> find_kth_lowest_in_2_arrays([1,5,6],[2,4,7], 2)
    2
    >>> find_kth_lowest_in_2_arrays([1,5,6],[2,4,7], 3)
    4
    >>> find_kth_lowest_in_2_arrays([1,5,6],[2,4,7], 4)
    5
    >>> find_kth_lowest_in_2_arrays([1],[2,4,7], 4)
    7
    >>> find_kth_lowest_in_2_arrays([1,3,5],[2,4], 4)
    4
    >>> find_kth_lowest_in_2_arrays([1,2,2,2,5],[2,4], 5)
    2
    """

    def kth(xs, m, ys, n, k):
        if k < 1 or m + n < k:
            return -1
        if n < m:
            return kth(ys, n, xs, m, k)
        if m == 0:
            return ys[k - 1]
        if k == 1:
            return min(xs[0], ys[0])
        i, j = min(m, k // 2), min(n, k // 2)
        if xs[i - 1] > ys[j - 1]:
            return kth(xs, m, ys[j:], n - j, k - j)
        return kth(xs[i:], m - i, ys, n, k - i)

    return kth(xs, len(xs), ys, len(ys), k)


if __name__ == "__main__":
    import doctest

    doctest.testmod()
