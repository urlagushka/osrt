#include  "sys.h"

TTaskStruct  gTaskQueue[TASK_MAX];

char   gRunningTask;

char   gFreeTask;

jmp_buf  gReturnSP;