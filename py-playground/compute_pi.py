import random


def compute_pi():
    """
    Area = pi * r^2

    if r == 1:
        area = pi

          ^
          |
          |
   1+-----+-----+
    |     |     |
   0+-----+-----+------>
    |     |     |
  -1+-----+-----+-
   -1     0     1

    x^2 + y^2 <= 1

    >>> import math
    >>> p = compute_pi()
    >>> abs(math.pi - p) / max(math.pi, p) < 1e-2
    True
    """
    n_count = 1000000
    inside = 0

    for _ in range(n_count):
        a = random.random() * 2 - 1  # [-1, 1)
        b = random.random() * 2 - 1

        if a ** 2 + b ** 2 <= 1:
            inside += 1

    return inside / n_count * 4


if __name__ == "__main__":
    import doctest

    doctest.testmod()
