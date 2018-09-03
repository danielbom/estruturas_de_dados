from turing_machine import turing_machine as tm

if __name__ == "__main__":

    with open("input_machine.txt", 'r') as reader:
        txt = reader.read()
        txt = txt.split("\n")

        transitions = [i.split() for i in txt[7:-1]]
        initial_state = '0'
        final_state = txt[5]
        blank_space = txt[2]

        for i in transitions:
            print(i)

        m = tm(transitions, initial_state,
               final_state, blank_space)

    inp = input()
    while inp != "exit":
        print(m.run(inp))
        inp = input()
