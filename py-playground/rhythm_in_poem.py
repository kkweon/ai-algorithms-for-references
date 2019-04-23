from typing import *

def find_rhythm(n : int) -> List[str]:
    """
    >>> find_rhythm(1)
    ['A']
    >>> find_rhythm(2)
    ['AA', 'AB']
    >>> find_rhythm(3)
    ['AAA', 'AAB', 'ABA', 'ABB', 'ABC']
    >>> len(find_rhythm(4))
    15
    """

    ret = []

    def helper(curr, c):
        if len(curr) == n:
            ret.append("".join(curr))
            return

        for i in range(c + 2):
            ch = chr(ord('A') + i)
            curr.append(ch)
            helper(curr, max(i, c))
            curr.pop()

    helper([], -1)
    return ret

if __name__ == "__main__":
    import doctest
    doctest.testmod()
