def is_alpha(x: str) -> bool:
    """
    >>> is_alpha("")
    False

    >>> is_alpha("Abc")
    True

    >>> is_alpha("ABC")
    True

    >>> is_alpha("AB1C")
    False
    """
    # return x.isalpha()
    if not x:
        return False
    return all("a" <= c <= "z" or "A" <= c <= "Z" for c in x)
