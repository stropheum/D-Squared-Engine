// pch.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
//#include "targetver.h"
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers


/// Include headers
#include "windows.h"
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <string>
#include "RTTI.h"

#include "TypeState.h"
#include "IntegerState.h"
#include "FloatState.h"
#include "VectorState.h"
#include "MatrixState.h"
#include "StringState.h"
#include "PointerState.h"

#define CLM_FORCE_CXX98
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#pragma warning(pop)