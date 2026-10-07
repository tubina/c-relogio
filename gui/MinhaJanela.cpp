#include "MinhaJanela.h"
#include "Despertador.h"

#include <ctime>
#include <iostream>

// ID personalizado do menu
enum
{
    ID_NOVO_DESPERTADOR = wxID_HIGHEST + 1
};


MinhaJanela::MinhaJanela()
    : wxFrame(
        nullptr,
        wxID_ANY,
        "TIMER",
        wxPoint(1000, 500),
        wxSize(300, 250)
    )
{
    // =========================
    // BARRA DE MENU
    // =========================

    wxMenuBar* barraMenu = new wxMenuBar();

    barraMenu->SetBackgroundColour(*wxBLACK);
    barraMenu->SetForegroundColour(*wxWHITE);

    wxMenu* menuFile = new wxMenu();

    menuFile->Append(
        ID_NOVO_DESPERTADOR,
        "Novo Despertador"
    );

    menuFile->AppendSeparator();

    barraMenu->Append(
        menuFile,
        "Despertador"
    );

    SetMenuBar(barraMenu);

    // =========================
    // EVENTO DO MENU
    // =========================

    Bind(
        wxEVT_MENU,
        &MinhaJanela::AbrirDespertador,
        this,
        ID_NOVO_DESPERTADOR
    );

    // =========================
    // FUNDO
    // =========================

    SetBackgroundColour(*wxBLACK);

    // =========================
    // RELÓGIO ATUAL
    // =========================

    textoHora = new wxStaticText(
        this,
        wxID_ANY,
        ""
    );

    wxColour azul(0, 150, 255);

    textoHora->SetForegroundColour(azul);

    wxFont fonteHora(
        40,
        wxFONTFAMILY_DEFAULT,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_BOLD
    );

    textoHora->SetFont(fonteHora);

    // =========================
    // TEXTO DO DESPERTADOR
    // =========================

    textoDespertador = new wxStaticText(
        this,
        wxID_ANY,
        "no timer"
    );

    textoDespertador->SetForegroundColour(*wxWHITE);

    wxFont fonteDespertador(
        15,
        wxFONTFAMILY_DEFAULT,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_BOLD
    );

    textoDespertador->SetFont(fonteDespertador);

    // =========================
    // BOTÃO EXCLUIR
    // =========================

    wxStaticText* excluir = new wxStaticText(
        this,
        wxID_ANY,
        "Excluir"  
    ); 
    excluir->SetForegroundColour(*wxWHITE); 

    excluir->SetCursor(
        wxCursor(wxCURSOR_HAND)
    );
  
    excluir->Bind(
        wxEVT_LEFT_DOWN,
        &MinhaJanela::ExcluirDespertador,
        this
    );

    // =========================
    // LINHA DO DESPERTADOR
    // =========================

    wxBoxSizer* linhaDespertador =
        new wxBoxSizer(wxHORIZONTAL);

    linhaDespertador->Add(
        textoDespertador,
        0,
        wxALIGN_CENTER_VERTICAL | wxRIGHT,
        10
    );

    linhaDespertador->Add(
        excluir,
        0,
        wxALIGN_CENTER_VERTICAL
    );


    // =========================
    // SIZER PRINCIPAL
    // =========================

    wxBoxSizer* sizer =
        new wxBoxSizer(wxVERTICAL);

    sizer->Add(
        textoHora,
        0,
        wxALIGN_CENTER | wxTOP,
        20
    );

    sizer->Add(
        linhaDespertador,
        0,
        wxALIGN_CENTER | wxTOP,
        10
    );

    SetSizer(sizer);


    // =========================
    // TIMER
    // =========================

    timer.SetOwner(this);

    Bind(
        wxEVT_TIMER,
        &MinhaJanela::OnTimer,
        this
    );

    AtualizarHora();

    timer.Start(1000);
}


// =========================
// ABRIR DESPERTADOR
// =========================

void MinhaJanela::AbrirDespertador(wxCommandEvent& event)
{
    Despertador* janela =
        new Despertador(this);

    janela->Show();
}


// =========================
// TIMER
// =========================

void MinhaJanela::OnTimer(wxTimerEvent& event)
{
    AtualizarHora();
}


// =========================
// ATUALIZAR HORA
// =========================

void MinhaJanela::AtualizarHora()
{
    std::time_t agora =
        std::time(nullptr);

    std::tm* tempo =
        std::localtime(&agora);


    // =========================
    // VERIFICAR ALARME
    // =========================

    if (
        tempo->tm_hour == defHorario.hora &&
        tempo->tm_min == defHorario.minuto &&
        tempo->tm_sec == defHorario.segundo
    )
    {
        std::cout
            << "ENTROU NO ALARME\n";

        audio.Tocar("som/som.wav");
    }


    // =========================
    // MOSTRAR HORA
    // =========================

    char hora[9];

    std::strftime(
        hora,
        sizeof(hora),
        "%H:%M:%S",
        tempo
    );

    textoHora->SetLabel(hora);
}


// =========================
// DEFINIR ALARME
// =========================

void MinhaJanela::DefinirAlarme(wxString hora)
{
    std::cout
        << "Alarme recebido: "
        << hora
        << std::endl;


    horaAlarme = hora;


    // =========================
    // FORMATAR HORA
    // 140204 -> 14:02:04
    // =========================

    wxString horario =
        hora.Mid(0, 2) + ":" +
        hora.Mid(2, 2) + ":" +
        hora.Mid(4, 2);


    // =========================
    // CONVERTER PARA INT
    // =========================

    int h =
        wxAtoi(hora.Mid(0, 2));

    int m =
        wxAtoi(hora.Mid(2, 2));

    int s =
        wxAtoi(hora.Mid(4, 2));


    // =========================
    // SALVAR HORÁRIO
    // =========================

    defHorario.hora = h;
    defHorario.minuto = m;
    defHorario.segundo = s;


    // =========================
    // MOSTRAR NA TELA
    // =========================

    textoDespertador->SetLabel(horario);

    Layout();
}

// =========================
// EXLUIR ALARME
// =========================
void MinhaJanela::ExcluirDespertador(wxMouseEvent& event)
{
    textoDespertador->SetLabel("");

    defHorario.hora = -1;
    defHorario.minuto = -1;
    defHorario.segundo = -1;
}