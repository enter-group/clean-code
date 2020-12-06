#include "Joypad.h"

#include <Carbon/Carbon.h>
#import <Cocoa/Cocoa.h>

using namespace OIS;
using namespace std;

namespace InputLib
{

Joypad::Joypad(uint8_t maxDevices)
    : maxDevices(maxDevices)
{
	joypads = new JoyStick*[maxDevices];
	numberOfPlayers = 0;
}

uint8_t Joypad::GetNumberOfDetectedPlayers()
{
	return numberOfPlayers;
}

Joypad::~Joypad()
{
	delete[] joypads;
	joypads = nullptr;

	inputManager = nullptr;
}

InputEvent Joypad::ReadButtons(uint8_t playerIndex)
{
	InputException ex("The controller index is invalid.");
	if (joypads[playerIndex] == nullptr)
		throw ex;
	else
		return AcquireJoypadInput(playerIndex);
}

InputEvent Joypad::AcquireJoypadInput(uint8_t index)
{
	joypads[index]->capture();

	auto aButton = ReadJoypadButtons(index).data()[static_cast<int>(Button::ButtonA)];
	auto bButton = ReadJoypadButtons(index).data()[static_cast<int>(Button::ButtonB)];
	auto cButton = ReadJoypadButtons(index).data()[static_cast<int>(Button::ButtonC)]; 
	auto startButton = ReadJoypadButtons(index).data()[static_cast<int>(Button::ButtonStart)];
	auto verticalAxis = ReadJoypadAxis(index).data()[static_cast<int>(Axis::Vertical)];
	auto horizontalAxis = ReadJoypadAxis(index).data()[static_cast<int>(Axis::Horizontal)];

	InputEvent event = {index, 
						aButton,
						bButton,
						cButton,
						startButton,
						horizontalAxis,
						verticalAxis
						};
	return event;
}

array<int, 6> Joypad::ReadJoypadAxis(uint8_t index)
{
	array<int, 6> axis;
	const JoyStickState& joy = joypads[index]->getJoyStickState();
	for(unsigned int i = 0; i < joy.mAxes.size(); ++i)
		if (joy.mAxes[i].abs >= -32768 && joy.mAxes[i].abs <= 32768)
			axis[i] = joy.mAxes[i].abs;

	return axis;
}

array<bool, 10> Joypad::ReadJoypadButtons(uint8_t index)
{
	array<bool, 10> buttons;
	const JoyStickState& joy = joypads[index]->getJoyStickState();
	for(unsigned int i = 0; i < joy.mButtons.size(); ++i)
		if (joy.mButtons[i])
			buttons[i] = true;
		else
			buttons[i] = false;

	return buttons;
}

void Joypad::InitializeJoypad()
{
	CreateNativeWindow();
	InitializeInputManager(windowHandle);
	CreateJoypads();
}

void Joypad::InitializeInputManager(size_t windowHandle)
{
	ParamList pl;
	pl.insert(std::make_pair("WINDOW", std::to_string((size_t)windowHandle)));
	this->inputManager = InputManager::createInputSystem(pl);
	this->inputManager->enableAddOnFactory(InputManager::AddOn_All);
}

void Joypad::CreateJoypads()
{
	for(int i = 0; i < maxDevices; i++)
		try
		{
			joypads[i] = (JoyStick*)inputManager->createInputObject(OISJoyStick, false);
			numberOfPlayers++;
		}
		catch(OIS::Exception& ex) 
		{
			joypads[i] = nullptr;
			continue;
		}
}

size_t GetWindowId()
{
	id window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 200, 200) styleMask:NSWindowStyleMaskTitled backing:NSBackingStoreBuffered defer:NO] autorelease];
	[window cascadeTopLeftFromPoint:NSMakePoint(20, 20)];
	[window setTitle:@"OIS Input"];
	[window makeKeyAndOrderFront:nil];
	[NSApp activateIgnoringOtherApps:YES];

	return (size_t)(window);
}

size_t InstantiateWindow(NSApplication* NSApp, NSMenu* appMenu, id appName)
{
	id quitTitle = [@"Quit " stringByAppendingString:appName];
	id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
	[appMenu addItem:quitMenuItem];

	return (size_t)GetWindowId();
}

size_t InstantiateNSApp(NSApplication* NSApp)
{
	id appMenu = [[NSMenu new] autorelease];
	id appName = [[NSProcessInfo processInfo] processName];

	return (size_t)InstantiateWindow(NSApp, appMenu, appName);
}

void Joypad::CreateNativeWindow()
{
	[NSAutoreleasePool new];
	[NSApplication sharedApplication];
	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
	windowHandle = (size_t)InstantiateNSApp(NSApp);
}

}