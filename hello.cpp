#include <pybind11/pybind11.h>

int hello(int x) {
    x++;
    printf("Hello, %d\n", x);
    return x;
}

PYBIND11_MODULE(hello, m) {
    m.def("hello", &hello, R"pbdoc(
        Say hello.
    )pbdoc");
}