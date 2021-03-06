#include"GameManager.h"
#include"menu.h"
#include"animations.h"
#include<string.h>
#include<chrono>
#include"OpenFileDialogBox.h"
#include<map>
using namespace std;
using namespace sf;

state_manager StateManager;
play_menu playMenu;
options_menu optionsMenu;
game_over_menu gameOver;

Sprite sprite[26];
Texture t;
GameMaster* game;
bool created = false;
chrono::time_point<std::chrono::system_clock> start;
int elapsed_seconds;
string path="images/image.jpeg",custom_path= "images/image.jpeg";
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
Texture game_texture;
Sprite game_background;
Texture option_texture;
Sprite option_background;
Texture victory_texture;
Sprite victory_background;

Music menu_music;
Music play_music;
Music victory_music;

ToggleButton sound_button;



Font font;
Font winner_font;

void initialize_font() {
	font.loadFromFile("fonts/Thanks Autumn.ttf");
	winner_font.loadFromFile("fonts/SF Distant Galaxy.ttf");
}




void initialize_background() {
	background_texture.loadFromFile("images/background.jpg");
	background.setTexture(background_texture);
	background.setTextureRect(IntRect(background.getGlobalBounds().width / 2 - 240 -10, 0, 480, 720));
	logo_texture.loadFromFile("images/logo.png");
	logo.setTexture(logo_texture);
	logo.setScale(1.22, 1.22);
	logo.setPosition((480 - logo.getGlobalBounds().width) / 2, 220);

	game_texture.loadFromFile("images/game background.png");
	game_background.setTexture(game_texture);

	option_texture.loadFromFile("images/option background.png");
	option_background.setTexture(option_texture);
	option_background.setTextureRect(IntRect(option_background.getGlobalBounds().width / 2 - 240 , 0, 480, 720));

	victory_texture.loadFromFile("images/over background.png");
	victory_background.setTexture(victory_texture);
	victory_background.setScale(0.5, 0.5);
}
void initialize_sounds() {
	hover.loadFromFile("sounds/hover.ogg");
	click_buffer.loadFromFile("sounds/click.ogg");
	click.setBuffer(click_buffer);
	menu_music.openFromFile("sounds/main music.ogg");
	menu_music.setVolume(20);
	menu_music.setLoop(true);
	play_music.openFromFile("sounds/play music.ogg");
	play_music.setLoop(true);
	victory_music.openFromFile("sounds/victory.ogg");
	victory_music.setVolume(50);
	victory_music.setLoop(true);
	slide_buffer.loadFromFile("sounds/slide click.ogg");
	slide_sound.setBuffer(slide_buffer);
	
}

void initialize_buttons() {
	Sprite button_sprites[30];
	ui.loadFromFile("images/ui.png");
	for (int i = 0;i < 12;i++) {
		button_sprites[i].setTexture(ui);
		button_sprites[i].setTextureRect(IntRect(0, 109 * i, 334, 109));
	}
	for (int i = 12;i <= 17;i++) {
		int j = i - 12;
		button_sprites[i].setTexture(ui);button_sprites[i].setTextureRect(IntRect(0, 1308 + 83*j, 83, 83));
	}
	button_sprites[18].setTexture(ui);button_sprites[18].setTextureRect(IntRect(0, 1806, 174, 55));
	button_sprites[19].setTexture(ui);button_sprites[19].setTextureRect(IntRect(0, 1861, 174, 55));
	button_sprites[20].setTexture(ui);button_sprites[20].setTextureRect(IntRect(0, 1916, 334, 51));
	button_sprites[21].setTexture(ui);button_sprites[21].setTextureRect(IntRect(0, 1967, 334, 51));
	button_sprites[22].setTexture(ui);button_sprites[22].setTextureRect(IntRect(84, 1308, 164, 164));
	buttons["play"]= Button(button_sprites[0], button_sprites[1], 123, 415);
	buttons["play"].setSound(hover);
	buttons["play"].setScale(0.7);
	buttons["option"]= Button(button_sprites[2], button_sprites[3], 123, 492);
	buttons["option"].setSound(hover);
	buttons["option"].setScale(0.7);
	buttons["quit"]= Button(button_sprites[4], button_sprites[5], 123, 569);
	buttons["quit"].setSound(hover);
	buttons["quit"].setScale(0.7);
	buttons["mode3"]= Button(button_sprites[6], button_sprites[7], 73, 210);
	buttons["mode3"].setSound(hover);
	buttons["mode4"]= Button(button_sprites[8], button_sprites[9], 73, 350);
	buttons["mode4"].setSound(hover);
	buttons["mode5"]= Button(button_sprites[10], button_sprites[11], 73, 490);
	buttons["mode5"].setSound(hover);
	buttons["back"]= Button(button_sprites[12], button_sprites[13], 385, 10);
	buttons["back"].setSound(hover);
	buttons["selected"]= Button(button_sprites[22], button_sprites[22], 10, 10,100+13,100+16);
	buttons["help"] = Button(button_sprites[14], button_sprites[15],  10, 10);
	sound_button=ToggleButton(button_sprites[16], button_sprites[17],  100, 10);
	buttons["browse"] = Button(button_sprites[18], button_sprites[19],  160, 600);
	buttons["browse"].setScale(0.95);
	buttons["again"]= Button(button_sprites[20], button_sprites[21], 240- button_sprites[21].getGlobalBounds().width/2 , 620);
	buttons["again"].setSound(hover);
	
}

