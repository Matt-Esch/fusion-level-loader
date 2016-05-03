// --------------------
// Object information
// --------------------

// Basic object details
#define	ObjectName			"Stone Goose Level Object"
#define	ObjectAuthor		"Matt Esch"
#define	ObjectCopyright		"Copyright � 2011 Stone Goose Studios"
#define	ObjectComment		"Saves level information to an XML level file, and loads the data back with callbacks for object recreation."
#define	ObjectURL			"http://www.mattesch.info"
#define	ObjectHelp			"Help\\EmptyObject.chm"

// If you register your object with Clickteam, change this to the ID you were given
#define ObjectRegID			REGID_PRIVATE

// Change N,O,N,E to 4 unique characters (MMF currently still uses this to keep track)
#define	IDENTIFIER			MAKEID(S,G,L,S)

// --------------------
// Version information
// --------------------

// PRODUCT_VERSION_TGF or PRODUCT_VERSION_DEVELOPER
#define ForVersion			PRODUCT_VERSION_STANDARD

// Set this to the latest MMF build out when you build the object
#define	MinimumBuild		247

// --------------------
// Beta information
// --------------------

// #define BETA
// #define POPUP_ON_DROP
// #define POPUP_ON_EXE
// #define POPUP_ON_BUILD
// #define POPUP_MESSAGE	"This is a beta extension- use with caution!"

// --------------------
// Handling priority
// --------------------
// If this extension will handle windows messages, specify the priority
// of the handling procedure, 0 = low and 255 = very high

#define	WINDOWPROC_PRIORITY 100
