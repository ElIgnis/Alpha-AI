#include "DeliveryMan.h"
//Sleeps for 8 hours before going to Idle(Starts based on the timing that went to sleep)

//Idle in store until order arrives

//If need to eat(Lunch, Dinner), finish eating before processing next order

//Else process order and start delivering(Delivery speed based on weather and peak period)

//Order prob randomizes 50% on every hour passed

//Waypoint to go out of shop

//Randomize which path to take and move accordingly

//If reached end of point, traverse back and return.

//After back in shop then idle

DeliveryMan::DeliveryMan()
: currentState(S_SLEEPING)

, m_bNeedToEat(false)
, m_bOutdoor(false)
, m_bExiting(false)
, m_bNeedToSleep(true)
, m_bPendingDelivery(false)
, m_bPathAssigned(false)
, m_bInCarriage(false)
, m_bOrderCollected(false)
, m_bOrderToCollect(false)
, m_bDeliveryCompleted(false)
, m_bRC_Barista(false)

, m_iHoursNeeded(2)
, m_iResult(0)
, m_iStartSleepHour(0)
, m_iCurrentPath(0)
, m_iStartHour(0)
, m_iNextPoint(0)

, m_fTotalTime(0.f)
, m_fMoveSpeed(500.f)
, m_fDistSquared(0.f)
, m_fDelay(0.f)

//Text file reading
, m_iReadLine(0)
, WPData("")
, m_cSplit_Char(',')
{
}

DeliveryMan::~DeliveryMan()
{
}

void DeliveryMan::Init(void)
{
	spriteAnim_Indoor = new SpriteAnimation();
	spriteAnim_Outdoor = new SpriteAnimation();
	spriteAnim_Outdoor_Night = new SpriteAnimation();
	spriteAnim_Legend = new SpriteAnimation();

	ReadWayPoints_Eat("Config\\Waypoints\\DeliveryMan\\Eat_1.txt");
	ReadWayPoints_Sleep("Config\\Waypoints\\DeliveryMan\\Sleep_1.txt");
	ReadWayPoints_RC_Barista("Config\\Waypoints\\DeliveryMan\\RC_ToBarista_1.txt");
	ReadWayPoints_Collecting("Config\\Waypoints\\DeliveryMan\\Collecting_1.txt");
	ReadWayPoints_Exiting("Config\\Waypoints\\DeliveryMan\\Exiting_1.txt");
	ReadWayPoints_Path1("Config\\Waypoints\\DeliveryMan\\PathOne_1.txt");
	ReadWayPoints_Path2("Config\\Waypoints\\DeliveryMan\\PathTwo_1.txt");
	ReadWayPoints_Path3("Config\\Waypoints\\DeliveryMan\\PathThree_1.txt");
	
	//Initialise at sleeping position first
	m_v2CurrentPos = Sleep.at(Sleep.size() - 1);
}

void DeliveryMan::ReadWayPoints_Eat(string fileName)
{
	//vector to contain elements split
	vector<string>WPTokens;

	//Reset line
	m_iReadLine = 0;

	//Load Level details
	std::ifstream inTxtFile;
	inTxtFile.open(fileName);
	if (inTxtFile.good())
	{
		while (getline(inTxtFile, WPData))
		{
			std::istringstream split(WPData);

			//Dont read lines with #
			if (WPData[0] == '#')
			{
				continue;
			}

			for (string each; std::getline(split, each, m_cSplit_Char);)
			{
				WPTokens.push_back(each);
			}

			//Load the points in
			AddWayPoints_Eat(Vector2(
				stof(WPTokens.at(X + m_iReadLine * POS_INDEX))
				, stof(WPTokens.at(Y + m_iReadLine * POS_INDEX))
				));

			++m_iReadLine;
		}
		WPTokens.clear();
		inTxtFile.close();
	}
	else
		std::cout << "Load Waypoint file failed" << std::endl;
}

