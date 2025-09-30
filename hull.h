#ifndef HULL_H
#define HULL_H

#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <algorithm>

static double cross2(const QPointF &O, const QPointF &A, const QPointF &B) {
    return (A.x() - O.x()) * (B.y() - O.y()) - (A.y() - O.y()) * (B.x() - O.x());
}

inline QPolygonF fastConvexHull(QVector<QPointF> pts) {
    QPolygonF hull;
    if (pts.size() <= 1) return QPolygonF(pts);

    std::sort(pts.begin(), pts.end(), [](const QPointF &a, const QPointF &b) {
        if (a.x() == b.x()) return a.y() < b.y();
        return a.x() < b.x();
    });

    QVector<QPointF> lower, upper;
    for (const QPointF &p : pts) {
        while (lower.size() >= 2 && cross2(lower[lower.size()-2], lower[lower.size()-1], p) <= 0)
            lower.pop_back();
        lower.push_back(p);
    }
    for (int i = pts.size()-1; i >= 0; --i) {
        const QPointF &p = pts[i];
        while (upper.size() >= 2 && cross2(upper[upper.size()-2], upper[upper.size()-1], p) <= 0)
            upper.pop_back();
        upper.push_back(p);
    }

    lower.pop_back();
    upper.pop_back();

    for (const QPointF &p : lower) hull << p;
    for (const QPointF &p : upper) hull << p;

    return hull;
}

#endif // HULL_H
