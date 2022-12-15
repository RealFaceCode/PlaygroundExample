#include <core.h>
#include <logger.h>

int main() {
    CoreInit();
    LOG_INFO({}, "hay");
    return 0;
}
