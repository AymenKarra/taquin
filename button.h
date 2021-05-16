#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;

class Button {
private:
	Sprite idle, hover;
	Sound sound;
	pair<int, int> position,dimension;
public:
	Button( Sprite idle, Sprite hover, /*SoundBuffer buffer,*/ int x, int y, int width=0, int height=0) {
		this->idle = idle;
		this->hover = hover;
		//sound.setBuffer(buffer);
		this->position.first = x; this->position.second = y;
		if (width == 0 && height == 0) {
			this->dimension.first = this->hover.getGlobalBounds().width;
			this->dimension.second = this->hover.getGlobalBounds().height;
		}
		else {
			this->dimension.first = width;
			this->dimension.second = height;
			float scale1 = width / this->idle.getGlobalBounds().width;
			float scale2 = height / this->idle.getGlobalBounds().height;
			this->idle.setScale(scale1, scale2);
			this->hover.setScale(scale1, scale2);
		}
		this->idle.setPosition(x, y);
		this->hover.setPosition(x, y);
	}
	bool inboundaries(Vector2i pos) {
		return((position.first <= pos.x && pos.x <= position.first + dimension.first) && (position.second <= pos.y && pos.y <= position.second + dimension.second));
	}
	void display(RenderWindow& app) {
		Vector2i pos = Mouse::getPosition(app);
		if (inboundaries(pos)) {
			app.draw(hover);
		}
		else {
			app.draw(idle);
		}
	}


	


};
