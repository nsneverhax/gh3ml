#pragma once

#include <cstdint>

namespace GH3
{
	struct EngineParams
	{
		uint32_t TargetNTSCFramerate;
		uint32_t GPUVSyncTimeInterval;
		uint32_t PollTextInstances;
		uint32_t FrameBufferWidth;
		float DefaultFarPlaneDistance;
		uint32_t HardwareLetterBox;
		uint32_t NumSoundInstances;
		uint32_t NumStreamInstances;
		uint32_t MaxStreams;
		uint32_t MaxSoundEntries;
		uint32_t MaxSoundEffects;
		uint32_t SoundMemorySize;
		uint32_t MaxCScriptInstancesPerScript;
		uint32_t CPUSkinningBufferSize;
		uint32_t CPUSkinningBufferHistory;
		float ScreenSpaceWidth;
		float ScreenSpaceHeight;
		uint32_t JobQWorkerCount;
		uint32_t Member_0x50;
		uint32_t Member_0x54;
		uint32_t Member_0x58;
		uint32_t Member_0x5C;
		uint32_t Member_0x60;
		uint32_t Member_0x64;
		uint32_t Member_0x68;
		uint32_t Member_0x6C;

		uint32_t PrimaryRingBufferSize;
		uint32_t SecondaryRingBufferSize;
		uint32_t SegmentSize;

		static EngineParams* Instance()
		{
			return reinterpret_cast<EngineParams*>(0x00c62f18);
		}
	};
}