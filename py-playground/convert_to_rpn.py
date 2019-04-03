import pytest

ops = {"(": 0, "+": 1, "-": 1, "*": 3, "/": 3}


def score(op):
    return ops.get(op, 0)


def convert_to_rpn(expression: str) -> str:
    """
    >>> conver_to_rpn('1 -2 * 3 - 4 + 5 * 6')
    '1 2 3 * - 4 5 6 * + -'
    """
    ret = []
    stack = []

    token = ""
    expression += "+"

    for c in expression:

        if c.isdigit():
            token += c

        elif c == "(":
            stack.append(c)

        elif c == ")":

            if token:
                ret.append(token)
            token = ""

            while stack[-1] != "(":
                ret.append(stack.pop())

            stack.pop()

        elif c in ops:

            if token:
                ret.append(token)
            token = ""

            while stack and score(c) <= score(stack[-1]):
                ret.append(stack.pop())

            stack.append(c)

    return " ".join(ret)


@pytest.mark.parametrize(
    "input,expected",
    [
        ("1 + 2 + 3", "1 2 + 3 +"),
        ("1 + (2 + 3) * 4", "1 2 3 + 4 * +"),
        ("1 + (2 + 3) * (4 / 2)", "1 2 3 + 4 2 / * +"),
    ],
)
def test_convert_to_rpn(input, expected):
    assert conver_to_rpn(input) == expected
