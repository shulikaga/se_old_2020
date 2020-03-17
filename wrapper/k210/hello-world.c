#define SBI_EXT_0_1_CONSOLE_PUTCHAR 0x1

// global variable for pointing to the "Hello World!    " string
char* foo;

void sbi_ecall_console_putc(char c) {
    asm volatile(
        "li a0, 1;"
        "li a1, 97;" // just a test to see if it prints 'a'
        "ecall;"
    );
}

static inline void write(uint64_t std_x, char* str, uint64_t no_chars) {
    (void) std_x;

    while (no_chars && str) {
        sbi_ecall_console_putc(*str++);
        --no_chars;
    }
}

// main procedure for printing "Hello World!    " on the console
uint64_t* main() {
  // point to the "Hello World!    " string
  foo = "Hello World!    ";

  // strings are actually stored in chunks of 8 characters in memory,
  // that is, here as "Hello Wo", and "rld!    " which allows us to
  // print them conveniently in chunks of 8 characters at a time

  // as long as there are characters print them
  while (*foo != 0) {
    // 1 means that we print to the console
    // foo points to a chunk of 8 characters
    // 8 means that we print 8 characters
    write(1, foo, 8);

    // go to the next chunk of 8 characters
    foo = foo + 1;
  }

  while (1)
      ;
}