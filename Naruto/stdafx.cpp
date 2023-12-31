#pragma once

#ifndef WINVER 
#define WINVER 0x0600 
#endif

#ifndef _WIN32_WINNT  
#define _WIN32_WINNT 0x0600  
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif

#ifndef _WIN32_IE  
#define _WIN32_IE 0x0700 
#endif


#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용은 Windows 헤더에서 제외

#include <windows.h>


#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
