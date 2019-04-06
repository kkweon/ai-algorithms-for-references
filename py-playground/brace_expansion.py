import pytest

from typing import *

def expand_braces(exp: str) -> List[str]:
    i = 0
    keywords = {'{', '}'}

    def parse_group() -> List[str]:
        nonlocal i

        if len(exp) <= i:
            return [ "" ]

        curr = []
        while i < len(exp) and exp[i] != "}":

            if exp[i] == "{":
                curr.append(parse_group)
            else:
                curr += exp[i]
            i += 1

        if exp[i] == "{":
            pass

    def parse_expression():
        nonlocal i

        if len(exp) <= i:
            return [""]

        if exp[i] == "{":
            i += 1
            return parse_expression()

        if exp[i] == "}":
            i += 1
            return parse_expression()

        if exp[i] == ",":
            i += 1
            return parse_expression()

        curr = ""
        while i < len(exp) and exp[i] not in keywords:
            curr += exp[i]
            i += 1

        if i == len(exp):
            return [curr]
        elif exp[i] == "{":
            i += 1
            return [curr + r for r in parse_expression()]
        elif exp[i] == "}":
            i += 1
            return [curr + r for r in parse_expression()]
        else:
            raise ValueError("Unknown character")


    return parse_expression()

"""
def expand_braces(s: str) -> str:
    def getitem(s, depth=0):
        out = [""]
        while s:
            c = s[0]
            if depth and (c == ',' or c == '}'):
                return out,s
            if c == '{':
                x = getgroup(s[1:], depth+1)
                if x:
                    out,s = [a+b for a in out for b in x[0]], x[1]
                    continue
            if c == '\\' and len(s) > 1:
                s, c = s[1:], c + s[1]

            out, s = [a+c for a in out], s[1:]

        return out,s

    def getgroup(s, depth):
        out, comma = [], False
        while s:
            g,s = getitem(s, depth)
            if not s: break
            out += g

            if s[0] == '}':
                if comma: return out, s[1:]
                return ['{' + a + '}' for a in out], s[1:]

            if s[0] == ',':
                comma,s = True, s[1:]

        return None

    return getitem(s)[0]
"""

@pytest.mark.parametrize(
    "input,expected",
    [
        (
            "~/{Downloads,Pictures}/*.{jpg,gif,png}",
            {
                "~/Downloads/*.jpg",
                "~/Downloads/*.gif",
                "~/Downloads/*.png",
                "~/Pictures/*.jpg",
                "~/Pictures/*.gif",
                "~/Pictures/*.png",
            },
        ),
        (
            "It{{em,alic}iz,erat}e{d,}, please.",
            {
                "Itemized, please.",
                "Itemize, please.",
                "Italicized, please.",
                "Italicize, please.",
                "Iterated, please.",
                "Iterate, please.",
            },
        ),
    ],
)
def test_brace_expansion(input, expected):
    assert set(expand_braces(input)) == expected
