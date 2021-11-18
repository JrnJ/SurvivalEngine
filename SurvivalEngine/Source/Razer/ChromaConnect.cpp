#define USE_ARRAY_EFFECTS true

#include "ChromaConnect.hpp"

#include <iostream>
#include <tchar.h>
#include <array>

// Statics maybe change later to be in .h
static ChromaSDK::FChromaSDKScene _sScene;

// Uhh
int* colorsChromaLink;
int* colorsHeadset;
int* colorsKeyboard;
int* colorsKeypad;
int* colorsMouse;
int* colorsMousepad;

ChromaConnect::ChromaConnect(bool initialize)
	: ChromaEnabled(true)
{
	// setup scene
	_sScene = ChromaSDK::FChromaSDKScene();

	if (initialize)
		this->Init();
	else
		ChromaEnabled = false;
}

ChromaConnect::~ChromaConnect()
{
	if (this->ChromaEnabled)
	{
		ChromaSDK::ChromaAnimationAPI::StopAll();
		ChromaSDK::ChromaAnimationAPI::CloseAll();
		RZRESULT result = ChromaSDK::ChromaAnimationAPI::Uninit();

		if (result != RZRESULT_SUCCESS)
		{
			std::cout << "Failed to uninitialize ChromaAnimationAPI!" << std::endl;
		}

		delete[] colorsChromaLink;
		delete[] colorsHeadset;
		delete[] colorsKeyboard;
		delete[] colorsKeypad;
		delete[] colorsMouse;
		delete[] colorsMousepad;
	}
}

/// <summary>
/// Initialize ChromaAnimationAPI
/// </summary>
void ChromaConnect::Init()
{
	std::cout << std::endl << "Razer ChromaConnect:" << std::endl << "Initializing ChromaConnect..." << std::endl;

	if (ChromaSDK::ChromaAnimationAPI::InitAPI() != 0)
	{
		std::cout << "(!) Failed to initialize ChromaAnimationAPI" << std::endl;
		this->ChromaEnabled = false;
	}
	else
	{
		std::cout << "Succesful initialization of ChromaAnimationAPI" << std::endl;

		ChromaSDK::APPINFOTYPE appInfo = {};

		_tcscpy_s(appInfo.Title, 256, _T("Survival Engine"));
		_tcscpy_s(appInfo.Description, 1024, _T("Survival Engine made in C++"));
		_tcscpy_s(appInfo.Author.Name, 256, _T("Jeroen"));
		_tcscpy_s(appInfo.Author.Contact, 256, _T("https://jeroenj.com"));

		// Supported Devices
		appInfo.SupportedDevice = (0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20);

		// Application Category
		appInfo.Category = 2;

		RZRESULT result = ChromaSDK::ChromaAnimationAPI::InitSDK(&appInfo);
		if (result != RZRESULT_SUCCESS)
		{
			std::cout << "(!) Failed to initialize ChromaAnimationAPI SDK!" << std::endl;
			ChromaEnabled = false;
		}
		else
		{
			// This is akward lol
			Sleep(100);

			// Setup variables
			_sizeChromaLink = GetColorArraySize1D(ChromaSDK::EChromaSDKDevice1DEnum::DE_ChromaLink);
			_sizeHeadset = GetColorArraySize1D(ChromaSDK::EChromaSDKDevice1DEnum::DE_Headset);
			_sizeKeyboard = GetColorArraySize2D(ChromaSDK::EChromaSDKDevice2DEnum::DE_Keyboard);
			_sizeKeypad = GetColorArraySize2D(ChromaSDK::EChromaSDKDevice2DEnum::DE_Keypad);
			_sizeMouse = GetColorArraySize2D(ChromaSDK::EChromaSDKDevice2DEnum::DE_Mouse);
			_sizeMousepad = GetColorArraySize1D(ChromaSDK::EChromaSDKDevice1DEnum::DE_Mousepad);

			colorsChromaLink = new int[_sizeChromaLink];
			colorsHeadset = new int[_sizeHeadset];
			colorsKeyboard = new int[_sizeKeyboard];
			colorsKeypad = new int[_sizeKeypad];
			colorsMouse = new int[_sizeMouse];
			colorsMousepad = new int[_sizeMousepad];

			std::cout << "Succesfully initialized ChromaConnect" << std::endl << std::endl;
		}
	}
}

