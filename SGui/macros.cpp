
#include "macros.h"

#include <iostream>


void sguiPerformAssertFailed(const char *expression, const char *file, int line)
{
  //printf("%s(%d): %s failed\n",  file, line, expression);
  //fflush(stdout);
  std::cout << file << "(" << line << "): " << expression << " failed" << std::endl;
	sGuiDebugBreak();
}
