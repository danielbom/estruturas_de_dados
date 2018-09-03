
class transition(object):
    def __init__(self, state, symbol, new_state, new_symbol, direction):
        self.state = state
        self.symbol = symbol
        self.direction = direction
        self.new_state = new_state
        self.new_symbol = new_symbol

    def __repr__(self):
        return "state({}), symbol({}), direction({}), new_state({}), new_symbol({})".format(self.state, self.symbol, self.direction, self.new_state, self.new_symbol)
