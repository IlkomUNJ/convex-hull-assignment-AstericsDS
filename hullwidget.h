#ifndef HULLWIDGET_H
#define HULLWIDGET_H

#include <QWidget>
#include <QPointF>
#include <QVector>

class HullWidget : public QWidget {
    Q_OBJECT
public:
    explicit HullWidget(QWidget *parent = nullptr);
    void setUseSlow(bool val) { useSlow = val; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPointF> points;
    bool useSlow = false;
};

#endif // HULLWIDGET_H
