#include "Audio.h"
#include <cstdlib>

void Audio::Tocar(const std::string& arquivo)
{
    std::string comando =  "aplay \"" + arquivo + "\" > /dev/null 2>&1 &";

    system(comando.c_str());
}