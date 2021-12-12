# constants
epsilon = 'e'

# Reading states
transition_count = int(input("Enter the number of transistions : "))
print("Enter the transitions of the form 'fromState' 'symbol' 'toState'")
print("For epsilon, use the symbol : ", epsilon)
print()

transit = dict()
for i in range(transition_count):
    user_in = input("transisiton : ")
    fromState, sym, toState = tuple(user_in.split())

    if fromState not in transit:
        transit[fromState] = set()
    if toState not in transit:
        transit[toState] = set()
    transit[fromState].add((sym, toState))


# finding eclosure
eclosure = dict()


def find_ECLOSURE(fromState):
    closures = {fromState}
    for (sym, toState) in transit[fromState]:
        if sym != epsilon:
            continue
        if toState not in eclosure:
            find_ECLOSURE(toState)
        closures.update(eclosure[toState])

    eclosure[fromState] = closures


for fromState in transit:
    if fromState not in eclosure:
        find_ECLOSURE(fromState)


# creating nfa from efna
NFA = dict()

for startState in transit:
    stateGroup = tuple(eclosure[startState])
    if stateGroup in NFA:
        continue

    newTransit = dict()

    for fromstate in stateGroup:
        for (sym, toState) in transit[fromstate]:
            if sym == epsilon:
                continue
            if sym not in newTransit:
                newTransit[sym] = set()
            newTransit[sym].update(eclosure[toState])

    NFA[stateGroup] = newTransit


# printing NFA
print("Computed NFA")
for fromStateGrp in NFA:
    for sym in NFA[fromStateGrp]:
        print(set(fromStateGrp), sym, NFA[fromStateGrp][sym])
