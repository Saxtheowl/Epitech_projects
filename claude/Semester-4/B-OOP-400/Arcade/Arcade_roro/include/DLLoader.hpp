/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Dynamic library loader encapsulation
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <string>
#include <memory>
#include <dlfcn.h>

namespace arcade {
    template<typename T>
    class DLLoader {
    private:
        void *_handle;
        std::string _path;
        T *_instance;
        
        // Function pointers
        T *(*_createFunc)();
        void (*_destroyFunc)(T*);

    public:
        DLLoader() : _handle(nullptr), _instance(nullptr), 
                     _createFunc(nullptr), _destroyFunc(nullptr) {}
        
        ~DLLoader() {
            unload();
        }

        // No copy/assignment
        DLLoader(const DLLoader&) = delete;
        DLLoader& operator=(const DLLoader&) = delete;

        // Move semantics
        DLLoader(DLLoader &&other) noexcept 
            : _handle(other._handle), _path(std::move(other._path)),
              _instance(other._instance), _createFunc(other._createFunc),
              _destroyFunc(other._destroyFunc) {
            other._handle = nullptr;
            other._instance = nullptr;
            other._createFunc = nullptr;
            other._destroyFunc = nullptr;
        }

        DLLoader& operator=(DLLoader &&other) noexcept {
            if (this != &other) {
                unload();
                _handle = other._handle;
                _path = std::move(other._path);
                _instance = other._instance;
                _createFunc = other._createFunc;
                _destroyFunc = other._destroyFunc;
                
                other._handle = nullptr;
                other._instance = nullptr;
                other._createFunc = nullptr;
                other._destroyFunc = nullptr;
            }
            return *this;
        }

        bool load(const std::string &libraryPath) {
            unload(); // Clean up any existing load
            
            _path = libraryPath;
            _handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
            
            if (!_handle) {
                return false;
            }

            // Clear any existing errors
            dlerror();

            // Load create function
            _createFunc = (T*(*)())dlsym(_handle, getCreateSymbolName().c_str());
            if (!_createFunc) {
                dlclose(_handle);
                _handle = nullptr;
                return false;
            }

            // Load destroy function  
            _destroyFunc = (void(*)(T*))dlsym(_handle, getDestroySymbolName().c_str());
            if (!_destroyFunc) {
                dlclose(_handle);
                _handle = nullptr;
                _createFunc = nullptr;
                return false;
            }

            return true;
        }

        void unload() {
            if (_instance && _destroyFunc) {
                _destroyFunc(_instance);
                _instance = nullptr;
            }
            
            if (_handle) {
                dlclose(_handle);
                _handle = nullptr;
            }
            
            _createFunc = nullptr;
            _destroyFunc = nullptr;
        }

        T* getInstance() {
            if (!_instance && _createFunc) {
                _instance = _createFunc();
            }
            return _instance;
        }

        bool isLoaded() const {
            return _handle != nullptr && _createFunc != nullptr;
        }

        const std::string& getPath() const {
            return _path;
        }

        std::string getLastError() const {
            const char *error = dlerror();
            return error ? std::string(error) : std::string();
        }

    private:
        std::string getCreateSymbolName() const;
        std::string getDestroySymbolName() const;
    };
}

#endif /* !DLLOADER_HPP_ */