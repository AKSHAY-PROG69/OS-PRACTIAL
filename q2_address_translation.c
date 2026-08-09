/* ===================================================================
   Question 2 - Logical to Physical Address Translation (Paging)
   -------------------------------------------------------------------
   Demonstrates the step-by-step translation performed by the MMU
   (Memory Management Unit) at execution time (dynamic / execution-
   time binding).

   Page size      = 1024 bytes (2^10)  -> offset uses lower 10 bits
   Logical addr   = 16-bit value -> Page Number (6 bits) | Offset (10 bits)
   Page Table     = maps each logical page -> a physical frame number
   Physical addr  = (frame_number * PAGE_SIZE) + offset

   The program also demonstrates protection: if a logical page is not
   present in the page table (invalid page number), the MMU raises a
   page-fault / addressing-error instead of translating it.
   =================================================================== */

#include <stdio.h>

#define PAGE_SIZE   1024                 /* bytes per page/frame   */
#define OFFSET_BITS 10                   /* log2(PAGE_SIZE)        */
#define NUM_PAGES   8                    /* pages in this process  */

/* Page table: index = page number, value = frame number (-1 = invalid) */
int page_table[NUM_PAGES] = {5, 2, 9, -1, 7, 0, -1, 3};

void translate(unsigned int logical_addr) {
    unsigned int page_number = logical_addr >> OFFSET_BITS;      /* step 1 */
    unsigned int offset      = logical_addr & (PAGE_SIZE - 1);   /* step 2 */

    printf("\n--- Translating Logical Address %u ---\n", logical_addr);
    printf("Step 1: Split address -> Page Number = %u , Offset = %u\n",
           page_number, offset);

    if (page_number >= NUM_PAGES) {
        printf("Step 2: Page number %u is OUTSIDE the process page table "
               "(size=%d)\n", page_number, NUM_PAGES);
        printf("Result : ADDRESSING ERROR (protection fault) - access denied.\n");
        return;
    }

    int frame = page_table[page_number];
    printf("Step 2: Page Table lookup -> Page %u maps to Frame %d\n",
           page_number, frame);

    if (frame == -1) {
        printf("Step 3: Frame is INVALID (page not resident / not allocated)\n");
        printf("Result : PAGE FAULT - OS must load page or deny access.\n");
        return;
    }

    unsigned int physical_addr = (frame * PAGE_SIZE) + offset;
    printf("Step 3: Physical Address = (Frame %d * PageSize %d) + Offset %u"
           " = %u\n", frame, PAGE_SIZE, offset, physical_addr);
    printf("Result : Translation SUCCESSFUL -> CPU accesses physical memory "
           "at %u\n", physical_addr);
}

int main() {
    printf("=============================================================\n");
    printf(" PAGE TABLE FOR THIS PROCESS  (Page Size = %d bytes)\n", PAGE_SIZE);
    printf("=============================================================\n");
    printf("%-12s %-12s\n", "Page No.", "Frame No.");
    for (int i = 0; i < NUM_PAGES; i++) {
        if (page_table[i] == -1)
            printf("%-12d %-12s\n", i, "INVALID");
        else
            printf("%-12d %-12d\n", i, page_table[i]);
    }

    unsigned int test_addresses[] = {2050, 5000, 100, 3300, 9000, 6500};
    int n = sizeof(test_addresses) / sizeof(test_addresses[0]);

    printf("\n=============================================================\n");
    printf(" ADDRESS TRANSLATION SIMULATION (Execution-time / Dynamic Binding)\n");
    printf("=============================================================\n");
    for (int i = 0; i < n; i++)
        translate(test_addresses[i]);

    printf("\n=============================================================\n");
    printf(" SIMULATION COMPLETE\n");
    printf("=============================================================\n");
    return 0;
}
