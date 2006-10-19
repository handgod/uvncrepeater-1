//  Copyright (C) 2002 RealVNC Ltd. All Rights Reserved.
//  Copyright (C) 1999 AT&T Laboratories Cambridge. All Rights Reserved.
//
//  This file is part of the VNC system.
//
//  The VNC system is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
//  USA.
//
// If the source code for the VNC system is not available from the place 
// whence you received this file, check http://www.uk.research.att.com/vnc or contact
// the authors on vnc@uk.research.att.com for information on obtaining it.


// vncAbout.cpp

// Implementation of the About dialog!

#include "stdhdrs.h"

#include "WinVNC.h"
#include "vncAbout.h"

int wdd=0;
int htd=0;

HBITMAP
    DoGetBkGndBitmap3(IN CONST UINT uBmpResId )
    {
        static HBITMAP hbmBkGnd = NULL;
        if (NULL == hbmBkGnd)
        {
            hbmBkGnd = (HBITMAP)LoadImage(NULL, "enter.bmp", IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE); 
			BITMAPINFOHEADER h2;
			h2.biSize=sizeof(h2);
			h2.biBitCount=0;
			// h2.biWidth=11; h2.biHeight=22; h2.biPlanes=1;
			HDC hxdc=CreateDC("DISPLAY",NULL,NULL,NULL);  
			GetDIBits(hxdc, hbmBkGnd, 0, 0, NULL, (BITMAPINFO*)&h2, DIB_RGB_COLORS);
			wdd=h2.biWidth; htd=h2.biHeight;
			DeleteDC(hxdc);
			//hbmBkGnd = (HBITMAP)LoadImage(
              //  GetModuleHandle(NULL), MAKEINTRESOURCE(uBmpResId),
                //    IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

            if (NULL == hbmBkGnd)
                hbmBkGnd = (HBITMAP)-1;
        }
        return (hbmBkGnd == (HBITMAP)-1)
            ? NULL : hbmBkGnd;
    }
BOOL
    DoSDKEraseBkGnd3(
        IN CONST HDC hDC,
        IN CONST COLORREF crBkGndFill
      )
    {
        HBITMAP hbmBkGnd = DoGetBkGndBitmap3(IDB_LOGO64);
        if (hDC && hbmBkGnd)
        {
            RECT rc;
            if ((ERROR != GetClipBox(hDC, &rc)) && !IsRectEmpty(&rc))
            {
                HDC hdcMem = CreateCompatibleDC(hDC);
                if (hdcMem)
                {
                    HBRUSH hbrBkGnd = CreateSolidBrush(crBkGndFill);
                    if (hbrBkGnd)
                    {
                        HGDIOBJ hbrOld = SelectObject(hDC, hbrBkGnd);
                        if (hbrOld)
                        {
                            SIZE size = {
                                (rc.right-rc.left), (rc.bottom-rc.top)
                            };

                            if (PatBlt(hDC, rc.left, rc.top, size.cx, size.cy, PATCOPY))
                            {
                                HGDIOBJ hbmOld = SelectObject(hdcMem, hbmBkGnd);
                                if (hbmOld)
                                {
                                    StretchBlt(hDC, rc.left, rc.top, size.cx, size.cy,
                                        hdcMem, rc.left, rc.top,wdd,htd, SRCCOPY);
                                    SelectObject(hdcMem, hbmOld);
                                }
                            }
                            SelectObject(hDC, hbrOld);
                        }
                        DeleteObject(hbrBkGnd);
                    }
                    DeleteDC(hdcMem);
                }
            }
			return TRUE;
        }
        return false;
    }

HBITMAP
    DoGetBkGndBitmap(IN CONST UINT uBmpResId )
    {
        static HBITMAP hbmBkGnd = NULL;
        if (NULL == hbmBkGnd)
        {
            hbmBkGnd = (HBITMAP)LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE); 
			//hbmBkGnd = (HBITMAP)LoadImage(
              //  GetModuleHandle(NULL), MAKEINTRESOURCE(uBmpResId),
                //    IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

            if (NULL == hbmBkGnd)
                hbmBkGnd = (HBITMAP)-1;
        }
        return (hbmBkGnd == (HBITMAP)-1)
            ? NULL : hbmBkGnd;
    }
