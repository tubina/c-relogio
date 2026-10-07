#include <wx/wx.h>
#include <ctime>
#include <wx/display.h>

#include "../gui/MinhaJanela.h"
  
class MinhaApp : public wxApp
{
public:

    bool OnInit() override
    {
        MinhaJanela* janela =
            new MinhaJanela(); 
        janela->Show();
 
        return true;
    }
};


wxIMPLEMENT_APP(MinhaApp);