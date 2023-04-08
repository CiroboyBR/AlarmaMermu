/***************************************************************
 * Name:      TesteMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Ciro Martins Meneses (ciroccuva@hotmail.com)
 * Created:   2021-08-12
 * Copyright: Ciro Martins Meneses (www.ciroboybr.blogspot.com)
 * License:
 **************************************************************/

#include "TesteMain.h"
#include "TesteApp.h"
#include <wx/msgdlg.h>
#include <fstream>
#include <wx/sound.h>

void salvaHorarios(); //salva os horarios em um arquivo TXT para posterior carregamento
void carregaHorarios(); //Carrega hor�rios a partir de um arquivo TXT para alarmar nos hor�rios
bool verificaHora(); //Verifica se est� na hora de alarmar
void alarma(); //Realiza os procedimentos pertinentes a a��o do alarme

wxDateTime pub_date;
wxString horarios[25]; //Horarios que ser�o armazenados
bool disparaAlarme; // 1 dispara, 0 j� disparou
int horariosDisparados[25]; // 0 = nao, 1 = disparar, 2 = j� disparou
wxSound * som_alarme;  // Arquivo WAV que vai ser utilizado como o som do alarme
wxFrame* frameHideShow; //para controle do hide e show da janela



using namespace std;

//(*InternalHeaders(TesteFrame)
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(TesteFrame)
const long TesteFrame::ID_STATICBITMAP1 = wxNewId();
const long TesteFrame::ID_CHECKBOX1 = wxNewId();
const long TesteFrame::ID_CHECKBOX2 = wxNewId();
const long TesteFrame::ID_CHECKBOX3 = wxNewId();
const long TesteFrame::ID_CHECKBOX4 = wxNewId();
const long TesteFrame::ID_CHECKBOX5 = wxNewId();
const long TesteFrame::ID_CHECKBOX6 = wxNewId();
const long TesteFrame::ID_CHECKBOX7 = wxNewId();
const long TesteFrame::ID_CHECKBOX8 = wxNewId();
const long TesteFrame::ID_CHECKBOX9 = wxNewId();
const long TesteFrame::ID_CHECKBOX10 = wxNewId();
const long TesteFrame::ID_CHECKBOX11 = wxNewId();
const long TesteFrame::ID_CHECKBOX12 = wxNewId();
const long TesteFrame::ID_CHECKBOX13 = wxNewId();
const long TesteFrame::ID_CHECKBOX14 = wxNewId();
const long TesteFrame::ID_CHECKBOX15 = wxNewId();
const long TesteFrame::ID_CHECKBOX16 = wxNewId();
const long TesteFrame::ID_CHECKBOX17 = wxNewId();
const long TesteFrame::ID_CHECKBOX18 = wxNewId();
const long TesteFrame::ID_CHECKBOX19 = wxNewId();
const long TesteFrame::ID_CHECKBOX20 = wxNewId();
const long TesteFrame::ID_CHECKBOX21 = wxNewId();
const long TesteFrame::ID_CHECKBOX22 = wxNewId();
const long TesteFrame::ID_CHECKBOX23 = wxNewId();
const long TesteFrame::ID_CHECKBOX24 = wxNewId();
const long TesteFrame::ID_STATICTEXT1 = wxNewId();
const long TesteFrame::ID_STATICTEXT2 = wxNewId();
const long TesteFrame::ID_BUTTON1 = wxNewId();
const long TesteFrame::idMenuQuit = wxNewId();
const long TesteFrame::idMenuAbout = wxNewId();
const long TesteFrame::ID_STATUSBAR1 = wxNewId();
const long TesteFrame::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(TesteFrame,wxFrame)

    //(*EventTable(TesteFrame)
    //*)
END_EVENT_TABLE()

