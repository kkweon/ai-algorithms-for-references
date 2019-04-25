from typing import *
import pytest

ops = {"(": 0, "+": 1, "-": 1, "*": 3, "/": 3}


def score(op):
    return ops.get(op, 0)


def tokenize(exps: str) -> List[str]:
    op_keys = set(ops.keys())
    op_keys.add(")")
    op_keys.remove('-')

    for op in op_keys:
        exps = exps.replace(op, " " + op + " ")
    return exps.split()


def to_rpn(expression: str) -> str:
    """
    >>> conver_to_rpn('1 - 2 * 3 - 4 + 5 * 6')
    '1 2 3 * - 4 5 6 * + -'
    """
    exps = tokenize(expression)
    op_stack = []
    result = []

    for tok in exps:
        if tok.isdigit() or tok[0] == '-' and tok[1:].isdigit():
            result.append(tok)
        elif tok == '(':
            op_stack.append(tok)
        elif tok == ')':
            while op_stack and op_stack[-1] != '(':
                result.append(op_stack.pop())
            op_stack.pop()
        elif tok in ops:
            while op_stack and score(tok) <= score(op_stack[-1]):
                result.append(op_stack.pop())
            op_stack.append(tok)
    while op_stack:
        result.append(op_stack.pop())
    return " ".join(result)

@pytest.mark.parametrize(
    "input,expected",
    [
        ("1 + 2 + 3", "1 2 + 3 +"),
        ("5 * (-3)", "5 -3 *"),
        ("5 * -3", "5 -3 *"),
        ("1 - 3", "1 3 -"),
        ("-2", "-2"),
        ("1 + (2 + 3) * 4", "1 2 3 + 4 * +"),
        ("1 + (2 + 3) * (4 / 2)", "1 2 3 + 4 2 / * +"),
    ],
)
def test_to_rpn(input, expected):
    assert to_rpn(input) == expected
