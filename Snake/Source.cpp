#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Point {
public:
	int X;
	int Y;

	Point() {
		X = 0;
		Y = 0;
	}

	void is(int x, int y) {
		X = x;
		Y = y;
	}

	Point(int x, int y) {
		X = x;
		Y = y;
	}

	bool operator == (Point &P) {
		return X == P.X && Y == P.Y;
	}
};


class Snake {

	char **_base;
	const int _size;
	const int _speed;
	vector<Point> _body;
	bool _isLost;
	Point _seed;
	int _score;
	

	void generateSeed() {
		_score += 10;
		bool inBody = true;

		while (inBody) {
			inBody = false;
			_seed.is(rand() % _size, rand() % _size);
			for (unsigned int i = 0; i < _body.size(); i++)
				if (_body[i] == _seed)
					inBody = true;
		}
	}

	void draw() {

		Sleep(_speed * 100);
		system("CLS");
		char sqr = 219;
		cout << "                          S N A K E     Score: " << _score << "\n\n";

		char gray[] = { 0x1b, '[', '1', ';', '3', '10', 'm', 0 };
		char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };

		for (unsigned int i = 0; i < _body.size(); i++) {
			_base[_body[i].X][_body[i].Y] = 254;
		}

		_base[_seed.X][_seed.Y] = 254;

		cout << "               ";
		for (int i = 0; i < _size * 2 + 2; i++)
			cout << sqr;
		cout << endl;

		for (int i = 0; i < _size; i++)
		{
			cout << "               " << sqr;

			for (int j = 0; j < _size; j++)
				if (_seed.X == i && _seed.Y == j)
					cout << gray << _base[i][j] << " " << normal;
				else
					cout << _base[i][j] << " ";

			cout << sqr << endl;
		}

		cout << "               ";
		for (int i = 0; i < _size * 2 + 2; i++)
			cout << sqr;

	}

	Point Right() {
		Point pos;
		Point head = _body[0];

		if (head.Y + 1 == _size)
			pos.is(head.X, 0);
		else
			pos.is(head.X, head.Y + 1);

		return pos;
	}
	Point Left() {
		Point pos;
		Point head = _body[0];

		if (head.Y - 1 == -1)
			pos.is(head.X, _size - 1);
		else
			pos.is(head.X, head.Y - 1);

		return pos;
	}
	Point Up() {
		Point pos;
		Point head = _body[0];

		if (head.X - 1 == -1)
			pos.is(_size - 1, head.Y);
		else
			pos.is(head.X - 1, head.Y);

		return pos;
	}
	Point Down() {
		Point pos;
		Point head = _body[0];

		if (head.X + 1 == _size)
			pos.is(0, head.Y);
		else
			pos.is(head.X + 1, head.Y);

		return pos;
	}

	void move(char &ch) {

		Point pos;

		if (ch == 'd')
			pos = Right();
		if (ch == 'a')
			pos = Left();
		if (ch == 'w')
			pos = Up();
		if (ch == 's')
			pos = Down();

		if (pos == _body[1]) {
			switch (ch) {
			case 'a': {
				ch = 'd';
				break;
			}
			case 'd': {
				ch = 'a';
				break;
			}
			case 'w': {
				ch = 's';
				break;
			}
			case 's': {
				ch = 'w';
				break;
			}
			}
			return;
		}

		for (unsigned int i = 0; i < _body.size(); i++)
			if (pos == _body[i]) {
				_isLost = true;
				return;
			}

		if (!(pos == _seed)) {
			Point tail = _body[_body.size() - 1];
			_base[tail.X][tail.Y] = ' ';
			_body.erase(_body.begin() + _body.size() - 1);
		}
		else
			generateSeed();

		_body.insert(_body.begin(), pos);

		draw();
	}

public:

	Snake(int size=15, int speed=1):_size(size) ,_speed(speed) {
		
		_body.push_back(Point(_size/2, _size/2));
		_body.push_back(Point(_size/2, _size/2-1));
		_body.push_back(Point(_size/2, _size/2-2));

		_score = -10;
		srand(time(NULL));
		generateSeed();

		_isLost = false;

		_base = new char*[_size];
		for (int i = 0; i < _size; i++)
		{
			_base[i] = new char[_size];
			for (int j = 0; j < _size; j++)
				_base[i][j] = ' ';
		}

		draw();

	}

	void start() {
		char ch = 'w';

		while (!_isLost) {
			if (_kbhit())
				ch = _getch();
			if (ch == 'w' || ch == 's' || ch == 'a' || ch == 'd')
				move(ch);
		}
	}

	~Snake() {
		for (int i = 0; i < _size; i++)
			delete[] _base[i];
		_base = NULL;
	}

};



int main() {
	Snake game;

	game.start();

	cout << endl<< endl;

	system("PAUSE");
	return 0;
}