/**
 * Configures the interface to change the bus frequency using the Phase Lock Loop (PLL).
 *
 * - Initialized the Phase-Lock-Loop to run at 50 Mhz
 */

#ifndef PHASE_LOCK_LOOP_H_
#define PHASE_LOCK_LOOP_H_

/** Configure the system to get its clock from the Phase Lock Loop (PLL). */
void initPhaseLockLoop(void);

#endif // PHASE_LOCK_LOOP_H_

