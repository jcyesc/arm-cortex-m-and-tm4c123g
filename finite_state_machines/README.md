# Finite State Machines (FSM)

A finite state machine is an abstraction that represents the
interactions between states, inputs, outputs and state transitions.

The FSM state graph defines the time-dependent relationship between its
inputs and outputs.

There are two types of FSM: Moore and Mealy.

## Moore FSM

In the Moore FSM, the outputs depend on current state and the
state transitions depend on the inputs. 

The following sequence is executed over and over by the Moore FSM:

1. Perform output, which depends on the current state
2. Wait a prescribe amount of time (optional)
3. Input
4. Go to next state, which depends on the input of the current state


## Mealy FSM

In the Mealy FSM, the outputs depend on the current state and the
inputs.

The following sequence is executed over and over by the Mealy FSM:

1. Wait a prescribed amount of time (optional)
2. Input
3. Perform output, which depends on the input and the current state
4. Go to next state, which depends on the input and the current state











