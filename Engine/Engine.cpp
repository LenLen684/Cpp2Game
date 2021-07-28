#include "Engine.h"

namespace nc
{
	void Engine::Startup()
	{
		systems.push_back(std::make_unique<ParticleSystem>());
		systems.push_back(std::make_unique<AudioSystem>());
		systems.push_back(std::make_unique<EventSystem>());

		for ( auto& system :systems)
		{
			system->Startup();
		}
	}
	void Engine::Shutdown()
	{
		for (auto& system : systems)
		{
			system->Shutdown();
		}
	}
	
	void Engine::Update(float dt)
	{
		for (auto& system : systems)
		{
			system->Update(dt);
		}

	}

	void Engine::Draw(Core::Graphics& graphics)
	{
		for (auto& system : systems) {
			GraphicsSystem* gsystem = dynamic_cast<GraphicsSystem*>(system.get());
			if (gsystem) {
				gsystem->Draw(graphics);
			}
		}
	}
}