from typing import TypeVar, Generic

BLACK = 0
RED = 1
T = TypeVar('T')


class RBNode(Generic[T]):
    def __init__(self, key: T = None, father: 'RBNode[T]' = None, left: 'RBNode[T]' = None, right: 'RBNode[T]' = None,
                 color=None):
        self.key = key
        self.father = father
        self.left = left
        self.right = right
        if color is None:
            self.color = BLACK
        if key is not None:
            self.color = RED
        else:
            self.key = -1

    def __str__(self) -> str:
        ret = "Key: {0}, color: {1}\n".format(self.key, self.color)
        if self.father is not None:
            ret += "Father key: {0}\n".format(self.father.key)
        else:
            ret += "No father, (root)\n"
        if self.left is not None:
            ret += "Left son key: {0}\n".format(self.left.key)
        else:
            ret += "No left son\n"
        if self.right is not None:
            ret += "Right son key: {0}\n".format(self.right.key)
        else:
            ret += "No right son\n"
        return ret

    def __repr__(self) -> str:
        return "NODE key: {0}[Father: {1}, Left: {2}, Right: {3}], color: {4}".format(self.key, self.father.key,
                                                                                      self.left.key, self.right.key,
                                                                                      self.color)

    def __bool__(self) -> bool:
        if self is not None:
            return self.key is not None
        else:
            return False

    def __eq__(self, other: 'RBNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key == other.key
            else:
                return False
        else:
            return False

    def __ne__(self, other: 'RBNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key != other.key
            else:
                return False
        else:
            return False

    def __lt__(self, other: 'RBNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key < other.key
            else:
                return False
        else:
            return False

    def __le__(self, other: 'RBNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key <= other.key
            else:
                return False
        else:
            return False

    def __gt__(self, other: 'RBNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key > other.key
            else:
                return False
        else:
            return False

    def __ge__(self, other: 'RBNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key >= other.key
            else:
                return False
        else:
            return False

    def __getitem__(self, item: int) -> T:
        if item == 0:
            return self.key
        elif item == 1:
            if self.father is not None:
                return self.father.key
            else:
                raise IndexError("No father")
        elif item == 2:
            if self.left is not None:
                return self.left.key
            else:
                raise IndexError("No left son")
        elif item == 3:
            if self.right is not None:
                return self.right.key
            else:
                raise IndexError("No right son")
        else:
            raise IndexError

    def is_left_son(self) -> bool:
        return self.father is not None and self.father.left == self

    def is_right_son(self) -> bool:
        return self.father is not None and self.father.right == self

    def max_node(self):
        if self.right is None:
            return self
        else:
            return self.right.max_node()

    def min_node(self):
        if self.left is None:
            return self
        else:
            return self.left.min_node()

    def node_successor(self) -> 'RBNode[T]' or None:
        if self is not None:
            if self.right is not None:
                return self.right.min_node()
            elif self.is_left_son():
                return self.father

            successor = self

            while True:
                successor = successor.father
                if (successor is None) or (not successor.is_right_son()):
                    break

            if successor is not None:
                return successor.father
            else:
                return None

        return None

    def node_predecessor(self) -> 'RBNode[T]' or None:
        if self is not None:
            if self.left is not None:
                return self.left.max_node()
            elif self.is_right_son():
                return self.father

            predecessor = self

            while True:
                predecessor = predecessor.father
                if (predecessor is None) or (not predecessor.is_left_son()):
                    break

            if predecessor is not None:
                return predecessor.father
            else:
                return None

        return None