void DeliveryMan::ReadWayPoints_RC_Barista(string fileName)
{
	//vector to contain elements split
	vector<string>WPTokens;

	//Reset line
	m_iReadLine = 0;

	//Load Level details
	std::ifstream inTxtFile;
	inTxtFile.open(fileName);
	if (inTxtFile.good())
	{
		while (getline(inTxtFile, WPData))
		{
			std::istringstream split(WPData);

			//Dont read lines with #
			if (WPData[0] == '#')
			{
				continue;
			}

			for (string each; std::getline(split, each, m_cSplit_Char);)
			{
				WPTokens.push_back(each);
			}

			//Load the points in
			AddWayPoints_RC_Barista(Vector2(
				stof(WPTokens.at(X + m_iReadLine * POS_INDEX))
				, stof(WPTokens.at(Y + m_iReadLine * POS_INDEX))
				));

			++m_iReadLine;
		}
		WPTokens.clear();
		inTxtFile.close();
	}
	else
		std::cout << "Load Waypoint file failed" << std::endl;
}

void DeliveryMan::ReadWayPoints_Collecting(string fileName)
{
	//vector to contain elements split
	vector<string>WPTokens;

	//Reset line
	m_iReadLine = 0;

	//Load Level details
	std::ifstream inTxtFile;
	inTxtFile.open(fileName);
	if (inTxtFile.good())
	{
		while (getline(inTxtFile, WPData))
		{
			std::istringstream split(WPData);

			//Dont read lines with #
			if (WPData[0] == '#')
			{
				continue;
			}

			for (string each; std::getline(split, each, m_cSplit_Char);)
			{
				WPTokens.push_back(each);
			}

			//Load the points in
			AddWayPoints_Collecting(Vector2(
				stof(WPTokens.at(X + m_iReadLine * POS_INDEX))
				, stof(WPTokens.at(Y + m_iReadLine * POS_INDEX))
				));

			++m_iReadLine;
		}
		WPTokens.clear();
		inTxtFile.close();
	}
	else
		std::cout << "Load Waypoint file failed" << std::endl;
}

void DeliveryMan::ReadWayPoints_Sleep(string fileName)
{
	//vector to contain elements split
	vector<string>WPTokens;

	//Reset line
	m_iReadLine = 0;

	//Load Level details
	std::ifstream inTxtFile;
	inTxtFile.open(fileName);
	if (inTxtFile.good())
	{
		while (getline(inTxtFile, WPData))
		{
			std::istringstream split(WPData);

			//Dont read lines with #
			if (WPData[0] == '#')
			{
				continue;
			}

			for (string each; std::getline(split, each, m_cSplit_Char);)
			{
				WPTokens.push_back(each);
			}

			//Load the points in
			AddWayPoints_Sleep(Vector2(
				stof(WPTokens.at(X + m_iReadLine * POS_INDEX))
				, stof(WPTokens.at(Y + m_iReadLine * POS_INDEX))
				));
			++m_iReadLine;
		}
		WPTokens.clear();
		inTxtFile.close();
	}
	else
		std::cout << "Load Waypoint file failed" << std::endl;
}

void DeliveryMan::ReadWayPoints_Exiting(string fileName)
{
	//vector to contain elements split
	vector<string>WPTokens;

	//Reset line
	m_iReadLine = 0;

	//Load Level details
	std::ifstream inTxtFile;
	inTxtFile.open(fileName);
	if (inTxtFile.good())
	{
		while (getline(inTxtFile, WPData))
		{
			std::istringstream split(WPData);

			//Dont read lines with #
			if (WPData[0] == '#')
			{
				continue;
			}

			for (string each; std::getline(split, each, m_cSplit_Char);)
			{
				WPTokens.push_back(each);
			}

			//Load the points in based on the type
			AddWayPoints_Exiting(Vector2(
				stof(WPTokens.at(X + m_iReadLine * POS_INDEX))
				, stof(WPTokens.at(Y + m_iReadLine * POS_INDEX))
				));

			++m_iReadLine;
		}
		WPTokens.clear();
		inTxtFile.close();
	}
	else
		std::cout << "Load Waypoint file failed" << std::endl;
}

