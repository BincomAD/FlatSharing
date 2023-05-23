//
// Created by nikita on 16.04.23.
//

#include "SmartLock.h"

SmartLock::SmartLock(size_t id, size_t flatId, bool isOpen): _id(id), _flatId(flatId), _isOpen(isOpen) {}
   
void SmartLock::open() {
    _isOpen = true;
    //updateLock в БД
}

void SmartLock::close() {
    _isOpen = false;
    //updateLock в БД
}

bool SmartLock::is_open() {
    return _isOpen;
}

size_t SmartLock::getId() {
	return _id;
}

size_t SmartLock::getFlatId() {
	return _flatId;
}
