#include "xhash.h"
#include "global.h"
#include <QApplication>
#include <QSettings>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSettings settings("config.ini", QSettings::IniFormat);
    g_configLanguage = settings.value("language", "English").toString();
    g_addContextMenu = settings.value("add_context_menu", false).toBool();
    g_directCalc = settings.value("direct_calc", false).toBool();
    g_calc_crc32 = settings.value("calc_crc32", false).toBool();
    g_calc_md5 = settings.value("calc_md5", true).toBool();
    g_calc_sha1 = settings.value("calc_sha1", false).toBool();
    g_calc_sha256 = settings.value("calc_sha256", true).toBool();
    g_calc_sha512 = settings.value("calc_sha512", false).toBool();

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "XHash_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    XHash window(argc, argv);
    window.show();
    return app.exec();
}
