#include "dialog.h"
#include "ui_dialog.h"
#include <QtWidgets>


TaskThread::TaskThread(QObject *parent, bool b) : QThread(parent), Stop(b)
{
}

void TaskThread::set_ip(QString setip)
{
    m_str_ip = setip;
}

void TaskThread::run()
{
    connect(&process, SIGNAL(readyReadStandardOutput()), this->parent(), SLOT(slotReadStandardOutput()));
    process.start("ping", QStringList() << m_str_ip);

    while (!Stop) {
        process.waitForFinished();
    }
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::WindowMinMaxButtonsHint);
    connect(ui->pbStart, SIGNAL(clicked()), this, SLOT(slotStart()));
    connect(ui->pbClear, SIGNAL(clicked()), this, SLOT(slotClear()));
    m_taskthread = new TaskThread(this);
}

Dialog::~Dialog()
{
    m_taskthread->Stop = 1;
    m_taskthread->msleep(1000);
    delete m_taskthread;
    delete ui;
}

void Dialog::slotStart()
{
    QString address = ui->leAddress->text().trimmed();

    m_taskthread->set_ip(address);
    m_taskthread->start();
}

void Dialog::slotClear()
{
    ui->lwResult->clear();
}

void Dialog::slotReadStandardOutput()
{
    QString strOutput = m_taskthread->process.readAll();
    if (!strOutput.isEmpty()) {
        ui->lwResult->addItem(strOutput.replace("\n", ""));
        ui->lwResult->scrollToBottom();
    }
}

void Dialog::slotReadStandardError()
{
    qDebug() << "__func__";
}

void Dialog::slotFinished(int)
{
    qDebug() << "__func__";
}
