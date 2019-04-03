def find_LCS(x: str, y: str) -> str:
    """
    >>> find_LCS("BCDBCDA", "ABECBAB")
    'BCBA'

    if x[i - 1] == y[j - 1]:
        dp[i][j] = dp[i - 1][j - 1]
    else:
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

       - B C D B C D A
    -  0 0 0 0 0 0 0 0
    A  0 0 0 0 0 0 0 1
    B  0 1 1 1 1 1 1 1
    E  0 1 1 1 1 1 1 1
    C  0 1 2 2 2 2 2 2
    B  0
    A  0
    B  0

    >>> find_LCS("ABCDAF", "ACBCF")
    'ABCF'

    """
    dp = [0 for _ in range(len(y) + 1)]
    ret = ["" for _ in range(len(y) + 1)]

    for x1 in x:
        pre = dp[0]
        pre_text = ret[0]

        for y_idx, y1 in enumerate(y):
            tmp = dp[y_idx + 1]
            tmp_text = ret[y_idx + 1]

            if x1 == y1:
                dp[y_idx + 1] = pre + 1
                ret[y_idx + 1] = tmp_text + y1
            else:
                dp[y_idx + 1] = max(dp[y_idx + 1], dp[y_idx])
                ret[y_idx + 1] = max(ret[y_idx + 1], ret[y_idx], key=lambda x: len(x))

            pre = tmp
            pre_text = tmp_text

    return ret[-1]