/// <summary>
/// Disable or enable Chroma Connect
/// </summary>
/// <param name="active">Activate or deactivate</param>
void ChromaConnect::SetActive(bool state)
{

}

const int ChromaConnect::GetColorArraySize1D(ChromaSDK::EChromaSDKDevice1DEnum device)
{
	const int maxLeds = ChromaSDK::ChromaAnimationAPI::GetMaxLeds((int)device);
	return maxLeds;
}

const int ChromaConnect::GetColorArraySize2D(ChromaSDK::EChromaSDKDevice2DEnum device)
{
	const int maxRow = ChromaSDK::ChromaAnimationAPI::GetMaxRow((int)device);
	const int maxColumn = ChromaSDK::ChromaAnimationAPI::GetMaxColumn((int)device);
	return maxRow * maxColumn;
}

int ChromaConnect::GetKeyColorIndex(int row, int column)
{
	return ChromaSDK::Keyboard::MAX_COLUMN * row + column;
}

void ChromaConnect::SetKeyColor(int* colors, int rzkey, int color)
{
	int row = HIBYTE(rzkey);
	int column = LOBYTE(rzkey);
	colors[ChromaConnect::GetKeyColorIndex(row, column)] = color;
}

void ChromaConnect::SetStaticColor(int* colors, int color, int size)
{
	for (int i = 0; i < size; ++i)
	{
		colors[i] = color;
	}
}

void ChromaConnect::Clear()
{
	SetStaticColor(colorsKeyboard, _sAmbientColor, _sizeKeyboard);
}

void ChromaConnect::Draw()
{
	ChromaSDK::ChromaAnimationAPI::SetCustomColorFlag2D((int)ChromaSDK::EChromaSDKDevice2DEnum::DE_Keyboard, colorsKeyboard);
	ChromaSDK::ChromaAnimationAPI::SetEffectKeyboardCustom2D((int)ChromaSDK::EChromaSDKDevice2DEnum::DE_Keyboard, colorsKeyboard);
}

void ChromaConnect::Test()
{
	// Get needed keys
	int keys[] = {
		ChromaSDK::Keyboard::RZKEY::RZKEY_W,
		ChromaSDK::Keyboard::RZKEY::RZKEY_S,
		ChromaSDK::Keyboard::RZKEY::RZKEY_A,
		ChromaSDK::Keyboard::RZKEY::RZKEY_D,

		ChromaSDK::Keyboard::RZKEY::RZKEY_F1,
		ChromaSDK::Keyboard::RZKEY::RZKEY_F2
	};
	int keysLength = sizeof(keys) / sizeof(int);

	// Loop through keys
	for (int i = 0; i < keysLength; ++i)
	{
		int color = ChromaSDK::ChromaAnimationAPI::GetRGB(0, 255, 255);
		int key = keys[i];
		ChromaConnect::SetKeyColor(colorsKeyboard, key, color);
	}
}

void ChromaConnect::Inventory(int selectedKey)
{
	// Get needed keys
	int keys[] = {
		ChromaSDK::Keyboard::RZKEY::RZKEY_1,
		ChromaSDK::Keyboard::RZKEY::RZKEY_2,
		ChromaSDK::Keyboard::RZKEY::RZKEY_3,
		ChromaSDK::Keyboard::RZKEY::RZKEY_4,
		ChromaSDK::Keyboard::RZKEY::RZKEY_5,
		ChromaSDK::Keyboard::RZKEY::RZKEY_6,
		ChromaSDK::Keyboard::RZKEY::RZKEY_7,
		ChromaSDK::Keyboard::RZKEY::RZKEY_8,
		ChromaSDK::Keyboard::RZKEY::RZKEY_9
	};
	int keysLength = sizeof(keys) / sizeof(int);

	// Loop through keys
	for (int i = 0; i < keysLength; ++i)
	{
		int color = ChromaSDK::ChromaAnimationAPI::GetRGB(0, 255, 255);
		if (i == selectedKey)
			color = ChromaSDK::ChromaAnimationAPI::GetRGB(255, 255, 255);

		int key = keys[i];
		ChromaConnect::SetKeyColor(colorsKeyboard, key, color);
	}
}