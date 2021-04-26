#include "kernel-header/output.h"

void getFullKeyWrapper(int *ptr) {
    *ptr = getFullKeyPress();
}
