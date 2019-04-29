from typing import List

import hypothesis
import hypothesis.strategies as st


def count_sort(xs: List[int], exp: int) -> List[int]:
    """
    >>> count_sort([131, 22, 3], 1)
    [131, 22, 3]

    >>> count_sort([131, 22, 3], 10)
    [3, 22, 131]
    """
    get_digit = lambda x: (x // exp) % 10

    cnt = [0] * 10

    for x in xs:
        cnt[get_digit(x)] += 1

    for i in range(1, len(cnt)):
        cnt[i] += cnt[i - 1]

    output = [0] * len(xs)

    for x in reversed(xs):
        idx = cnt[get_digit(x)] - 1
        output[idx] = x
        cnt[get_digit(x)] -= 1

    for i, v in enumerate(output):
        xs[i] = v

    return xs


def radix_sort(xs: List[int]) -> List[int]:
    """
    >>> radix_sort([1111111, 2222])
    [2222, 1111111]
    """
    if not xs:
        return xs

    m = max(xs)

    exp = 1

    while 0 < m // exp:
        count_sort(xs, exp)
        exp *= 10

    return xs


@hypothesis.given(
    st.lists(st.integers(min_value=100_000, max_value=999_999), max_size=1_000_000)
)
def test_radix_sort(xs: List[int]):
    assert radix_sort(xs) == sorted(xs)
