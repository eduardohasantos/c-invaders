
#ifndef TIMER_H
#define TIMER_H

void timerInit(void);
void timerDestroy(void);
unsigned int timerGetDelta(void);
int timerHasElapsed(unsigned int milliseconds);

#endif