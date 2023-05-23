//
// Created by nikita on 01.05.23.
//
#include "gtest/gtest.h"
#include "../SmartLock/SmartLock.h"

TEST(SmartLockTest, LockIsClosedByDefault) {
    SmartLock lock(1, 1, false);
    EXPECT_FALSE(lock.is_open());
}

TEST(SmartLockTest, LockCanBeOpenedAndClosed) {
    SmartLock lock(1, 1, false);
    EXPECT_FALSE(lock.is_open());

    lock.open();
    EXPECT_TRUE(lock.is_open());

    lock.close();
    EXPECT_FALSE(lock.is_open());
}
