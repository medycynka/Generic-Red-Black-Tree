from rbtree_ import RBTree


if __name__ == '__main__':
    t = RBTree[int]()
    for i in range(0, 10):
        t.insert(i)

    normal = ""
    for t_ in t:
        normal += str(t_) + ", "
    """
    cos nie chce dzialac
    for r_ in reversed(t):
        rev += str(r_) + ", "
    """
    # To dziala
    rev = ""
    pom = t.__reversed__()
    while True:
        try:
            rev += str(pom.__next__()) + ", "
        except StopIteration:
            break

    print("{0}\n{1}".format(normal, rev))
    t.clear()
    print("size =", t.size(), "\n")
