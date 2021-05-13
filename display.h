#include"menu.h"
using namespace std;
using namespace sf;

main_menu mainMenu;
play_menu playMenu;
options_menu optionsMenu;

Sprite sprite[26];
Texture t;
GameMaster* game;
bool created = false;

void fillTable(int n) {
	int w = 480 / n;
	if (optionsMenu.get_number_mode()) {
		int w2 = 91;
		t.loadFromFile("images/numbers.png");
		float scale = 480.0 / (91 * n);
		for (int i = 0; i < n * n;i++) {
			sprite[i + 1].setTexture(t);
			sprite[i + 1].setTextureRect(IntRect(i * w2, 0, w2, w2));
			sprite[i + 1].setScale(scale, scale);
		}
	}
	//
	if (optionsMenu.get_picture_mode()) {
		string name = "image.jpg";
		t.loadFromFile("images/" + name);
		Sprite photo;
		photo.setTexture(t);
		int l = min(photo.getGlobalBounds().width, photo.getGlobalBounds().height);
		float scale = 480.0 / l;
		//float scale =0.5;
		photo.setTextureRect(IntRect(0, 0, l, l));
		//photo.setScale(scale, scale);
		float w2 = l / n;
		int c = 1;
		for (int i = 0;i < n;i++) {
			for (int j = 0;j < n; j++) {
				sprite[c] = photo;
				sprite[c].setTextureRect(IntRect(j * w2, i * w2, w2, w2));
				sprite[c].setScale(scale, scale);
				c++;
			}
		}
	}
}


void display_mainMenu(RenderWindow& app, Event& e) {
	Font font;
	font.loadFromFile("fonts/Thanks Autumn.ttf");
	Text play,options,quit;
	play.setFont(font);
	options.setFont(font);
	quit.setFont(font);
	play.setString("play");
	options.setString("options");
	quit.setString("quit");
	play.setPosition(10, 300);
	options.setPosition(10, 350);
	quit.setPosition(10, 400);
	app.clear();
	app.draw(play);
	app.draw(options);
	app.draw(quit);
	
	while (app.pollEvent(e)) {
		if (e.type == Event::Closed)
			app.close();
		if (e.type == Event::MouseButtonPressed) {
			if (e.key.code == Mouse::Left) {
				Vector2i pos = Mouse::getPosition(app);
				if (pos.y <= 320 && pos.y >= 280) {
					mainMenu.switch_play_state();
					
				}
			}
		}
	}
	
}
void display_playMenu(RenderWindow& app , Event& e) {
	Font font;
	font.loadFromFile("fonts/Thanks Autumn.ttf");
	Text play,options,quit;
	play.setFont(font);
	options.setFont(font);
	quit.setFont(font);
	play.setString("3*3");
	options.setString("4*4");
	quit.setString("5*5");
	play.setPosition(10, 300);
	options.setPosition(10, 350);
	quit.setPosition(10, 400);
	app.clear();
	app.draw(play);
	app.draw(options);
	app.draw(quit);
	
	while (app.pollEvent(e)) {
		if (e.type == Event::Closed)
			app.close();
		if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Left) {
				Vector2i pos = Mouse::getPosition(app);
				if (pos.y <= 320 && pos.y >= 280) {
					mainMenu.play_state=false;
					playMenu.select_level(3);
				}
				if (pos.y <= 370 && pos.y >= 330) {
					mainMenu.play_state = false;
					playMenu.select_level(4);
				}
				if (pos.y <= 420 && pos.y >= 380) {
					mainMenu.play_state = false;
					playMenu.select_level(5);
				}
			}
	}
	
}
void display_optionsMenu(RenderWindow& app) {
	
}
void runGame(RenderWindow& app ,int n , Event& e) {
	
		int w = 480 / n;
		if (!created) {
			game = new GameMaster(n);
			fillTable(n);
			created = true;
		}
	while (app.pollEvent(e))
	{
		if (e.type == Event::Closed)
			app.close();

		if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Left)
			{
				Vector2i pos = Mouse::getPosition(app);
				int x = pos.x / w;
				int y = (pos.y - 240) / w;
				cout << y << " " << x << "\n";
				if( pos.y>240 ) game->move(y, x);
			}
	}
	app.clear(Color::White);
	for (int i = 0;i < n;i++)
		for (int j = 0;j < n;j++)
		{
			int num = game->getItem(i, j);
			sprite[num].setPosition(j * w, 240 + i * w);
			app.draw(sprite[num]);
		}
	
}
void display_currentState(RenderWindow& app , Event& e) {
	if (mainMenu.get_main_state()) {
		display_mainMenu(app,e);
		cout << "main" << endl;
	}
	
	if (mainMenu.get_play_state()) {
		display_playMenu(app,e);
		cout << "play\n";
	}
	int n = playMenu.get_level();
	if (n) {
		runGame(app, n,e);
	}

	
}
