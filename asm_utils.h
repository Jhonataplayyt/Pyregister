#ifndef ASM_UTILS_H
#define ASM_UTILS_H

static inline int read_eax() {
    int eax_val;
    asm volatile(
        "mov %0, eax"
        : "=r"(eax_val)
        :
        : "eax");
    return eax_val;
}

static inline int read_ebx() {
    int ebx_val;
    asm volatile(
        "mov %0, ebx"
        : "=r"(ebx_val)
        :
        : "ebx");
    return ebx_val;
}

static inline void write_eax(int val) {
    asm volatile(
        "mov eax, %0"
        :
        : "r"(val)
        : "eax");
}

static inline void write_ebx(int val) {
    asm volatile(
        "mov ebx, %0"
        :
        : "r"(val)
        : "ebx");
}

#endif // ASM_UTILS_H
