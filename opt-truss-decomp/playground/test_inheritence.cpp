//
// Created by yche on 7/16/19.
//
#include "util/log/log.h"

class A {
    int a;
public:
    explicit A(int a) : a(a) {}

    void test() {
        log_info("a: %d", a);
    }

    void func(const char *s) {
        log_info("str: %s", s);
    };
};

class B : public A {
    int b;

public:
    B(int a, int b) : A(a), b(b) {}

    void operator()() {
        test();
        log_info("b: %d", b);
    }

    using A::func;  // pull it out for searching

    void func(int x) {
        log_info("int: %d", x);
    };
};

int main() {
    B b(1, 2);
    b();

    b.func(1);
    auto str = "abc";
    b.func(str);
}

