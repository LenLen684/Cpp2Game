#include "EventSystem.h"

namespace nc {
	void nc::EventSystem::Startup()
	{

	}
	void nc::EventSystem::Shutdown()
	{

	}
	void nc::EventSystem::Update(float dt)
	{

	}
	void EventSystem::Subscribe(const std::string& name, function_t func)
	{
		Observer obs;
		obs.function = func;

		observers[name].push_back(obs);
	}
	void EventSystem::Notify(const Event& e)
	{
		for (auto& obs : observers[e.name]) {
			obs.function(e);
		}
	}
}