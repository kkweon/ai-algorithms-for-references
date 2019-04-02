
def decompress(s: str) -> str:
    """
    >>> decompress('abc')
    'abc'

    >>> decompress('3[abc]4[ab]c')
    'abcabcabcababababc'

    >>> decompress('10[a]')
    'aaaaaaaaaa'

    >>> decompress('2[3[a]b]')
    'aaabaaab'
    """

    res = ""
    num = 0

    st = []

    for c in s:

        if c.isdigit():
            num = num * 10 + int(c)
        elif c == "[":
            st.append(res)
            st.append(num)

            res = ""
            num = 0
        elif c == "]":
            cnt = st.pop()
            old_result = st.pop()
            res = old_result + cnt * res

        elif c.isalpha():
            res += c

    return res
