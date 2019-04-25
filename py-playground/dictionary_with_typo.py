from typing import *
from collections import defaultdict

class Node:
    def __init__(self):
        self.C = defaultdict(Node)
        self.is_leaf = False

def insert(node, word):
    for c in word: node = node.C[c]
    node.is_leaf = True

def find(node, word) -> bool:

    def dfs(node, i, count):
        if 2 <= count: return False
        if len(word) <= i: return node.is_leaf

        for char, next_node in node.C.items():
            if char == word[i]:
                if dfs(next_node, i + 1, count):
                    return True
            elif dfs(next_node, i + 1, count + 1):
                return True

        return False

    return dfs(node, 0, 0)

def find_word_at_most_one_typo(words: List[str], queries: List[str]) -> List[bool]:
    """
    >>> find_word_at_most_one_typo(['apple','banana','orange'], ['', 'banana', 'banena', 'banan', 'banxnn','xpple', 'pple', 'bananaa'])
    [False, True, True, False, False, True, False, False]
    """
    root = Node()
    for word in words:
        insert(root, word)

    return [find(root, q) for q in queries]

if __name__ == "__main__":
    import doctest
    doctest.testmod()
