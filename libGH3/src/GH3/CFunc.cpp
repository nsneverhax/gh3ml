#include <GH3/CFunc.hpp>
#include <GH3/Keys.hpp>

#include <GH3/HashMapNode.hpp>

#include <GH3/Addresses.hpp>

#include <iostream>

#include <algorithm>

bool SetNewWhammyValue(QbStruct* qbStruct)
{
	bool bVar2;
	QbStruct* playerStatus;
	uint32_t whammyWibbleKey;
	void* whammyNode = nullptr;
	float whammySpeed;
	float pvVar4;
	float magicVar;
	int iVar5;
	uint32_t iVar6;
	float highwayRatio;
	float fVar7;
	float highwaySpeed;
	uint32_t kPlayerStatus;
	uint32_t player;
	float timeRemaining;
	float value;
	float whammyNodeKey2;
	void* whammyNodeKey = nullptr;
	float pvVar1;

	float(__thiscall * SetArrayValue)(void*, int, float) = reinterpret_cast<float(__thiscall*)(void*, int, float)>(0x0055e2e0);

	qbStruct->GetKey(KEY_PLAYER_STATUS, kPlayerStatus, 1);
	playerStatus = reinterpret_cast<QbStruct * (__cdecl*)(uint32_t)>(0x004a5d70)(kPlayerStatus);
	bVar2 = qbStruct->GetFloat(KEY_VALUE, value, 1);
	if (!bVar2)
	{
		return false;
	}
	qbStruct->GetQbArrayItem(KEY_PLAYER, &player);
	whammyWibbleKey = KEY_WHAMMYWIBBLE0;
	if (player != 1)
	{
		whammyWibbleKey = KEY_WHAMMYWIBBLE1;
	}
	whammyNode = reinterpret_cast<void* (__cdecl*)(uint32_t)>(0x004a5e00)(whammyWibbleKey);


	whammyNodeKey = *(void**)(reinterpret_cast<uint32_t>(whammyNode) + 4);
	whammyNodeKey2 = (float)(int)(whammyNodeKey);

	qbStruct->GetFloat(KEY_TIME_REMAINING, timeRemaining, 1);

	//timeRemaining *= (*DeltaTime * 60.0f);

	bVar2 = Functions::GetTypedValue(playerStatus, KEY_HIGHWAY_SPEED, QbValueType::QTypeFloat, &highwaySpeed);

	if (!bVar2)
	{
		// Stubbed::FUN_004f6500((char)playerStatus, 0, 1);
		highwaySpeed = 0.0;
	}
	highwayRatio = (*reinterpret_cast<float*>(0x00a12fb8)) / highwaySpeed;

	if (highwayRatio < 0.0)
	{
		highwayRatio = highwayRatio * -1.0;
	}
	magicVar = (float)((int)(((float)(int)whammyNodeKey / highwayRatio) * timeRemaining * 0.001) + 2);
	// magicVar *= (*DeltaTime * 60.0f);
	highwaySpeed = magicVar;

	whammySpeed = ((float)reinterpret_cast<uint32_t(__cdecl*)(uint32_t)>(0x004a5960)(KEY_WHAMMY_WIBBLE_SPEED));
	if ((int)whammyNodeKey < (int)magicVar)
	{
		magicVar = (float)(int)whammyNodeKey;
		highwaySpeed = (float)(int)whammyNodeKey;
	}
	pvVar4 = whammySpeed;


	if ((int)whammySpeed < 1)
	{
		pvVar4 = 0x1;
	}
	if ((int)magicVar - (int)pvVar4 < 0)
	{
		magicVar = (float)(int)(pvVar4);
		highwaySpeed = (float)(int)(pvVar4);
	}
	iVar6 = (int)magicVar - 1;
	if ((int)whammySpeed <= (int)iVar6)
	{
		iVar5 = iVar6 - whammySpeed;
		do
		{
			fVar7 = reinterpret_cast<float(__thiscall*)(void*, int)>(0x0055e450)(whammyNode, iVar5);
			SetArrayValue(whammyNode, iVar6, (float)fVar7);
			iVar6 -= 1;
			iVar5 += -1;
			magicVar = highwaySpeed;
		} while ((int)whammySpeed <= (int)iVar6);
	}
	iVar5 = 0;
	highwayRatio = whammyNodeKey2;
	if (0 < (int)whammySpeed)
	{
		do
		{
			SetArrayValue(whammyNode, iVar5, value);
			iVar5 += 1;
			highwayRatio = whammyNodeKey2;
		} while (iVar5 < (int)whammySpeed);
	}
	for (; pvVar1 = whammyNodeKey2, (int)magicVar < (int)whammyNodeKey2; magicVar = (float)((int)magicVar + 1))
	{
		whammyNodeKey2 = highwayRatio;
		SetArrayValue(whammyNode, (int)magicVar, 1.0);
		highwayRatio = whammyNodeKey2;
		whammyNodeKey2 = pvVar1;
	}
	return true;
}
