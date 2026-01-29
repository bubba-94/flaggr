#include <stddef.h>
#include "flaggr.h"

int main() {
    FlagBuffer flags[2];

    japan(&flags[0]);
    germany(&flags[1]);
 
    for (size_t i = 0; i < COUNT_OF(flags); i++) {
        render(&flags[i]);
    }

    return 0;
}