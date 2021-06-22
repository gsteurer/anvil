#pragma once
// https://en.wikipedia.org/wiki/Linear_congruential_generator
// http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf // page 256
// https://stackoverflow.com/questions/6161322/using-stdlibs-rand-from-multiple-threads // thread safety
static unsigned long int next = 1;

int rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed) {
    next = seed;
}