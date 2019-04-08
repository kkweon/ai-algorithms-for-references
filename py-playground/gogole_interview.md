Google Interview Questions

1. Round
Returns the shortest unique prefix

```
Input:
w = cat
words = [ cow, foo, bar ]

Output:
ca
```

Returns the unique shortest prefix

```
Input:
words = [ foo, bar, cat, cow]

Output:
[f, b, ca, co]
```

2. Round

Design a SkipIterator class

Suppose stream = [10, 50, 30, 60]

```
skip(50)
next() -> 10
next() -> 30
has_next() -> True
skip(60)
has_next() -> False
```

```
class SkipIterator(Iterator):

    def __init__(self):
        pass

    def next(self):
        pass

    def has_next(self):
        pass
```

3. Round

Given a complete binary tree

```
      1
    /   \
   2     3
  / \   / \
 4  5  6   7
```


```
class Node:
    def __init__(self):
        self.left = self.right = None
```


```
def exists(root_node: Node, index: int) -> bool:
    pass
```

```
def size(root_node: Node) -> int:
    pass
```

4. Round

Write a function that expands word

```
def expand(s: str) -> List[str]:
    pass

Input: ~/{Downloads,Pictures}/*.{jpg,gif,png}

Output:
~/Downloads/*.jpg
~/Downloads/*.gif
~/Downloads/*.png
~/Pictures/*.jpg
~/Pictures/*.gif
~/Pictures/*.png


Input: It{{em,alic}iz,erat}e{d,}, please.

Output:
Itemized, please.
Itemize, please.
Italicized, please.
Italicize, please.
Iterated, please.
Iterate, please.

Input: {,{,gotta have{ ,\, again\, }}more }cowbell!

Output:
cowbell!
more cowbell!
gotta have more cowbell!
gotta have\, again\, more cowbell!

Input: {}} some }{,{\\{ edge, edge} \,}{ cases, {here} \\\\\}

Output:
{}} some }{,{\\ edge \,}{ cases, {here} \\\\\}
{}} some }{,{\\ edge \,}{ cases, {here} \\\\\}
```

5. Round


```
USD GBP 5.0
GBP EUR 3.0
...
```


```
USD EUR ?
```

```
Stock Buy and Sell at most 2 times
```
