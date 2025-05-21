#pragma once

#include "WashingMachine.h"
#include "WMQueue.h"

// Dump WashingMachine structure into the file. Return 0 on failure, 1 on success
char wmdump(const char* path, const WashingMachine* wm);
// Load  WashingMachine structure from the file. Return NULL on failure, loaded structure on success
WashingMachine* wmload(const char* path);

// Dump array of WashingMachine structures into the file. Return 0 on failure, 1 on success
char wmarrdump(const char* path, const WashingMachine** wmarr, int size);
// Load array of WashingMachine structures into the file. Return NULL on failure, loaded array on success
WashingMachine** wmarrload(const char* path, int* size);

// Dump WashingMachine queue structure into the file. Return 0 on failure, 1 on success
char wmqueuedump(const char* path, WMQueue* wmqueue);
// Load WashingMachine queue structure into the file. Return NULL on failure, loaded queue on success
WMQueue* wmqueueload(const char* path);