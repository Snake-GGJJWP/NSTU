#pragma once

#include "WashingMachine.h"
#include "WMQueue.h"

char wmdump(const char* path, const WashingMachine* wm);
WashingMachine* wmload(const char* path);

char wmarrdump(const char* path, const WashingMachine** wmarr, int size);
WashingMachine** wmarrload(const char* path, int* size);

char wmqueuedump(const char* path, WMQueue* wmqueue);
WMQueue* wmqueueload(const char* path);