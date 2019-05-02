#ifndef QTIDDCUPDATER_ADMINAUTHORIZATION_P_H
#define QTIDDCUPDATER_ADMINAUTHORIZATION_P_H

#include "iddcupdater/adminauthoriser.h"

namespace QtIDDCUpdater
{

class AdminAuthorization : public AdminAuthoriser
{
public:
	bool hasAdminRights() override;
	bool executeAsAdmin(const QString &program, const QStringList &arguments) override;
};

}

#endif // QTIDDCUPDATER_ADMINAUTHORIZATION_P_H
