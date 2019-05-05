#ifndef QTIDCCUPDATER_ADMINAUTHORIZATION_P_H
#define QTIDCCUPDATER_ADMINAUTHORIZATION_P_H

#include "idccupdater/adminauthoriser.h"

namespace QtIDCCUpdater
{

class AdminAuthorization : public AdminAuthoriser
{
public:
	bool hasAdminRights() override;
	bool executeAsAdmin(const QString &program, const QStringList &arguments) override;
};

}

#endif // QTIDCCUPDATER_ADMINAUTHORIZATION_P_H
