#pragma once
#include <cstring>
#include "ReportesAdminMenuManager.h"

class ReportesAdminMenu {
private:
    ReportesAdminMenuManager _reportesAdminMenuManager;

public:
    void run(std::string titulo);
};

