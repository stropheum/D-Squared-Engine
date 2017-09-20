#pragma once

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN

/////////////////////////////
//  Project Dependencies  //
///////////////////////////
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <string>
#include <vector>
#include <future>
#include <sstream>

//////////////////////////
//  Local Dependencies //
////////////////////////
#include "RTTI.h"
#include "TypeState.h"
#include "IntegerState.h"
#include "FloatState.h"
#include "VectorState.h"
#include "MatrixState.h"
#include "StringState.h"
#include "PointerState.h"
#include "WorldState.h"
#include "ActionList.h"
#include "Entity.h"
#include "ScopeState.h"
#include "Scope.h"
#include "Action.h"
#include "EventSubscriber.h"
#include "EventPublisher.h"
#include "GameTime.h"
#include "Event.h"
#include "World.h"
#include "EventMessageAttributed.h"
#include "Vector.h"
#include "SharedDataScope.h"
#include "ActionListIf.h"
#include "IXmlParseHelper.h"


#define CLM_FORCE_CXX98
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#pragma warning(pop)