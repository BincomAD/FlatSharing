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

# Добавьте ваш исходный код
add_executable(backend_cpp main.cpp Server_class/Server.cpp Server_class/Server.h DBHelper/DBHelper.cpp DBHelper/DBHelper.h Flat/Flat.cpp Flat/Flat.h SmartLock/SmartLock.cpp SmartLock/SmartLock.h urls/index/IndexPage.cpp User/User.cpp User/User.h User/User.cpp urls/index/IndexPage.h urls/AbstractPage.cpp urls/AbstractPage.h)

# Линкуйте ваше приложение со статической библиотекой Wt
target_link_libraries(backend_cpp
        Boost::system
        Boost::thread
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
        ${PQXX_LIBRARIES})
