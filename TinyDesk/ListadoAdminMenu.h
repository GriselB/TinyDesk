//
//  ListadoAdminMenu.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 30/10/2025.
//

#pragma once
#include "cstring"
#include "ListadoAdminManager.h"

class ListadoAdminMenu {
private:
    ListadoAdminManager _listadoAdminManager;

public:
    void run(std::string titulo);
};
