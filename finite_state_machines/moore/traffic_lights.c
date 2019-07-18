/**
 * Simulating Traffic lights using a Moore FSM
 *
 * Let's assume that this program is going to run in the TM4C123G
 * microcontroller and that the ports PB and PE will be used.
 *
 * The goal of this program is to show how to implement the traffic lights
 * for a Southbound (North to South) and Westbound (East to West) cars.
 *
 * The Moore FSM will have two inputs (car sensors on North and East
 * roads) and six outputs (one for each light in the traffic signal).
 *
 * The six traffic lights are interfaces to Port B bits 5-0, and the two
 * sensors are connected to Port E bits 1-0.
 *
 * PE1 = 0, PE0 = 0 means no cars exist on either road
 * PE1 = 0, PE0 = 1 means there are cars on the East road
 * PE1 = 1, PE0 = 0 means there are cars on the North road
 * PE1 = 1, PE0 = 1 means there are cars on both roads
 *
 * The next thing that we need to define are the states:
 *
 * goSouthbound      PB5-0 = 100001 makes it  green on North and red on East
 * waitSouthbound    PB5-0 = 100010 makes it yellow on North and red on East
 * goWestbound		 PB5-0 = 001100 makes it red on North and green on East
 * waitWestbound     PB5-0 = 010100 makes it red on North and yellow on East
 *
 * The states and transitions can be represented using a table:
 *
 * State (output, delay)      |          Inputs
 *                            |   00                01              10           11
 * ----------------------------------------------------------------------------------------
 * goSouthbound(100001, 3s)   | goSouthbound  waitSouthbound   goSouthbound   waitSouthbound
 * waitSouthbound(100010, 1s) | goWestbound   goWestbound      goWestbound    goWestbound
 * goWestbound(001100, 3s)    | goWestbound   goWestbound      waitWestbound  waitWestbound
 * waitWestbound(010100, 1s)  | goSouthbound  goSouthbound     goSouthbound   goSouthbound
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef struct FiniteState {
	uint32_t output;
	uint32_t delay;
	char *name;
	const struct FiniteState *nextStates[4];
} State;

#define goSouthbound &states[0]
#define waitSouthbound &states[1]
#define goWestbound &states[2]
#define waitWestbound &states[3]

State states[4] = {
    {0x21, 3, "goSouthbound", {goSouthbound, waitSouthbound, goSouthbound, waitSouthbound}},
    {0x22, 1, "waitSouthbound", {goWestbound,goWestbound, goWestbound, goWestbound}},
    {0x0C, 3, "goWestbound", {goWestbound,goWestbound, waitWestbound, waitWestbound}},
    {0x14, 1, "waitWestbound", {goSouthbound ,goSouthbound, goSouthbound, goSouthbound}}
};

int main() {
	printf("\nMoore Finite State Machines");

	uint32_t input = 0;

	State *current_state_ptr = goSouthbound;

	while (input <= 3) {
		printf("\n%s Ox%x ", current_state_ptr->name, current_state_ptr->output);
		fflush(stdout);
		sleep(current_state_ptr->delay);
		printf("\nEnter the sensors input [0-3] (4 to exit): "); // 00 = 0, 01 = 1, 10 = 2, 11 = 3 (binary = decimal)
		scanf("%d", &input); // Reading sensors
		current_state_ptr = (State *) current_state_ptr->nextStates[input];
	}

	printf("\nFinishing....\n");
	return 0;
}

