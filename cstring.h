#ifndef CSTR_H
#define CSTR_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint64_t length;
    char data[];
} cstr;

static cstr* cstr_alloc(const char* str);
static void cstr_free(cstr** cstr);
static uint64_t cstr_len(const char* str);
static void cstr_copy(void* dst, const void* src, uint64_t length);
static void cstr_concat_str(cstr** cstr_dst, const char* str_src);
static void cstr_concat_cstr(cstr** cstr_dst, const cstr* cstr_src);
static int cstr_cmp_str(const cstr* cstr, const char* str);
static int cstr_cmp_cstr(const cstr* cstr_1, const cstr* cstr_2);

#ifdef CSTR_IMPLEMENTATION

cstr* cstr_alloc(const char* str) {
    uint64_t length;
    uint64_t cstr_size;
    cstr* cstring = NULL;

    length = cstr_len(str);
    cstr_size = length + 1 + sizeof(cstr);
    cstring = (cstr*)malloc(cstr_size);
    assert(cstring != NULL);

    cstring->length = length;
    cstr_copy(cstring->data, str, length);
    return cstring;
}

void cstr_free(cstr** cstr) {
    free(*cstr);
    *cstr = NULL;
}

uint64_t cstr_len(const char* str) {
    uint64_t length = 0;
    const char* ptr = str;
    for (; *ptr != 0; ptr++, length++);
    return length;
}

void cstr_copy(void* dst, const void* src, uint64_t length) {
    char* ptr_dst = (char*)dst;
    const char* ptr_src = (const char*)src;
    for (; length > 0; ptr_dst++, ptr_src++, length--) *ptr_dst = *ptr_src;
}

void cstr_concat_str(cstr** cstr_dst, const char* str_src) {
    uint64_t str_length = cstr_len(str_src);
    uint64_t cstr_curr_size = (*cstr_dst)->length + 1 + sizeof(cstr);
    uint64_t cstr_new_size = cstr_curr_size + str_length;

    *cstr_dst = (cstr*)realloc(*cstr_dst, cstr_new_size);
    char* cstr_data = (*cstr_dst)->data + (*cstr_dst)->length;
    cstr_copy(cstr_data, str_src, str_length);
    (*cstr_dst)->length += str_length;
}

void cstr_concat_cstr(cstr** cstr_dst, const cstr* cstr_src) {
    cstr_concat_str(cstr_dst, cstr_src->data);
}

int cstr_cmp_str(const cstr* cstr, const char* str) { return 0; }
int cstr_cmp_cstr(const cstr* cstr_1, const cstr* cstr_2) { return 0; }

#endif // CSTR_IMPLEMENTATION
#endif // CSTR_H
