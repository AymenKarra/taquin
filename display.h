#include"menu.h"
#include"button.h"
#include<string.h>
#include<chrono>
#include"OpenFileDialogBox.h"
using namespace std;
using namespace sf;

main_menu mainMenu;
play_menu playMenu;
options_menu optionsMenu;
game_over_menu gameOver;

Sprite sprite[26];
Texture t;
GameMaster* game;
bool created = false;
chrono::time_point<std::chrono::system_clock> start;
int elapsed_seconds;
Button* back_game;
bool back_created=false;
Button* play;
bool play_created=false;
string path;


void fillTable(int n,string path="image.jpeg") {
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
		//string name = "image.jpeg";
		//t.loadFromFile("images/" + name);
		t.loadFromFile(path);
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
void sliding_animation(RenderWindow& app, int x,int y, int w,int n) {
	
	float velocity = 15;
	if (game->CheckMove(x, y)) {
		cout << "animation\n";
		pair<int, int> zero_pos = game->zero_position();
		
		
		if (y > zero_pos.second) {
			for (int i = 0;i < w;i += velocity) {
				app.clear(Color::White);
				for (int j = zero_pos.second + 1;j <= y;j++) {
					int num = game->getItem(zero_pos.first, j);
					sprite[num].move( velocity * (-1),0);
				}
				for (int u = 1;u < n * n;u++) app.draw(sprite[u]);
				app.display();
			}
		}
		if(y< zero_pos.second){
			for (int i = 0;i < w;i += velocity) {
				app.clear(Color::White);
				for (int j = zero_pos.second - 1;j >= y;j--) {
					int num = game->getItem(zero_pos.first, j);
					sprite[num].move(velocity * (1), 0);
				}
				for (int u = 1;u < n * n;u++) app.draw(sprite[u]);
				app.display();
			}
		}
		if (x > zero_pos.first) {
			for (int i = 0;i < w;i += velocity) {
				app.clear(Color::White);
				for (int j = zero_pos.first + 1;j <= x;j++) {
					int num = game->getItem(j, zero_pos.second);
					sprite[num].move(0, velocity * (-1));
				}
				for (int u = 1;u < n * n;u++) app.draw(sprite[u]);
				app.display();
			}
		}
		if(x < zero_pos.first){
			for (int i = 0;i < w;i += velocity) {
				app.clear(Color::White);
				for (int j = zero_pos.first - 1; j >= x; j--) {
					int num = game->getItem(j, zero_pos.second);
					sprite[num].move(0, velocity * (1));
				}
				for (int u = 1; u < n * n; u++) app.draw(sprite[u]);
				app.display();
			}
		}
	}
}


void display_mainMenu(RenderWindow& app, Event& e) {
	/*Font font;
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
	app.draw(quit);*/
	Texture ui;
	ui.loadFromFile("images/ui.jpg");
	Sprite play_idle, play_hover,option_idle,option_hover,quit_idle,quit_hover;
	play_idle.setTexture(ui);
	play_hover.setTexture(ui);
	option_idle.setTexture(ui);
	option_hover.setTexture(ui);
	quit_idle.setTexture(ui);
	quit_hover.setTexture(ui);
	play_idle.setTextureRect(IntRect(0, 0, 334, 108));
	play_hover.setTextureRect(IntRect(0, 108, 334, 108));
	option_idle.setTextureRect(IntRect(0, 108*2, 334, 108));
	option_hover.setTextureRect(IntRect(0, 108*3, 334, 108));
	quit_idle.setTextureRect(IntRect(0, 108*4, 334, 108));
	quit_hover.setTextureRect(IntRect(0, 108*5, 334, 108));
	if (!play_created) {
		play= new Button(play_idle, play_hover, 73, 200);play_created = true;
	}
	Button option(option_idle, option_hover, 73, 310);
	Button quit(quit_idle, quit_hover, 73, 420);
	app.clear();
	play->display(app);
	option.display(app);
	quit.display(app);



	
	while (app.pollEvent(e)) {
		if (e.type == Event::Closed)
			app.close();
		if (e.type == Event::MouseButtonPressed) {
			if (e.key.code == Mouse::Left) {
				Vector2i pos = Mouse::getPosition(app);
				if (play->inboundaries(pos)) {
					mainMenu.switch_play_state();
				}
				if (option.inboundaries(pos)) {
					optionsMenu.switch_picture_mode();
					path = open_file();
				}
				if (quit.inboundaries(pos)) {
					app.close();
				}
			}
		}
	}
	
}
void display_playMenu(RenderWindow& app , Event& e) {
	/*Font font;
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
	*/
	Texture ui2;
	ui2.loadFromFile("images/ui2.jpg");
	Sprite mode3_idle, mode3_hover, mode4_idle, mode4_hover, mode5_idle, mode5_hover;
	mode3_idle.setTexture(ui2);
	mode3_hover.setTexture(ui2);
	mode4_idle.setTexture(ui2);
	mode4_hover.setTexture(ui2);
	mode5_idle.setTexture(ui2);
	mode5_hover.setTexture(ui2);
	mode3_idle.setTextureRect(IntRect(0, 0, 334, 108));
	mode3_hover.setTextureRect(IntRect(0, 108, 334, 108));
	mode4_idle.setTextureRect(IntRect(0, 108 * 2, 334, 108));
	mode4_hover.setTextureRect(IntRect(0, 108 * 3, 334, 108));
	mode5_idle.setTextureRect(IntRect(0, 108 * 4, 334, 108));
	mode5_hover.setTextureRect(IntRect(0, 108 * 5, 334, 108));
	Button mode3(mode3_idle, mode3_hover, 73, 200);
	Button mode4(mode4_idle, mode4_hover, 73, 310);
	Button mode5(mode5_idle, mode5_hover, 73, 420);
	


	Texture t;
	t.loadFromFile("images/ui.jpg");
	Sprite back_idle;
	Sprite back_hover;
	back_idle.setTexture(t);
	back_hover.setTexture(t);
	back_idle.setTextureRect(IntRect(616, 0, 84, 84));
	back_hover.setTextureRect(IntRect(616, 84, 84, 84));
	Button back(back_idle, back_hover, 380, 10);
	
	app.clear();
	back.display(app);
	mode3.display(app);
	mode4.display(app);
	mode5.display(app);
	//app.draw(play);
	//app.draw(options);
	//app.draw(quit);
	
	while (app.pollEvent(e)) {
		if (e.type == Event::Closed)
			app.close();
		if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Left) {
				Vector2i pos = Mouse::getPosition(app);
				/*if (pos.y <= 330 && pos.y >= 300) {
					mainMenu.play_state=false;
					playMenu.select_level(3);
				}
				if (pos.y <= 380 && pos.y >= 350) {
					mainMenu.play_state = false;
					playMenu.select_level(4);
				}
				if (pos.y <= 430 && pos.y >= 400) {
					mainMenu.play_state = false;
					playMenu.select_level(5);
				}*/
				if (mode3.inboundaries(pos)) {
					mainMenu.play_state = false;
					playMenu.select_level(3);

				}
				if (mode4.inboundaries(pos)) {
					mainMenu.play_state = false;
					playMenu.select_level(4);

				}
				if (mode5.inboundaries(pos)) {
					mainMenu.play_state = false;
					playMenu.select_level(5);

				}
				if (back.inboundaries(pos)) {
					mainMenu.switch_play_state();
				}
			}
	}
	
}
void display_optionsMenu(RenderWindow& app, Event& e) {
	
}
void runGame(RenderWindow& app ,int n , Event& e) {
	
	int w = 480 / n;
	if (!created) {
		game = new GameMaster(n);
		fillTable(n,path);
		created = true;
		start = std::chrono::system_clock::now();
	}
	Texture t;
	t.loadFromFile("images/ui.jpg");
	Sprite back_idle;
	Sprite back_hover;
	back_idle.setTexture(t);
	back_hover.setTexture(t);
	back_idle.setTextureRect(IntRect(616, 0, 84, 84));
	back_hover.setTextureRect(IntRect(616, 84, 84, 84));
	if (!back_created) {
		back_game = new Button(back_idle, back_hover, 380, 10);
		back_created = true;
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
				if (pos.y > 240) {
					sliding_animation(app,y,x,w,n);
					game->move(y, x);
				}
				if (back_game->inboundaries(pos)) {
					created = false;
					mainMenu.play_state = true;
					playMenu.reset();
				}
			}
	}
	app.clear(Color::White);
	back_game->display(app);
	for (int i = 0;i < n;i++)
		for (int j = 0;j < n;j++)
		{
			int num = game->getItem(i, j);
			sprite[num].setPosition(j * w, 240 + i * w);
			app.draw(sprite[num]);
		}
	if (game->GameOver()) {
		std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
		elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
		cout << elapsed_seconds << endl;
		gameOver.switch_over_state();
		playMenu.reset();
	}
	
}
void display_over_menu(RenderWindow& app,Event& e) {
	Font font;
	font.loadFromFile("fonts/Thanks Autumn.ttf");
	Text over,again,score ;
	over.setFont(font);
	again.setFont(font);
	score.setFont(font);
	over.setString("Game Over");
	again.setString("Play Again");
	score.setString(to_string(elapsed_seconds)+" seconds");
	over.setPosition(10, 350);
	again.setPosition(10, 400);
	score.setPosition(175, 100);
	Sprite photo;
	photo.setTexture(t);
	photo.move(0, 240);
	int l = min(photo.getGlobalBounds().width, photo.getGlobalBounds().height);
	float scale = 480.0 / l;
	photo.setTextureRect(IntRect(0, 0, l, l));
	photo.setScale(scale, scale);



	app.clear();
	app.draw(photo);
	app.draw(over);
	app.draw(again);
	app.draw(score);
	while (app.pollEvent(e)) {
		if (e.type == Event::Closed)
			app.close();
		if (e.type == Event::MouseButtonPressed) {
			if (e.key.code == Mouse::Left) {
				Vector2i pos = Mouse::getPosition(app);
				if (pos.y <= 450 && pos.y >= 400) {
					mainMenu.switch_main_menu_state();
					gameOver.switch_over_state();
					created = false;
				}
			}
		}
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
	if (gameOver.get_over_state()) {
		display_over_menu(app,e);
	}
	/*if (mainMenu.get_options_state()) {
		display_optionsMenu(app, e);
	}*/

	
}