void DeliveryMan::ReadWayPoints_Path1(string fileName)
{
	//vector to contain elements split
	vector<string>WPTokens;

	//Reset line
	m_iReadLine = 0;

	//Load Level details
	std::ifstream inTxtFile;
	inTxtFile.open(fileName);
	if (inTxtFile.good())
	{
		while (getline(inTxtFile, WPData))
		{
			std::istringstream split(WPData);

			//Dont read lines with #
			if (WPData[0] == '#')
			{
				continue;
			}

			for (string each; std::getline(split, each, m_cSplit_Char);)
			{
				WPTokens.push_back(each);
			}

			//Load the points in
			AddWayPoints_Path1(Vector2(
				stof(WPTokens.at(X + m_iReadLine * POS_INDEX))
				, stof(WPTokens.at(Y + m_iReadLine * POS_INDEX))
				));

			++m_iReadLine;
		}
		WPTokens.clear();
		inTxtFile.close();
	}
	else
		std::cout << "Load Waypoint file failed" << std::endl;
}

void DeliveryMan::ReadWayPoints_Path2(string fileName)
{
	//vector to contain elements split
	vector<string>WPTokens;

	//Reset line
	m_iReadLine = 0;

	//Load Level details
	std::ifstream inTxtFile;
	inTxtFile.open(fileName);
	if (inTxtFile.good())
	{
		while (getline(inTxtFile, WPData))
		{
			std::istringstream split(WPData);

			//Dont read lines with #
			if (WPData[0] == '#')
			{
				continue;
			}

			for (string each; std::getline(split, each, m_cSplit_Char);)
			{
				WPTokens.push_back(each);
			}

			//Load the points in
			AddWayPoints_Path2(Vector2(
				stof(WPTokens.at(X + m_iReadLine * POS_INDEX))
				, stof(WPTokens.at(Y + m_iReadLine * POS_INDEX))
				));

			++m_iReadLine;
		}
		WPTokens.clear();
		inTxtFile.close();
	}
	else
		std::cout << "Load Waypoint file failed" << std::endl;
}

void DeliveryMan::ReadWayPoints_Path3(string fileName)
{
	//vector to contain elements split
	vector<string>WPTokens;

	//Reset line
	m_iReadLine = 0;

	//Load Level details
	std::ifstream inTxtFile;
	inTxtFile.open(fileName);
	if (inTxtFile.good())
	{
		while (getline(inTxtFile, WPData))
		{
			std::istringstream split(WPData);

			//Dont read lines with #
			if (WPData[0] == '#')
			{
				continue;
			}

			for (string each; std::getline(split, each, m_cSplit_Char);)
			{
				WPTokens.push_back(each);
			}

			//Load the points in
			AddWayPoints_Path3(Vector2(
				stof(WPTokens.at(X + m_iReadLine * POS_INDEX))
				, stof(WPTokens.at(Y + m_iReadLine * POS_INDEX))
				));
			++m_iReadLine;
		}
		WPTokens.clear();
		inTxtFile.close();
	}
	else
		std::cout << "Load Waypoint file failed" << std::endl;
}

