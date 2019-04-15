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


def find_median_in_2_arrays(xs: List[int], ys: List[int]) -> float:
    """
    >>> find_median_in_2_arrays([1,3],[2]) # 1 2 3
    2.0
    >>> find_median_in_2_arrays([1,2,3],[4,5,6]) # 1 2 3 4 5 6
    3.5
    >>> find_median_in_2_arrays([1,2,2],[4,6]) # 1 2 2 4 6
    2.0
    >>> find_median_in_2_arrays([1,2,2],[]) # 1 2 2
    2.0
    >>> find_median_in_2_arrays([2,2],[]) # 2 2
    2.0
    >>> find_median_in_2_arrays([-10,5],[-5,3]) # -10 -5 3 5
    -1.0
    """
    if len(xs) < len(ys):
        xs, ys = ys, xs
    if not ys:
        return 0.5 * (xs[(len(xs)) // 2] + xs[(len(xs) - 1) // 2])

    l, r = 0, len(ys) * 2 - 1

    while l <= r:
        cut2 = (l + r) >> 1
        cut1 = len(xs) + len(ys) - cut2

        L1 = xs[(cut1 - 1) // 2] if 0 < cut1 else float("-inf")
        L2 = ys[(cut2 - 1) // 2] if 0 < cut2 else float("-inf")

        R1 = xs[cut1 // 2] if cut1 < 2 * len(xs) else float("inf")
        R2 = ys[cut2 // 2] if cut2 < 2 * len(ys) else float("inf")

        if L1 > R2:
            l = cut2 + 1
        elif L2 > R1:
            r = cut2 - 1
        else:
            return 0.5 * (max(L1, L2) + min(R1, R2))

    return -1


if __name__ == "__main__":
    import doctest

    doctest.testmod()
