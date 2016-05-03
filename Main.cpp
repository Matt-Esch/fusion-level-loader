// ============================================================================
//
// This file contains the actions, conditions and expressions your object uses
// 
// ============================================================================

#include "common.h"
#include "levelxml.h"


// ============================================================================
//
// CONDITIONS
// 
// ============================================================================

CONDITION(
	/* ID */			0,
	/* Name */			"%o: On Load Object",
	/* Flags */			0,
	/* Params */		(0)
) {
    return true;
}

CONDITION(
	/* ID */			1,
	/* Name */			"%o: On Load Backdrop Object",
	/* Flags */			0,
	/* Params */		(0)
) {
    return true;
}

CONDITION(
	/* ID */			2,
	/* Name */			"%o: On Load Level Success",
	/* Flags */			0,
	/* Params */		(0)
) {
    return true;
}

CONDITION(
	/* ID */			3,
	/* Name */			"%o: On Load Level Failure",
	/* Flags */			0,
	/* Params */		(0)
) {
    return true;
}

CONDITION(
	/* ID */			4,
	/* Name */			"%o: On Save Level Success",
	/* Flags */			0,
	/* Params */		(0)
) {
    return true;
}

CONDITION(
	/* ID */			5,
	/* Name */			"%o: On Save Level Failure",
	/* Flags */			0,
	/* Params */		(0)
) {
    return true;
}

CONDITION(
	/* ID */			6,
	/* Name */			"%o: Level Has String Property \"...\"",
	/* Flags */			EVFLAGS_ALWAYS | EVFLAGS_NOTABLE,
	/* Params */		(0)
) {
    return true;
}

CONDITION(
	/* ID */			7,
	/* Name */			"%o: Level Has Number Property \"...\"",
	/* Flags */			EVFLAGS_ALWAYS | EVFLAGS_NOTABLE,
	/* Params */		(0)
) {
    return true;
}

// ============================================================================
//
// ACTIONS
// 
// ============================================================================


ACTION(
	/* ID */			0,
	/* Name */			"Load Level",
	/* Flags */			0,
	/* Params */		( 1, PARAM_STRING, "Filename" )
) {
    char* fileName = (char*)Param(TYPE_STRING);
    LoadLevel( rdPtr, fileName );
}

ACTION(
	/* ID */			1,
	/* Name */			"Save Level",
	/* Flags */			0,
	/* Params */		( 1, PARAM_STRING, "Filename" )
) {
    char* fileName = (char*)Param(TYPE_STRING);
    SaveLevel( rdPtr, fileName );
}

ACTION(
	/* ID */			2,
	/* Name */			"Set Level Property",
	/* Flags */			0,
	/* Params */		( 1, PARAM_STRING, "Property Name" )
) {
    char* propName = (char*)Param(TYPE_STRING);

}

ACTION(
	/* ID */			3,
	/* Name */			"Remove Level Property",
	/* Flags */			0,
	/* Params */		( 1, PARAM_STRING, "Property Name" )
) {
    char* fileName = (char*)Param(TYPE_STRING);
    SaveLevel( rdPtr, fileName );
}


// ============================================================================
//
// EXPRESSIONS
// 
// ============================================================================

EXPRESSION(
	/* ID */			0,
	/* Name */			"ObjectName(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(0)
) {
	ReturnString((char*)&rdPtr->objName[0]);
}

EXPRESSION(
	/* ID */			1,
	/* Name */			"ObjectPosX(",
	/* Flags */			0,
	/* Params */		(0)
) {
	return rdPtr->posX;
}

EXPRESSION(
	/* ID */			2,
	/* Name */			"ObjectPosY(",
	/* Flags */			0,
	/* Params */		(0)
) {
	return rdPtr->posY;
}

EXPRESSION(
	/* ID */			3,
	/* Name */			"ObjectLayer(",
	/* Flags */			0,
	/* Params */		(0)
) {
	return rdPtr->layer;
}

EXPRESSION(
	/* ID */			4,
	/* Name */			"ObjectProperty(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(1,PARAM_STRING,"Property Name")
) {
	return rdPtr->layer;
}

EXPRESSION(
	/* ID */			5,
	/* Name */			"LevelProperty(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(1,PARAM_STRING,"Property Name")
) {
	return rdPtr->layer;
}

