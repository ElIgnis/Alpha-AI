#ifndef DELIVERYMAN_H
#define DELIVERYMAN_H

#include "GameObject2D.h"
#include "SceneManager.h"
#include "Vector2.h"
#include <fstream>
#include <sstream>

using std::getline;

class DeliveryMan : GameObject2D
{
public:
	enum STATES
	{
		S_IDLE = 0,
		S_SLEEPING,
		S_EATING,
		S_DELIVERING,
		S_RETURNING,
		NUM_STATES,
	};

	enum POS
	{
		X = 0,
		Y,
		POS_INDEX,
	};

	enum SPRITES_INDOOR
	{
		WALK_DOWN,
		WALK_LEFT,
		WALK_RIGHT,
		WALK_UP,
		NUM_SPRITES,
	};

	DeliveryMan();
	~DeliveryMan();

	void Init();

	STATES getCurrentState(void);

	void Update(double dt, int worldTime, int weather, bool order);
	void UpdateIdle(double dt, int worldTime, bool order);
	void UpdateEating(double dt, int worldTime);
	void UpdateSleeping(double dt, int worldTime);
	void UpdateDelivering(double dt, int worldTime, int weather, bool order);
	void UpdateReturning(double dt, int worldTime, int weather, bool order);
	void Draw(SceneManager* sceneManager);

	//Outdoor controls
	bool GenerateOrder(void);
	int RandomizePath(void);

	bool getOutdoor(void);
	void setOutdoor(const bool isOutDoor);

	bool getInCarriage(void);

	void ReadWayPoints_Eat(string fileName);
	void ReadWayPoints_Sleep(string fileName);
	void ReadWayPoints_Exiting(string fileName);
	void ReadWayPoints_Path1(string fileName);
	void ReadWayPoints_Path2(string fileName);
	void ReadWayPoints_Path3(string fileName);

	void AddWayPoints_Eat(Vector2 newWayPoint);
	void AddWayPoints_Sleep(Vector2 newWayPoint);
	void AddWayPoints_Exiting(Vector2 newWayPoint);
	void AddWayPoints_Path1(Vector2 newWayPoint);
	void AddWayPoints_Path2(Vector2 newWayPoint);
	void AddWayPoints_Path3(Vector2 newWayPoint);

	Vector2 GetPos();
	Vector2 GetDir();

	vector<Vector2> ReturnCurrentPath;
	bool UpdatePath(vector<Vector2> PathToUpdate, bool Reverse, double dt);

	SpriteAnimation* GetIndoorSpriteAnim(void);
	SpriteAnimation* GetOutdoorSpriteAnim(void);
	void SetIndoorSpriteAnim(SpriteAnimation* NewSpriteAnim);
	void SetOutdoorSpriteAnim(SpriteAnimation* NewSpriteAnim);
	
private:
	SpriteAnimation* spriteAnim_Indoor;
	SpriteAnimation* spriteAnim_Outdoor;

	STATES currentState;
	bool m_bNeedToEat;
	bool m_bNeedToSleep;
	bool m_bOutdoor;
	bool m_bReturn;
	bool m_bPathAssigned;
	bool m_bPendingDelivery;
	bool m_bInCarriage;

	int m_iHoursNeeded;
	int m_iResult;
	int m_iStartSleepHour;
	int m_iCurrentPath;
	int m_iStartHour;
	int m_iNextPoint;

	float m_fTotalTime;
	float m_fMoveSpeed;			//Speed is decided by time and weather

	float m_fDistSquared;
	Vector2 m_v2CurrentPos;
	Vector2 m_v2NextPos;
	Vector2 m_v2Direction;

	vector<Vector2> Eat;
	vector<Vector2> Sleep;
	vector<Vector2> Exiting;
	vector<Vector2> PathOne;
	vector<Vector2> PathTwo;
	vector<Vector2> PathThree;

	//Text file reading
	int m_iReadLine;
	string WPData;
	char m_cSplit_Char;
};

#endif