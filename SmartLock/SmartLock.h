//
// Created by nikita on 16.04.23.
//

#ifndef BACKEND_CPP_SMARTLOCK_H
#define BACKEND_CPP_SMARTLOCK_H
#include<iostream>

class SmartLock {
private:
    size_t _id;
    bool _open;

public:
    void open();
    void close();
    bool is_open();
};

#endif //BACKEND_CPP_SMARTLOCK_H
