#pragma once
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

// Texture exceptions

class TextureNotFoundException : public std::exception {
    public:
        explicit TextureNotFoundException(const std::string& msg) : message(msg) {};

        const char* what() const noexcept override {
            return message.c_str();
        }
    
    private:
        std::string message;
};

class TextureFileNotFoundException : public std::exception {
    public:
        explicit TextureFileNotFoundException(const std::string& msg) : message(msg) {};

        const char* what() const noexcept override {
            return message.c_str();
        }
    
    private:
        std::string message;
};

class TextureException : public std::exception {
    public:
        explicit TextureException(const std::string& msg) : message(msg) {};

        const char* what() const noexcept override {
            return message.c_str();
        }
    
    private:
        std::string message;
};

#endif // EXCEPTIONS_HPP