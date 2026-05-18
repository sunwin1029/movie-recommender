#include "UserInterface.h"

int main() {

    Manager m;
    m.loadAll();
    program(m);
    m.saveAll();

    return 0;
}
