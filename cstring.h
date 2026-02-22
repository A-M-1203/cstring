#ifndef CSTR_H
#define CSTR_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint64_t length;
    char data[];
} cstr_t;

static cstr_t* cstr_alloc(const char* str);
static void cstr_free(cstr_t** cstr);
static uint64_t cstr_len(const char* str);
static void cstr_copy(void* dst, const void* src, uint64_t length);
static void cstr_concat_str(cstr_t** cstr_dst, const char* str_src);
static void cstr_concat_cstr(cstr_t** cstr_dst, const cstr_t* cstr_src);
static int32_t cstr_cmp_str(const cstr_t* cstr, const char* str);
static int32_t cstr_cmp_cstr(const cstr_t* cstr_1, const cstr_t* cstr_2);

#ifdef CSTR_IMPLEMENTATION

cstr_t* cstr_alloc(const char* str) {
    uint64_t str_length;
    uint64_t cstr_size;
    cstr_t* cstr = NULL;

    str_length = cstr_len(str);
    cstr_size = str_length + 1 + sizeof(cstr_t);
    cstr = (cstr_t*)malloc(cstr_size);
    assert(cstr != NULL);

    cstr->length = str_length;
    cstr_copy(cstr->data, str, str_length);
    return cstr;
}

void cstr_free(cstr_t** cstr) {
    free(*cstr);
    *cstr = NULL;
}

uint64_t cstr_len(const char* str) {
    uint64_t str_length = 0;
    const char* str_ptr = str;
    for (; *str_ptr != 0; str_ptr++, str_length++);
    return str_length;
}

void cstr_copy(void* dst, const void* src, uint64_t length) {
    char* ptr_dst = (char*)dst;
    const char* ptr_src = (const char*)src;
    for (; length > 0; ptr_dst++, ptr_src++, length--) *ptr_dst = *ptr_src;
}

void cstr_concat_str(cstr_t** cstr_dst, const char* str_src) {
    uint64_t str_length = cstr_len(str_src);
    uint64_t cstr_curr_size = (*cstr_dst)->length + 1 + sizeof(cstr_t);
    uint64_t cstr_new_size = cstr_curr_size + str_length;

    *cstr_dst = (cstr_t*)realloc(*cstr_dst, cstr_new_size);
    char* cstr_data = (*cstr_dst)->data + (*cstr_dst)->length;
    cstr_copy(cstr_data, str_src, str_length);
    (*cstr_dst)->length += str_length;
}

void cstr_concat_cstr(cstr_t** cstr_dst, const cstr_t* cstr_src) {
    cstr_concat_str(cstr_dst, cstr_src->data);
}

int32_t cstr_cmp_str(const cstr_t* cstr, const char* str) {
    uint64_t i = 0;
    uint64_t str_length = cstr_len(str);
    while (i < cstr->length && i < str_length) {
        if (cstr->data[i] != str[i]) {
            return (uint8_t)cstr->data[i] - (uint8_t)str[i];
        }
        i++;
    }
    if (cstr->length < str_length) return -1;
    if (cstr->length > str_length) return 1;
    return 0;
}

int32_t cstr_cmp_cstr(const cstr_t* cstr_1, const cstr_t* cstr_2) {
    return cstr_cmp_str(cstr_1, cstr_2->data);
}

#endif // CSTR_IMPLEMENTATION
#endif // CSTR_H
