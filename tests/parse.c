#include <scratch/parse.h>
#include <stdio.h>

int main(void) {
    size_t identifier;
    scratch_project_load(
        "/home/lexi/Documents/Programming/NativeWarp/ScratchParser/tests/resources/Impulse 2D Physics Engine 1.3.0.sb3",
        &identifier
    );

    printf("scratch_project_load identifier: %zu\n", identifier);
}