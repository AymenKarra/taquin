#include"menu.h"
#include"button.h"
#include<string.h>
#include<chrono>
#include"OpenFileDialogBox.h"
#include<map>
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
string path="images/image.jpeg";
int moves_number;
SoundBuffer hover;
SoundBuffer click_buffer;
SoundBuffer slide_buffer;
Sound click;
Sound slide_sound;


Texture ui;
map<string, Button> buttons;

Texture background_texture;
Sprite background;
Texture logo_texture;
Sprite logo;

Music menu_music;
Music play_music;
Music victory_music;

Texture game_texture;
Sprite game_background;

ToggleButton sound_button;


void initialize_background() {
	background_texture.loadFromFile("images/background.jpg");
	background.setTexture(background_texture);
	background.setTextureRect(IntRect(background.getGlobalBounds().width / 2 - 240 -10, 0, 480, 720));
	logo_texture.loadFromFile("images/logo.png");
	logo.setTexture(logo_texture);
	logo.setScale(1.22, 1.22);
	logo.setPosition((480 - logo.getGlobalBounds().width) / 2, 220);
}


void initialize_buttons() {
	Sprite button_sprites[15];
	ui.loadFromFile("images/ui.png");
	for (int i = 0;i < 12;i++) {
		button_sprites[i].setTexture(ui);
		button_sprites[i].setTextureRect(IntRect(0, 109 * i, 334, 109));
	}
	button_sprites[12].setTexture(ui);button_sprites[12].setTextureRect(IntRect(0, 109 * 12, 83, 83));
	button_sprites[13].setTexture(ui);button_sprites[13].setTextureRect(IntRect(0, 109 * 12+83, 83, 83));
	button_sprites[14].setTexture(ui);button_sprites[14].setTextureRect(IntRect(83, 109 * 12 , 109, 109));
	buttons["play"]= Button(button_sprites[0], button_sprites[1],hover, 123, 415);
	buttons["play"].setScale(0.7);
	buttons["option"]= Button(button_sprites[2], button_sprites[3], hover, 123, 492);
	buttons["option"].setScale(0.7);
	buttons["quit"]= Button(button_sprites[4], button_sprites[5], hover, 123, 569);
	buttons["quit"].setScale(0.7);
	buttons["mode3"]= Button(button_sprites[6], button_sprites[7], hover, 73, 210);
	buttons["mode4"]= Button(button_sprites[8], button_sprites[9], hover, 73, 350);
	buttons["mode5"]= Button(button_sprites[10], button_sprites[11], hover, 73, 490);
	buttons["back"]= Button(button_sprites[12], button_sprites[13], hover, 385, 10);
	buttons["selected"]= Button(button_sprites[14], button_sprites[14], hover, 10, 10,100+13,100+16);
	sound_button=ToggleButton(button_sprites[0], button_sprites[1], hover, 10, 10);
	sound_button.setScale(0.25);
	buttons["browse"] = Button(button_sprites[0], button_sprites[1], hover, 230, 205);
	buttons["browse"].setScale(0.25);
}

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

		t.loadFromFile(path);
		Sprite photo;
		photo.setTexture(t);
		int l = min(photo.getGlobalBounds().width, photo.getGlobalBounds().height);
		float scale = 480.0 / l;

		photo.setTextureRect(IntRect(0, 0, l, l));

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

void display_ui(RenderWindow& app) {
	app.draw(game_background);
	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	Font font;
	font.loadFromFile("fonts/Thanks Autumn.ttf");
	Text score,moves;
	score.setFont(font);
	moves.setFont(font);
	score.setFillColor(Color::Red);
	moves.setFillColor(Color::Red);
	score.setString(to_string(elapsed_seconds) + " seconds");
	moves.setString("moves: "+ to_string(moves_number));
	score.setPosition(175, 100);
	moves.setPosition(175, 150);
	app.draw(score);
	app.draw(moves);
	buttons["back"].display(app);
	sound_button.setPosition(10, 10);sound_button.display(app);
	////////////////////bléda////////////////////////
			                                       //
	font.loadFromFile("fonts/regular_cozy.otf");   //
	Text version;                                  //
	version.setFont(font);                         //
	version.setString("ALPHA BUILD 0.1.1.07");     //
	version.setPosition(330, 2);                   //
	version.setCharacterSize(15);                  //
	version.setFillColor(sf::Color::Red);          //
	app.draw(version);                             //
	/////////////////////////////////////////////////

}

