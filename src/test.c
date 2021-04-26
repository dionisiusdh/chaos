#include "kernel-header/config.h"
#include "std-header/std.h"

int main()
{
    print("Hello World\n", BIOS_WHITE);

    returnToSender();

    return 0;
}
