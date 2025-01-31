#include <GH3/CFunc.hpp>
#include <GH3/Keys.hpp>

#include <GH3/Node.hpp>

#include <GH3/HashMapNode.hpp>

bool SetNewWhammyValue(QbStruct* qbStruct)
{
	uint32_t kPlayerStatus = 0;

	qbStruct->GetKey(KEY_PLAYER_STATUS, kPlayerStatus, 1);

	//Nx::Global::KeySymbolHashTable::sGetStructValue?()
	QbStruct* playerStatus = reinterpret_cast<QbStruct* (__cdecl*)(uint32_t)>(0x004a5d70)(kPlayerStatus);

	char cVar2 = -0x35;

	if (cVar2 == '\0')
		return false;

	float value = 0;

	if (!qbStruct->GetFloat(KEY_VALUE, value))
		return false;

	int player = 0;

	qbStruct->GetQbArrayItem(KEY_PLAYER, &player);

	void* node = reinterpret_cast<void*(__cdecl*)(uint32_t)>(0x004a5e00)(player != 1 ? KEY_WHAMMYWIBBLE1 : KEY_WHAMMYWIBBLE0);

	int32_t whammyWibbleValue = *(reinterpret_cast<int32_t*>(node) + 0x04);


	float timeRemaining = 0;
	float highwaySpeed = 0;

	qbStruct->GetFloat(KEY_TIME_REMAINING, timeRemaining);
	if (!playerStatus->GetFloat(KEY_HIGHWAY_SPEED, highwaySpeed))
	{
		// stubbed function 004fc500
		highwaySpeed = 0;
	}

	// BUG: Divide by zero!
	float fVar1 = (*reinterpret_cast<float*>(0x00a12fb8)) / highwaySpeed;

	if (fVar1 < 0.0f)
		fVar1 = fVar1 * -1.0f;

	float fVar2 = (((float)whammyWibbleValue / fVar1) * timeRemaining * 0.0001) + 2.0;

	int whammySpeed = reinterpret_cast<uint32_t(__cdecl*)(uint32_t)>(0x004a5960)(KEY_WHAMMY_WIBBLE_SPEED);

	if (whammyWibbleValue < fVar1)
	{
		fVar1 = whammyWibbleValue;
		highwaySpeed = whammyWibbleValue;
	}

	float fVar3 = whammySpeed;

	if (whammySpeed < 1)
		fVar3 = 1;

	if (fVar1 - fVar3 < 0)
	{
		fVar1 = fVar3;
		highwaySpeed = whammyWibbleValue;
	}

	int iVar1 = fVar1 + -1;


	float(__thiscall * FUN_0055e2e0)(void*, int, float) = reinterpret_cast<float(__thiscall *)(void*, int, float)>(0x0055e2e0);

	if (whammySpeed < iVar1)
	{
		int iVar2 = iVar1 - whammySpeed;

		do
		{
			float fVar4 = reinterpret_cast<float(__thiscall*)(void*, int)>(0x0055e450)(node, iVar2);
			FUN_0055e2e0(node, iVar2, fVar4);
			iVar1--;
			iVar2--;
			fVar1 = highwaySpeed;
		} while (whammySpeed <= iVar1);
	}

	iVar1 = 0;

	auto fVar5 = whammyWibbleValue;

	if (0 < whammySpeed)
	{
		do
		{
			FUN_0055e2e0(node, iVar1, value);
			iVar1 += 1;
			fVar5 = whammyWibbleValue;
		} while (iVar1 < whammySpeed);
	}

	float fVar6 = 0;

	for (; fVar6 = whammyWibbleValue, fVar1 < whammyWibbleValue; fVar1++)
	{
		whammyWibbleValue = fVar5;

		FUN_0055e2e0(node, fVar1, 1);
		fVar5 = whammyWibbleValue;
		whammyWibbleValue = fVar6;
	}

	return true;
}