void fillTable(int n)//fill the table with numbers or tiles of the photo
{
	int w = 480 / n;
	if (optionsMenu.get_number_mode()) {
		int w2 = 91;//the width of the original number sprite  
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

		photo.setTextureRect(IntRect(0, 0, l, l));//select a square of the photo

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
void display_version(RenderWindow& app ,String ver= "ALPHA BUILD 0.1.1.07") {
	Font version_font;		                                      
	version_font.loadFromFile("fonts/regular_cozy.otf");  
	Text version;                                 
	version.setFont(version_font);                        
	version.setString(ver);    
	version.setPosition(330, 2);                  
	version.setCharacterSize(15);                  
	version.setFillColor(sf::Color::Red);          
	app.draw(version);
}

void display_ui(RenderWindow& app)//display: score , number of moves , return button , sound on/off button , help button
{
	app.draw(game_background);
	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	Text score,moves;
	score.setFont(font);
	moves.setFont(font);
	score.setFillColor(Color::White);
	moves.setFillColor(Color::White);
	score.setString(to_string(elapsed_seconds) + " seconds");
	moves.setString("moves: "+ to_string(moves_number));
	score.setPosition(175, 100);
	moves.setPosition(175, 150);
	app.draw(score);
	app.draw(moves);
	buttons["back"].display(app);
	sound_button.setPosition(199, 10);sound_button.display(app);
	buttons["help"].display(app);
	display_version(app);

}

void sliding(RenderWindow& app, int x,int y, int w,int n)//the sliding animation
{
	
	float velocity = 15;

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
					StateManager.switch_play_state();
					click.play();
				}
				if (buttons["option"].inboundaries(pos)) {
					StateManager.switch_options_state();
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
					StateManager.switch_runnig_state();
					playMenu.select_level(3);
					click.play();
					menu_music.stop();
					play_music.play();
				}
				if (buttons["mode4"].inboundaries(pos)) {
					StateManager.switch_runnig_state();
					playMenu.select_level(4);
					click.play();
					menu_music.stop();
					play_music.play();
				}
				if (buttons["mode5"].inboundaries(pos)) {
					StateManager.switch_runnig_state();
					playMenu.select_level(5);
					click.play();
					menu_music.stop();
					play_music.play();
				}
				if (buttons["back"].inboundaries(pos)) {
					StateManager.switch_play_state();
					click.play();

				}
			}
	}
	
}
void display_optionsMenu(RenderWindow& app, Event& e) {
	Texture num_texture, photo_texture1, photo_texture2, photo_texture3, custom_texture;
	string path1= "images/image.jpeg", path2= "images/image2.jpeg", path3= "images/image3.jpeg";
	num_texture.loadFromFile("images/numbers_button.jpg");
	photo_texture1.loadFromFile(path1);
	photo_texture2.loadFromFile(path2);
	photo_texture3.loadFromFile(path3);
	custom_texture.loadFromFile(custom_path);
	Sprite num_button,photo1,photo2,photo3,custom_photo;
	num_button.setTexture(num_texture);
	photo1.setTexture(photo_texture1);
	photo2.setTexture(photo_texture2);
	photo3.setTexture(photo_texture3);
	custom_photo.setTexture(custom_texture);
	Button numbers(num_button, num_button, 120, 120, 100, 100); 
	Button photo_button1(photo1, photo1, 260, 120, 100, 100);
	Button photo_button2(photo2, photo2, 120, 260, 100, 100);
	Button photo_button3(photo3, photo3, 260, 260, 100, 100);
	Button custom_photo_button(custom_photo, custom_photo, 190,485, 100, 100);

	app.clear();
	app.draw(option_background);
	numbers.display(app);
	photo_button1.display(app);
	photo_button2.display(app);
	photo_button3.display(app);
	custom_photo_button.display(app);
	if (optionsMenu.get_number_mode()) {
		buttons["selected"].setPosition(120-7, 120-8);
		buttons["selected"].display(app);
	}
	if (optionsMenu.get_picture_mode()) {
		//buttons["selected"].setPosition(220 - 7, 100 - 8);
		buttons["selected"].display(app);
	}
	
	
	buttons["back"].display(app);
	sound_button.setPosition(10,10);sound_button.display(app);

	buttons["browse"].display(app);
	
	while (app.pollEvent(e)) {
		if (e.type == Event::Closed)
			app.close();
		if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Left) {
				Vector2i pos = Mouse::getPosition(app);
				if (numbers.inboundaries(pos)) {
					optionsMenu.set_numbers_mode();
					click.play();
				}
				if (photo_button1.inboundaries(pos)) {
					optionsMenu.set_picture_mode();
					path = path1;
					buttons["selected"].setPosition(260 - 7, 120 - 8);
					click.play();
				}
				if (photo_button2.inboundaries(pos)) {
					optionsMenu.set_picture_mode();
					path = path2;
					buttons["selected"].setPosition(120 - 7, 260 - 8);
					click.play();
				}
				if (photo_button3.inboundaries(pos)) {
					optionsMenu.set_picture_mode();
					path = path3;
					buttons["selected"].setPosition(260 - 7, 260 - 8);
					click.play();
				}
				if (custom_photo_button.inboundaries(pos)) {
					optionsMenu.set_picture_mode();
					path = custom_path;
					buttons["selected"].setPosition(190 - 7, 485 - 8);
					click.play();
				}

				if (buttons["browse"].inboundaries(pos)) {
					click.play();
					string str = open_file();
					if (str.length() > 0) {
						custom_path = str;
						path = custom_path;
					}
				}
				if (buttons["back"].inboundaries(pos)) {
					StateManager.switch_options_state();
					click.play();
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
		fillTable(n);
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
				if (pos.y > 240) {
					if (game->CheckMove(y, x)) {
						moves_number++;
						slide_sound.play();
						sliding(app,y,x,w,n);
						game->move(y, x);
						game->ResetClosedList();
					}
				}
				if (buttons["back"].inboundaries(pos)) {
					click.play();
					created = false;
					StateManager.switch_runnig_state();
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
				if (buttons["help"].inboundaries(pos)) {
					pair<int, int> next_move=game->BestNextMove();
					int x = next_move.first;
					int y = next_move.second;

					moves_number++;
					slide_sound.play();
					sliding(app, x, y, w, n);
					game->move(x, y);
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

		gameOver.switch_over_state();
		playMenu.reset();
		play_music.stop();
		victory_music.play();
	}
	
}
void display_over_menu(RenderWindow& app,Event& e) {

	
	Text win,score, moves;
	win.setFont(winner_font);
	score.setFont(font);
	moves.setFont(font);
	win.setString("YOU WIN");
	win.setCharacterSize(90);
	win.setFillColor(Color::Black);
	moves.setString("Moves: " + to_string(moves_number));
	moves.setFillColor(Color::Black);
	score.setString("Time: " + to_string(elapsed_seconds));
	score.setFillColor(Color::Black);
	win.setPosition(25, 230);
	score.setPosition(175, 90);
	moves.setPosition(175, 120);
	Sprite photo;
	photo.setTexture(t);
	photo.move(0, 240);
	int l = min(photo.getGlobalBounds().width, photo.getGlobalBounds().height);
	float scale = 480.0 / l;
	photo.setTextureRect(IntRect(0, 0, l, l));
	photo.setScale(scale, scale);



	app.clear();
	app.draw(victory_background);
	if(optionsMenu.get_picture_mode())app.draw(photo);
	app.draw(win);
	app.draw(score);
	app.draw(moves);
	buttons["again"].display(app);
	
	
	banana_animation(app);
	
	while (app.pollEvent(e)) {
		if (e.type == Event::Closed)
			app.close();
		if (e.type == Event::MouseButtonPressed) {
			if (e.key.code == Mouse::Left) {
				Vector2i pos = Mouse::getPosition(app);
				if (buttons["again"].inboundaries(pos)) {
					StateManager.switch_main_menu_state();
					gameOver.switch_over_state();
					created = false;
					click.play();
				}
			}
		}

	}

}

void display_currentState(RenderWindow& app , Event& e) //check which state is true and display it  
{
	if (StateManager.get_main_state()) {
		display_mainMenu(app,e);
	}
	
	if (StateManager.get_play_state()) {
		display_playMenu(app,e);
	}
	int n = playMenu.get_level();
	if (n) {
		runGame(app, n,e);
	}
	if (gameOver.get_over_state()) {
		display_over_menu(app,e);
	}
	if (StateManager.get_options_state()) {
		display_optionsMenu(app, e);
	}

}
