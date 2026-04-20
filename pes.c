// pes.c — CLI entry point and command dispatch
//
// This file is PROVIDED. Do not modify.

#include "pes.h"
#include "index.h"
#include "commit.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// ─── PROVIDED: Command Implementations ──────────────────────────────────────

// Usage: pes init
void cmd_init(void) {
    if (mkdir(PES_DIR, 0755) != 0 && access(PES_DIR, F_OK) != 0) {
        fprintf(stderr, "error: failed to create %s\n", PES_DIR);
        return;
    }
    mkdir(OBJECTS_DIR, 0755);
    mkdir(".pes/refs", 0755);
    mkdir(REFS_DIR, 0755);

    if (access(HEAD_FILE, F_OK) != 0) {
        FILE *f = fopen(HEAD_FILE, "w");
        if (f) {
            fprintf(f, "ref: refs/heads/main\n");
            fclose(f);
        }
    }

    printf("Initialized empty PES repository in %s/\n", PES_DIR);
}

// Usage: pes add <file>...
void cmd_add(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: pes add <file>...\n");
        return;
    }

    Index index;
    if (index_load(&index) != 0) {
