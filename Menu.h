// --------------------------------
// Condition menu
// --------------------------------

#ifdef CONDITION_MENU

	ITEM(0, "On Load Object")
    ITEM(1, "On Load Backdrop Object")
	SEPARATOR
    ITEM(2, "On Load Success")
    ITEM(3, "On Load Failure")
    ITEM(4, "On Save Success")
    ITEM(5, "On Save Failure")
    SEPARATOR
    ITEM(6, "Level Has String Property")
    ITEM(7, "Level Has Number Property")

#endif

// --------------------------------
// Action menu
// --------------------------------

#ifdef ACTION_MENU
  
    ITEM(0,"Load level")
    ITEM(1,"Save level")
    SEPARATOR
    ITEM(2,"Add Level String Property")
    ITEM(3,"Add Level Number Property")
    ITEM(4,"Remove Level String Property")
    ITEM(5,"Remove Level Number Property")
    ITEM(6,"Remove All Level Properties")    
    SEPARATOR
    ITEM(7,"Add Named Backdrop")
    ITEM(8,"Remove Named Backdrop")
    ITEM(9,"Remove All Named Backdrops")

#endif


// --------------------------------
// Expression menu
// --------------------------------

#ifdef EXPRESSION_MENU

    SUB_START("Object Creation")
	    ITEM(0,"Object Name")
        ITEM(1,"Object Position X")
        ITEM(2,"Object Position Y")
        ITEM(3,"Object Layer")
        ITEM(4,"Backdrop Object Type")
    SUB_END
    ITEM(5,"Get String Property")
    ITEM(6,"Get Number Property")

#endif