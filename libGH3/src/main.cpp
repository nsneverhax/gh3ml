#include <GH3/Keys.hpp>
#include "../include/GH3/Qb.hpp"

#include <GH3/Misc.hpp>

#include "../include/GH3/CFunc.hpp"

#include <GH3/Script/ScriptCache.hpp>
#include <GH3/Mdl/Module.hpp>
#include <GH3/Mdl/Manager.hpp>


#include <GH3/Script/CPair.hpp>
#include <GH3/Script/CSymbolTableEntry.hpp>

#include <GH3/Lst/Head.hpp>
#include <GH3/Lst/Node.hpp>
#include <GH3/Lst/StringHashTable.hpp>

#include <GH3/Tsk/List.hpp>
#include <GH3/Tsk/BaseTask.hpp>
#include <GH3/Tsk/Task.hpp>

#include <GH3/Mem/Allocator.hpp>
#include <GH3/Mem/Heap.hpp>
#include <GH3/Mem/CCompactPool.hpp>
#include <GH3/Ass/CAssMan.hpp>

#include <GH3/Obj/CTracker.hpp>
#include <GH3/Qb/CArray.hpp>

#include <GH3/Front/CScreenElement.hpp>
#include <GH3/Front/CSpriteElement.hpp>

#include <GH3/Gfx/CDofPoissonFXPropsState.hpp>
#include <GH3/Gfx/CScreenFXPropsState.hpp>

GH3::Spt::SingletonPtr<GH3::Obj::CTracker> GH3::Obj_CTracker = { reinterpret_cast<GH3::Obj::CTracker*>(0x00b4f360) };
