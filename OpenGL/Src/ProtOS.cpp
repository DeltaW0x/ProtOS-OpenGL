#include <iostream>
#include "Application.hpp"

int main()
{
    Application* app = new Application(1024, 256,"ProtOS");
    app->start();
}
