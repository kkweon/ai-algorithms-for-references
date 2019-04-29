def find_largest_sum_of_non_adjacent_numbers(xs):
    """
    >>> find_largest_sum_of_non_adjacent_numbers([2,4,6,2,5])
    13

    >>> find_largest_sum_of_non_adjacent_numbers([5,1,1,5])
    10

    dp(i) = largest sum until i

    incl(i) = max(excl(i - 1) + value, incl(i - 1))
    excl(i) = max(incl(i - 1), excl(i - 1))
            = incl(i - 1)
    """
    if not xs:
        return 0

    excl, incl = 0, xs[0]

    for i in range(1, len(xs)):
        val = xs[i]
        excl, incl = incl, max(excl + val, incl)

    return incl