void DeliveryMan::Update(double dt, int worldTime, int weather, int& deliveries, int& deliveriesPrepared, MessageBoard* mb)
{
	// Need to eat at 1200 hours
	if (worldTime == 1200 || worldTime == 1800)
	{
		m_bNeedToEat = true;
	}

	//Need to sleep at night
	if (worldTime == 0)
	{
		m_bNeedToSleep = true;
	}

	if (deliveriesPrepared > 0)
	{
		m_bPendingDelivery = true;
	}
	else if (deliveriesPrepared == 0 && !m_bOrderCollected)
	{
		m_bPendingDelivery = false;
	}

	switch (currentState)
	{
	case S_IDLE:
		//m_fMoveSpeed = 500.f;
		UpdateIdle(dt, worldTime, mb);
		break;
	case S_SLEEPING:
		m_v2Direction.Set(0, -1);
		UpdateSleeping(dt, worldTime);
		break;
	case S_EATING:
		UpdateEating(dt, worldTime);
		break;
	case S_COLLECTING:
		m_v2Direction.Set(0, -1);
		UpdateCollecting(dt, worldTime, deliveriesPrepared);
		break;
	case S_DELIVERING:
		UpdateDelivering(dt, worldTime, weather);
		break;
	case S_RETURNING:
		UpdateReturning(dt, worldTime, weather, deliveries);
		break;
	default:
		break;
	}

	// Update sprite based on direction
	if (!m_bInCarriage)
	{
		spriteAnim_Indoor->Update(dt);

		if (m_v2Direction.x == -1)
			this->spriteAnim_Indoor->currentAni = WALK_LEFT;
		else if (m_v2Direction.x == 1)
			this->spriteAnim_Indoor->currentAni = WALK_RIGHT;
		else if (m_v2Direction.y == 1)
			this->spriteAnim_Indoor->currentAni = WALK_UP;
		else if (m_v2Direction.y == -1)
			this->spriteAnim_Indoor->currentAni = WALK_DOWN;
		else
			this->spriteAnim_Indoor->currentAni = WALK_DOWN;
	}
	else
	{
		spriteAnim_Outdoor->Update(dt);
		spriteAnim_Outdoor_Night->Update(dt);

		if (m_v2Direction.x == -1)
		{
			this->spriteAnim_Outdoor->currentAni = WALK_LEFT;
			this->spriteAnim_Outdoor_Night->currentAni = WALK_LEFT;
		}
		else if (m_v2Direction.x == 1)
		{
			this->spriteAnim_Outdoor->currentAni = WALK_RIGHT;
			this->spriteAnim_Outdoor_Night->currentAni = WALK_RIGHT;
		}
		else if (m_v2Direction.y == 1)
		{
			this->spriteAnim_Outdoor->currentAni = WALK_UP;
			this->spriteAnim_Outdoor_Night->currentAni = WALK_UP;
		}
		else if (m_v2Direction.y == -1)
		{
			this->spriteAnim_Outdoor->currentAni = WALK_DOWN;
			this->spriteAnim_Outdoor_Night->currentAni = WALK_DOWN;
		}
		else
		{
			this->spriteAnim_Outdoor->currentAni = WALK_DOWN;
			this->spriteAnim_Outdoor_Night->currentAni = WALK_DOWN;
		}	
	}
	spriteAnim_Legend->Update(dt);
}
void DeliveryMan::UpdateIdle(double dt, int worldTime, MessageBoard* mb)
{
	
	//if (!m_bOrderToCollect && !m_bNeedToEat && !m_bNeedToSleep)
	//{
		////Return to idle post if not doing anything
		//if (m_v2CurrentPos != Sleep.at(0))
		//	UpdatePath(Sleep, true, dt);

	
	//}

	////Role change
	//if (!m_bNeedToSleep && !m_bNeedToEat  && !m_bExiting)
	//{

	//}
	//else
	//{

	//}
	//Only perform delivery duties if no need to role change
	if (m_bRC_Barista)
	{
		if (UpdatePath(RC_Barista, false, dt))
		{
			m_v2Direction.Set(0, -1);
			m_bRC_Completed = true;
			m_bRC_Barista = false;
		}
	}


		// Sleeping portion
	else if (m_bNeedToSleep && !m_bExiting)
		{
			// Proceed to sleep after moving to sleeping area
			if (UpdatePath(Sleep, false, dt))
			{
				currentState = S_SLEEPING;

				//Assign the start of action hour
				if (m_iStartHour == 0)
					m_iStartHour = worldTime;
			}
		}

		//Eating portion
		else if (m_bNeedToEat && !m_bExiting && !m_bOrderToCollect)
		{
			// Proceed to eat after moving to eating area
			if (UpdatePath(Eat, false, dt))
			{
				currentState = S_EATING;

				//Assign the start of action hour
				if (m_iStartHour == 0)
					m_iStartHour = worldTime;
			}
		}

		//Delivery only when no need to eat/sleep
		else if (m_bPendingDelivery)
		{
			//Check if the order is collected
			if (!m_bOrderCollected)
			{
				//Collect order items when done message is received
				if (!m_bOrderToCollect && mb->GetMsg(MSG_DELIVERY_READY))
				{
					m_bOrderToCollect = true;
				}
				//If there is an order to collect
				if (m_bOrderToCollect)
				{
					//Proceed to collect after moving to collection area
					if (UpdatePath(Collect, false, dt))
					{
						currentState = S_COLLECTING;
					}
				}
			}
			else
			{
				//Get out of cafe first
				if (!m_bOutdoor)
				{
					m_bExiting = true;
					if (m_v2CurrentPos == Exiting.at(2))
						m_bInCarriage = true;

					if (UpdatePath(Exiting, false, dt))
					{
						m_bOutdoor = true;
					}
				}
				//Randomizes outdoor path
				if (m_bOutdoor)
				{
					//Assign the start of action hour
					if (m_iStartHour == 0)
						m_iStartHour = worldTime;

					//Snap new position to outside of cafe
					m_v2CurrentPos = Vector2(1290, 600);

					currentState = S_DELIVERING;
					m_iCurrentPath = RandomizePath();
				}
			}
		}
	
}
void DeliveryMan::UpdateCollecting(double dt, int worldTime, int& deliveriesPrepared)
{
	m_fDelay += (float)dt;

	//Out of deliveries to collect
	if (m_bPendingDelivery == false)
	{
		m_fDelay = 0.f;
		m_bOrderToCollect = false;
		if (UpdatePath(Collect, true, dt))
		{
			currentState = S_IDLE;
		}
	}

	//Receive msg to move to collect drinks
	if (m_fDelay > 1.5f)
	{
		--deliveriesPrepared;
		m_bOrderCollected = true;
		m_fDelay = 0.f;
	}
	if (m_bOrderCollected)
	{
		if (UpdatePath(Collect, true, dt))
		{
			currentState = S_IDLE;
		}
	}
}
void DeliveryMan::UpdateEating(double dt, int worldTime)
{
	int tempConversion = worldTime - m_iStartHour;

	if (tempConversion < 0)
	{
		tempConversion += 2400;
	}
	
	//Finish eating after 1 hour
	if (tempConversion >= 100)
	{
		if (UpdatePath(Eat, true, dt))
		{
			m_bNeedToEat = false;
			currentState = S_IDLE;
			m_iStartHour = 0;
			m_v2Direction.SetZero();
		}
		
	}
}
void DeliveryMan::UpdateSleeping(double dt, int worldTime)
{
	int tempConversion = worldTime - m_iStartHour;

	if (tempConversion < 0)
	{
		tempConversion += 2400;
	}

	//Finish eating after 1 hour
	if (tempConversion > 700)
	{
		if (UpdatePath(Sleep, true, dt))
		{
			m_bNeedToSleep = false;
			currentState = S_IDLE;
			m_iStartHour = 0;
			m_v2Direction.SetZero();
		}
	}
}
void DeliveryMan::UpdateDelivering(double dt, int worldTime, int weather)
{
	//Generate time
	if (m_bPendingDelivery)
	{
		if (worldTime >= 1700 && worldTime <= 2100)
		{
			m_iHoursNeeded = 2;
		}
		else
		{
			m_iHoursNeeded = 1;
		}

		m_fTotalTime = (float)(weather * m_iHoursNeeded);
		if (m_fTotalTime > m_iHoursNeeded)
		{
			//m_fMoveSpeed = 250.f * (m_fTotalTime / m_iHoursNeeded);
		}
	}

	//Update and travel according to path and returns after hitting the last waypoint
	switch (m_iCurrentPath)
	{
	case 0:
		if (UpdatePath(PathOne, false, dt))
		{
			currentState = S_RETURNING;
		}
		break;
	case 1:
		if (UpdatePath(PathTwo, false, dt))
		{
			currentState = S_RETURNING;
		}
		break;
	case 2:
		if (UpdatePath(PathThree, false, dt))
		{
			currentState = S_RETURNING;
		}
		break;
	default:
		break;
	}
}
void DeliveryMan::UpdateReturning(double dt, int worldTime, int weather, int& deliveries)
{
	//Add a delay of 1.5s before returning
	m_fDelay += (float)dt;

	//Update and travel according to path
	if (m_bOutdoor && m_fDelay > 1.5f)
	{
		switch (m_iCurrentPath)
		{
		case 0:
			if (UpdatePath(PathOne, true, dt))
			{
				m_bOutdoor = false;
				m_bPendingDelivery = false;
				m_v2CurrentPos = Vector2(1350, 930);
				m_v2Direction = Vector2(-1, 0);
			}
			break;
		case 1:
			if (UpdatePath(PathTwo, true, dt))
			{
				m_bOutdoor = false;
				m_bPendingDelivery = false;
				m_v2CurrentPos = Vector2(1350, 930);
				m_v2Direction = Vector2(-1, 0);
			}
			break;
		case 2:
			if (UpdatePath(PathThree, true, dt))
			{
				m_bOutdoor = false;
				m_bPendingDelivery = false;
				m_v2CurrentPos = Vector2(1350, 930);
				m_v2Direction = Vector2(-1, 0);
			}
			break;
		default:
			break;
		}
	}
	
	//Returns to idle post
	if (!m_bOutdoor)
	{
		m_fDelay = 0.f;
		if (m_v2CurrentPos == Exiting.at(2))
		{
			m_bInCarriage = false;
		}

		if (UpdatePath(Exiting, true, dt))
		{
			currentState = S_IDLE;
			m_bDeliveryCompleted = true;
			m_iStartHour = 0;
			m_v2Direction.SetZero();
			m_bExiting = false;
			m_bOrderToCollect = false;
			--deliveries;
			m_bOrderCollected = false;
		}
	}
}

