// index.h — Staging area (index) interface
//
// The index is a text file (.pes/index) that tracks which files are
// staged for the next commit. It maps file paths to their blob hashes
// and stores metadata for fast change detection.

#ifndef INDEX_H
#define INDEX_H

#include "pes.h"

#define MAX_INDEX_ENTRIES 10000

typedef struct {
    uint32_t mode;          // File mode (100644, 100755, etc.)
    ObjectID hash;          // SHA-256 of the staged blob
    uint64_t mtime_sec;     // Last modification time (seconds since epoch)
    uint32_t size;          // File size in bytes at time of staging
    char path[512];         // Relative path from repo root (e.g., "src/main.c")
} IndexEntry;

typedef struct {
    IndexEntry entries[MAX_INDEX_ENTRIES];
    int count;
} Index;
