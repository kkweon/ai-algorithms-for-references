from typing import *


def find_kth_largest(nums: List[int], k) -> int:
    """
    >>> find_kth_largest([5,3,1], 1)
    5

    >>> find_kth_largest([5,1,3], 2)
    3

    >>> find_kth_largest([15,3,1], 3)
    1

    >>> find_kth_largest([], 3)
    -1
    """

    def quickselect(xs, l, r, k):
        while l <= r:
            pivot_idx = (l + r) >> 1
            pivot_val = xs[pivot_idx]

            xs[pivot_idx], xs[r] = xs[r], xs[pivot_idx]

            write_idx = 0

            for i, v in enumerate(xs):
                if v < pivot_val:
                    xs[write_idx], xs[i] = xs[i], xs[write_idx]
                    write_idx += 1

            xs[write_idx], xs[r] = xs[r], xs[write_idx]

            if write_idx == len(xs) - k:
                return pivot_val
            if write_idx < len(xs) - k:
                l = write_idx + 1
            else:
                r = write_idx - 1

        return -1

    return quickselect(nums, 0, len(nums) - 1, k)
