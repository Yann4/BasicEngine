struct Point
{
	float x, y;
	Point():x(0), y(0){};
	Point(float x, float y): x(x), y(y){};
};

enum Shape
{
	RECTANGLE, CIRCLE, TRIANGLE, OTHER, UNDEFINED
};

class GameObject
{
	private:
		Point position;
		Shape shape;
		Point size;
		
	public:
		GameObject();
		GameObject(Shape shape, Point pos, float width, float height);
		void Update();
		void Draw();
};
