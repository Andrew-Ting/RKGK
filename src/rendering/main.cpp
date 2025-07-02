#include <vector>
#include <volk.h>
#include <SDL3/SDL.h>

#include "vk_engine.h"

int main()
{
	VulkanEngine renderEngine;

	bool bQuitEngine = false;

	// engine loop
	while (!bQuitEngine)
	{
		std::vector<SDL_Event> sdlEvents;
		SDL_Event sdlEvent;
		// Gather SDL events on queue
		while (SDL_PollEvent(&sdlEvent) != 0)
		{
			if (sdlEvent.type == SDL_EVENT_QUIT)
				bQuitEngine = true;
			sdlEvents.push_back(sdlEvent);
		}
		renderEngine.renderFrame(sdlEvents);
	}

}
