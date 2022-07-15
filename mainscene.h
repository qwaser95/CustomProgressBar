#pragma once

#include <QMainWindow>
#include <QFrame>
#include <QSlider>
#include <QVBoxLayout>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class mainScene; }
QT_END_NAMESPACE


class CircularProgress : public QWidget
{
    Q_OBJECT

public:
    CircularProgress(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void addShadow(bool enable);

    QPainter *paint = nullptr;
    QRect rect;
    QPen pen;
    QGraphicsDropShadowEffect *shadow;

    //default property
    int     value = 0,
            width = 200,
            height = 200,
            progress_width = 10,
            max_value = 100,
            font_size = 12;
    bool    progress_rounded_cap = true;
    int     progress_color = 0x498BD1,
            text_color = 0x498BD1;
    QString font_family = "Segoe UI",
            suffix = "%";

public slots:
    void setValue(int value);

};

class mainScene : public QMainWindow
{
    Q_OBJECT

public:
    mainScene(QWidget *parent = nullptr);
    ~mainScene();

private:
    Ui::mainScene *ui;
    QSlider *slider;
    QVBoxLayout *layout = nullptr;
    CircularProgress *progress = nullptr;
};
