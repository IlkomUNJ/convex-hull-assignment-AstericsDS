#ifndef SLOWHULL_H
#define SLOWHULL_H

#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <cmath>

static double cross(const QPointF &O, const QPointF &A, const QPointF &B) {
    return (A.x() - O.x()) * (B.y() - O.y()) - (A.y() - O.y()) * (B.x() - O.x());
}

inline QPolygonF slowConvexHull(const QVector<QPointF> &points) {
    QPolygonF hull;
    int n = points.size();
    if (n < 3) {
        for (auto &p : points) hull << p;
        return hull;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            QPointF p = points[i], q = points[j];
            int pos = 0, neg = 0;
            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) continue;
                double c = cross(p, q, points[k]);
                if (c > 0) pos++;
                else if (c < 0) neg++;
            }
            if (pos == 0 || neg == 0) {
                hull << p << q;
            }
        }
    }

    QVector<QPointF> uniq;
    for (const QPointF &pt : hull) if (!uniq.contains(pt)) uniq << pt;

    QPointF center(0,0);
    for (const QPointF &pt : uniq) center += pt;
    center /= uniq.size();

    std::sort(uniq.begin(), uniq.end(), [&](const QPointF &a, const QPointF &b) {
        return atan2(a.y() - center.y(), a.x() - center.x())
        < atan2(b.y() - center.y(), b.x() - center.x());
    });

    return QPolygonF(uniq);
}

#endif // SLOWHULL_H
