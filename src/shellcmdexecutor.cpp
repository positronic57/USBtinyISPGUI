#include "shellcmdexecutor.h"

void ShellCMDExecutor::add_argument(const QString &new_argument)
{
   shell_cmd_arguments << new_argument;
}

void ShellCMDExecutor::slotStartShellCMDExecution()
{
    if (shell_cmd_arguments.isEmpty())
    {
        start(shell_cmd);
    }
    else
    {
        start(shell_cmd, shell_cmd_arguments);
    }
}

void ShellCMDExecutor::slotStopShellCMDExecution()
{
    shell_cmd.clear();
    shell_cmd_arguments.clear();
}


void ShellCMDExecutor::slotSetShellCmd(const QString &new_cmd)
{
    shell_cmd = new_cmd;
}

void ShellCMDExecutor::slotSetShellCmdArguments(const QStringList &new_cmd_arguments)
{
    shell_cmd_arguments = new_cmd_arguments;
}


void ShellCMDExecutor::slotShellCmdWithNoArguments()
{
    shell_cmd_arguments.clear();
}

