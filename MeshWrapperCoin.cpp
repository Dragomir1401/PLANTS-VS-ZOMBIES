#include "MeshWrapperCoin.hpp"

MeshWrapperCoin::MeshWrapperCoin(Mesh* mesh)
	: MeshWrapper(mesh)
{
}

MeshWrapperCoin::~MeshWrapperCoin()
{
}

void MeshWrapperCoin::setCoinWasCollected(bool value)
{
	coinWasCollected = value;
}

bool MeshWrapperCoin::getCoinWasCollected()
{
	return coinWasCollected;
}

void MeshWrapperCoin::setIsBigCoin(bool value)
{
	isBigCoin = value;
}

bool MeshWrapperCoin::getIsBigCoin()
{
	return isBigCoin;
}
