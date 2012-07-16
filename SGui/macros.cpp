
#include "macros.h"


void sguiPerformAssertFailed(const char *expression, const char *file, int line)
{
	printf("%s(%d): %s failed\n",  file, line, expression);
	fflush(stdout);
	sGuiDebugBreak();
}
