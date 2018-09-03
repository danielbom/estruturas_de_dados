from duo_deque import duo_deque
from termcolor import colored


class tape(object):
    def __init__(self, input=' ', blank_space=' '):
        self.blank_space = blank_space
        self._list = duo_deque()
        for i in list(input):
            self._list.append(i)
        self.head = self._list.begin()

    def left(self):
        if not self.head.prev:
            self._list.appendleft(self.blank_space)
        self.head = self.head.prev

    def right(self):
        if not self.head.next:
            self._list.append(self.blank_space)
        self.head = self.head.next

    def set_head(self, symbol):
        self.head.value = symbol

    def print(self):
        for i in self._list:
            print(colored(i, 'blue')
                  if i is not self.head
                  else colored(i, 'red'), end='')

    def __repr__(self):
        return str()
