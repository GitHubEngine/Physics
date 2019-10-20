#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DCore>
#include <QGeometryRenderer>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QGeometry>

class Trajectory
{
public:
    Trajectory(Qt3DCore::QEntity *rootEntity);

    void Draw(QVector3D point);
    void Clear(QVector3D point);
    void SetDot(QVector3D point);

private:
    Qt3DCore::QEntity *rootEntity;
    Qt3DRender::QGeometry *geometry;

    Qt3DRender::QBuffer *vertexBuffer;
    Qt3DRender::QBuffer *indexBuffer;

    Qt3DRender::QAttribute *positionAttr;
    Qt3DRender::QAttribute *indexAttr;

    QByteArray *vertexBytes;
    QByteArray *indexBytes;

    int dotsAmount = 1000;
    QList<float> dots;

    Qt3DCore::QEntity *lineEntity;
    Qt3DRender::QGeometryRenderer *line;
    Qt3DExtras::QPhongMaterial *material;
};

#endif
