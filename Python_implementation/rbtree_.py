from typing import TypeVar, Generic
from rbtree_node import BLACK, RED, RBNode


T = TypeVar('T')


class RBTree(Generic[T]):
    def __init__(self, root_: 'RBNode[T]' = None):
        self.size_ = 0
        self.__root = root_

    def __display(self, in_: 'RBNode[T]', level: int):
        if in_ is None:
            return

        print("Level: {0} \n{1}".format(level, in_))

        self.__display(in_.left, level+1)
        self.__display(in_.right, level+1)

    def __rotate_right(self, y: 'RBNode[T]'):
        if y.left is None:
            return
        else:
            x = y.left
            b = x.right
            f = y.father

            if f is None:
                x.father = None
                self.__root = x
            else:
                x.father = f
                if f.left == y:
                    f.left = x
                if x.right == y:
                    f.right = x

            x.right = y
            y.father = x
            y.left = b

            if b is not None:
                b.father = y

    def __rotate_left(self, x: 'RBNode[T]'):
        if x.right is None:
            return
        else:
            y = x.right
            b = y.left
            f = x.father

            if f is None:
                y.father = None
                self.__root = y
            else:
                y.father = f
                if f.left == x:
                    f.left = y
                if f.right == x:
                    f.right = y

            y.left = x
            x.father = y
            x.right = b

            if b is not None:
                b.father = x

    def __insert_fix(self, create: 'RBNode[T]'):
        while create != self.__root and create.father.color == RED:
            if create.father == create.father.father.left:
                y = create.father.father.right

                if y is not None and y.color == RED:
                    create.father.color = BLACK
                    y.color = BLACK
                    create.father.father.color = RED
                    create = create.father.father
                else:
                    if create.father.right == create:
                        create = create.father
                        self.__rotate_left(create)

                    create.father.color = BLACK
                    create.father.father.color = RED
                    self.__rotate_right(create.father.father)
            else:
                y = create.father.father.left

                if y is not None and y.color == RED:
                    create.father.color = BLACK
                    y.color = BLACK
                    create.father.father.color = RED
                    create = create.father.father
                else:
                    if create.father.left == create:
                        create = create.father
                        self.__rotate_right(create)

                    create.father.color = BLACK
                    create.father.father.color = RED
                    self.__rotate_left(create.father.father)

        self.__root.color = BLACK

    def __delete_fix(self, p: 'RBNode[T]'):
        if p is not None:
            # s = RBNode[T]()

            while p != self.__root and p.color == BLACK:
                if p.father.left == p:
                    s = p.father.right

                    if s.color == RED:
                        s.color = BLACK
                        p.father.color = RED
                        self.__rotate_left(p.father)
                        s = p.father.right

                    if s.right.color == BLACK and s.left.color == BLACK:
                        s.color = RED
                        p = p.father
                    else:
                        if s.right.color == BLACK:
                            s.left.color = BLACK
                            s.color = RED
                            self.__rotate_right(s)
                            s = p.father.right

                        s.color = p.father.color
                        p.father.color = BLACK
                        s.right.color = BLACK
                        self.__rotate_left(p.father)
                        p = self.__root
                else:
                    s = p.father.left

                    if s.color == RED:
                        s.color = RED
                        p.father.color = RED
                        self.__rotate_right(p.father)
                        s = p.father.left

                    if s.left.color == BLACK and s.right.color == BLACK:
                        s.color = RED
                        p = p.father
                    else:
                        if s.left.color == BLACK:
                            s.right.color = BLACK
                            s.color = RED
                            self.__rotate_left(s)
                            s = p.father.left

                        s.color = p.father.color
                        p.father.color = BLACK
                        s.left.color = BLACK
                        self.__rotate_right(p.father)
                        p = self.__root

                p.color = BLACK
                self.__root = BLACK

    def __merge(self, p: 'RBNode[T]'):
        if p is not None:
            if p.left is not None:
                self.__merge(p.left)
            if p.right is not None:
                self.__merge(p.right)

            self.insert(p.key)

    def __split(self, p: 'RBNode[T]'):
        if p is not None:
            if p.left is not None:
                self.__split(p.left)
            if p.right is not None:
                self.__split(p.right)

            self.delete(p.key)

    def __copy(self, in_: 'RBNode[T]'):
        if in_ is not None:
            self.insert(in_.key)
            self.__copy(in_.left)
            self.__copy(in_.right)

    def __chop(self, in_: 'RBNode[T]'):
        if in_ is not None:
            self.__chop(in_.left)
            self.__chop(in_.right)

            del in_

    """Magic Methods"""
    def __add__(self, other: 'RBTree[T]'):
        self.__merge(other.__root)

    def __radd__(self, other: 'RBTree[T]'):
        self.__merge(other.__root)

    def __sub__(self, other: 'RBTree[T]'):
        self.__split(other.__root)

    def __rsub__(self, other: 'RBTree[T]'):
        self.__split(other.__root)

    def __iter__(self):
        self.curr_it = self.min_it()
        self.rev_or_not = False
        return self

    def __reversed__(self):
        self.curr_it = self.max_it()
        self.rev_or_not = True
        return self

    def __next__(self):
        if self.curr_it is None:
            raise StopIteration
        else:
            ret = self.curr_it.key
            if self.rev_or_not:
                self.curr_it = self.curr_it.node_predecessor()
            else:
                self.curr_it = self.curr_it.node_successor()
            return ret

    def __eq__(self, other: 'RBTree[T]') -> bool:
        if self.size_ != other.size_ or self.__root != self.__root:
            return False
        else:
            it = iter(self)
            other_it = iter(other)

            while it is not None and other_it is not None:
                try:
                    i_ = it.__next__()
                    oi_ = other_it.__next__()

                    if i_ != oi_:
                        return False
                except StopIteration:
                    it = None
                    other_it = None

        return True

    def __ne__(self, other: 'RBTree[T]') -> bool:
        return not self == other

    def __lt__(self, other: 'RBTree[T]') -> bool:
        if self.size_ > other.size_ or self.__root >= self.__root:
            return False
        else:
            it = iter(self)
            other_it = iter(other)

            while it is not None and other_it is not None:
                try:
                    i_ = it.__next__()
                    oi_ = other_it.__next__()

                    if i_ >= oi_:
                        return False
                except StopIteration:
                    it = None
                    other_it = None

        return True

    def __le__(self, other: 'RBTree[T]') -> bool:
        return not self > other

    def __gt__(self, other: 'RBTree[T]') -> bool:
        if self.size_ < other.size_ or self.__root <= self.__root:
            return False
        else:
            it = iter(self)
            other_it = iter(other)

            while it is not None and other_it is not None:
                try:
                    i_ = it.__next__()
                    oi_ = other_it.__next__()

                    if i_ <= oi_:
                        return False
                except StopIteration:
                    it = None
                    other_it = None

        return True

    def __ge__(self, other: 'RBTree[T]') -> bool:
        return not self < other

    def __getitem__(self, item: int) -> T:
        if item < 0 or item > self.size_:
            raise IndexError
        else:
            if item == 0:
                return self.min_it().key

            count = 1
            n = self.min_it().node_successor()

            while count != item:
                count += 1
                n = n.node_successor()

            return n.key

    def __repr__(self):
        ret = "Root key: {0}\nAl keys: ".format(self.__root.key)
        for i in self:
            ret += str(i)

        return ret

    def __len__(self):
        return self.size_

    def display(self):
        self.__display(self.__root, 0)

    def get_root(self) -> RBNode[T] or None:
        return self.__root

    def size(self) -> int:
        return self.size_

    def empty(self) -> bool:
        return self.size_ == 0 and self.__root is None

    def clear(self):
        self.__chop(self.__root)
        self.__root = None
        self.size_ = 0

    def max_it(self) -> RBNode[T] or None:
        if self.empty():
            return None
        else:
            return self.__root.max_node()

    def min_it(self) -> RBNode[T] or None:
        if self.empty():
            return None
        else:
            return self.__root.min_node()

    def insert(self, input_: 'T'):
        create = RBNode[T](input_)
        q = RBNode[T]()
        p = self.__root

        if self.__root is None:
            self.__root = create
            create.father = None
        else:
            while p is not None:
                q = p

                if p.key > create.key:
                    p = p.left
                elif p.key < create.key:
                    p = p.right
                else:
                    return

            create.father = q

            if q.key < create.key:
                q.right = create
            elif q.key > create.key:
                q.left = create
            else:
                return

        self.size_ += 1
        self.__insert_fix(create)

    def find(self, in_: T) -> bool:
        t_ = self.__root
        while t_ is not None:
            if t_.key == in_:
                return True

            if in_ > t_.key:
                t_ = t_.right
            elif in_ < t_.key:
                t_ = t_.left

        return False

    def find_node(self, in_: T) -> RBNode[T] or None:
        t_ = self.__root
        while t_ is not None:
            if t_.key == in_:
                return t_

            if in_ > t_.key:
                t_ = t_.right
            elif in_ < t_.key:
                t_ = t_.left

        return None

    def delete(self, x: T) -> bool:
        if self.__root is None:
            print("Tree is empty")
            return False

        p = self.__root
        if self.find(x):
            y = RBNode[T]()
            q = RBNode[T]()
            if p.left is None or p.right is None:
                y = p
            else:
                y = p.node_successor()

            if y.left is not None:
                q = y.left
            else:
                if y.right is not None:
                    q = y.right
                else:
                    q = None

            if q is not None:
                q.father = y.father

            if y.father is None:
                self.__root = q
            else:
                if y == y.father.left:
                    y.father.left = q
                else:
                    y.father.right = q

            if y != p:
                p.color = y.color
                p.key = y. key

            if y.color == BLACK:
                self.__delete_fix(q)

            self.size_ -= 1
            return True
        else:
            return False
