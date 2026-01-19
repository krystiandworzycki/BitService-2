#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP

/**
 * @file Logger.hpp
 * @brief Wątkowo-bezpieczne narzędzie do logowania z obsługą informacji o lokalizacji w kodzie źródłowym.
 * 
 * Plik definiuje klasę Logger, która udostępnia statyczny interfejs do zapisywania komunikatów
 * logów wraz z informacją o miejscu wywołania (przykład):
 * 
 *  file: /home/folder/main.cpp(48:11) `int main()`: Tresc informacji.
 * 
 * W zależności od używanego standardu języka C++, wykorzystywany jest
 * std::source_location (C++20) lub std::experimental::source_location.
 */

#if __cplusplus >= 202002L
#include <source_location>
using std::source_location;
#else
#include <experimental/source_location>
using std::experimental::source_location;
#endif

#include <fstream>
#include <mutex>

/**
 * @class Logger
 * @brief Udostępnia statyczny, wątkowo-bezpieczny interfejs logowania.
 * 
 * Klasa Logger jest klasą narzędziową (utility class), przeznaczoną
 * do centralizacji mechanizmu logowania w całej aplikacji.
 * 
 * Dostęp do mechanizmu logowania jest synchronizowany przy użyciu
 * std::mutex, który zapobiega przeplataniu się wpisów logów w środowisku wielowątkowym.
 */
class Logger final {
    public:
        /**
         * @brief Zapisuje komunikat do logu
         * 
         * Funkcja zapisuje podany komunikat tekstowy wraz z informacją o lokalizacji
         * w kodzie źródłowym, w której została wywołana.
         * 
         * Parametr lokalizacji domyślnie przyjmuje wartość source_location::current(), dzięki czemu
         * wywołujący nie musi przekazywać go jawnie.
         * 
         * @param msg Łańcuch znaków (W stylu języku C) zawierający treść komunikatu logu.
         * @param loc Informacja o lokalizacji wywołania (plik, linia, funkcja). Zazwyczaj
         *            parametr ten nie powinien być przekazywany ręcznie.
         * 
         * @note Funkcja oznaczona jest jako noexcept i nie może zgłaszać wyjątków.
         * 
         * @thread_safety Funkcja jest bezpieczna w użyciu w środowisku wielowątkowym.
         */
        static void log(
            const char* msg, 
            const source_location loc = source_location::current()
        ) noexcept;
    
    private:
        /**
         * @brief Mutex chroniący operację logowania.
         * 
         * Zapewnia bezpieczny dostęp do wyjścia logów, uniemożliwiając
         * jednoczesny zapis z wielu wątków.
         */
        static std::mutex s_log_mutex;
        static std::ofstream s_log_file;
};

#endif // LOGGER_HPP