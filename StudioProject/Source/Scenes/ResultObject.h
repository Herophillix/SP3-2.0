#ifndef RESULT_OBJECT_H
#define RESULT_OBJECT_H

#include "GameObject.h"
// THIS CLASS IS FOR THE RESULT SCREEN AT THE END OF MINIGAMES FOR THE DISTRIBUTION OF STATS
// EXAMPLE:
//
// Score: xxxxxx
// Stats Gained: xxxxxx
// Character 01:							Character 02:
//  +  /  -  Frustration: 50%				  +  /  -  Frustration: 70%
//  +  /  -  Motivation: 50%				  +  /  -  Motivation: 30%
//
// This class is for the + and -  and continue and reset buttons
//
class ResultObject : public GameObject
{
public:
	enum RESULT_TYPE
	{
		GO_NONE = 0,
		GO_PLUS,
		GO_MINUS,
		GO_CONTINUE,
		GO_RESET,
		GO_TOTAL
	};
	enum WHICH_CHARACTER
	{
		C_NONE = 0,
		C_01,
		C_02,
		C_03,
		C_04,
		C_TOTAL
	};
	enum WHICH_STAT
	{
		S_NONE = 0,
		S_MOTIVATION,
		S_FRUSTRATION,
		S_TOTAL,
	};
	ResultObject(RESULT_TYPE typeValue = GO_NONE);
	~ResultObject();


	RESULT_TYPE objType;
	WHICH_CHARACTER belong;
	WHICH_STAT stat;

};

#endif // !RESULT_OBJECT_H

