#include "types.h"

struct sysinfo { 
  uint64 uptime;       // Seconds since boot 
  uint64 totalram;     // Total usable memory 
  uint64 freeram;      // Available memory size
  ushort procs;        // Number of current processes 
};