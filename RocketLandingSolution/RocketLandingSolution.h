#include <iostream>
using namespace std;


//Changable parameters:
const int LANDING_FIELD_LENGHT = 50;
const float CRUSH_SPEED = 5.0;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 500;
const float GRAVITY_ACCELERATION = 0.091;
const float AIR_RESISTANCE = 0.02;

struct Rocket
{
private:

	float x, y, fuel,
		velocityX, velocityY,
		sidePower, centralPower;

public:

	Rocket(float x_ = 0, float y_ = 0, float fuel_ = 70) :
		x(x_), y(y_), fuel(fuel_),
		velocityX(0), velocityY(0),
		sidePower(0), centralPower(0) {}

	//------- GETTERS -------//
	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
	}

	float getVelocityX()
	{
		return velocityX;
	}

	float getVelocityY()
	{
		return velocityY;
	}

	float getFuel()
	{
		return fuel;
	}

	float getSidePower()
	{
		return sidePower;
	}

	float getCentralPower()
	{
		return centralPower;
	}
	//------- ------- -------//

	//------- SETTERS -------//
	void setX(float coordinate)
	{
		x = coordinate;
	}

	void setY(float coordinate)
	{
		y = coordinate;
	}

	void setVelocityX(float velocity)
	{
		velocityX = velocity;
	}

	void setVelocityY(float velocity)
	{
		velocityY = velocity;
	}

	void setFuel(float fuel_)
	{
		fuel = fuel_;
	}

	void setSidePower(float power)
	{
		sidePower = power;
	}

	void setCentralPower(float power)
	{
		centralPower = power;
	}
	//------- ------- -------//

	void landingAlgorithm( int landingFieldSize, int landingFieldPosition, float gravity, float wind,
		int windowHeight, int windowWidth, float crushSpeed, float fuel );

};

void Rocket::landingAlgorithm( int landingFieldSize, int landingFieldPosition, float gravity, float wind,
	int windowHeight, int windowWidth, float crushSpeed, float fuel ) {

	float x = getX(), y = getY(), vX = getVelocityX(), vY = getVelocityY();

	cout << "_________________________________\n\n Approximate Time: " 
		<< (-1 * vY + sqrt(vY * vY + 2 * gravity * (windowHeight - y))) 
		<< "; vY: " << vY << "\n_________________________________\n\n";

	if (2 * gravity * (windowHeight - y) < 3 * vY * vY + 4 && vY > -2
		/*&& !(x > landingFieldPosition && x < landingFieldPosition + landingFieldSize)*/) {
		setCentralPower(-2 * gravity);
	}

	if ( (x < landingFieldPosition) && (vX * vX + vY * vY < CRUSH_SPEED*CRUSH_SPEED) ) {
		setSidePower(gravity);
	}
	else if ( (x > landingFieldPosition + landingFieldSize) && (vX * vX + vY * vY < CRUSH_SPEED*CRUSH_SPEED) ) {
		setSidePower(-gravity);
	} // RIGHT side:
	if ( (windowWidth - x) < (x && 2 * gravity * (windowWidth - x) < 3 * vX * vX + 4 && vX > -2) ) {
		setSidePower(-2 * gravity);
	} // LEFT side:
	if ( (windowWidth - x > x) && (2 * gravity * (x) < 3 * vX * vX + 4 && vX < 2) ) {
		setSidePower(2 * gravity);
	}
	/*if (x < landingFieldPosition) {
		setSidePower(gravity);
	}
	if (x > landingFieldPosition + landingFieldSize) {
		setSidePower(-gravity);
	}
	if (x > landingFieldPosition && x < landingFieldPosition + landingFieldSize) {

	}*/
}