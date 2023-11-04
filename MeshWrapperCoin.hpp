#include "lab_m1/tema1/MeshWrapper.hpp"


class MeshWrapperCoin : public MeshWrapper {

public:
	MeshWrapperCoin(Mesh* mesh);
	~MeshWrapperCoin();
	void setCoinWasCollected(bool value);
	bool getCoinWasCollected();
	void setIsBigCoin(bool value);
	bool getIsBigCoin();

protected:
	bool coinWasCollected = false;
	bool isBigCoin = false;
};