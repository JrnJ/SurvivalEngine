#ifndef CHROMACONNECT_HPP
#define CHROMACONNECT_HPP

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
	void SingleColor(/*int* colors, int color, int size*/);
	void SetActive(bool state);
};

#endif 