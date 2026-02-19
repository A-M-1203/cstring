#include <stdint.h>

typedef struct cstr_string {
    uint64_t length;
    char data[];
} String;

uint64_t cstr_len(const char* str);
void cstr_copy(void* dst, const void* src, uint64_t length);
String* cstr_alloc(const char* str);
void cstr_concat_str(String* cstr_dst, const char* str_src);
void cstr_concat_cstr(String* cstr_dst, const String* cstr_src);
void cstr_free(String* cstr);
