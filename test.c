#define CSTR_IMPLEMENTATION
#include "cstring.h"

#include <stdio.h>
int main() {
    string* str = str_alloc("Hello");
    printf("%s\n", str->data);
    string* str1 = str_alloc(" World!");
    printf("%s\n", str1->data);
    str_concat_str(&str, str1);
    printf("%s\n", str->data);
    str_free(str1);
    str_free(str);
    return 0;
}
