#include "core/engine.h"

#include "scenes/example.h"

#include <iostream>
#include <memory.h>

int main()
{
    Engine::get().init("OpenGL Framework", std::make_shared<ExampleScene>());
	
    return 0;
}