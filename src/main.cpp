#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>
#include "editor.h"


int main(int argc, char *argv[])
{


    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Editor myEditor;

    QQmlContext *context = engine.rootContext();
    /* Below line makes myEditor object and methods available in QML as "MyEditor" */
    context->setContextProperty("MyEditor", &myEditor);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    engine.load(url);

    return app.exec();


}
