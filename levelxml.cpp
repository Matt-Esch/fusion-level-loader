#include "levelxml.h"


levelProperty* NewLevelProperty( char* name, char* value )
{
    levelProperty* lp = (levelProperty*)malloc(sizeof(levelProperty));
    lp->next = NULL;
    lp->name = (char*)malloc(strlen(name)+1);
    strcpy(lp->name,name);
    lp->value = (char*)malloc(strlen(value)+1);
    strcpy(lp->value,value);
    return lp;
}

void FreeLevelProperty( levelProperty* lp )
{
    if( lp != NULL )
    {
        FreeLevelProperty(lp->next);
        free(lp->name);
        free(lp->value);
        free(lp);
    }
}


LPOI HandleToOI( int handle, LPRDATA rdPtr )
{
    CRunApp* rhApp = rdPtr->rHo.hoAdRunHeader->rhApp;
    for( int i = 0; i <= rhApp->m_oiMaxIndex; i++ )
    {
        if( rhApp->m_ois[i]->oiHdr.oiHandle == handle )
        {
            return rhApp->m_ois[i];
        }
    }
    return NULL;    
}

LPHO ObjToHO( npObj obj, LPRH rhPtr )
{

	LPOBL   oblPtr = (LPOBL)rhPtr->rhObjectList;

    for (int i=0; i<rhPtr->rhNObjects; i++)
	{
        LPHO hoPtr = (LPHO)(oblPtr->oblOffset);
      
        LPRO rObj = LPRO(oblPtr->oblOffset);
        
        if( rObj->roc.rcSprite != NULL && obj == &rObj->roc.rcSprite->sprObj)
        {
            return hoPtr;
        }

        oblPtr++;
    }

    return NULL;
    
}

TiXmlElement* CreateBasicElement( char* name, int posx, int posy, int layer )
{
        TiXmlElement* objectE = new TiXmlElement( "Object" );

        TiXmlElement* nameE = new TiXmlElement( "Name" );
        TiXmlText* nameT = new TiXmlText( name );
        nameE->LinkEndChild( nameT );

        char charposx [24];
        _itoa( posx, charposx, 10 );
        char charposy [24];
        _itoa( posy, charposy, 10 );
        char charlayer[24];
        _itoa( layer, charlayer, 10 );

        TiXmlElement* posxE = new TiXmlElement( "PosX" );
        TiXmlText* posxT = new TiXmlText( &charposx[0] );
        posxE->LinkEndChild( posxT );

        TiXmlElement* posyE = new TiXmlElement( "PosY" );
        TiXmlText* posyT = new TiXmlText( &charposy[0] );
        posyE->LinkEndChild( posyT );

        TiXmlElement* layerE = new TiXmlElement( "Layer" );
        TiXmlText* layerT = new TiXmlText( &charlayer[0] );
        layerE->LinkEndChild( layerT );
        
        objectE->LinkEndChild( nameE );
        objectE->LinkEndChild( posxE );
        objectE->LinkEndChild( posyE );
        objectE->LinkEndChild( layerE );

        return objectE;
}

bool SetProperties( LPRDATA rdPtr, 
                    const char* name, 
                    const char* posx, 
                    const char* posy, 
                    const char* layer,
                    const char* type )
{
    if( name == NULL || posx == NULL || posy == NULL || layer == NULL  )
    {
        return false;
    }

    strcpy( rdPtr->objName, name );
    rdPtr->objName[OBJECT_NAME_MAX_SIZE] = '\0';
    rdPtr->posX = atoi(posx);
    rdPtr->posY = atoi(posy);
    rdPtr->layer = atoi(layer);
    if( rdPtr->layer < 0 )
    {
        rdPtr->layer = 0;
    }

    if( type == NULL )
    {
        rdPtr->type = OBSTACLE_NONE;
    }
    else
    {
        rdPtr->type = atoi(type);
        if( rdPtr->type != OBSTACLE_NONE &&
            rdPtr->type != OBSTACLE_LADDER &&
            rdPtr->type != OBSTACLE_PLATFORM &&
            rdPtr->type != OBSTACLE_SOLID &&
            rdPtr->type != OBSTACLE_TRANSPARENT )
        {
            rdPtr->type = OBSTACLE_NONE;
        }
    }

    return true;
}

void ClearProperties( LPRDATA rdPtr )
{
    strcpy( rdPtr->objName, "" );
    rdPtr->posX = 0;
    rdPtr->posY = 0;
    rdPtr->layer = 0;
    rdPtr->type = 0;
}

