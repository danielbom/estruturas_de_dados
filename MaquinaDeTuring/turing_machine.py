from transitions import transitions
from tape import tape


class turing_machine(object):
    def __init__(self, all_transitions, begin_state, final_state, blank_space):
        self.all_transitions = all_transitions
        self.begin_state = begin_state
        self.final_state = final_state
        self.blank_space = blank_space

    def do_transition(self, tape, transition):
        tape.set_head(transition.new_symbol)
        if transition.direction == 'E' or transition.direction == 'L':
            tape.left()
        elif transition.direction == 'D' or transition.direction == 'R':
            tape.right()
        return (transition.new_state, tape.head.value)

    def run(self, _input):
        _tape = tape(_input, self.blank_space)
        _transitions = transitions(self.all_transitions)

        state = self.begin_state
        symbol = _tape.head.value

        transition = _transitions.search(state, symbol)

        count_previous = 0

        for i in range(100):
            previous_state, previous_symbol = state, symbol  # Evitar loop infinito

            # printando o estado da fita
            print(state, end='')
            _tape.print()
            print()

            # Verifica se acabaram as transições
            if not transition:
                print("No transition break")
                break

            # Realiza a transição
            state, symbol = self.do_transition(_tape, transition[0])

            # Evita loop infinito - Ciclo
            if previous_state == state and previous_symbol == symbol and count_previous < 3:
                count_previous += 1
            elif previous_state == state and previous_symbol == symbol and count_previous >= 3:
                print("Cicle find break")
                break
            else:
                count_previous = 0
            # Busca transições
            transition = _transitions.search(state, symbol)

        return state == self.final_state
