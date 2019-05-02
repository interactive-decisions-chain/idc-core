#ifndef IDDCUPDATER_IDDCUPDATER_P_H
#define IDDCUPDATER_IDDCUPDATER_P_H

#include "iddcupdater.h"
#include "simplescheduler_p.h"
#include "atomfeeder.h"
#include "downloadmanager.h"

#include <QtCore/QProcess>
#include <QtCore/QLoggingCategory>
#include <QtCore/QException>

#include <exception>

namespace QtIDDCUpdater
{

class IDDCUpdaterPrivate : public QObject
{
public:
	IDDCUpdater *q;

	QString currentVersion;
	QList<IDDCUpdater::IDDCUpdateInfo> updateInfos;
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

	IDDCUpdaterPrivate(IDDCUpdater *q_ptr);
	~IDDCUpdaterPrivate();

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

Q_DECLARE_LOGGING_CATEGORY(logIDDCUpdater)

#endif // IDDCUPDATER_IDDCUPDATER_P_H
