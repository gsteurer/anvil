#include <stdio.h>
#include <time.h>

#include "ads/arrayutils.h"
#include "ads/list.h"
#include "ads/map.h"
#include "ads/redblacktree.h"
#include "ads/slice.h"
#include "option.h"
#include "rand.h"
#include "types.h"

static const anvil::i64_t TEST_SIZE = 42069;
static const clockid_t PRECISION = CLOCK_THREAD_CPUTIME_ID;

// https://stackoverflow.com/questions/17705786/getting-negative-values-using-clock-gettime
timespec diff(timespec start, timespec end) {
    timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

void slice() {
    printf("\n>>>slice test\n");
    timespec t_initial, t_final, delta;
    int* elements = new int[TEST_SIZE];
    anvil::Slice<anvil::u64_t>* slice = new anvil::Slice<anvil::u64_t>();

    clock_gettime(PRECISION, &t_initial);
    for (anvil::isize_t idx = 0; idx < TEST_SIZE; idx++) {
        int val = anvil::rand();
        slice->Insert(anvil::rand());
        elements[idx] = val;
    }
    clock_gettime(PRECISION, &t_final);

    delta = diff(t_initial, t_final);
    printf("slice insert time: %lds || %ldns\n", delta.tv_sec, delta.tv_nsec);

    anvil::scramble(elements, TEST_SIZE);

    clock_gettime(PRECISION, &t_initial);
    for (anvil::isize_t idx = 0; idx < TEST_SIZE; idx++) {
        slice->IndexOf(elements[idx]);
    }
    clock_gettime(PRECISION, &t_final);

    delta = diff(t_initial, t_final);
    printf("slice search time: %lds || %ldns\n", delta.tv_sec, delta.tv_nsec);

    delete slice;
    delete[] elements;
    printf("<<<\n");
}

void list() {
    printf("\n>>>list test\n");
    timespec t_initial, t_final, delta;
    int* elements = new int[TEST_SIZE];
    List<anvil::u64_t>* list = new List<anvil::u64_t>();

    clock_gettime(PRECISION, &t_initial);
    for (anvil::isize_t idx = 0; idx < TEST_SIZE; idx++) {
        int val = anvil::rand();
        list->PushFront(val);
        elements[idx] = val;
    }
    clock_gettime(PRECISION, &t_final);

    delta = diff(t_initial, t_final);
    printf("list insert time: %lds || %ldns\n", delta.tv_sec, delta.tv_nsec);

    anvil::scramble(elements, TEST_SIZE);

    clock_gettime(PRECISION, &t_initial);
    for (anvil::isize_t idx = 0; idx < TEST_SIZE; idx++) {
        list->IndexOf(elements[idx]);
    }
    clock_gettime(PRECISION, &t_final);

    delta = diff(t_initial, t_final);
    printf("list search time: %lds || %ldns\n", delta.tv_sec, delta.tv_nsec);

    delete list;
    delete[] elements;
    printf("<<<\n");
}

void rbtree() {
    printf("\n>>>rbtree test\n");
    timespec t_initial, t_final, delta;
    anvil::srand(time(0));
    int* elements = new int[TEST_SIZE];

    clock_gettime(PRECISION, &t_initial);
    RBTree<anvil::u64_t>* tree = new RBTree<anvil::u64_t>();
    for (anvil::isize_t idx = 0; idx < TEST_SIZE; idx++) {
        int val = anvil::rand();
        tree->Insert(val);
        elements[idx] = val;
    }
    clock_gettime(PRECISION, &t_final);

    delta = diff(t_initial, t_final);
    printf("tree insert time: %lds || %ldns\n", delta.tv_sec, delta.tv_nsec);

    anvil::scramble(elements, TEST_SIZE);

    clock_gettime(PRECISION, &t_initial);
    for (anvil::isize_t idx = 0; idx < TEST_SIZE; idx++) {
        tree->Search(elements[idx]);
    }
    clock_gettime(PRECISION, &t_final);

    delta = diff(t_initial, t_final);
    printf("tree search time: %lds || %ldns\n", delta.tv_sec, delta.tv_nsec);

    delete tree;
    delete[] elements;
    printf("<<<\n");
}

void map() {
    printf("\n>>>map test\n");
    timespec t_initial, t_final, delta;
    int* elements = new int[TEST_SIZE];
    Map<anvil::u64_t, anvil::u64_t>* map = new Map<anvil::u64_t, anvil::u64_t>();

    clock_gettime(PRECISION, &t_initial);
    for (anvil::isize_t idx = 0; idx < TEST_SIZE; idx++) {
        anvil::u64_t val = static_cast<anvil::u64_t>(anvil::rand());
        (*map)[val] = val;
        elements[idx] = val;
    }
    clock_gettime(PRECISION, &t_final);

    delta = diff(t_initial, t_final);
    printf("map insert time: %lds || %ldns\n", delta.tv_sec, delta.tv_nsec);

    anvil::scramble(elements, TEST_SIZE);

    clock_gettime(PRECISION, &t_initial);
    for (anvil::isize_t idx = 0; idx < TEST_SIZE; idx++) {
        (*map)[elements[idx]];
    }
    clock_gettime(PRECISION, &t_final);

    delta = diff(t_initial, t_final);
    printf("map search time: %lds || %ldns\n", delta.tv_sec, delta.tv_nsec);

    delete map;
    delete[] elements;
    printf("<<<\n");
}

int main() {
    slice();
    list();
    rbtree();
    map();
}
