#define USE_ARRAY_EFFECTS true

#include "ChromaConnect.hpp"

#include <iostream>
#include <tchar.h>
#include <array>

#include "ChromaAnimationAPI.h"
#include "ChromaSDKPluginTypes.h"
#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"

// Statics maybe change later to be in .h
static ChromaSDK::FChromaSDKScene _sScene;

static int _sAmbientColor = 0;

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

		_tcscpy_s(appInfo.Title, 256, _T("Platformer Engine"));
		_tcscpy_s(appInfo.Description, 1024, _T("Platformer Engine made in C++"));
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
			std::cout << "Succesfully initialized ChromaConnect" << std::endl << std::endl;
		}
	}
}

const int GetColorArraySize2D(ChromaSDK::EChromaSDKDevice2DEnum device)
{
	const int maxRow = ChromaSDK::ChromaAnimationAPI::GetMaxRow((int)device);
	const int maxColumn = ChromaSDK::ChromaAnimationAPI::GetMaxColumn((int)device);
	return maxRow * maxColumn;
}

/// <summary>
/// Disable or enable Chroma Connect
/// </summary>
/// <param name="active">Activate or deactivate</param>
void ChromaConnect::SetActive(bool state)
{

}

void ChromaConnect::SingleColor(/*int* colors, int color, int size*/)
{
	if (this->ChromaEnabled)
	{
		const int sizeKeyboard = GetColorArraySize2D(ChromaSDK::EChromaSDKDevice2DEnum::DE_Keyboard);
		int* colorsKeyboard = new int[sizeKeyboard];
		int* tempColorsKeyboard = new int[sizeKeyboard];

		for (int i = 0; i < sizeKeyboard; ++i)
		{
			colorsKeyboard[i] = _sAmbientColor;
		}
	}
}