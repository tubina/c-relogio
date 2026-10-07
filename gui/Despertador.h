#ifndef DESPERTADOR_H
#define DESPERTADOR_H

#include <wx/wx.h>

class MinhaJanela;

class Despertador : public wxFrame
{
    public:
        Despertador(MinhaJanela* janela);
 
    private:
        wxTextCtrl* campo;
        MinhaJanela* janelaPrincipal;
        void SalvarHora(wxCommandEvent& event);
};

#endif