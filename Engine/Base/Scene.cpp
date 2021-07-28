#include "Scene.h"
#include "Actor.h"
//#include <algorithm>

namespace nc
{
	void Scene::Update(float dt)
	{
		//add new actors
		actors.insert(actors.end(), std::make_move_iterator(shrek.begin()), std::make_move_iterator(shrek.end()));
		shrek.clear();

		// update actors
		//std::for_each(actors.begin(), actors.end(), [dt](auto& element) mutable 
		//{
		//	element->Update(dt);
		//});

		for (auto& actor : actors) {
			actor->Update(dt);
		}

		// check collisions
		for (size_t i = 0; i < actors.size(); i++)
		{
			for (size_t j = i + 1; j < actors.size(); j++)
			{
				if (actors[i]->destroy || actors[j]->destroy) continue;
				nc::Vector2 dir = actors[i]->transform.position - actors[j]->transform.position;
				float distance = dir.Length();
				//if (distance < actors[i]->GetRadius() + actors[j]->GetRadius()) {
				if (distance < 30) {
					actors[i]->OnCollision(actors[j].get());
					actors[j]->OnCollision(actors[i].get());
				}
			}
		}

	
		// destroy actors
		auto iter = actors.begin();
		while (iter != actors.end())
		{
			if ((*iter)->destroy) {
				iter = actors.erase(iter);
			}
			else 
			{
				iter++;
			}
		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		for (auto& actor : actors) {
			actor->Draw(graphics);
		}
	}
	
	void Scene::AddActor(std::unique_ptr<nc::Actor> actor)
	{
		//std::cout << actor->tag << std::endl;
		actor->scene = this;
		shrek.push_back(std::move(actor));
	}

	void Scene::RemoveActor(Actor* actor)
	{
		
	}
	
	void Scene::RemoveAllActors()
	{
		actors.clear();
	}
}