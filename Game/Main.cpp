#include "Game.h"
#include <variant>

nc::Transform transform{ {400, 300}, 0 , 3 };


const float speed = 300;
float timer = 0;
nc::ParticleSystem particleSystem;
nc::Vector2 psPosition;

float deltaTime;
float gameTime = 0;

//nc::Engine engine;
//nc::Scene scene;

Game game;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	//int x, y;
	//Core::Input::GetMousePos(x, y);
	//
	//psPosition.x = static_cast<float>(x);
	//psPosition.y = static_cast<float>(y);

	//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	//{
	//	std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::orange, nc::Color::yellow };
	//	engine.Get<nc::ParticleSystem>()->Create(psPosition, 150, 2, colors[nc::RandomRangeInt(0, colors.size())], 150);
	//}

	game.Update(dt);
	
	return quit;
}

void Init() {

}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

int inc(int i) { return ++i; }
int dec(int i) { return --i; }

//union Data
//{
//	int i;
//	char str[5];
//	bool b;
//};

int main()
{
	/*int (*operation)(int);
	operation = &dec;*/

	//Data data;
	//data.str[0] = 't';
	//data.i = 532;

	//std::cout << data.i << std::endl;
	//std::cout << data.b << std::endl;
	//std::cout << data.str << std::endl;

	//std::variant<int, std::string, float, bool> var;

	//system("pause");

	char name[] = "Game :D";
	Core::Init(name, 800, 600, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Init();
	
	game.Initialize();

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}