TiXmlElement* CreateBackdropElement( char* name, 
                                     int posx, 
                                     int posy, 
                                     int type, 
                                     int layer )
{
        TiXmlElement* objectE = new TiXmlElement( "Backdrop" );

        TiXmlElement* nameE = new TiXmlElement( "Name" );
        TiXmlText* nameT = new TiXmlText( name );
        nameE->LinkEndChild( nameT );

        char charposx [24];
        _itoa( posx, charposx, 10 );
        char charposy [24];
        _itoa( posy, charposy, 10 );
        char charlayer[24];
        _itoa( layer, charlayer, 10 );
        char chartype[24];
        _itoa( type, chartype, 10 );

        TiXmlElement* posxE = new TiXmlElement( "PosX" );
        TiXmlText* posxT = new TiXmlText( &charposx[0] );
        posxE->LinkEndChild( posxT );

        TiXmlElement* posyE = new TiXmlElement( "PosY" );
        TiXmlText* posyT = new TiXmlText( &charposy[0] );
        posyE->LinkEndChild( posyT );

        TiXmlElement* typeE = new TiXmlElement( "Type" );
        TiXmlText* typeT = new TiXmlText( &chartype[0] );
        typeE->LinkEndChild( typeT );

        TiXmlElement* layerE = new TiXmlElement( "Layer" );
        TiXmlText* layerT = new TiXmlText( &charlayer[0] );
        layerE->LinkEndChild( layerT );

        objectE->LinkEndChild( nameE );
        objectE->LinkEndChild( posxE );
        objectE->LinkEndChild( posyE );
        objectE->LinkEndChild( layerE );
        objectE->LinkEndChild( typeE );

        return objectE;
}

void CreateBackdropObject( LPRDATA rdPtr )
{
    LPRH rhPtr = rdPtr->rHo.hoAdRunHeader;

    // Find the identical backdrop
    LPOI* ois = rhPtr->rhApp->m_ois;

	// List of object offsets
	LPOBL   oblPtr = (LPOBL)rhPtr->rhObjectList;

    CRunFrame* frame = (CRunFrame*)rhPtr->rhFrame;
    RunFrameLayer* layerPtr = frame->m_pLayers;

    // Find backdrop
    for(int i=0; i<frame->m_nLayers; i++)
    {
        LPLO backdropPtr = (LPLO)(frame->m_los + layerPtr->nFirstLOIndex);
        
        for( int j = 0; j<(int)layerPtr->nBkdLOs; j++ )
        {
            LPOI objOI = rhPtr->rhApp->m_ois[rhPtr->rhApp->m_oi_handle_to_index[backdropPtr->loOiHandle]];
            if( strcmp(objOI->oiName,rdPtr->objName) == 0 )
            {
                LPBackdrop_OC test = (LPBackdrop_OC)objOI->oiOC;

                cSurface imageSurface;
                LockImageSurface (rhPtr->rhIdAppli, test->ocImage, imageSurface, LOCKIMAGE_READBLITONLY);

                rdPtr->rHo.hoAdRunHeader->rh4.rh4Mv->mvAddBackdrop( &imageSurface, 
                                                                    rdPtr->posX, 
                                                                    rdPtr->posY, 
                                                                    objOI->oiHdr.oiInkEffect, 
                                                                    objOI->oiHdr.oiInkEffectParam, 
                                                                    rdPtr->type, 
                                                                    rdPtr->layer );
                UnlockImageSurface(imageSurface);
                    
                return;
            }

            backdropPtr++;
        }

        layerPtr++;
    }

}

void SaveObject( LPRDATA rdPtr, LPHO hoPtr, TiXmlDocument* doc)
{
        // Don't add stone goose level objects or any object inside the
        // exclusion zone.
        if(hoPtr->hoIdentifier != IDENTIFIER && !
            ((hoPtr->hoX >= rdPtr->rHo.hoX && hoPtr->hoX <= rdPtr->rHo.hoX + rdPtr->width)
                && (hoPtr->hoY >= rdPtr->rHo.hoY && hoPtr->hoY <= rdPtr->rHo.hoY+rdPtr->height) ) )
        {
            LPOI objOI = rdPtr->rHo.hoAdRunHeader->rhApp->m_ois[rdPtr->rHo.hoAdRunHeader->rhApp->m_oi_handle_to_index[hoPtr->hoOi]];
            doc->LinkEndChild( CreateBasicElement( objOI->oiName, 
                                                  hoPtr->hoX, 
                                                  hoPtr->hoY,
                                                  hoPtr->hoLayer) );
        }
}

