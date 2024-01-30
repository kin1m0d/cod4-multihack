

//#include "Utility.h"
//#include "KPlayer.h"


/*

bool 3Dto2D(K_Vector3D &WorldLocation, K_Vector3D &mm_fPlayerPosY)
{
	K_Vector3D vLocal, vTransForm;
	g_vForward = new K_Vector3D();
	g_vRight = new K_Vector3D();
	g_vUpward = new K_Vector3D();

	AngleVectors();
	
	K_Vector3D lol;

	vLocal = SubVectorDist(WorldLocation, mm_fPlayerPosY);


	vTransForm.x = vLocal.GetKreuzProdukt(*g_vRight);
	vTransForm.y = vLocal.GetKreuzProdukt(*g_vUpward);
	vTransForm.z = vLocal.GetKreuzProdukt(*g_vForward);

	if (vTransForm.z < 0.01)
		return False;

	g_fScreenX = g_iScreencenter[0] + (g_iScreencenter[0] / vTransForm.z * (1 / g_fov[0])) * vTransForm.x;
	g_fScreenY = g_iScreencenter[1] - (g_iScreencenter[1] / vTransForm.z * (1 / g_fov[1])) * vTransForm.y;

	return True;
}

K_Vector3D SubVectorDist(K_Vector3D &playerFrom, K_Vector3D &playerTo)
{
	return K_Vector3D(playerFrom.x - playerTo.x, playerFrom.y - playerTo.y, playerFrom.z - playerTo.z);
}



/// <summary>
/// One of Kn4cker's functions, this beauty does all our complex maths
/// if you want to know more about it get very comfortable with Pythagora
/// </summary>
void AngleVectors()
{
	float angle;
	float sr, sp, sy, cr, cp, cy,
		cpi = (3.141f * 2 / 360);

	angle = g_viewAngles.y * cpi;
	//cpi = same view angles.x isn't

	sy = (float)sin(angle);
	cy = (float)cos(angle);
	angle = g_viewAngles.x * cpi;
	sp = (float)sin(angle);
	cp = (float)cos(angle);
	angle = g_viewAngles.z * cpi;
	sr = (float)sin(angle);
	cr = (float)cos(angle);

	g_vForward->x = cp * cy;
	g_vForward->y = cp * sy;
	g_vForward->z = -sp;


	g_vRight->x = (-1 * sr * sp * cy + -1 * cr * -sy);
	g_vRight->y = (-1 * sr * sp * sy + -1 * cr * cy);
	g_vRight->z = -1 * sr * cp;


	g_vUpward->x = (cr * sp * cy + -sr * -sy);
	g_vUpward->y = (cr * sp * sy + -sr * cy);
	g_vUpward->z = cr * cp;
}



*/