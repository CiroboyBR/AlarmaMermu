/***************************************************************
 * Name:      TesteApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Ciro Martins Meneses (ciroccuva@hotmail.com)
 * Created:   2021-08-12
 * Copyright: Ciro Martins Meneses (www.ciroboybr.blogspot.com)
 * License:
 **************************************************************/

#include "TesteApp.h"

//(*AppHeaders
#include "TesteMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(TesteApp);

bool TesteApp::OnInit()
{

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	TesteFrame* Frame = new TesteFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
