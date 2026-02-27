#ifndef CSTR_H
#define CSTR_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint64_t length;
    char data[];
} string;

static string* str_alloc(const char* cstr);
static void str_free(string* str);
static uint64_t str_cstr_length(const char* cstr);
static void str_copy(void* dst, const void* src, uint64_t length);
static void str_concat_cstr(string** str_dst, const char* cstr_src);
static void str_concat_str(string** str_dst, const string* str_src);
static int32_t str_cmp_cstr(const string* str, const char* cstr);
static int32_t str_cmp_str(const string* str_1, const string* str_2);

#ifdef CSTR_IMPLEMENTATION

string* str_alloc(const char* cstr) {
    uint64_t cstr_length;
    uint64_t str_size;
    string* str = NULL;

    cstr_length = str_cstr_length(cstr);
    str_size = cstr_length + 1 + sizeof(string);
    str = (string*)malloc(str_size);
    assert(str != NULL);

    str->length = cstr_length;
    str_copy(str->data, cstr, cstr_length);
    return str;
}

void str_free(string* str) { free(str); }

uint64_t str_cstr_length(const char* cstr) {
    uint64_t cstr_length = 0;
    for (; *cstr != 0; cstr++, cstr_length++);
    // const char* cstr_ptr = cstr;
    // for (; *str_ptr != 0; str_ptr++, str_length++);
    return cstr_length;
}

void str_copy(void* dst, const void* src, uint64_t length) {
    char* ptr_dst = (char*)dst;
    const char* ptr_src = (const char*)src;
    for (; length > 0; ptr_dst++, ptr_src++, length--) *ptr_dst = *ptr_src;
}

void str_concat_cstr(string** str_dst, const char* cstr_src) {
    uint64_t cstr_length = str_cstr_length(cstr_src);
    uint64_t str_old_size = (*str_dst)->length + 1 + sizeof(string);
    uint64_t str_new_size = str_old_size + cstr_length;

    *str_dst = (string*)realloc(*str_dst, str_new_size);
    char* str_data = (*str_dst)->data + (*str_dst)->length;
    str_copy(str_data, cstr_src, cstr_length);
    (*str_dst)->length += cstr_length;
}

void str_concat_str(string** str_dst, const string* str_src) {
    str_concat_cstr(str_dst, str_src->data);
}

int32_t str_cmp_cstr(const string* str, const char* cstr) {
    uint64_t cstr_length = str_cstr_length(cstr);
    if (str->length < cstr_length) return -1;
    if (str->length > cstr_length) return 1;
    uint64_t i = 0;
    while (i < str->length && i < cstr_length) {
        if (str->data[i] != cstr[i]) {
            return (uint8_t)str->data[i] - (uint8_t)cstr[i];
        }
        i++;
    }
    return 0;
}

int32_t str_cmp_str(const string* str_1, const string* str_2) {
    return str_cmp_cstr(str_1, str_2->data);
}

#endif // CSTR_IMPLEMENTATION
#endif // CSTR_H
