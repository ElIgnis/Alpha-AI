#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "GameObject2D.h"
#include "SceneManager.h"
#include "Vector2.h"
#include "SpriteAnimation.h"
#include "MessageBoard.h"

#define Urgent "Urgent!"
#define Busy "Busy on Call!"

class Customer : GameObject2D
{
public: 
	enum STATES
	{
		S_IDLE,
		S_WALKING,
		S_DECIDE,
		S_QUEUE,
		S_BUY,
		S_WAIT,
		S_PICKUP,
		NUM_STATES
	};

	enum SPRITES
	{
		WALK_DOWN,
		WALK_LEFT,
		WALK_RIGHT,
		WALK_UP,
		NUM_SPRITES
	};

	enum TYPE
	{
		NORMAL,
		FAMILY,
		NUM_TYPE
	};

	Customer(Vector2 startPos);	//Default constructor
	~Customer();	//Default destructor

	void Update(double dt, int worldTime, int weather, MessageBoard *mb);	//Update based on state	

	STATES getCurrentState(void);	//Get current state 
	Vector2 getCurrentPos();	//Get current position
	void setStartPos(Vector2 startpos);	//Setting new start position 
	void setNextPoint(Vector2 nextpoint);	//Set next point to head towards
	Vector2 getNextPoint(void);	//Get next point

	void SetQueueID(int id);	//Set Customer's Q ID
	int GetQueueID(void);	//Get Customer's Q ID

	void setCutQueueStatus(bool status,int IDtoGO);
	bool getCutQueueStatus(void);

	bool getOutdoorStatus();	//Get where customer is (outdoor / indoor)
	void setActive(bool active);	//Set active status

	bool getActive();	//Get active status
	bool getQueueStatus();	//Get queue status

	bool getInQueueStatus();	//Get queue status
	void setInQueueStatus(bool inqueue);	//Set queue status

	bool getWaitStatus();	//Get wait status
	bool getInWaitStatus();	//Get in wait status

	void setInWaitStatus(bool wait);	//Set in wait status
	void setDrinkAvailable(bool available);	//set If drink available status

	Vector2 getPos();	//Get customer pos

	float getDelay();	//Get delay
	void setPickedUp(bool pickup);	//Set if drink has been picked up status

	void setOrderPlaced(bool placed);	//Get whether customer has placed order
	bool getOrderPlaced(void);	//Get whether customer has placed order

	bool CalculateUrgentProbability(void);	//Calculate if customer is urgent
	bool CalculateBusyProbability(void);	//Calculate if family is busy
	bool CalculateProbability(int time, int weather);	//Calculating probability based on time, weather

	void setSprite(SpriteAnimation* sprite);	//Set current sprite
	SpriteAnimation* getSprite(void);	//Get current sprite

	STATES getState(void);	//Get current state
	void setState(STATES state);	//Set state
	void Reset(void);	//Reset variables

	int m_IDtoGO;
	TYPE m_TypeOfCustomer;
	bool m_bChanged;	//FAmily has changed
private:
	STATES currentState;	//Current state

	const float m_fSpeed = 500.f;	//Speed of movement
	float m_fDistanceSq;	//Distance squared
	Vector2 m_v2CurrentPos;	//Current position
	Vector2 m_v2NextPos;	//Next position

	Vector2 m_v2BuyPos;	//Buying position inside shop
	Vector2 m_v2ShopPos;	//Position of shop
	Vector2 m_v2WaitPos;	//Waiting position inside shop
	Vector2 m_v2PickupPos;	//Pick up position inside shop

	bool m_bActive;	//Active
	bool m_bDrinkAvailable;	//If drinks availabe to pick up
	bool m_bOutdoor;	//Outdoor / indoor status
	bool m_bQueue;	//Start queuing
	bool m_bInQueue;	//Inside queue
	bool m_bPickedUp;	//Picked up drink 
	bool m_bDeciding;	//Deciding boolean for feedback
	bool m_bWait;	//Start waiting
	bool m_bInWait;	//Inside waiting queue
	bool m_bOrderPlaced;	//Placed Order status
	bool m_bRandomUrgent;	//Random Urgent status
	bool m_bAbleToCut;	//Able to Cut Queue, Only if Customer Infront is Queuing as well this will be set to true
	float m_fDelay;	//Timer for delays

	int m_QueueID;	//Customer's Q ID, -1 == not in queue

	SpriteAnimation* currentSprite;
};

#endif