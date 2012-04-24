/*
 * lolapp.cpp
 *
 *  Created on: 23 apr. 2012
 *      Author: Jan
 */

#include "lolapp.h"

/**
 * The application class.
 */

LolApp::LolApp() :
	mPhoneGapMessageHandler(getWebView()),
	mNativeUIMessageHandler(getWebView()),
	mResourceMessageHandler(getWebView())
{
	maScreenSetOrientation(SCREEN_ORIENTATION_DYNAMIC);
	// Extract files in LocalFiles folder to the device.
	extractFileSystem();

	// Enable message sending from JavaScript to C++.
	enableWebViewMessages();

	// Show the WebView that contains the HTML/CSS UI
	// and the JavaScript code.
	getWebView()->setVisible(true);

	MAExtent scrSize = maGetScrSize();

	int width = EXTENT_X(scrSize);
	int height = EXTENT_Y(scrSize);

	// The page in the "LocalFiles" folder to
	// show when the application starts.
	showPage("index.html");
	// Send the Device Screen size to JavaScript.
	char buf[512];
	sprintf(buf, "{mosyncScreenWidth=%d; mosyncScreenHeight = %d;}", width, height);
	callJS(buf);

	WebView* webview = this->getWebView();
	ContentHandler* contentHandler = new ContentHandler(webview);
	this->addIdleListener(contentHandler);

	// Set the beep sound. This is defined in the
	// Resources/Resources.lst file. You can change
	// this by changing the sound file in that folder.
	mPhoneGapMessageHandler.setBeepSound(BEEP_WAV);

	// Initialize PhoneGap.
	mPhoneGapMessageHandler.initializePhoneGap();
}

/**
 * This method is called when a key is pressed.
 * Forwards the event to PhoneGapMessageHandler.
 */
void LolApp::keyPressEvent(int keyCode, int nativeCode)
{
	// Forward to PhoneGap MessageHandler.
	mPhoneGapMessageHandler.processKeyEvent(keyCode, nativeCode);
}

/**
 * This method handles messages sent from the WebView.
 *
 * Note that the data object will be valid only during
 * the life-time of the call of this method, then it
 * will be deallocated.
 *
 * @param webView The WebView that sent the message.
 * @param urlData Data object that holds message content.
 */
void LolApp::handleWebViewMessage(WebView* webView, MAHandle data)
{
	// Uncomment to print message data for debugging.
	// You need to build the project in debug mode for
	// the log output to be displayed.
	//printMessage(data);

	// Check the message protocol.
	MessageProtocol protocol(data);
	if (protocol.isMessageStreamJSON())
	{
		handleMessageStreamJSON(webView, data);
	}
	else if (protocol.isMessageStream())
	{
		handleMessageStream(webView, data);
	}
	else
	{
		lprintfln("@@@ MOSYNC: Undefined message protocol");
	}
}

/**
 * Handles JSON messages. This is used by PhoneGap.
 *
 * You can send your own messages from JavaScript and handle them here.
 *
 * @param webView A pointer to the web view posting this message.
 * @param data The raw encoded JSON message array.
 */
void LolApp::handleMessageStreamJSON(WebView* webView, MAHandle data)
{
	// Create the message object. This parses the message data.
	// The message object contains one or more messages.
	JSONMessage message(webView, data);

	// Loop through messages.
	while (message.next())
	{
		// This detects the PhoneGap protocol.
		if (message.is("PhoneGap")) {
			mPhoneGapMessageHandler.handlePhoneGapMessage(message);
		}
		// Here we add our own messages. See index.html for
		// the JavaScript code used to send the message.
		else if (message.is("Custom")) {
			String command = message.getParam("command");
			if (command == "vibrate") {

			}
		}
	}
}

	/**
	 * Handles string stream messages (generally faster than JSON messages).
	 * This is used by the JavaScript NativeUI system.
	 *
	 * You can send your own messages from JavaScript and handle them here.
	 *
	 * @param webView A pointer to the web view posting this message.
	 * @param data The raw encoded stream of string messages.
	 */
void LolApp::handleMessageStream(WebView* webView, MAHandle data)
{
	// Create a message stream object. This parses the message data.
	// The message object contains one or more strings.
	MessageStream stream(webView, data);

	// Pointer to a string in the message stream.
	const char* p;

	// Process messages while there are strings left in the stream.
	while (p = stream.getNext())
	{
		if (0 == strcmp(p, "NativeUI"))
		{
			//Forward NativeUI messages to the respective message handler
			mNativeUIMessageHandler.handleMessage(stream);
		}
		else if (0 == strcmp(p, "Resource"))
		{
			//Forward Resource messages to the respective message handler
			mResourceMessageHandler.handleMessage(stream);
		}
		else if (0 == strcmp(p, "close"))
		{
			// Close the application (calls method in class Moblet).
			close();
		}
		//Custom commands
		else if (0 == strcmp(p, "Custom")) {
			const char* command = stream.getNext();
			if (NULL != command) {
				if(0 == strcmp(command, "beep")) {
					close();
				}
			}
		}
	}
}



