#include "lab_m1/tema1/MeshWrapper.hpp"


class MeshWrapperCoin : public MeshWrapper {

public:
	MeshWrapperCoin(Mesh* mesh);
	~MeshWrapperCoin();
	void setCoinWasCollected(bool value);
	bool getCoinWasCollected();

protected:
	bool coinWasCollected = false;
};