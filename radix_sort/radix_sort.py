from typing import *

import pytest


def radix_sort(xs: List[int]) -> None:
    if not xs:
        return

    def helper(exp: int):
        """
        x = 123456
        to get 1st digit (1)
            123456 % 10
        to get 2nd digit (5)
            123456 // 10 % 10

        >>> helper(10)
        123456 // 10
        """

        buckets = [0] * 10

        for i, v in enumerate(xs):
            bucket_idx = v // exp % 10
            buckets[bucket_idx] += 1

        for i in range(1, len(buckets)):
            buckets[i] += buckets[i - 1]

        output = [0] * len(xs)

        for i in range(len(xs) - 1, -1, -1):
            bucket_idx = xs[i] // exp % 10
            buckets[bucket_idx] -= 1

            output[buckets[bucket_idx]] = xs[i]

        for i, v in enumerate(output):
            xs[i] = v

    max_value = max(xs)
    exp = 1

    while 0 < max_value // exp:
        helper(exp)
        exp *= 10


@pytest.mark.parametrize(
    "input, expected",
    [
        ([10, 9, 8], [8, 9, 10]),
        ([10, 10, 1], [1, 10, 10]),
        ([], []),
        ([10], [10]),
        ([111, 11, 1], [1, 11, 111]),
    ],
)
def test_raidx_sort(input, expected):
    radix_sort(input)
    assert input == expected
