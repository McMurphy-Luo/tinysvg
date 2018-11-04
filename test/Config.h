#ifdef _WIN32

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type

#define DumpMemoryLeaks() _CrtDumpMemoryLeaks();

#else // _WIN32

#define DumpMemoryLeaks()

#endif // _WIN32