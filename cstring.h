#ifndef CSTR_H
#define CSTR_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int64_t length;
    char data[];
} string;

static string* str_alloc(const char* cstr);
static void str_free(string* str);
static int64_t str_cstr_length(const char* cstr);
static void str_copy(void* dst, const void* src, int64_t length);
static void str_concat_cstr(string** str_dst, const char* cstr_src);
static void str_concat_str(string** str_dst, const string* str_src);
static int32_t str_cmp_cstr(const string* str, const char* cstr);
static int32_t str_cmp_str(const string* str_1, const string* str_2);
static void str_upper(string* str);
static void str_lower(string* str);
static void str_capitalize(string* str);
static int64_t str_index_of(const string* str, const char* csubstr);
static int64_t str_last_index_of(const string* str, const char* csubstr);

// #ifdef CSTR_IMPLEMENTATION

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

int64_t str_cstr_length(const char* cstr) {
    int64_t cstr_length = 0;
    for (; *cstr != 0; cstr++, cstr_length++);
    return cstr_length;
}

void str_copy(void* dst, const void* src, int64_t length) {
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
    int64_t cstr_length = str_cstr_length(cstr);
    int64_t str_length = str->length;
    if (str_length < cstr_length) return -1;
    if (str_length > cstr_length) return 1;
    for (int64_t i = 0; i < str_length && i < cstr_length; i++) {
        if (str->data[i] != cstr[i]) {
            return (uint8_t)str->data[i] - (uint8_t)cstr[i];
        }
    }

    return 0;
}

int32_t str_cmp_str(const string* str_1, const string* str_2) {
    return str_cmp_cstr(str_1, str_2->data);
}

void str_upper(string* str) {
    int8_t decrement = 'a' - 'A';
    for (int64_t i = 0; i < str->length; i++) {
        if (str->data[i] >= 97 && str->data[i] <= 122) str->data[i] -= decrement;
    }
}

void str_lower(string* str) {
    int8_t increment = 'a' - 'A';
    for (int64_t i = 0; i < str->length; i++) {
        if (str->data[i] >= 65 && str->data[i] <= 90) str->data[i] += increment;
    }
}

void str_capitalize(string* str) {
    if (str->length == 0) return;
    int8_t decrement = 'a' - 'A';
    int8_t increment = decrement;
    if (str->data[0] >= 97 && str->data[0] <= 122) str->data[0] -= decrement;
    for (int64_t i = 1; i < str->length; i++) {
        if (str->data[i] >= 65 && str->data[i] <= 90) str->data[i] += increment;
    }
}

int64_t str_index_of(const string* str, const char* csubstr) {
    int64_t csubstr_length = str_cstr_length(csubstr);
    int64_t difference = str->length - csubstr_length;
    if (csubstr_length == 0 || difference < 0) return -1;
    int64_t j;
    for (int64_t i = 0; i <= difference; i++) {
        for (j = 0; j < csubstr_length && str->data[i + j] == csubstr[j]; j++);
        if (j == csubstr_length) return i;
    }

    return -1;
}

int64_t str_last_index_of(const string* str, const char* csubstr) {
    int64_t csubstr_length = str_cstr_length(csubstr);
    int64_t difference = str->length - csubstr_length;
    if (csubstr_length == 0 || difference < 0) return -1;
    int64_t j;
    for (int64_t i = difference; i >= 0; i--) {
        for (j = csubstr_length - 1; j >= 0 && str->data[i + j] == csubstr[j]; j--);
        if (j < 0) return i;
    }

    return -1;
}
// #endif // CSTR_IMPLEMENTATION
#endif // CSTR_H
