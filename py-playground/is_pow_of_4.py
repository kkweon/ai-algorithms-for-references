def is_pow_of_4(x: int) -> bool:
    """
    >>> is_pow_of_4(0)
    False

    >>> is_pow_of_4(1)
    True

    >>> is_pow_of_4(2)
    False

    >>> is_pow_of_4(4)
    True

    >>> is_pow_of_4(5)
    False

    >>> is_pow_of_4(16)
    True
    """
    return (not not x) and not (x & (x - 1)) and not (x & 0xAAAAAAAA)


if __name__ == "__main__":
    import doctest

    doctest.testmod()