bool DeliveryMan::getRC_Barista(void)
{
	return m_bRC_Barista;
}
void DeliveryMan::setRC_Barista(bool roleChanged)
{
	this->m_bRC_Barista = roleChanged;
}
bool DeliveryMan::getRC_Completed(void)
{
	return m_bRC_Completed;
}
void DeliveryMan::setRC_Completed(bool rc_Completed)
{
	this->m_bRC_Completed = rc_Completed;
}

void DeliveryMan::setNeedToSleep(bool needToSleep)
{
	this->m_bNeedToSleep = needToSleep;
}
bool DeliveryMan::getNeedToSleep(void)
{
	return m_bNeedToSleep;
}
bool DeliveryMan::getNeedToEat(void)
{
	return m_bNeedToEat;
}
bool DeliveryMan::getOrderToCollect(void)
{
	return m_bOrderToCollect;
}
bool DeliveryMan::getOrderCollected(void)
{
	return m_bOrderCollected;
}

int DeliveryMan::RandomizePath(void)
{
	return Math::RandIntMinMax(0, 2);
}

Vector2 DeliveryMan::GetPos(void)
{
	return m_v2CurrentPos;
}

Vector2 DeliveryMan::GetDir(void)
{
	return m_v2Direction;
}

void DeliveryMan::SetPos(Vector2 newPos)
{
	this->m_v2CurrentPos = newPos;
}

