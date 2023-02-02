/*
** EPITECH PROJECT, 2019
** Test_1
** File description:
** main
*/

#include "src/Window/Window.hpp"

int main(void)
{
    try {
        window::Window test;
        test.setWindow();
        test.runWindow();
    } catch (Error const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
