#include "pch.h"

#include "Maple/Core/Window.h"
#include "Maple/Core/Common.h"

int main(int argc, char** argv)
{
	MPL_LOGGER_INIT();

	Maple::WindowPtr window = Maple::OpenWindow(640, 480, "Hello, World!");
	window->SetResizeCallback([&](uint32_t sizeX, uint32_t sizeY)
	{
		MPL_LOG("Window resized! Size: ({0}, {1})", sizeX, sizeY);
	});

	while (!window->ShouldClose())
	{
		window->OnUpdate();
	}
}