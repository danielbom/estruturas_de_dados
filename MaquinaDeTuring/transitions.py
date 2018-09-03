from transition import transition


class transitions(object):
    def __init__(self, all_transitions):
        self._list = [transition(line[0], line[2], line[1], line[3], line[4])
                      for line in all_transitions]

    def search(self, state, symbol):
        return [t for t in self._list if t.state == state and t.symbol == symbol]

    def __iter__(self):
        return iter(self._list)
