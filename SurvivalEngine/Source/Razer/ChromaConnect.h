#ifndef CHROMACONNECT_H
#define CHROMACONNECT_H

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