#include <iostream>
#include <set>
#include "ddraw.h"

// Screen resolution
typedef std::pair<int, int> DisplayMode;
// Collection of resolutions
typedef std::set<DisplayMode> DisplayModes;
// This function saves desired display mode to context
HRESULT WINAPI CallBackFunc(LPDDSURFACEDESC2 _surfaceDesc, LPVOID _context);

int main()
{
    // Get DirectDraw7 interface
    HRESULT result;
    IDirectDraw7* DDInterface;
    result = DirectDrawCreateEx( NULL,
                                 reinterpret_cast<LPVOID*>(&DDInterface),
                                 IID_IDirectDraw7,
                                 NULL );
    if ( result != DD_OK )
        // DirectDrawCreateEx failed
        return -1;

    // Surface description
    DDSURFACEDESC2 surfaceDesc;

    // Clean object
    ZeroMemory( &surfaceDesc, sizeof(surfaceDesc) );
    surfaceDesc.dwSize = sizeof(surfaceDesc);

    // Get display mode
    result = DDInterface->GetDisplayMode(&surfaceDesc);

    if ( result != DD_OK )
        // GetDisplayMode failed
        return -1;

    // Print display width and height
    std::cout << "Display width: "  << surfaceDesc.dwWidth  << std::endl
              << "Display height: " << surfaceDesc.dwHeight << std::endl;

    // Clean object
    ZeroMemory( &surfaceDesc, sizeof(surfaceDesc) );
    surfaceDesc.dwSize = sizeof(surfaceDesc);

    // Check modes with 32 color bit depth
    surfaceDesc.dwFlags = DDSD_PIXELFORMAT;
    surfaceDesc.ddpfPixelFormat.dwFlags = DDSD_DEPTH;
    surfaceDesc.ddpfPixelFormat.dwRGBBitCount = 32;

    // Collection for display widths and heights
    DisplayModes displayModes;
    result = DDInterface->EnumDisplayModes( DDEDM_REFRESHRATES,
                                            &surfaceDesc,
                                            &displayModes,
                                            CallBackFunc );

    if ( result != DD_OK )
        // EnumDisplayModes failed
        return -1;

    // Print all display modes, that support 32 color bit depth
    std::cout << "Display modes, that support 32 color bit depth:\n";
    for ( DisplayModes::const_iterator it = displayModes.begin();
          it != displayModes.end(); ++it )
        std::cout << it->first << " x " << it->second << "\t";

    // All OK
    return 0;
}


HRESULT WINAPI CallBackFunc(LPDDSURFACEDESC2 _surfaceDesc, LPVOID _context)
{
    // Get collection of display modes
    DisplayModes* displayModes = static_cast<DisplayModes*>(_context);

    // Add current mode to collection
    displayModes->insert( std::make_pair( _surfaceDesc->dwWidth,
                                            _surfaceDesc->dwHeight ) );
    // Continue
    return DDENUMRET_OK;
}