BOOL
    DoSDKEraseBkGnd(
        IN CONST HDC hDC,
        IN CONST COLORREF crBkGndFill
      )
    {
        HBITMAP hbmBkGnd = DoGetBkGndBitmap(IDB_LOGO64);
        if (hDC && hbmBkGnd)
        {
            RECT rc;
            if ((ERROR != GetClipBox(hDC, &rc)) && !IsRectEmpty(&rc))
            {
                HDC hdcMem = CreateCompatibleDC(hDC);
                if (hdcMem)
                {
                    HBRUSH hbrBkGnd = CreateSolidBrush(crBkGndFill);
                    if (hbrBkGnd)
                    {
                        HGDIOBJ hbrOld = SelectObject(hDC, hbrBkGnd);
                        if (hbrOld)
                        {
                            SIZE size = {
                                (rc.right-rc.left), (rc.bottom-rc.top)
                            };

                            if (PatBlt(hDC, rc.left, rc.top, size.cx, size.cy, PATCOPY))
                            {
                                HGDIOBJ hbmOld = SelectObject(hdcMem, hbmBkGnd);
                                if (hbmOld)
                                {
                                    StretchBlt(hDC, rc.left, rc.top, size.cx, size.cy,
                                        hdcMem, rc.left, rc.top,1,283, SRCCOPY);
                                    SelectObject(hdcMem, hbmOld);
                                }
                            }
                            SelectObject(hDC, hbrOld);
                        }
                        DeleteObject(hbrBkGnd);
                    }
                    DeleteDC(hdcMem);
                }
            }
			return TRUE;
        }
        return false;
    }

// Constructor/destructor
vncAbout::vncAbout()
{
	m_dlgvisible = FALSE;
}

vncAbout::~vncAbout()
{
}

// Initialisation
BOOL
vncAbout::Init()
{
	return TRUE;
}

// Dialog box handling functions
void
vncAbout::Show(BOOL show)
{
	if (show)
	{
		if (!m_dlgvisible)
		{
			DialogBoxParam(hAppInstance,
				MAKEINTRESOURCE(IDD_ABOUT), 
				NULL,
				(DLGPROC) DialogProc,
				(LONG) this);
		}
	}
}

BOOL CALLBACK
vncAbout::DialogProc(HWND hwnd,
					 UINT uMsg,
					 WPARAM wParam,
					 LPARAM lParam )
{
	// We use the dialog-box's USERDATA to store a _this pointer
	// This is set only once WM_INITDIALOG has been recieved, though!
	vncAbout *_this = (vncAbout *) GetWindowLong(hwnd, GWL_USERDATA);

	switch (uMsg)
	{

	case WM_INITDIALOG:
		{
			// Retrieve the Dialog box parameter and use it as a pointer
			// to the calling vncProperties object
			SetWindowLong(hwnd, GWL_USERDATA, lParam);
			_this = (vncAbout *) lParam;

			// Insert the build time information
			extern char buildtime[];
			SetDlgItemText(hwnd, IDC_BUILDTIME, buildtime);

			// Show the dialog
			SetForegroundWindow(hwnd);

			_this->m_dlgvisible = TRUE;

			return TRUE;
		}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case IDCANCEL:
		case IDOK:
			// Close the dialog
			EndDialog(hwnd, TRUE);

			_this->m_dlgvisible = FALSE;

			return TRUE;
		}

		break;

	case WM_DESTROY:
		EndDialog(hwnd, FALSE);
		_this->m_dlgvisible = FALSE;
		return TRUE;
	/*case WM_ERASEBKGND:
            {
                DoSDKEraseBkGnd((HDC)wParam, RGB(255,0,0));
				return true;
            }
	case WM_CTLCOLORSTATIC:
   {

    //GetStockObject(NULL_BRUSH);
    SetBkMode((HDC) wParam, TRANSPARENT);
	return (DWORD) GetStockObject(NULL_BRUSH);

   }*/
	}
	return 0;
}
