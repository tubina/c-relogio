#include "Despertador.h"
#include "MinhaJanela.h"

#include <iostream>

Despertador::Despertador(MinhaJanela* janela)
    : wxFrame(
        janela,
        wxID_ANY,
        "Novo Despertador",
        wxDefaultPosition,
        wxSize(300, 250)
    ),
    janelaPrincipal(janela)
{
    SetBackgroundColour(*wxBLACK);

    campo = new wxTextCtrl(
        this,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_PROCESS_ENTER
    );

    campo->Bind(
        wxEVT_TEXT_ENTER,
        &Despertador::SalvarHora,
        this
    );

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(
        campo,
        0,
        wxALIGN_CENTER | wxTOP,
        20
    );

    SetSizer(sizer);
}

void Despertador::SalvarHora(wxCommandEvent& event)
{
    wxString hora = campo->GetValue();

    std::cout << "Hora salva: "
              << hora
              << std::endl;

    janelaPrincipal->DefinirAlarme(hora);

    Close();
}