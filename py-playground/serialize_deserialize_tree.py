from collections import deque


class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def __str__(self):
        return "Node({}, {}, {})".format(self.val, self.left, self.right)


def serialize_level(node):
    """
    >>> node = Node('root', Node('left', Node('left.left')), Node('right'))
    >>> serialize_level(node)
    'root,left,right,left.left,null'
    """
    ret = []

    def helper(node):
        queue = deque()
        queue.append(node)

        while queue:
            node = queue.popleft()

            if node:
                ret.append(node.val)
                queue.append(node.left)
                queue.append(node.right)
            else:
                ret.append("null")

    helper(node)

    while 2 <= len(ret) and ret[-2] == "null" and ret[-1] == "null":
        ret.pop()

    return ",".join(ret)


def deserialize_level(payload):
    """
    >>> node = Node('root', Node('left', Node('left.left')), Node('right'))
    >>> new_node = deserialize_level(serialize_level(node))
    >>> is_equal_tree(node, new_node)
    True
    """
    nodes = payload.split(",")
    if not nodes:
        return None
    root = Node(nodes[0])

    q = deque([root])

    for i in range(1, len(nodes), 2):
        curr = q.popleft()

        curr.left = Node(nodes[i]) if nodes[i] != "null" else None
        curr.right = Node(nodes[i + 1]) if nodes[i + 1] != "null" else None

        q.append(curr.left)
        q.append(curr.right)

    return root


def serialize_inorder(node: Node) -> str:
    """
    >>> node = Node('root', Node('left', Node('left.left')), Node('right'))
    >>> serialize_inorder(node)
    'root,left,left.left,null,null,null,right,null,null'
    """
    ret = []

    def helper(node: Node):
        if not node:
            ret.append("null")
            return
        ret.append(node.val)
        helper(node.left)
        helper(node.right)

    helper(node)

    return ",".join(ret)


def deserialize_inorder(msg: str) -> Node:
    """
    >>> node = Node('root', Node('left', Node('left.left')), Node('right'))
    >>> new_node = deserialize_inorder(serialize_inorder(node))
    >>> is_equal_tree(node, new_node)
    True
    """
    if not msg:
        return None
    msg = msg.split(",")
    i = 0

    def helper():
        nonlocal i
        if i < len(msg) and msg[i] == "null":
            i += 1
            return None
        val = msg[i]
        i += 1
        node = Node(val)
        node.left = helper()
        node.right = helper()

        return node

    return helper()


def is_equal_tree(node1, node2):
    if not node1 and not node2:
        return True
    if not node1 or not node2:
        return False
    if node1.val != node2.val:
        return False

    return is_equal_tree(node1.left, node2.left) and is_equal_tree(
        node1.right, node2.right
    )
