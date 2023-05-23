//
// Created by nikita on 16.04.23.
//

#ifndef BACKEND_CPP_SMARTLOCK_H
#define BACKEND_CPP_SMARTLOCK_H
#include<iostream>

class SmartLock {
private:
    size_t _id;
    size_t _flatId;
    bool _isOpen;
public:
    SmartLock(size_t id, size_t flatId, bool isOpen);
    void open();
    void close();
    size_t getId();
    size_t getFlatId();
    bool is_open();
    
};

#endif //BACKEND_CPP_SMARTLOCK_H
