#ifndef MINHAJANELA_H
#define MINHAJANELA_H

#include <wx/wx.h>
#include <ctime>

#include "../audio/Audio.h"

struct Horario
{
    int hora;
    int minuto;
    int segundo;
};

class MinhaJanela : public wxFrame {

    public:
        MinhaJanela();
        void DefinirAlarme(wxString hora);

    private: 
        wxBoxSizer* sizerDespertadores;
        Audio audio;
        Horario defHorario;
        wxStaticText* textoDespertador; 
        wxStaticText* textoHora; 
        wxTimer timer;
        wxString horaAlarme;
        void AbrirDespertador(wxCommandEvent& event);
        void OnTimer(wxTimerEvent& event);
        void AtualizarHora();  
        void ExcluirDespertador(wxMouseEvent& event);
};

#endif