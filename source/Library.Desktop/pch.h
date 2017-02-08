// pch.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers


/// Include headers
#include "windows.h"
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <string>
#include "RTTI.h"

#define CLM_FORCE_CXX98
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#pragma warning(pop)