bool DeliveryMan::getOutdoor(void)
{
	return m_bOutdoor;
}

bool DeliveryMan::getInCarriage(void)
{
	return m_bInCarriage;
}

bool DeliveryMan::GetDeliveryCompleted(void)
{
	return m_bDeliveryCompleted;
}

void DeliveryMan::SetDeliveryCompleted(bool deliveryCompleted)
{
	this->m_bDeliveryCompleted = deliveryCompleted;
}

void DeliveryMan::AddWayPoints_Eat(Vector2 newWayPoint)
{
	Eat.push_back(newWayPoint);
}
void DeliveryMan::AddWayPoints_RC_Barista(Vector2 newWayPoint)
{
	RC_Barista.push_back(newWayPoint);
}
void DeliveryMan::AddWayPoints_Collecting(Vector2 newWayPoint)
{
	Collect.push_back(newWayPoint);
}
void DeliveryMan::AddWayPoints_Sleep(Vector2 newWayPoint)
{
	Sleep.push_back(newWayPoint);
}
void DeliveryMan::AddWayPoints_Exiting(Vector2 newWayPoint)
{
	Exiting.push_back(newWayPoint);
}
void DeliveryMan::AddWayPoints_Path1(Vector2 newWayPoint)
{
	PathOne.push_back(newWayPoint);
}
void DeliveryMan::AddWayPoints_Path2(Vector2 newWayPoint)
{
	PathTwo.push_back(newWayPoint);
}
void DeliveryMan::AddWayPoints_Path3(Vector2 newWayPoint)
{
	PathThree.push_back(newWayPoint);
}

