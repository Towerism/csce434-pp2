/* File: utiliy.cc
 * ---------------
 * Implementation of simple printing functions to report failures or
 * debugging information triggered by keys.
 */

#include "utility.hh"
#include <stdarg.h>
#include "list.hh"
#include <string.h>

static List<const char*> debugKeys;
static const int BufferSize = 2048;
static testT testType = (testT)0;

void Failure(const char *format, ...)
{
  va_list args;
  char errbuf[BufferSize];

  va_start(args, format);
  vsprintf(errbuf, format, args);
  va_end(args);
  fflush(stdout);
  fprintf(stderr,"\n*** Failure: %s\n\n", errbuf);
  abort();
}



int IndexOf(const char *key)
{
  for (int i = 0; i < debugKeys.NumElements(); i++)
    if (!strcmp(debugKeys.Nth(i), key)) return i;
  return -1;
}

bool IsDebugOn(const char *key)
{
  return (IndexOf(key) != -1);
}


void SetDebugForKey(const char *key, bool value)
{
  int k = IndexOf(key);
  if (!value && k != -1)
    debugKeys.RemoveAt(k);
  else if (value && k == -1)
    debugKeys.Append(key);
}



void PrintDebug(const char *key, const char *format, ...)
{
  va_list args;
  char buf[BufferSize];

  if (!IsDebugOn(key))
    return;

  va_start(args, format);
  vsprintf(buf, format, args);
  va_end(args);
  printf("+++ (%s): %s%s", key, buf, buf[strlen(buf)-1] != '\n'? "\n" : "");
}

testT getTestType() {
  return testType;
}

void ParseCommandLine(int argc, char *argv[])
{
  if (argc == 1)
    return;

  if (strcmp(argv[1], "-d") != 0) { // first arg is not -d
    if (strcmp(argv[1], "-s") == 0) // syntax test
      testType = SyntaxTest;
    else if (strcmp(argv[1], "-c") == 0) // scope test
      testType = ScopeTest;
    else {
      printf("Usage: [ -s | -c | [-d <debug-key-1> <debug-key-2> ... ]\n");
      exit(2);
    }
  }

  for (int i = 2; i < argc; i++)
    SetDebugForKey(argv[i], true);
}

