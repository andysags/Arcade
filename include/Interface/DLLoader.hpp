/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** DLLoader.hpp
*/

#ifndef DLLOADER_HPP
    #define DLLOADER_HPP
    #include <iostream>
    #include <dlfcn.h>
    #include <stdexcept>
    #include "Error.hpp"

using namespace std;

template <typename T>   
class DLLoader {
private:
    void *handle;
    T *(*createFunc)();
    void (*destroyFunc)(T *);

public:
    DLLoader(const std::string &libPath) : handle(nullptr), createFunc(nullptr), destroyFunc(nullptr) {
        handle = dlopen(libPath.c_str(), RTLD_LAZY);
        if (!handle) {
            throw Error("Failed to open library: " + std::string(dlerror()));
        }
        createFunc = (T *(*)()) dlsym(handle, "create");
        destroyFunc = (void (*)(T *)) dlsym(handle, "destroy");
        
        if (!createFunc || !destroyFunc) {
            dlclose(handle);
            throw Error("Failed to load symbols from library: " + std::string(dlerror()));
        }
        // cout << "azertyu\n";
    }

    ~DLLoader() {
        if (handle) {
            dlclose(handle);
        }
    }

    T *getInstance() {
        return createFunc();
    }

    void destroyInstance(T *instance) {
        destroyFunc(instance);
    }
};

#endif
