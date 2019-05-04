#ifndef ADDEDITIDCCNODE_H
#define ADDEDITIDCCNODE_H

#include <QDialog>

namespace Ui {
class AddEditIDCCNode;
}


class AddEditIDCCNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditIDCCNode(QWidget *parent = 0);
    ~AddEditIDCCNode();

protected:

private Q_SLOTS:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

signals:

private:
    Ui::AddEditIDCCNode *ui;
};

#endif // ADDEDITIDCCNODE_H
