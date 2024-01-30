
#include "KVector3D.h"



/*
// Subtrahiert 2 Vektoren und gibt die Differenz davon zurück
K_Vector3D K_Vector3D::SubVectorDist(K_Vector3D &playerFrom, K_Vector3D &playerTo)
{
	return K_Vector3D(playerFrom.x - playerTo.x, playerFrom.y - playerTo.y, playerFrom.z - playerTo.z);
}
*/


K_Vector3D K_Vector3D::SubVectorDist(K_Vector3D &pkPlayer)
{
	return K_Vector3D(this->x - pkPlayer.x, this->y - pkPlayer.y, this->z - pkPlayer.z);
}






