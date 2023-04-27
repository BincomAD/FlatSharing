//
// Created by nikita on 16.04.23.
//

#include "SmartLock.h"

void SmartLock::open() {
    _open = true;
    //updateLock в БД
}

void SmartLock::close() {
    _open = false;
    //updateLock в БД
}

bool SmartLock::is_open() {
    return _open;
}
