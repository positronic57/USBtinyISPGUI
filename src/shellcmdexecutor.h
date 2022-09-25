#ifndef SHELLCMDEXECUTOR_H
#define SHELLCMDEXECUTOR_H

#include <QObject>
#include <QProcess>
#include <QString>


class ShellCMDExecutor: public QProcess
{
    Q_OBJECT

private:
    QString shell_cmd;
    QStringList shell_cmd_arguments;

public:
    ShellCMDExecutor(QObject *parent = nullptr):QProcess(parent) {}
    ~ShellCMDExecutor() {}

    void cmd(const QString &new_cmd) { shell_cmd = new_cmd; }
    void cmd_arguments(const QStringList &new_cmd_arguments) { shell_cmd_arguments = new_cmd_arguments; }
    void cmd_no_arguments() { shell_cmd_arguments.clear(); }
    void cmd_clear_arguments() { shell_cmd_arguments.clear(); }
    void add_argument(const QString &new_argument);

public slots:
    void slotStartShellCMDExecution();
    void slotStopShellCMDExecution();
    void slotSetShellCmd(const QString &new_cmd);
    void slotSetShellCmdArguments(const QStringList &new_cmd_arguments);
    void slotShellCmdWithNoArguments();

signals:
    void signalProcessTerminated(int);
};

#endif //SHELLCMDEXECUTOR_H
