#ifndef LEVELXML_H
#define LEVELXML_H

#include "common.h"
#include "ObjectSelection.h"
#include "tinyxml.h"

typedef struct levelProperty
{
    levelProperty* next;    
    char* name;
    char* value;
} levelProperty;

LPOI HandleToOI( int handle, LPRDATA rdPtr );
bool SetProperties( LPRDATA rdPtr, 
                    const char* name, 
                    const char* posx, 
                    const char* posy, 
                    const char* layer,
                    const char* type );
void ClearProperties( LPRDATA rdPtr );
TiXmlElement* CreateBasicElement( char* name, int posx, int posy, int layer );
TiXmlElement* CreateBackdropElement( char* name, int posx, int posy, int type, int layer );
void CreateBackdropObject( LPRDATA rdPtr );
void SaveLevel( LPRDATA rdPtr, char* fileName );
void LoadLevel( LPRDATA rdPtr, char* filename );

#endif