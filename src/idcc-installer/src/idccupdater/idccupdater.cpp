#include "iddcupdater.h"
#include "iddcupdater_p.h"
#include "../updatecontroller_p.h"

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QMap>

using namespace QtIDDCUpdater;

const QStringList IDDCUpdater::NormalUpdateArguments = {QStringLiteral("--updater")};
const QStringList IDDCUpdater::PassiveUpdateArguments = {QStringLiteral("--updater"), QStringLiteral("skipPrompt=true")};
const QStringList IDDCUpdater::HiddenUpdateArguments = {QStringLiteral("--silentUpdate")};

IDDCUpdater::IDDCUpdater(QObject *parent) :
	IDDCUpdater("", parent)
{}

IDDCUpdater::IDDCUpdater(const QString &currentVersion, QObject *parent) :
	QObject(parent),
	d(new IDDCUpdaterPrivate(this))
{
	d->currentVersion = currentVersion;
}

IDDCUpdater::~IDDCUpdater() {}

bool IDDCUpdater::exitedNormally() const
{
	return d->normalExit;
}

int IDDCUpdater::errorCode() const
{
	return d->lastErrorCode;
}

QByteArray IDDCUpdater::errorLog() const
{
	return d->lastErrorLog;
}

bool IDDCUpdater::willRunOnExit() const
{
	return d->runOnExit;
}

QString IDDCUpdater::currentVersion() const
{
	return d->currentVersion;
}

bool IDDCUpdater::isRunning() const
{
	return isUpdaterRunning;
}

QList<IDDCUpdater::IDDCUpdateInfo> IDDCUpdater::updateInfo() const
{
	return d->updateInfos;
}

bool IDDCUpdater::checkForUpdates()
{
	return d->startUpdateCheck();
}

void IDDCUpdater::abortUpdateCheck(int maxDelay, bool async)
{
	d->stopUpdateCheck(maxDelay, async);
}

int IDDCUpdater::scheduleUpdate(int delaySeconds, bool repeated)
{
	if((((qint64)delaySeconds) * 1000ll) > (qint64)INT_MAX) {
		qCWarning(logIDDCUpdater) << "delaySeconds to big to be converted to msecs";
		return 0;
	}
	return d->scheduler->startSchedule(delaySeconds * 1000, repeated);
}

int IDDCUpdater::scheduleUpdate(const QDateTime &when)
{
	return d->scheduler->startSchedule(when);
}

void IDDCUpdater::cancelScheduledUpdate(int taskId)
{
	d->scheduler->cancelSchedule(taskId);
}

void IDDCUpdater::runUpdaterOnExit(AdminAuthoriser *authoriser)
{
	runUpdaterOnExit(NormalUpdateArguments, authoriser);
}

void IDDCUpdater::runUpdaterOnExit(const QStringList &arguments, AdminAuthoriser *authoriser)
{
	d->runOnExit = true;
	d->runArguments = arguments;
	d->adminAuth.reset(authoriser);
}

void IDDCUpdater::cancelExitRun()
{
	d->runOnExit = false;
	d->adminAuth.reset();
}



IDDCUpdater::IDDCUpdateInfo::IDDCUpdateInfo() :
	name(),
	version(),
	size(0ull)
{}

IDDCUpdater::IDDCUpdateInfo::IDDCUpdateInfo(const IDDCUpdater::IDDCUpdateInfo &other) :
	name(other.name),
	version(other.version),
	size(other.size)
{}

IDDCUpdater::IDDCUpdateInfo::IDDCUpdateInfo(QString name, QString version, quint64 size) :
	name(name),
	version(version),
	size(size)
{}

QDebug &operator<<(QDebug &debug, const IDDCUpdater::IDDCUpdateInfo &info)
{
	QDebugStateSaver state(debug);
	Q_UNUSED(state);

	debug.noquote() << QStringLiteral("{Name: \"%1\"; Version: %2; Size: %3}")
					   .arg(info.name)
					   .arg(info.version.toUtf8().constData())
					   .arg(info.size);
	return debug;
}
