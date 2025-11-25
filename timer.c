#include "timer.h"
#include <sys/time.h>
#include <stdio.h>

static struct timeval startTime;
static unsigned int lastUpdateTime = 0;

void timerInit(void)
{
    gettimeofday(&startTime, NULL);
    lastUpdateTime = 0;
}

void timerDestroy(void)
{
}

unsigned int timerGetDelta(void)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    
    unsigned int milliseconds = (unsigned int)(
        ((now.tv_sec - startTime.tv_sec) * 1000) +
        ((now.tv_usec - startTime.tv_usec) / 1000)
    );
    
    return milliseconds;
}

int timerHasElapsed(unsigned int milliseconds)
{
    unsigned int currentTime = timerGetDelta();
    if (currentTime - lastUpdateTime >= milliseconds) {
        lastUpdateTime = currentTime;
        return 1;
    }
    return 0;
}