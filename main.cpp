#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "includes/SortAlgorithms.h"

template <class T>
void printVec(std::vector<T> vec) {
    for(unsigned int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
};

int main(int argc, char *argv[])
{
    std::vector<char> vec{'a', 'z', 'g', 'l', 'r', 'b', 'c'};
    SortAlgorithms<char>* sa = new IterationMerge<char>();
    sa->sort(vec);
    printVec(vec);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
