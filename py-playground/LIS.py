from typing import *

def find_length_of_LIS(xs: List[int]) -> int:
    """
    >>> find_length_of_LIS([5,7,4,-3,9,1])
    [5, 7, 9]
    """
    dp = [1 for _ in xs]

    ret = [[x] for x in xs]

    for i in range(1, len(xs)):
        for j in range(i):
            if xs[j] < xs[i]:
                if dp[i] < dp[j] + 1:
                    dp[i] = dp[j] + 1
                    ret[i] = ret[j] + [xs[i]]

    return max(ret, key=lambda xs: len(xs))
