#include "engine/engine_lib.h"

int main() {
    struct Engine_App app;

    try {
        run(&app);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
