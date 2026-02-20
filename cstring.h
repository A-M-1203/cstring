#ifndef CSTRING_H
#define CSTRING_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct cstr_string {
    uint64_t length;
    char data[];
} String;

static String* cstr_alloc(const char* str);
static void cstr_free(String* cstr);
static uint64_t cstr_len(const char* str);
static void cstr_copy(void* dst, const void* src, uint64_t length);
static void cstr_concat_str(String* cstr_dst, const char* str_src);
static void cstr_concat_cstr(String* cstr_dst, const String* cstr_src);
static int cstr_cmp_str(String* cstr, const char* str);
static int cstr_cmp_cstr(String* cstr_1, String* cstr_2);

#ifdef CSTRING_IMPLEMENTATION

String* cstr_alloc(const char* str) {
    uint64_t length;
    uint64_t cstr_size;
    String* cstr = NULL;

    length = cstr_len(str);
    cstr_size = length + 1 + sizeof(String);
    cstr = (String*)malloc(cstr_size);
    assert(cstr != NULL);

    cstr->length = length;
    cstr_copy(cstr->data, str, length);
    return cstr;
}

void cstr_free(String* cstr) {
    free(cstr);
    cstr = NULL;
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

void cstr_concat_str(String* cstr_dst, const char* str_src) {
    uint64_t str_length = cstr_len(str_src);
    uint64_t cstr_curr_size = cstr_dst->length + 1 + sizeof(String);
    uint64_t cstr_new_size = cstr_curr_size + str_length;

    cstr_dst = (String*)realloc(cstr_dst, cstr_new_size);
    char* cstr_data = cstr_dst->data + cstr_dst->length;
    cstr_copy(cstr_data, str_src, str_length);
    cstr_dst->length += str_length;
}

void cstr_concat_cstr(String* cstr_dst, const String* cstr_src) {
    cstr_concat_str(cstr_dst, cstr_src->data);
}

int cstr_cmp_str(String* cstr, const char* str) { return 0; }
int cstr_cmp_cstr(String* cstr_1, String* cstr_2) { return 0; }

#endif // CSTRING_IMPLEMENTATION
#endif // CSTRING_H
