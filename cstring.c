#include "cstring.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

String* cstr_alloc(const char* str) {
    uint64_t length;
    uint32_t cstr_size;
    String* cstr = NULL;

    length = cstr_len(str);
    cstr_size = length + 1 + sizeof(String);
    cstr = (String*)malloc(cstr_size);
    assert(cstr != NULL);

    cstr->length = length;
    cstr_copy(cstr->data, str, length);
    return cstr;
}

int main(int argc, char** argv) {
    String* str = NULL;
    str = cstr_alloc("Hello World!");
    printf("%s\n", str->data);
    return 0;
}
