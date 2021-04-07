#include<SFML/Graphics.hpp>
#include<iostream>
#include"GameManager.h"

using namespace std;
using namespace sf;

int main() {
	cout << "enter the level you want to play, levels 3,4,5" << endl;
	int n;
	cin >> n;
	while (!(n == 3 || n == 4 || n == 5)) {
		cout << "invalid level, please enter again" << endl;
		cin >> n;
	}
	GameMaster game(n);
	RenderWindow app(VideoMode(91*n, 91*n), "TAQUIN");
	app.setFramerateLimit(10);
	Texture t;
	t.loadFromFile("images/numbers.png");
	int w = 91;
	Sprite sprite[25];
	for (int i = 0; i < n*n;i++) {
		sprite[i+1].setTexture(t);
		sprite[i+1].setTextureRect(IntRect(i*w, 0, w, w));
	}


	while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left)
                {
                    Vector2i pos = Mouse::getPosition(app);
                    int x = pos.x / w ;
                    int y = pos.y / w ;

					game.move(y, x);
                    
                }

        }
		app.clear(Color::White);
		for (int i = 0;i < n;i++)
			for (int j = 0;j < n;j++)
			{
				int num = game.getItem(i, j);
				sprite[num].setPosition(j * w, i * w);
				app.draw(sprite[num]);
			}

		app.display();
		if (game.GameOver()) {
			cout << "winner" << endl;
			app.close();
		}
	}
}