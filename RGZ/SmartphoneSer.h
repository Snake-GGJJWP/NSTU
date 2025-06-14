#pragma once

#include "Smartphone.h"
#include "SmartphoneList.h"

// Dump Smartphone structure into the file. Return 0 on failure, 1 on success
char smdump(const char* path, const Smartphone* sm);
// Load  Smartphone structure from the file. Return NULL on failure, loaded structure on success
Smartphone* smload(const char* path);

// Dump list of Smartphone structures into the file. Return 0 on failure, 1 on success
char smlistdump(const char* path, const SMList* smlist);
// Load list of Smartphone structures into the file. Return NULL on failure, loaded list on success
SMList* smlistload(const char* path);