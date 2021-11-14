#ifndef CHROMACONNECT_HPP
#define CHROMACONNECT_HPP
#define NOMINMAX // Avoid std::min / std::max errors with windows.h

#include "ChromaAnimationAPI.h"
#include "ChromaSDKPluginTypes.h"
#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"

class ChromaConnect
{
public:
	// Properties
	bool ChromaEnabled;

	// Constructors
	ChromaConnect(bool initialize);
	~ChromaConnect();

	// Methods
	void Init();
	void SetActive(bool state);

	// Methods
	void Clear();
	void Draw();

	void Test();
	void Inventory(int selectedKey);

private:
	static const int _sAmbientColor = 0;

	int _sizeChromaLink = 0;
	int _sizeHeadset = 0;
	int _sizeKeyboard = 0;
	int _sizeKeypad = 0;
	int _sizeMouse = 0;
	int _sizeMousepad = 0;

	// Methods
	const int GetColorArraySize2D(ChromaSDK::EChromaSDKDevice2DEnum device);
	const int GetColorArraySize1D(ChromaSDK::EChromaSDKDevice1DEnum device);

	int GetKeyColorIndex(int row, int column);
	void SetKeyColor(int* colors, int rzkey, int color);
	void SetStaticColor(int* colors, int color, int size);
};

#endif 