/* ===================================================================
   Question 1 - Memory Protection using Base & Limit Registers
   -------------------------------------------------------------------
   Simulates a multi-user system where every process is given a
   Base Register (start of its allotted memory partition), a Limit
   Register (size of the partition) and an Access Permission byte
   (R = Read, W = Write, X = Execute).

   For every memory access request the CPU (simulated here) checks:
      1. Bounds check   : base <= (base + logical_address) < base+limit
      2. Permission chk : requested operation is allowed for that page
   If either check fails, a PROTECTION FAULT is raised and the
   offending process is trapped to the OS (simulated by aborting
   only that access, logging it, and continuing the simulation so
   multiple test cases can be demonstrated in one run).
   =================================================================== */

#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 5

typedef struct {
    int  pid;
    char name[20];
    unsigned int base;     /* Base register value  */
    unsigned int limit;    /* Limit register value */
    char permissions[4];   /* e.g. "RW", "RWX", "R" */
} PCB;                     /* Process Control Block (simplified) */

typedef struct {
    int pid;
    unsigned int logical_addr;
    char op;                /* 'R', 'W', or 'X' */
} AccessRequest;

int has_permission(PCB *p, char op) {
    return (strchr(p->permissions, op) != NULL);
}

void check_access(PCB table[], int n, AccessRequest req) {
    PCB *p = NULL;
    for (int i = 0; i < n; i++)
        if (table[i].pid == req.pid) { p = &table[i]; break; }

    if (!p) {
        printf("[FAULT] PID %d not found in process table.\n", req.pid);
        return;
    }

    printf("\n--- Access Request : PID=%d (%s) | LogicalAddr=%u | Op=%c ---\n",
           p->pid, p->name, req.logical_addr, req.op);

    /* 1. Bounds check using base & limit registers */
    if (req.logical_addr >= p->limit) {
        printf("[TRAP] Memory Protection Violation: Address %u exceeds "
               "LIMIT (%u) for process %s\n", req.logical_addr, p->limit, p->name);
        printf("[OS ACTION] Segmentation fault -> process terminated, "
               "logged for security audit.\n");
        return;
    }

    /* 2. Compute physical address */
    unsigned int phys_addr = p->base + req.logical_addr;

    /* 3. Permission check */
    if (!has_permission(p, req.op)) {
        printf("[TRAP] Access Denied: Process %s does not have '%c' "
               "permission (allowed: %s)\n", p->name, req.op, p->permissions);
        printf("[OS ACTION] Protection fault raised -> process suspended.\n");
        return;
    }

    printf("[OK] Address translated: Base(%u) + Logical(%u) = "
           "Physical(%u)\n", p->base, req.logical_addr, phys_addr);
    printf("[OK] '%c' operation permitted -> memory access GRANTED.\n", req.op);
}

int main() {
    PCB table[MAX_PROCESSES] = {
        {101, "PayrollApp",  1000, 500, "RW"},
        {102, "ReportGen",   2000, 300, "R"},
        {103, "AdminTool",   3000, 800, "RWX"}
    };

    printf("=============================================================\n");
    printf(" MULTI-USER SYSTEM - PROCESS MEMORY PARTITION TABLE\n");
    printf("=============================================================\n");
    printf("%-6s %-12s %-8s %-8s %-10s\n", "PID", "Process", "Base", "Limit", "Perms");
    for (int i = 0; i < 3; i++)
        printf("%-6d %-12s %-8u %-8u %-10s\n", table[i].pid, table[i].name,
               table[i].base, table[i].limit, table[i].permissions);

    /* Test cases: mix of valid and invalid (violating) accesses */
    AccessRequest tests[] = {
        {101, 250,  'R'},   /* valid: within limit, has R */
        {101, 250,  'W'},   /* valid: within limit, has W */
        {101, 600,  'R'},   /* INVALID: exceeds limit (bounds violation) */
        {102, 100,  'W'},   /* INVALID: no W permission */
        {103, 799,  'X'},   /* valid: boundary case, has X */
        {102, 999,  'R'},   /* INVALID: exceeds limit */
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    printf("\n=============================================================\n");
    printf(" SIMULATING MEMORY ACCESS REQUESTS\n");
    printf("=============================================================\n");
    for (int i = 0; i < n; i++)
        check_access(table, 3, tests[i]);

    printf("\n=============================================================\n");
    printf(" SIMULATION COMPLETE\n");
    printf("=============================================================\n");
    return 0;
}
