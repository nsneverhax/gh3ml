#include <GH3/CFunc.hpp>
#include <GH3/Keys.hpp>

#include <GH3/HashMapNode.hpp>

#include <GH3/Addresses.hpp>

#include <iostream>

bool SetNewWhammyValue(QbStruct* qbStruct)
{
	uint32_t kPlayerStatus = 0;

	qbStruct->GetKey(KEY_PLAYER_STATUS, kPlayerStatus, 1);

	//Nx::Global::KeySymbolHashTable::sGetStructValue?()
	QbStruct* playerStatus = reinterpret_cast<QbStruct* (__cdecl*)(uint32_t)>(0x004a5d70)(kPlayerStatus);

	float value = 0;

	if (!qbStruct->GetFloat(KEY_VALUE, value))
		return false;

	int player = 0;

	//float delta = (*DeltaTime * 60.0f);

	qbStruct->GetQbArrayItem(KEY_PLAYER, &player);

	HashMapNode* whammyNode = reinterpret_cast<HashMapNode *(__cdecl*)(uint32_t)>(0x004a5e00)(player != 1 ? KEY_WHAMMYWIBBLE1 : KEY_WHAMMYWIBBLE0);
	//
	float whammyWibbleValue = *reinterpret_cast<float*>(&whammyNode->Value);

	//
	//whammyWibbleValue *= delta;

	float timeRemaining = 0;
	float highwaySpeed = 0;

	qbStruct->GetFloat(KEY_TIME_REMAINING, timeRemaining);
	if (!playerStatus->GetFloat(KEY_HIGHWAY_SPEED, highwaySpeed))
	{
		// stubbed function 004fc500
		highwaySpeed = 0;
	}

	// BUG: Divide by zero!
	float pvVar3 = (*reinterpret_cast<float*>(0x00a12fb8)) / highwaySpeed;

	if (pvVar3 < 0.0f)
		pvVar3 *= -1.0f;

	float fVar2 = ((whammyWibbleValue / pvVar3) * timeRemaining * 0.001) + 2;
	highwaySpeed = fVar2;

	int whammySpeed = (float)reinterpret_cast<uint32_t(__cdecl*)(uint32_t)>(0x004a5960)(KEY_WHAMMY_WIBBLE_SPEED);


	if (whammyWibbleValue < fVar2)
	{
		fVar2 = whammyWibbleValue;
		highwaySpeed = whammyWibbleValue;
	}

	float fVar3 = whammySpeed;

	if (whammySpeed < 1.0f)
		fVar3 = 1.0f;

	if (fVar2 - fVar3 < 0)
	{
		fVar2 = fVar3;
		highwaySpeed = fVar3;
	}

	int iVar6 = (int)fVar2 + -1;


	float(__thiscall * FUN_0055e2e0)(void*, int, float) = reinterpret_cast<float(__thiscall *)(void*, int, float)>(0x0055e2e0);

	if (whammySpeed <= iVar6)
	{
		float iVar5 = iVar6 - whammySpeed;

		do
		{
			float fVar7 = reinterpret_cast<float(__thiscall*)(void*, int)>(0x0055e450)(whammyNode, iVar5);
			FUN_0055e2e0(whammyNode, iVar6, fVar7);
			iVar6--;
			iVar5--;
			fVar2 = highwaySpeed;
		} while (whammySpeed <= iVar6);
	}


	iVar6 = 0;

	pvVar3 = whammyWibbleValue;

	if (0 < whammySpeed)
	{
		
		do
		{
			FUN_0055e2e0(whammyNode, iVar6, value); // set whammy size
			iVar6 += 1;
			pvVar3 = whammyWibbleValue;
		} while (iVar6 < whammySpeed);
	}

	float fVar6 = 0;
	for (; fVar6 = whammyWibbleValue, fVar2 < whammyWibbleValue; fVar2++)
	{
		whammyWibbleValue = pvVar3;

		FUN_0055e2e0(whammyNode, fVar2, 1.0); // speed
		pvVar3 = whammyWibbleValue;
		whammyWibbleValue = fVar6;
	}

	return true;
}