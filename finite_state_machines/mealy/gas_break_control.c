/**
 * Mealy Finite State Machines
 *
 * In general, we use Mealy Finite State Machines when the output
 * is needed to cause the state to change.In the Mealy FSM, the output depends
 * on input and state. In this example, we are going to implement a Mealy FSM
 * that has a control (input) and two outputs (Gas and Brake). The heuristics
 * of this machine are:
 *
 * - If we are stopped, and the control is low, we press the brake and remain stopped.
 * - If we are stopped, and the control is high, we release the brake and begin to go.
 * - If we are going, and the control is low, we release the gas and begin to stop
 * - If we are going, and the control is high, we press the gas and continue to go.
 * There must be at least 1 ms of no break, no gas as it switches between go and stop.
 *
 * 00 is the output pattern to change states (Stop to Go and Go to Stop)
 * 10 is the output pattern to loop in the Stop state.
 * 01 is the output pattern to loop in the Go state.
 */


#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef struct FiniteState {
	uint32_t output[2];
	uint32_t delay;
	char *name;
	const struct FiniteState *nextStates[4];
} State;

#define stopState &states[0]
#define goState &states[1]

State states[2] = {
    {{2, 0}, 2, "stop", {stopState, goState}}, // Stop state: with Input 0 outputs 2 (10 binary) and goes again to Stop.
	{{0, 1}, 2, "go", {stopState, goState}}, // Go state: with Input 0 outputs 0 (00 binary) and goes to Stop.
};

int main() {
	printf("\nMealy Finite State Machines");
	uint32_t input = 0; // Possible inputs 0 and 1 (number of elements in the array usually).

	State *current_state_ptr = stopState; // Initial state

	while (input <= 1) {
		// Step 1 - Get new input from control
		printf("\nInput for state `%s` [0-1] (2 to exit): ", current_state_ptr->name);
		scanf("%d", &input);

		if (input > 1) break;

		// Step 2 - Output depends on input and current state
		printf("\n`%s` Ox%x \n", current_state_ptr->name, current_state_ptr->output[input]);
		fflush(stdout);

		// Step 3 - Wait
		sleep(current_state_ptr->delay);

		// Step 4 - Go to the next state depending on the input and current state
		current_state_ptr = (State *) current_state_ptr->nextStates[input];
	}

	printf("\nFinishing....\n");
	return 0;
}


