#include "hullwidget.h"

#include "slowhull.h"
#include "hull.h"
#include <QPainter>
#include <QRandomGenerator>

HullWidget::HullWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(300,300);
    // Generate random points
    for (int i=0; i<20; i++) {
        points << QPointF(QRandomGenerator::global()->bounded(280),
                          QRandomGenerator::global()->bounded(280));
    }
}

void HullWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Draw points
    p.setBrush(Qt::black);
    for (const QPointF &pt : points)
        p.drawEllipse(pt, 3, 3);

    // Compute hull
    QPolygonF hull = useSlow ? slowConvexHull(points) : fastConvexHull(points);

    // Draw hull
    p.setPen(QPen(Qt::red, 2));
    p.setBrush(Qt::NoBrush);
    p.drawPolygon(hull);
}
