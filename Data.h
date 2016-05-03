class rRundata;
typedef rRundata * LPRRDATA;


#define OBJECT_NAME_MAX_SIZE 4096
// --------------------------------
// RUNNING OBJECT DATA STRUCTURE
// --------------------------------
// If you want to store anything between actions/conditions/expressions
// you should store it here

typedef struct tagRDATA
{
	#include "MagicRDATA.h"
    
    char objName[OBJECT_NAME_MAX_SIZE];
    int posX;
    int posY;
    int layer;
    int type;


    // Object Properties
    int width;
    int height;

    // Level Properties
    void* lp;
	
} RUNDATA;
typedef	RUNDATA	* LPRDATA;

// --------------------------------
// EDITION OF OBJECT DATA STRUCTURE
// --------------------------------
// These values let you store data in your extension that will be saved in the MFA
// You should use these with properties

typedef struct tagEDATA_V1
{
	extHeader		eHeader;
    int swidth;
    int sheight;

} EDITDATA;
typedef EDITDATA * LPEDATA;
