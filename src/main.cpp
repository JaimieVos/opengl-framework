#include "core/engine.h"

#include "scenes/example.h"

#include <iostream>
#include <memory.h>

int main()
{
    std::shared_ptr<Scene> scene = std::make_shared<ExampleScene>();

    Engine::get().init("OpenGL Framework", 1000, 800, scene);
	
    return 0;
}