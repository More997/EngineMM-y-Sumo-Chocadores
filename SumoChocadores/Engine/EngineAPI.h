#pragma once
#ifdef DLL_EXPORTS
#define IMPORTEXPORT __declspec(dllimport)
#else
#define IMPORTEXPORT __declspec(dllexport)
#endif