void SaveLevel( LPRDATA rdPtr, char* fileName  )
{
    LPRH rhPtr = rdPtr->rHo.hoAdRunHeader;
    TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );

    LPOI* ois = rhPtr->rhApp->m_ois;

    CRunFrame* frame = (CRunFrame*)rhPtr->rhFrame;
    RunFrameLayer* layerPtr = frame->m_pLayers;

    // List of object offsets
	LPOBL   oblPtr = (LPOBL)(rhPtr->rhObjectList+rhPtr->rh1stObjectNumber);
    
    // Save backdrops
    for(int i=0; i<frame->m_nLayers; i++)
    {
        LPLO backdropPtr = (LPLO)(frame->m_los + layerPtr->nFirstLOIndex);
        
        for( int j = 0; j<(int)layerPtr->nBkdLOs; j++ )
        {
            LPOI objOI = rhPtr->rhApp->m_ois[rhPtr->rhApp->m_oi_handle_to_index[backdropPtr->loOiHandle]];
            if(! ( (backdropPtr->loX >= rdPtr->rHo.hoX && backdropPtr->loX <= rdPtr->rHo.hoX + rdPtr->width)
                && backdropPtr->loY >= rdPtr->rHo.hoY && backdropPtr->loY <= rdPtr->rHo.hoY+rdPtr->height) )
            {
                doc.LinkEndChild( CreateBackdropElement( objOI->oiName, 
                                                         backdropPtr->loX, 
                                                         backdropPtr->loY, 
                                                         backdropPtr->loType, 
                                                         backdropPtr->loLayer ) );
            }
            backdropPtr++;
        }

        layerPtr++;
    }

    // Get sprites on the background layer (OEFLAG_BACKGROUND)
    DWORD dwFlags = GS_BACKGROUND;
    
    for( int k=0; k<2; k++)
    {
        for(int i=0; i<frame->m_nLayers; i++)
        {
            npSpr sprite = GetFirstSprite(rhPtr->rhIdEditWin,i,dwFlags);
            while(sprite != NULL)
            {
                LPHO hoPtr = ObjToHO(&sprite->sprObj,rhPtr);
                if(hoPtr != NULL)
                {
                    SaveObject(rdPtr,hoPtr,&doc);
                }
                sprite = GetNextSprite(rhPtr->rhIdMainWin,sprite,dwFlags);
            }
        }

        // Get sprites on the active layer (OEFLAG_SPRITE)
        dwFlags = GS_SAMELAYER;
    }

    
    // Iterate main objects non-sprite objects
	for (int i=0; i<rhPtr->rhNObjects; i++)
	{
        LPHO hoPtr = (LPHO)(oblPtr->oblOffset);        
        LPRO rObj = LPRO(oblPtr->oblOffset);
        
        // Check sprite structure, sprites were already added in z-order
        if( rObj->roc.rcSprite == NULL )
        {
            SaveObject(rdPtr,hoPtr,&doc);
        }

        oblPtr++;
	}

    doc.SaveFile( fileName );
    doc.Clear();
}

void LoadLevel( LPRDATA rdPtr, char* filename )
{
    TiXmlDocument doc(filename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
        TiXmlElement* currentE = doc.FirstChildElement();
        TiXmlElement* nameE;
        TiXmlElement* posxE;
        TiXmlElement* posyE;
        TiXmlElement* layerE;
        TiXmlElement* typeE;
        
        const char* value;
        while( currentE )
        {
            value = currentE->Value();
            if( strcmp( value, "Object" ) == 0 )
            {
                nameE = currentE->FirstChildElement("Name");
                posxE = currentE->FirstChildElement("PosX");
                posyE = currentE->FirstChildElement("PosY");
                layerE = currentE->FirstChildElement("Layer");

                if( nameE && posxE && posyE && layerE && 
                    SetProperties( rdPtr,
                                   nameE->GetText(),
                                   posxE->GetText(),
                                   posyE->GetText(),
                                   layerE->GetText(),
                                   NULL ) )
                {
                    //Object creation callback
                    rdPtr->rRd->GenerateEvent(0);
                }
                    
                ClearProperties( rdPtr );

                nameE = NULL;
                posxE = NULL;
                posyE = NULL;
                layerE = NULL;
                
            }
            else if( strcmp( value, "Backdrop" ) == 0 )
            {
                // Create the backdrop
                nameE = currentE->FirstChildElement("Name");
                posxE = currentE->FirstChildElement("PosX");
                posyE = currentE->FirstChildElement("PosY");
                layerE = currentE->FirstChildElement("Layer");
                typeE = currentE->FirstChildElement("Type");

                if( nameE && posxE && posyE && layerE && typeE && 
                    SetProperties( rdPtr,
                                   nameE->GetText(),
                                   posxE->GetText(),
                                   posyE->GetText(),
                                   layerE->GetText(),
                                   typeE->GetText() ) )
                {
                    CreateBackdropObject( rdPtr );
                }
                

                nameE = NULL;
                posxE = NULL;
                posyE = NULL;
                layerE = NULL;
                typeE = NULL;
            }

            currentE = currentE->NextSiblingElement();
        }

        // On load success
        rdPtr->rRd->GenerateEvent(1);
	}
	else
	{
        // On load failure
		rdPtr->rRd->GenerateEvent(2);
	}

    doc.Clear();
}