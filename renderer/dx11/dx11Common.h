#ifndef RENDER_DX11_DX11_COMMON_H_
#define RENDER_DX11_DX11_COMMON_H_

#include <wrl.h>

#include <windows.h>

#include <dxerr.h>

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

#ifdef _DEBUG
// wchar converter for macros
#define __WCC2__(x) L##x
#define __WCC__(x) __WCC2__(x)
#define DX_CHK(x)\
{                                                          \
	HRESULT hr = (x);                                      \
	if(FAILED(hr))                                         \
	{                                                      \
		DXTrace(__WCC__(__FILE__), (DWORD)__LINE__, hr, L#x, true); \
	}                                                      \
}
#else
#define DX_CHK(x) x

#endif // _DEBUG


#endif // RENDER_DX11_DX11_COMMON_H_