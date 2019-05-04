#ifndef IDCCNODECONFIGDIALOG_H
#define IDCCNODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class IDCCNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class IDCCNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IDCCNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:28666", QString privkey="MASTERNODEPRIVKEY");
    ~IDCCNodeConfigDialog();

private:
    Ui::IDCCNodeConfigDialog *ui;
};

#endif // IDCCNODECONFIGDIALOG_H
