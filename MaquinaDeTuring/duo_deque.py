from collections import deque
from duo_index import duo_index


class duo_deque(deque):
    def begin(self):
        return self[0]

    def end(self):
        return self[-1]

    def append(self, value):
        if not self:
            super().append(duo_index(value))
        else:
            _end = self.end()
            _new = duo_index(value)
            _end.next, _new.prev = _new, _end
            super().append(_new)

    def appendleft(self, value):
        if not self:
            super().append(duo_index(value))
        else:
            _begin = self.begin()
            _new = duo_index(value)
            _begin.prev, _new.next = _new, _begin
            super().appendleft(_new)


if __name__ == "__main__":
    d = duo_deque()

    for i in range(10):
        d.append(i)

    b = d.begin()

    b = b.next
    print(b)
    b = b.next
    print(b)
    b = b.next
    print(b)
    b = b.next
    print(b)

    b = b.prev
    print(b)
    b = b.prev
    print(b)
    b = b.prev
    print(b)
