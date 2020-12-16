#include <iostream>
using namespace std;

//Changable parameters:
const float FUEL = 50.0;
const float CRUSH_SPEED = 5.0;
const float ROCKET_INITIAL_X = 500.0;
const float ROCKET_INITIAL_Y = 0.0;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 500;
const int LANDING_FIELD_LENGHT = 50;
const float GRAVITY_ACCELERATION = 0.091;
const float AIR_RESISTANCE = 0.02;

struct Rocket
{
private:

	float x, y, fuel,
		velocityX, velocityY,
		sidePower, centralPower;

public:

	Rocket(float x_ = ROCKET_INITIAL_X, float y_ = ROCKET_INITIAL_Y, float fuel_ = FUEL) :
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

	// FOR ALGORITHM 1:
	float x = getX(), y = getY(), vX = getVelocityX(), vY = getVelocityY();
	float speed = sqrt(vX * vX + vY * vY);

	float h = windowHeight - y - 30;
	float rToBoard = vX > 0 ? WINDOW_WIDTH - x - 10 : -x + 10;
	int directionX = vX > 0 ? 1 : -1;
	float sLF = x > landingFieldPosition ? -x + landingFieldPosition + landingFieldSize : landingFieldPosition - x;


	float tToBroadWithoutP = (-directionX * vX + sqrt(vX * vX + 2 * (abs(wind) * directionX * rToBoard))) / abs(wind);
	float tOfFallWithoutP = (-vY + sqrt(vY * vY + 2 * gravity * h)) / gravity;
	float tToBroadWithP = -1;
	float tOfFallWithP = -1;

	if (landingFieldPosition + landingFieldSize > x && x > landingFieldPosition) {
		sLF = 0;
	}
	else if (x > landingFieldPosition) {
		sLF = landingFieldPosition + landingFieldSize - x;
	}
	else if (x < landingFieldPosition) {
		sLF = landingFieldPosition - x;
	}

	// FOR ALGORITHM 2 AND 3: 
	//float x = getX(), y = getY(), vX = getVelocityX(), vY = getVelocityY();
	//float potTimeOfFall = (-vY + sqrt(vY * vY + 2 * gravity * (windowHeight - y)) / gravity);

	//cout << "_________________________________\n\n Approximate Landing Time: " 
	//	<< (-1 * vY + sqrt(vY * vY + 2 * gravity * (windowHeight - y))) - 1.5
	//	<< /*"; vY: " << vY <<*/ "\n_________________________________\n\n";

	if (getFuel() > 0)
	{
		if (speed < (1 - 2 * gravity) * crushSpeed && sLF != 0) {
			setSidePower((gravity)*sLF / abs(sLF));
		}
		else if (speed > (1 - 2 * gravity) * crushSpeed && vY < 3) {
			setSidePower(gravity * (-directionX));
		}
		else if (sLF == 0 && abs(vX) > 0.1) {
			setSidePower(gravity * (-directionX));
		}

		//float tOfCrushX = -1
		//if(vX*vX - 2* (0.9*(gravity ))

		//cout << "\n\n\n" << vX * vX - 2 * (0.9 * (gravity - abs(wind)) * directionX * rToBoard) << "\n\n\n";

		if (vX * vX - 2 * (0.9 * (gravity - abs(wind)) * directionX * rToBoard) > 0) {
			tToBroadWithP = abs((-vX + sqrt(vX * vX - 2 * (0.9 * (gravity - abs(wind)) * directionX * rToBoard))) / abs(wind));
		}
		if (tToBroadWithP > 0) {
			setSidePower(-directionX * (2 * gravity + abs(wind)));
		}


		if (vY * vY - 2 * (0.9 * gravity) * h > 0) {
			tOfFallWithP = abs((-vY + sqrt(vY * vY - 2 * (0.9 * gravity) * h)) / gravity);
		}
		if (tOfFallWithP > 0 && vY > -1) {
			setCentralPower(-2 * gravity);
		}
	}
	else
	{
		cout << "\n OUT OF FUEL! \n";
	}

	cout << "\n Height: " << h << "\n Distance to Board in present way: " << rToBoard
		<< "\n S to LF: " << sLF << "\n Time of Fall: " << tOfFallWithoutP
		<< "\n Time to Board in present direction with P: " << tToBroadWithoutP
		<< "; without P: " << tOfFallWithP << "\n Time of Stop: "
		<< "\n Central Power: " << getCentralPower() << "\n Speed: " << speed << endl << endl;

		// ---------- ALGORITHM 2 WE KNOW: H = Vt + (gt^2)/2, THEN 2V^3 > 2gH ---------- //
		// ----------------------------- IRRATIONAL ROUTE ---------------------------- //
		/*if (2 * gravity * (windowHeight - y) < 3 * vY * vY + 4 && vY > -2) 
		{
			setCentralPower(-2 * gravity);
		}

		if (x < landingFieldPosition && vX * vX + vY * vY < CRUSH_SPEED * CRUSH_SPEED) 
		{
			setSidePower(gravity);
		}
		else if ((x > landingFieldPosition + landingFieldSize) && (vX * vX + vY * vY < CRUSH_SPEED * CRUSH_SPEED)) 
		{
			setSidePower(-gravity);
		} 

		// OPTIMIZING MORE SAMPLES:
		float sX = vX * vX / abs(vX) * potTimeOfFall
			- 1 / 2 * AIR_RESISTANCE * vX / abs(vX) * potTimeOfFall * potTimeOfFall;
		if (sX < abs(landingFieldPosition - 10 + landingFieldSize - x) && sX > abs(landingFieldPosition + 10 - x)) {
			setSidePower(0);
			//setCentralPower(0);
		}
		// X-borgers:
		if (windowWidth - x < x && 2 * gravity * (windowWidth - x) < 3 * vX * vX + 4 && vX > -2) 
		{
			cout << " (Stop becuse of left border) ";
			setSidePower(-gravity);
		}
		if (windowWidth - x > x && 2 * gravity * (x) < 3 * vX * vX + 4 && vX < 2) 
		{
			cout << " (Stop because of right border) ";
			setSidePower(gravity);
		}*/
		// --------------------------------------------------------- //

		
		// --------------- ALGORITHM 3 FOR LINEAR MOVING --------------- //
		// --------------- TAKES MORE FUEL IN GENERAL --------------- //


		/*float potTimeOfFall = (-vY + sqrt(vY * vY + 2 * gravity * (windowHeight - y)) / gravity);
		float sX = abs(vX * vX / abs(vX) * potTimeOfFall
			- 1 / 2 * AIR_RESISTANCE * vX / abs(vX) * potTimeOfFall * potTimeOfFall);
		cout << "\nsX: " << sX << "\nS to LF: " << '\n';
		float SToLF = 0;
		if (x > landingFieldPosition + landingFieldSize) {
			SToLF = -landingFieldPosition - 10 + x;
		}			
		else if (x < landingFieldPosition) {
			SToLF = landingFieldPosition - 10 + -x;
		}
		cout << SToLF << '\n';

		int vectorOfSpeed = x > landingFieldPosition + landingFieldSize ? 1 : -1;
		if (SToLF == 0) {
			setSidePower(vectorOfSpeed * gravity);
		}
		else if (sX > SToLF) {
			setSidePower(vectorOfSpeed * gravity);
		}
		else if (sX < SToLF) {
			setSidePower(-1 * vectorOfSpeed * gravity);
		}*/

		// --------------------------------------------------------- //
}