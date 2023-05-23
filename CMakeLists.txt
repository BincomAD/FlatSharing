cmake_minimum_required(VERSION 3.5)
project(backend_cpp)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

include_directories(${PQXX_INCLUDE_DIRS})
link_directories(${PQXX_LIBRARY_DIRS})

# Проверка наличия GTest на компьютере
find_package(GTest REQUIRED)

# Включение заголовочных файлов GTest
include_directories(${GTEST_INCLUDE_DIRS})

# Создание нового исполняемого файла для тестов
# add_executable(backend_cpp_tests Tests/test_main.cpp Tests/FlatTest.cpp Flat/Flat.cpp Tests/SmartLockTest.cpp SmartLock/SmartLock.cpp Tests/UserTest.cpp User/User.cpp Tests/DBHelperTest.cpp DBHelper/DBHelper.cpp)

# Связывание тестов с GTest и GTest_main
# target_link_libraries(backend_cpp_tests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} ${PQXX_LIBRARIES} pthread)


# Добавьте ваш исходный код
add_executable(backend_cpp main.cpp
        Server_class/Server.cpp Server_class/Server.h
        DBHelper/DBHelper.cpp DBHelper/DBHelper.h
        Flat/Flat.cpp Flat/Flat.h
        SmartLock/SmartLock.cpp SmartLock/SmartLock.h
        urls/index/IndexPage.cpp urls/index/IndexPage.h
        User/User.cpp User/User.h
        urls/AbstractPage.cpp urls/AbstractPage.h
        Auth/AuthHelper.cpp Auth/AuthHelper.h
        urls/flatList/FlatListPage.cpp urls/flatList/FlatListPage.h
        urls/CurrentFlatPage/CurrentFlatPage.cpp urls/CurrentFlatPage/CurrentFlatPage.h
        urls/LogIn/LoginPage.cpp urls/LogIn/LoginPage.h
        urls/LockStatusPage/LockStatusPage.cpp urls/LockStatusPage/LockStatusPage.h
        urls/RegistrationPage/RegistrationPage.cpp urls/RegistrationPage/RegistrationPage.h urls/UserPage/UserPage.cpp urls/UserPage/UserPage.h urls/RentAFlat/RentAFlatPage.cpp urls/RentAFlat/RentAFlatPage.h)

# Линкуйте ваше приложение со статической библиотекой Wt
target_link_libraries(backend_cpp
        Boost::system
        Boost::thread
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
        ${PQXX_LIBRARIES})
