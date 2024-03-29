#include "mainwidget.h"
#include "eb_common.h"
#include "eb_options.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QTextCodec>
#include <QFontDatabase>
#include <QFont>

extern "C"
{
#include <stdlib.h>
}


int main(int argc, char *argv[])
{
#if SINGLETON
    // Ensure only one process is running at the same time.
#if 1
    QFile lockFile;
    lockFile.setFileName(QString("~/.lock_easybench"));
    if (lockFile.exists()) {
        return 0;
    }
    else {
        //system("touch /home/root/.lock_easybench");
    }
#else
    if(!is_singleton()) {
        printf("(W) The program is already running.\n");
        return -1;
    }
#endif
#endif

    QApplication a(argc, argv);

    QFile qssFile(":/qss/easybench.qss");
    qssFile.open(QFile::ReadOnly);
    a.setStyleSheet(qssFile.readAll());
    qssFile.close();

#if LANGUAGE_CHINESE

#if QT_VERSION_5
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#else
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

    int index = QFontDatabase::addApplicationFont("/usr/share/fonts/ttf/LiHeiPro.ttf");
    if(index != -1) {
        QStringList fontList(QFontDatabase::applicationFontFamilies(index));

        // font : LiHei Pro
        if(fontList.count() > 0) {
            QFont font_zh(fontList.at(0));
            //font_zh.setPointSize(26);
            font_zh.setBold(false);
            a.setFont(font_zh);
        }
    }
#endif

    //calcCheckSum("1234567890", 10);
    EbOptions g_opt;

    MainWidget w(&g_opt);
    w.show();

    return a.exec();
}
