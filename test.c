#define CSTRING_IMPLEMENTATION
#include "cstring.h"

#include <stdio.h>
int main() {
    String* str = NULL;
    str = cstr_alloc("Hello ");
    cstr_concat_str(str, "THERE");
    printf("%s\n", str->data);
    cstr_free(str);
    return 0;
}
