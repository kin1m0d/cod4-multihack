


#include "KGameProcess.h"
#include "KDrawController.h"
#include "KHack.h"


int main()
{
	std::cout << "v1.0 - Call of Duty 4 Multihack\n\n" << std::endl;
	K_GameProcess lkCoD4("Call of Duty 4");

	if (lkCoD4.checkGameProcess())
	{
		std::cout << ">>> checkGameProcess = True" << std::endl;
		K_DrawController lkDraw(GetDC(lkCoD4.getGameWindowHandle()));
		K_Hack lkESP(lkCoD4.getProcessHandle(), lkDraw);
		lkESP.initHack();

		while (!GetAsyncKeyState(VK_F4))
		{
			lkESP.runHack();

			if (GetAsyncKeyState(VK_NUMPAD1))
			{
				lkESP.turnOnOff_Crosshair();
			}

			if (GetAsyncKeyState(VK_NUMPAD2))
			{
				lkESP.turnOnOff_ESP();
			}

			if (GetAsyncKeyState(VK_NUMPAD3))
			{
				lkESP.turnOnOff_HealthDistanceRange();
			}

			if (GetAsyncKeyState(VK_NUMPAD4))
			{
				lkESP.turnOnOff_Invincible();
			}

			if (GetAsyncKeyState(VK_NUMPAD5))
			{
				lkESP.turnOnOff_Snapline();
			}
			
			if (GetAsyncKeyState(VK_NUMPAD6))
			{
				lkESP.turnOnOff_Collision();
			}

			if (GetAsyncKeyState(VK_NUMPAD7))
			{
				lkESP.turnOnOff_SuperJump();
			}

			if (GetAsyncKeyState(VK_NUMPAD8))
			{
				lkESP.turnOnOff_HighSpeed();
			}


		}


	}
	else
	{
		std::cout << lkCoD4.getErrorMessage() << std::endl;
	}

	system("pause");
	return 0;
}





