/***************************************************************
 * Name:      TesteMain.h
 * Purpose:   Defines Application Frame
 * Author:    Ciro Martins Meneses (ciroccuva@hotmail.com)
 * Created:   2021-08-12
 * Copyright: Ciro Martins Meneses (www.ciroboybr.blogspot.com)
 * License:
 **************************************************************/

#ifndef TESTEMAIN_H
#define TESTEMAIN_H

//(*Headers(TesteFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/timer.h>
//*)

class TesteFrame: public wxFrame
{
    public:

        TesteFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~TesteFrame();
        void inicializaChecks();

    private:

        //(*Handlers(TesteFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnCheckBox17Click(wxCommandEvent& event);
        void OnCheckBox18Click(wxCommandEvent& event);
        void OnCheckBox1Click(wxCommandEvent& event);
        void OnCheckBox2Click(wxCommandEvent& event);
        void OnCheckBox3Click(wxCommandEvent& event);
        void OnCheckBox4Click(wxCommandEvent& event);
        void OnCheckBox5Click(wxCommandEvent& event);
        void OnCheckBox6Click(wxCommandEvent& event);
        void OnCheckBox7Click(wxCommandEvent& event);
        void OnCheckBox8Click(wxCommandEvent& event);
        void OnCheckBox9Click(wxCommandEvent& event);
        void OnCheckBox10Click(wxCommandEvent& event);
        void OnCheckBox11Click(wxCommandEvent& event);
        void OnCheckBox12Click(wxCommandEvent& event);
        void OnCheckBox13Click(wxCommandEvent& event);
        void OnCheckBox14Click(wxCommandEvent& event);
        void OnCheckBox15Click(wxCommandEvent& event);
        void OnCheckBox16Click(wxCommandEvent& event);
        void OnCheckBox19Click(wxCommandEvent& event);
        void OnCheckBox20Click(wxCommandEvent& event);
        void OnCheckBox21Click(wxCommandEvent& event);
        void OnCheckBox22Click(wxCommandEvent& event);
        void OnCheckBox23Click(wxCommandEvent& event);
        void OnCheckBox24Click(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(TesteFrame)
        static const long ID_STATICBITMAP1;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX4;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX6;
        static const long ID_CHECKBOX7;
        static const long ID_CHECKBOX8;
        static const long ID_CHECKBOX9;
        static const long ID_CHECKBOX10;
        static const long ID_CHECKBOX11;
        static const long ID_CHECKBOX12;
        static const long ID_CHECKBOX13;
        static const long ID_CHECKBOX14;
        static const long ID_CHECKBOX15;
        static const long ID_CHECKBOX16;
        static const long ID_CHECKBOX17;
        static const long ID_CHECKBOX18;
        static const long ID_CHECKBOX19;
        static const long ID_CHECKBOX20;
        static const long ID_CHECKBOX21;
        static const long ID_CHECKBOX22;
        static const long ID_CHECKBOX23;
        static const long ID_CHECKBOX24;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(TesteFrame)
        wxButton* Button1;
        wxCheckBox* CheckBox10;
        wxCheckBox* CheckBox11;
        wxCheckBox* CheckBox12;
        wxCheckBox* CheckBox13;
        wxCheckBox* CheckBox14;
        wxCheckBox* CheckBox15;
        wxCheckBox* CheckBox16;
        wxCheckBox* CheckBox17;
        wxCheckBox* CheckBox18;
        wxCheckBox* CheckBox19;
        wxCheckBox* CheckBox1;
        wxCheckBox* CheckBox20;
        wxCheckBox* CheckBox21;
        wxCheckBox* CheckBox22;
        wxCheckBox* CheckBox23;
        wxCheckBox* CheckBox24;
        wxCheckBox* CheckBox2;
        wxCheckBox* CheckBox3;
        wxCheckBox* CheckBox4;
        wxCheckBox* CheckBox5;
        wxCheckBox* CheckBox6;
        wxCheckBox* CheckBox7;
        wxCheckBox* CheckBox8;
        wxCheckBox* CheckBox9;
        wxStaticBitmap* StaticBitmap1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStatusBar* StatusBar1;
        wxTimer Timer1;
        //*)
        DECLARE_EVENT_TABLE()
};

#endif // TESTEMAIN_H