bool DeliveryMan::UpdatePath(vector<Vector2> PathToUpdate, bool Reverse, double dt)
{
	//Assign the start point of path
	if (!m_bPathAssigned)
	{
		if (Reverse)
		{
			m_iNextPoint = PathToUpdate.size() - 1;
		}
		else
		{
			m_iNextPoint = 0;
			
		}
		m_bPathAssigned = true;
	}
	
	m_v2NextPos = PathToUpdate.at(m_iNextPoint);

	//Continue to update if have not reached next waypoint
	if (m_v2CurrentPos != PathToUpdate.at(m_iNextPoint))
	{
		m_v2Direction = (m_v2NextPos - m_v2CurrentPos).Normalized();

		//Getting distance
		m_fDistSquared = ((m_v2NextPos.x - m_v2CurrentPos.x) * (m_v2NextPos.x - m_v2CurrentPos.x) +
			(m_v2NextPos.y - m_v2CurrentPos.y) * (m_v2NextPos.y - m_v2CurrentPos.y));

		//Moving to position
		m_v2CurrentPos += m_v2Direction * ((float)dt * m_fMoveSpeed);

		//Comparing if destination has been reached
		if (m_fDistSquared < ((dt * m_fMoveSpeed) * (dt * m_fMoveSpeed)))
		{
			m_v2CurrentPos = m_v2NextPos;
		}
	}
	//Go to next waypoint
	else
	{
		if (!Reverse)
			++m_iNextPoint;
		else
			--m_iNextPoint;

		//Finished moving through waypoints
		if (m_iNextPoint == PathToUpdate.size())
		{
			m_bPathAssigned = false;
			return true;
		}
		if (m_iNextPoint < 0)
		{
			m_bPathAssigned = false;
			return true;
		}
	}
	return false;
}

void DeliveryMan::Draw(SceneManager* sceneManager)
{
	sceneManager->Render2DMesh(this->getMesh(), true, Vector2(1, 1), Vector2(this->getPosition().x, this->getPosition().y), 0);
}

DeliveryMan::STATES DeliveryMan::getCurrentState(void)
{
	return currentState;
}

void DeliveryMan::setCurrentState(DeliveryMan::STATES newState)
{
	this->currentState = newState;
}

void DeliveryMan::SetIndoorSpriteAnim(SpriteAnimation* newSprite)
{
	*(this->spriteAnim_Indoor) = *newSprite;
	*(this->spriteAnim_Legend) = *newSprite;
	this->spriteAnim_Indoor->currentAni = WALK_DOWN;
	this->spriteAnim_Legend->currentAni = WALK_DOWN;
}

void DeliveryMan::SetOutdoorSpriteAnim(SpriteAnimation* newSprite)
{
	*(this->spriteAnim_Outdoor) = *newSprite;
	this->spriteAnim_Outdoor->currentAni = WALK_DOWN;
}

void DeliveryMan::SetOutdoorSpriteAnim_Night(SpriteAnimation* newSprite)
{
	*(this->spriteAnim_Outdoor_Night) = *newSprite;
	this->spriteAnim_Outdoor_Night->currentAni = WALK_DOWN;
}

SpriteAnimation* DeliveryMan::GetIndoorSpriteAnim(void)
{
	return spriteAnim_Indoor;
}

SpriteAnimation* DeliveryMan::GetOutdoorSpriteAnim(void)
{
	return spriteAnim_Outdoor;
}

SpriteAnimation* DeliveryMan::GetOutdoorSpriteAnim_Night(void)
{
	return spriteAnim_Outdoor_Night;
}

SpriteAnimation* DeliveryMan::GetLegendSpriteAnim(void)
{
	return spriteAnim_Legend;
}