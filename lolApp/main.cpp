/**
 * @file main.cpp
 *
 * This template application shows how to extend the functionality
 * in HTML5/JS with custom code written in C++. See code below
 * for custom code added in methods handleMessageStreamJSON()
 * and handleMessageStream().
 *
 * When reading the code below, it is good to know that there are
 * two message formats: JSON and string streams. String streams are
 * generally faster. See comments in the code below for further details.
 * PhoneGap uses JSON messages, NativeUI uses string streams.
 */

#include <Wormhole/WebAppMoblet.h>
#include <Wormhole/MessageProtocol.h>
#include <Wormhole/MessageStream.h>
#include <Wormhole/Libs/JSONMessage.h>
#include <Wormhole/Libs/PhoneGap/PhoneGapMessageHandler.h>
#include <Wormhole/Libs/JSNativeUI/NativeUIMessageHandler.h>
#include <Wormhole/Libs/JSNativeUI/ResourceMessageHandler.h>
#include "lolapp.h"
#include "MAHeaders.h"
#include "contentHandler.h"

// Namespaces we want to access.
using namespace MAUtil; // Class Moblet
using namespace NativeUI; // WebView widget.
using namespace Wormhole; // Wormhole library.


/**
 * Main function that is called when the program starts.
 * Here an instance of the MyMoblet class is created and
 * the program enters the main event loop.
 */
extern "C" int MAMain()
{
	Moblet::run(new LolApp());
	return 0;
}
