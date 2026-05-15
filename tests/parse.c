#include <scratch/parse.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t identifier;
    bool success = scratch_project_load(
        "../../tests/resources/Impulse 2D Physics Engine 1.3.0.sb3",
        &identifier
    );
    if (!success) abort();
}