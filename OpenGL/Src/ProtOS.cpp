#include <iostream>
#include "Application.hpp"

int main()
{
    Application* app = new Application(1280, 320,"ProtOS");
    app->start();
}
