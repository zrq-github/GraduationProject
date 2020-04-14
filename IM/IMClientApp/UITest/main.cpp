#include "UITest.h"
#include <QtWidgets/QApplication>

#include "IMClientApp/IMClientApp.h"
#include "LogonPanel/LogonPanel.h"
#include "LogonPanel/NetSettingsPanel.h"
#include "ChatPanel/ChatPanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //UITest w;
    //w.show();
    
    //NetSettingsPanel *w = new NetSettingsPanel;
    //w->show();

    //ChatPanel *w = new ChatPanel;
    //w->show();

    LogonPanel *w = new LogonPanel;
    w->show();

    return a.exec();
}
