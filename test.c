#define CSTR_IMPLEMENTATION
#include "cstring.h"

#include <stdio.h>
int main() {
    cstr_t* str = NULL;
    str = cstr_alloc("Helloa");
    cstr_t* str1 = cstr_alloc("Hello");
    printf("%d\n", cstr_cmp_cstr(str, str1));
    // cstr_concat_str(&str, "THERE");
    // printf("%s\n", str->data);
    // cstr_t* str1 = cstr_alloc(" THERE TWO!!!");
    // cstr_concat_cstr(&str, str1);
    // printf("%s\n", str->data);
    // cstr_t* str2 = cstr_alloc(" There three?!!");
    // cstr_concat_cstr(&str, str2);
    // printf("%s\n", str->data);
    // cstr_free(&str2);
    cstr_free(&str1);
    cstr_free(&str);
    return 0;
}
