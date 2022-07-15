#include "mainscene.h"
#include "ui_mainscene.h"
#include <QDebug>

mainScene::mainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainScene)
{
    ui->setupUi(this);
    this->resize(500, 500);

    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    layout = new QVBoxLayout(this);

    progress = new CircularProgress(this);
    progress->value = 50;
    progress->font_size = 12;
    progress->setMinimumSize(progress->width, progress->height);
    progress->addShadow(true);

    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, 100);
    connect(slider, &QSlider::valueChanged, progress, &CircularProgress::setValue);


    layout->addWidget(progress, Qt::AlignCenter, Qt::AlignCenter);
    layout->addWidget(slider, Qt::AlignCenter, Qt::AlignCenter);

    ui->container->setLayout(layout);
}

mainScene::~mainScene()
{
    delete ui;
}

CircularProgress::CircularProgress(QWidget *parent)
{
    Q_UNUSED(parent)
}

void CircularProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    int width = this->width - this->progress_width,
        height = this->height - this->progress_width,
        margin = this->progress_width / 2,
        value = this->value * 360 / this->max_value;

    paint = new QPainter();
    paint->begin(this);
    paint->setRenderHints(QPainter::Antialiasing);
    paint->setFont(QFont(font_family, font_size));

    rect = QRect(0, 0, this->width, this->height);
    paint->setPen(Qt::NoPen);
    paint->drawRect(rect);

    pen = QPen();
    pen.setColor(QColor(this->progress_color));
    pen.setWidth(this->progress_width);

    if (progress_rounded_cap)
        pen.setCapStyle(Qt::RoundCap);

    paint->setPen(pen);
    paint->drawArc(margin, margin, width, height, -90 * 16, -value * 16);

    pen.setColor(QColor(text_color));
    paint->setPen(pen);
    paint->drawText(rect, Qt::AlignCenter, QString::number(this->value) + suffix);


    paint->end();
}

void CircularProgress::addShadow(bool enable)
{
    if (enable) {
        shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(15);
        shadow->setXOffset(0);
        shadow->setYOffset(0);
        shadow->setColor(QColor(0, 0, 0, 80));
        setGraphicsEffect(shadow);
    }
}

void CircularProgress::setValue(int value)
{
    this->value = value;
    this->repaint();
}