void sliding_animation(RenderWindow& app, int x,int y, int w,int n) {
	
	float velocity = 15;
		cout << "animation\n";
		pair<int, int> zero_pos = game->zero_position();
		
		
		if (y > zero_pos.second) {
			for (int i = 0;i < w;i += velocity) {
				app.clear(Color::White);
				display_ui(app);
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
				display_ui(app);
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
				display_ui(app);
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
				display_ui(app);
				for (int j = zero_pos.first - 1; j >= x; j--) {
					int num = game->getItem(j, zero_pos.second);
					sprite[num].move(0, velocity * (1));
				}
				for (int u = 1; u < n * n; u++) app.draw(sprite[u]);
				app.display();
			}
		}
}



void display_mainMenu(RenderWindow& app, Event& e) {
	
	play_music.stop();
	victory_music.stop();
	if(! menu_music.getStatus())menu_music.play();
	app.clear();

	app.draw(background);
	app.draw(logo);
	
	buttons["play"].display(app);
	buttons["option"].display(app);
	buttons["quit"].display(app);



	
	while (app.pollEvent(e)) {
		if (e.type == Event::Closed)
			app.close();
		if (e.type == Event::MouseButtonPressed) {
			if (e.key.code == Mouse::Left) {
				Vector2i pos = Mouse::getPosition(app);
				if (buttons["play"].inboundaries(pos)) {
					mainMenu.switch_play_state();
					click.play();
				}
				if (buttons["option"].inboundaries(pos)) {
					mainMenu.switch_options_state();
					click.play();
				}
				if (buttons["quit"].inboundaries(pos)) {
					click.play();
					app.close();
				}
			}
		}
	}
	
}
void display_playMenu(RenderWindow& app , Event& e) {
	
	app.clear();
	app.draw(background);
	
	buttons["back"].display(app);
	buttons["mode3"].display(app);
	buttons["mode4"].display(app);
	buttons["mode5"].display(app);

	
	while (app.pollEvent(e)) {
		if (e.type == Event::Closed)
			app.close();
		if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Left) {
				Vector2i pos = Mouse::getPosition(app);
				
				if (buttons["mode3"].inboundaries(pos)) {
					mainMenu.play_state = false;
					playMenu.select_level(3);
					click.play();
					menu_music.stop();
					play_music.play();
				}
				if (buttons["mode4"].inboundaries(pos)) {
					mainMenu.play_state = false;
					playMenu.select_level(4);
					click.play();
					menu_music.stop();
					play_music.play();
				}
				if (buttons["mode5"].inboundaries(pos)) {
					mainMenu.play_state = false;
					playMenu.select_level(5);
					click.play();
					menu_music.stop();
					play_music.play();
				}
				if (buttons["back"].inboundaries(pos)) {
					mainMenu.switch_play_state();
					click.play();

				}
			}
	}
	
}
void display_optionsMenu(RenderWindow& app, Event& e) {
	Texture num_texture,photo_texture;
	num_texture.loadFromFile("images/numbers_button.jpg");
	photo_texture.loadFromFile(path);
	Sprite num_button,photo_button;
	num_button.setTexture(num_texture);
	photo_button.setTexture(photo_texture);
	Button numbers(num_button, num_button, hover, 100, 100, 100, 100), photo(photo_button, photo_button, hover, 220, 100, 100, 100);

	app.clear();
	numbers.display(app);
	photo.display(app);
	if (optionsMenu.get_number_mode()) {
		buttons["selected"].setPosition(100-7, 100-8);
		buttons["selected"].display(app);
	}
	if (optionsMenu.get_picture_mode()) {
		buttons["selected"].setPosition(220-7, 100-8);
		buttons["selected"].display(app);
	}
	
	
	buttons["back"].display(app);
	sound_button.setPosition(10,300);sound_button.display(app);

	buttons["browse"].display(app);
	
	while (app.pollEvent(e)) {
		if (e.type == Event::Closed)
			app.close();
		if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Left) {
				Vector2i pos = Mouse::getPosition(app);
				if (numbers.inboundaries(pos)) {
					optionsMenu.set_numbers_mode();
				}
				if (photo.inboundaries(pos)) {
					optionsMenu.set_picture_mode();

				}
				if (buttons["browse"].inboundaries(pos)) {
					string str = open_file();
					if (str.length() > 0) path = str;
				}
				if (buttons["back"].inboundaries(pos)) {
					mainMenu.switch_options_state();
				}

				if (sound_button.inboundaries(pos)) {
					sound_button.switchState();
					if (sound_button.getState()) {
						play_music.setVolume(100);
						menu_music.setVolume(20);
						victory_music.setVolume(50);
					}
					else {
						play_music.setVolume(0);
						menu_music.setVolume(0);
						victory_music.setVolume(0);
					}
				}
			}
	}


}
void runGame(RenderWindow& app ,int n , Event& e) {
	
	int w = 480 / n;
	if (!created) {
		game = new GameMaster(n);
		fillTable(n,path);
		created = true;
		start = std::chrono::system_clock::now();
		moves_number = 0;
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
					if (game->CheckMove(y, x)) {
						moves_number++;
						slide_sound.play();
						sliding_animation(app,y,x,w,n);
						game->move(y, x);
					}
				}
				if (buttons["back"].inboundaries(pos)) {
					click.play();
					created = false;
					mainMenu.play_state = true;
					playMenu.reset();
					play_music.stop();
					menu_music.play();
				}
				if (sound_button.inboundaries(pos)) {
					sound_button.switchState();
					if (sound_button.getState()) {
						play_music.setVolume(100);
						menu_music.setVolume(20);
						victory_music.setVolume(50);
					}
					else {
						play_music.setVolume(0);
						menu_music.setVolume(0);
						victory_music.setVolume(0);
					}
				}
			}
	}
	app.clear(Color::White);

	display_ui(app);
	buttons["back"].display(app);
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
		play_music.stop();
		victory_music.play();
	}
	
}
void display_over_menu(RenderWindow& app,Event& e) {
	Font font;
	font.loadFromFile("fonts/Thanks Autumn.ttf");
	Text over,again,score,moves ;
	over.setFont(font);
	again.setFont(font);
	score.setFont(font);
	moves.setFont(font);
	over.setString("Game Over");
	again.setString("Play Again");
	moves.setString("Moves: " + to_string(moves_number));
	score.setString("Time: " + to_string(elapsed_seconds));
	over.setPosition(10, 350);
	again.setPosition(10, 400);
	score.setPosition(175, 100);
	moves.setPosition(175, 150);
	Sprite photo;
	photo.setTexture(t);
	photo.move(0, 240);
	int l = min(photo.getGlobalBounds().width, photo.getGlobalBounds().height);
	float scale = 480.0 / l;
	photo.setTextureRect(IntRect(0, 0, l, l));
	photo.setScale(scale, scale);



	app.clear();
	if(optionsMenu.get_picture_mode())app.draw(photo);
	app.draw(over);
	app.draw(again);
	app.draw(score);
	app.draw(moves);
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
	if (mainMenu.get_options_state()) {
		display_optionsMenu(app, e);
	}
	////////////////////bléda////////////////////////
	Font font;                                     //
	font.loadFromFile("fonts/regular_cozy.otf");   //
	Text version;                                  //
	version.setFont(font);                         //
	version.setString("ALPHA BUILD 0.1.1.07");     //
	version.setPosition(330, 2);                   //
	version.setCharacterSize(15);                  //
	version.setFillColor(sf::Color::Red);          //
	app.draw(version);                             //
	///////////////////////////////////////////////// 
}
