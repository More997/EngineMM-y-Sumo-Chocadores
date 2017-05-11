#pragma once
#ifdef DLL_EXPORTS
#define IMPORTEXPORT __declspec(dllexport)
#else
#define IMPORTEXPORT __declspec(dllimport)
#endif