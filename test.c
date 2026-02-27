#define CSTR_IMPLEMENTATION
#include "cstring.h"

#include <stdio.h>
int main() {
    string* str = str_alloc("Hello");
    printf("%s\n", str->data);
    string* str1 = str_alloc(" Hello");
    printf("%s\n", str1->data);

    str_concat_str(&str, str1);
    printf("%s\n", str->data);

    // str_upper(str);
    // printf("%s\n", str->data);

    // str_lower(str);
    // printf("%s\n", str->data);

    // str_capitalize(str);
    // printf("%s\n", str->data);

    int64_t index = str_index_of(str, "Hello");
    printf("Index: %ld\n", index);

    str_free(str1);
    str_free(str);
    return 0;
}
