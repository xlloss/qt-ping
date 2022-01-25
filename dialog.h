#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QProcess>
#include <QThread>

namespace Ui {
class Dialog;
}

class TaskThread : public QThread
{
    Q_OBJECT
public:
    explicit TaskThread(QObject *parent = 0, bool b = false);

public:
    QString m_str_ip;
    void set_ip(QString setip);
    bool Stop;
    void run();
    QProcess process;
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected slots:
    void slotStart();
    void slotClear();
    void slotReadStandardOutput();
    void slotReadStandardError();
    void slotFinished(int);

private:
    Ui::Dialog *ui;
    TaskThread *m_taskthread;
};

#endif // DIALOG_H