TesteFrame::TesteFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(TesteFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("AlarmaMermu - Santa Casa de Sobral"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(333,427));
    SetBackgroundColour(wxColour(255,128,128));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("favicon.ico"))));
    	SetIcon(FrameIcon);
    }
    StaticBitmap1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxBitmap(wxImage(_T("logostacasa.png")).Rescale(wxSize(256,112).GetWidth(),wxSize(256,112).GetHeight())), wxPoint(32,16), wxSize(256,112), 0, _T("ID_STATICBITMAP1"));
    CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("00h"), wxPoint(72,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(false);
    CheckBox2 = new wxCheckBox(this, ID_CHECKBOX2, _("01h"), wxPoint(72,176), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox2->SetValue(false);
    CheckBox3 = new wxCheckBox(this, ID_CHECKBOX3, _("02h"), wxPoint(72,200), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    CheckBox3->SetValue(false);
    CheckBox4 = new wxCheckBox(this, ID_CHECKBOX4, _("03h"), wxPoint(72,224), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CheckBox4->SetValue(false);
    CheckBox5 = new wxCheckBox(this, ID_CHECKBOX5, _("04h"), wxPoint(72,248), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    CheckBox5->SetValue(false);
    CheckBox6 = new wxCheckBox(this, ID_CHECKBOX6, _("05h"), wxPoint(72,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    CheckBox6->SetValue(false);
    CheckBox7 = new wxCheckBox(this, ID_CHECKBOX7, _("06h"), wxPoint(72,296), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    CheckBox7->SetValue(false);
    CheckBox8 = new wxCheckBox(this, ID_CHECKBOX8, _("07h"), wxPoint(72,320), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    CheckBox8->SetValue(false);
    CheckBox9 = new wxCheckBox(this, ID_CHECKBOX9, _("08h"), wxPoint(136,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
    CheckBox9->SetValue(false);
    CheckBox10 = new wxCheckBox(this, ID_CHECKBOX10, _("09h"), wxPoint(136,176), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
    CheckBox10->SetValue(false);
    CheckBox11 = new wxCheckBox(this, ID_CHECKBOX11, _("10h"), wxPoint(136,200), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
    CheckBox11->SetValue(false);
    CheckBox12 = new wxCheckBox(this, ID_CHECKBOX12, _("11h"), wxPoint(136,224), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
    CheckBox12->SetValue(false);
    CheckBox13 = new wxCheckBox(this, ID_CHECKBOX13, _("12h"), wxPoint(136,248), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
    CheckBox13->SetValue(false);
    CheckBox14 = new wxCheckBox(this, ID_CHECKBOX14, _("13h"), wxPoint(136,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
    CheckBox14->SetValue(false);
    CheckBox15 = new wxCheckBox(this, ID_CHECKBOX15, _("14h"), wxPoint(136,296), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
    CheckBox15->SetValue(false);
    CheckBox16 = new wxCheckBox(this, ID_CHECKBOX16, _("15h"), wxPoint(136,320), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
    CheckBox16->SetValue(false);
    CheckBox17 = new wxCheckBox(this, ID_CHECKBOX17, _("16h"), wxPoint(192,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX17"));
    CheckBox17->SetValue(false);
    CheckBox18 = new wxCheckBox(this, ID_CHECKBOX18, _("17h"), wxPoint(192,176), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX18"));
    CheckBox18->SetValue(false);
    CheckBox19 = new wxCheckBox(this, ID_CHECKBOX19, _("18h"), wxPoint(192,200), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX19"));
    CheckBox19->SetValue(false);
    CheckBox20 = new wxCheckBox(this, ID_CHECKBOX20, _("19h"), wxPoint(192,224), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX20"));
    CheckBox20->SetValue(false);
    CheckBox21 = new wxCheckBox(this, ID_CHECKBOX21, _("20h"), wxPoint(192,248), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX21"));
    CheckBox21->SetValue(false);
    CheckBox22 = new wxCheckBox(this, ID_CHECKBOX22, _("21h"), wxPoint(192,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX22"));
    CheckBox22->SetValue(false);
    CheckBox23 = new wxCheckBox(this, ID_CHECKBOX23, _("22h"), wxPoint(192,296), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX23"));
    CheckBox23->SetValue(false);
    CheckBox24 = new wxCheckBox(this, ID_CHECKBOX24, _("23h"), wxPoint(192,320), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX24"));
    CheckBox24->SetValue(false);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("AlarmaMermu"), wxPoint(96,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(14,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Selecione os hor�rios para ativar o alarme"), wxPoint(24,128), wxSize(264,16), 0, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    Button1 = new wxButton(this, ID_BUTTON1, _("Esconder"), wxPoint(256,208), wxSize(64,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button1->SetBackgroundColour(wxColour(95,33,33));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Sair\tAlt-F4"), _("Sair do programa"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("Arquivo"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("Sobre\tF1"), _("Mostra informa��es sobre o software"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Ajuda"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(1000, false);

    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox1Click);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox2Click);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox3Click);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox4Click);
    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox5Click);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox6Click);
    Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox7Click);
    Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox8Click);
    Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox9Click);
    Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox10Click);
    Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox11Click);
    Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox12Click);
    Connect(ID_CHECKBOX13,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox13Click);
    Connect(ID_CHECKBOX14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox14Click);
    Connect(ID_CHECKBOX15,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox15Click);
    Connect(ID_CHECKBOX16,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox16Click);
    Connect(ID_CHECKBOX17,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox17Click);
    Connect(ID_CHECKBOX18,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox18Click);
    Connect(ID_CHECKBOX19,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox19Click);
    Connect(ID_CHECKBOX20,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox20Click);
    Connect(ID_CHECKBOX21,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox21Click);
    Connect(ID_CHECKBOX22,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox22Click);
    Connect(ID_CHECKBOX23,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox23Click);
    Connect(ID_CHECKBOX24,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TesteFrame::OnCheckBox24Click);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TesteFrame::OnButton1Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TesteFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TesteFrame::OnAbout);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&TesteFrame::OnTimer1Trigger);
    //*)


    carregaHorarios();

    if(horarios[0] == _("1") )
        CheckBox1->SetValue(true);
    if(horarios[1] == _("1") )
        CheckBox2->SetValue(true);
    if(horarios[2] == _("1") )
        CheckBox3->SetValue(true);
    if(horarios[3] == _("1") )
        CheckBox4->SetValue(true);
    if(horarios[4] == _("1") )
        CheckBox5->SetValue(true);
    if(horarios[5] == _("1") )
        CheckBox6->SetValue(true);
    if(horarios[6] == _("1") )
        CheckBox7->SetValue(true);
    if(horarios[7] == _("1") )
        CheckBox8->SetValue(true);
    if(horarios[8] == _("1") )
        CheckBox9->SetValue(true);
    if(horarios[9] == _("1") )
        CheckBox10->SetValue(true);
    if(horarios[10] == _("1") )
        CheckBox11->SetValue(true);
    if(horarios[11] == _("1") )
        CheckBox12->SetValue(true);
    if(horarios[12] == _("1") )
        CheckBox13->SetValue(true);
    if(horarios[13] == _("1") )
        CheckBox14->SetValue(true);
    if(horarios[14] == _("1") )
        CheckBox15->SetValue(true);
    if(horarios[15] == _("1") )
        CheckBox16->SetValue(true);
    if(horarios[16] == _("1") )
        CheckBox17->SetValue(true);
    if(horarios[17] == _("1") )
        CheckBox18->SetValue(true);
    if(horarios[18] == _("1") )
        CheckBox19->SetValue(true);
    if(horarios[19] == _("1") )
        CheckBox20->SetValue(true);
    if(horarios[20] == _("1") )
        CheckBox21->SetValue(true);
    if(horarios[21] == _("1") )
        CheckBox22->SetValue(true);
    if(horarios[22] == _("1") )
        CheckBox23->SetValue(true);
    if(horarios[23] == _("1") )
        CheckBox24->SetValue(true);

    //inicializa gatilhos para o alarme
    for(int i = 0; i < 25; i++)
        horariosDisparados[i] = 0;

    //carrega som
    som_alarme = new wxSound (_T("alarme.wav"), false );

        wxMessageBox(_("Alarme Iniciado"));

}

TesteFrame::~TesteFrame()
{
    //(*Destroy(TesteFrame)
    //*)
}

void TesteFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void TesteFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(_("AlarmaMermu\n\nDescri��o: Programa desenvolvido para alarmar nos hor�rios selecionados, com a finalidade de alertar os funcion�rios do Banco de Sangue para a verifica��o rotineira das temperaturas do congelador\n\nDESENVOLVEDOR: Ciro Martins Meneses\nLINGUAGEM: C/C++\nIDE: CodeBlocks\nCOMPILADOR: Gcc MingW\nBIBLIOTECA: WxWidgets\nFERRAMENTAS: WxSmith"));
}

//salva os horarios em um arquivo TXT para posterior carregamento
void salvaHorarios()
{

    //Cria arquivo
    fstream arq;
    arq.open("horariosConfigurados.cfg", ios::out | ios::ate);

    for(int i = 0; i < 24; i++)
    {
        if( horarios[i] == _("1") )
            arq << horarios[i];
        else
            arq << 0;
        arq << "\n";
    }
    arq.close();
}

//Carrega hor�rios a partir de um arquivo TXT para alarmar nos hor�rios
void carregaHorarios()
{
    //Cria arquivo
    string linha;
    ifstream arq ("horariosConfigurados.cfg");
    if (arq.is_open())
    {
        for(int i = 0; getline (arq,linha) || i < 24; i++)
        {
            if( linha == "1")
                horarios[i] << "1";
            else
                horarios[i] << "0";
        }
        arq.close();
    }

    else {
         for(int i = 0; i < 24; i++)
            horarios[i] = "0";
    }



}

//Verifica se est� na hora de alarmar
bool verificaHora()
{
    //wxString debugSTR;

    for(int i = 0; i < 24; i++) {
        wxString s;
        wxString s_i;

        s_i << i;
        s << wxDateTime::Now().GetHour();
      /*  debugSTR << s;
        debugSTR << " ";
        debugSTR << s_i;
        debugSTR << "\n";
      */
        //se o horario estiver ativo e a Hora atual for igual ao i�simo iterador
        if( horarios[i] == _("1") && s == s_i ) {
            if(horariosDisparados[wxDateTime::Now().GetHour()] == 0){ //Se o gatilho[horaAtual] nao estiver ativo
                disparaAlarme = true;
                //ativa somente o gatilho atual, para n�o repetir o alarme
                horariosDisparados[wxDateTime::Now().GetHour()] = 1;
                alarma();

                //desativa todos os gatilhos
                for(int x = 0; x < 24; x++) {
                    horariosDisparados[x] = 0;
                }
                //ativa somente o gatilho atual, para n�o repetir o alarme
                horariosDisparados[wxDateTime::Now().GetHour()] = 1;
                break;
            }

        }
    }
    //wxMessageBox(debugSTR);

}

//Realiza os procedimentos pertinentes a a��o do alarme
void alarma()
{   int saida = 0;

  if(disparaAlarme == true) {
    som_alarme->Play( wxSOUND_ASYNC | wxSOUND_LOOP );
    disparaAlarme = false;  //Desativa um disparo repetido no memso horario
    frameHideShow->Show();
    saida = wxMessageBox(_("Verifique as temperaturas dos refrigeradores das boldas de sangue!") );
  }

  if(saida != 0)
    som_alarme->Stop();

//  wxMessageBox(wxString::Format(wxT("%i"),saida));

}

void TesteFrame::OnCheckBox17Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox17->GetValue())
        s << 1;
    else
        s << 0;

    horarios[16] = s;
    salvaHorarios();

}

void TesteFrame::OnCheckBox18Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox18->GetValue())
        s << 1;
    else
        s << 0;

    horarios[17] = s;
    salvaHorarios();

}

void TesteFrame::OnCheckBox1Click(wxCommandEvent& event)
{

    wxString s;
    if(CheckBox1->GetValue())
        s << 1;
    else
        s << 0;

    horarios[0] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox2Click(wxCommandEvent& event)
{

    wxString s;
    if(CheckBox2->GetValue())
        s << 1;
    else
        s << 0;

    horarios[1] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox3Click(wxCommandEvent& event)
{

    wxString s;
    if(CheckBox3->GetValue())
        s << 1;
    else
        s << 0;

    horarios[2] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox4Click(wxCommandEvent& event)
{

    wxString s;
    if(CheckBox4->GetValue())
        s << 1;
    else
        s << 0;

    horarios[3] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox5Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox5->GetValue())
        s << 1;
    else
        s << 0;

    horarios[4] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox6Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox6->GetValue())
        s << 1;
    else
        s << 0;

    horarios[5] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox7Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox7->GetValue())
        s << 1;
    else
        s << 0;

    horarios[6] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox8Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox8->GetValue())
        s << 1;
    else
        s << 0;

    horarios[7] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox9Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox9->GetValue())
        s << 1;
    else
        s << 0;

    horarios[8] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox10Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox10->GetValue())
        s << 1;
    else
        s << 0;

    horarios[9] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox11Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox11->GetValue())
        s << 1;
    else
        s << 0;

    horarios[10] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox12Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox12->GetValue())
        s << 1;
    else
        s << 0;

    horarios[11] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox13Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox13->GetValue())
        s << 1;
    else
        s << 0;

    horarios[12] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox14Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox14->GetValue())
        s << 1;
    else
        s << 0;

    horarios[13] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox15Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox15->GetValue())
        s << 1;
    else
        s << 0;

    horarios[14] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox16Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox16->GetValue())
        s << 1;
    else
        s << 0;

    horarios[15] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox19Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox19->GetValue())
        s << 1;
    else
        s << 0;

    horarios[18] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox20Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox20->GetValue())
        s << 1;
    else
        s << 0;

    horarios[19] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox21Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox21->GetValue())
        s << 1;
    else
        s << 0;

    horarios[20] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox22Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox22->GetValue())
        s << 1;
    else
        s << 0;

    horarios[21] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox23Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox23->GetValue())
        s << 1;
    else
        s << 0;

    horarios[22] = s;
    salvaHorarios();
}

void TesteFrame::OnCheckBox24Click(wxCommandEvent& event)
{
    wxString s;
    if(CheckBox24->GetValue())
        s << 1;
    else
        s << 0;

    horarios[23] = s;
    salvaHorarios();
}

//Realiza a verifica��o de 1 em 1s para saber se chegou o momento de alarmar
void TesteFrame::OnTimer1Trigger(wxTimerEvent& event)
{
    verificaHora();
}

void inicializaChecks() {

}

void TesteFrame::OnButton1Click(wxCommandEvent& event)
{
    frameHideShow = this; //Faz um ponteiro global apontar para a aplica��o para depois dar um Hide() e Show()
    this->Hide();//esconde a aplica��o
}
