#include "idccupdater.h"
#include "idccupdater_p.h"
#include "../updatecontroller_p.h"

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QMap>

using namespace QtIDCCUpdater;

const QStringList IDCCUpdater::NormalUpdateArguments = {QStringLiteral("--updater")};
const QStringList IDCCUpdater::PassiveUpdateArguments = {QStringLiteral("--updater"), QStringLiteral("skipPrompt=true")};
const QStringList IDCCUpdater::HiddenUpdateArguments = {QStringLiteral("--silentUpdate")};

IDCCUpdater::IDCCUpdater(QObject *parent) :
	IDCCUpdater("", parent)
{}

IDCCUpdater::IDCCUpdater(const QString &currentVersion, QObject *parent) :
	QObject(parent),
	d(new IDCCUpdaterPrivate(this))
{
	d->currentVersion = currentVersion;
}

IDCCUpdater::~IDCCUpdater() {}

bool IDCCUpdater::exitedNormally() const
{
	return d->normalExit;
}

int IDCCUpdater::errorCode() const
{
	return d->lastErrorCode;
}

QByteArray IDCCUpdater::errorLog() const
{
	return d->lastErrorLog;
}

bool IDCCUpdater::willRunOnExit() const
{
	return d->runOnExit;
}

QString IDCCUpdater::currentVersion() const
{
	return d->currentVersion;
}

bool IDCCUpdater::isRunning() const
{
	return isUpdaterRunning;
}

QList<IDCCUpdater::IDCCUpdateInfo> IDCCUpdater::updateInfo() const
{
	return d->updateInfos;
}

bool IDCCUpdater::checkForUpdates()
{
	return d->startUpdateCheck();
}

void IDCCUpdater::abortUpdateCheck(int maxDelay, bool async)
{
	d->stopUpdateCheck(maxDelay, async);
}

int IDCCUpdater::scheduleUpdate(int delaySeconds, bool repeated)
{
	if((((qint64)delaySeconds) * 1000ll) > (qint64)INT_MAX) {
		qCWarning(logIDCCUpdater) << "delaySeconds to big to be converted to msecs";
		return 0;
	}
	return d->scheduler->startSchedule(delaySeconds * 1000, repeated);
}

int IDCCUpdater::scheduleUpdate(const QDateTime &when)
{
	return d->scheduler->startSchedule(when);
}

void IDCCUpdater::cancelScheduledUpdate(int taskId)
{
	d->scheduler->cancelSchedule(taskId);
}

void IDCCUpdater::runUpdaterOnExit(AdminAuthoriser *authoriser)
{
	runUpdaterOnExit(NormalUpdateArguments, authoriser);
}

void IDCCUpdater::runUpdaterOnExit(const QStringList &arguments, AdminAuthoriser *authoriser)
{
	d->runOnExit = true;
	d->runArguments = arguments;
	d->adminAuth.reset(authoriser);
}

void IDCCUpdater::cancelExitRun()
{
	d->runOnExit = false;
	d->adminAuth.reset();
}



IDCCUpdater::IDCCUpdateInfo::IDCCUpdateInfo() :
	name(),
	version(),
	size(0ull)
{}

IDCCUpdater::IDCCUpdateInfo::IDCCUpdateInfo(const IDCCUpdater::IDCCUpdateInfo &other) :
	name(other.name),
	version(other.version),
	size(other.size)
{}

IDCCUpdater::IDCCUpdateInfo::IDCCUpdateInfo(QString name, QString version, quint64 size) :
	name(name),
	version(version),
	size(size)
{}

QDebug &operator<<(QDebug &debug, const IDCCUpdater::IDCCUpdateInfo &info)
{
	QDebugStateSaver state(debug);
	Q_UNUSED(state);

	debug.noquote() << QStringLiteral("{Name: \"%1\"; Version: %2; Size: %3}")
					   .arg(info.name)
					   .arg(info.version.toUtf8().constData())
					   .arg(info.size);
	return debug;
}
