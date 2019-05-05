#ifndef IDCCUPDATER_IDCCUPDATER_P_H
#define IDCCUPDATER_IDCCUPDATER_P_H

#include "idccupdater.h"
#include "simplescheduler_p.h"
#include "atomfeeder.h"
#include "downloadmanager.h"

#include <QtCore/QProcess>
#include <QtCore/QLoggingCategory>
#include <QtCore/QException>

#include <exception>

namespace QtIDCCUpdater
{

class IDCCUpdaterPrivate : public QObject
{
public:
	IDCCUpdater *q;

	QString currentVersion;
	QList<IDCCUpdater::IDCCUpdateInfo> updateInfos;
	bool normalExit;
	int lastErrorCode;
	QByteArray lastErrorLog;

	AtomFeeder *atomFeeder;
	int currentVersionPos;
	QString newVersion;
	DownloadManager *downloadManager;

	SimpleScheduler *scheduler;

	bool runOnExit;
	QStringList runArguments;
	QScopedPointer<AdminAuthoriser> adminAuth;

	IDCCUpdaterPrivate(IDCCUpdater *q_ptr);
	~IDCCUpdaterPrivate();

	bool startUpdateCheck();
	void stopUpdateCheck(int delay, bool async);

	void updaterError();

public Q_SLOTS:
	void onAppAboutToExit();
	void onUpdaterReady();
	void onDownloadProgress(DownloadManager::DownloadProgress progress);
	void onDownloadFinished(DownloadManager::DownloadProgress progress);
	void onDownloadCheckSize(DownloadManager::DownloadProgress progress);

private:
	QString getDownloadUrl(QString version);
};

}

Q_DECLARE_LOGGING_CATEGORY(logIDCCUpdater)

#endif // IDCCUPDATER_IDCCUPDATER_P_H
