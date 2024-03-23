#pragma once
class Point {
public:
	Point();
	Point(int x, int y);
	int get_x() const;
	int get_y() const;
	void set_x(int x);
	void set_y(int y);
private:
	int x, y;
};