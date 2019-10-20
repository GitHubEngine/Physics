#include "trajectory.h"

Trajectory::Trajectory(Qt3DCore::QEntity *rootEntity)
{
    this->rootEntity = rootEntity;

    geometry = new Qt3DRender::QGeometry(rootEntity);

    vertexBytes = new QByteArray();
    vertexBytes->resize(3 * 2 * sizeof(float));

    vertexBuffer = new Qt3DRender::QBuffer(geometry);
    vertexBuffer->setData(*vertexBytes);

    positionAttr = new Qt3DRender::QAttribute(geometry);
    positionAttr->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    positionAttr->setVertexBaseType(Qt3DRender::QAttribute::Float);
    positionAttr->setVertexSize(3);
    positionAttr->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttr->setBuffer(vertexBuffer);
    positionAttr->setByteStride(3 * sizeof(float));
    positionAttr->setCount(0);
    geometry->addAttribute(positionAttr);


    indexBytes = new QByteArray();
    indexBytes->resize(dotsAmount * sizeof(unsigned int));
    unsigned int *indices = reinterpret_cast<unsigned int*>(indexBytes->data());
    for (unsigned int i = 0; i < dotsAmount; i++)
        *indices++ = i;

    indexBuffer = new Qt3DRender::QBuffer(geometry);
    indexBuffer->setData(*indexBytes);

    indexAttr = new Qt3DRender::QAttribute(geometry);
    indexAttr->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
    indexAttr->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    indexAttr->setBuffer(indexBuffer);
    indexAttr->setCount(dotsAmount);
    geometry->addAttribute(indexAttr);

    line = new Qt3DRender::QGeometryRenderer();
    line->setGeometry(geometry);
    line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);

    material = new Qt3DExtras::QPhongMaterial(rootEntity);
    material->setAmbient(QColor(0, 0, 0, 255));

    lineEntity = new Qt3DCore::QEntity(rootEntity);
    lineEntity->addComponent(material);
    lineEntity->addComponent(line);
}

void Trajectory::SetDot(QVector3D point)
{
    dots.append(point.x());
    dots.append(point.y());
    dots.append(point.z());
    dots.append(point.x());
    dots.append(point.y());
    dots.append(point.z());

    positionAttr->setCount(2);
    indexAttr->setCount(2);
    vertexBytes->resize(dots.size() * sizeof(float));

    float *pos = reinterpret_cast<float*>(vertexBytes->data());
    for (auto x : dots)
        *pos++ = x;

    vertexBuffer->setData(*vertexBytes);
}

void Trajectory::Draw(QVector3D point)
{   
    line->setPrimitiveType(Qt3DRender::QGeometryRenderer::LineStrip);

    dots.append(point.x());
    dots.append(point.y());
    dots.append(point.z());

    if (dots.size() > dotsAmount * 3)
        for (int i = 0; i < 3; i++)
            dots.pop_front();

    positionAttr->setCount(dots.size() / 3);
    indexAttr->setCount(dots.size() / 3);
    vertexBytes->resize(dots.size() * sizeof(float));

    float *pos = reinterpret_cast<float*>(vertexBytes->data());
    for (auto x : dots)
        *pos++ = x;

    vertexBuffer->setData(*vertexBytes);
}

void Trajectory::Clear(QVector3D point)
{
    dots.clear();

    dots.append(point.x());
    dots.append(point.y());
    dots.append(point.z());

    dots.append(point.x());
    dots.append(point.y());
    dots.append(point.z());

    vertexBytes->clear();
    vertexBytes->resize(3 * 2 * sizeof(float));
    positionAttr->setCount(2);
    indexAttr->setCount(2);

    float *pos = reinterpret_cast<float*>(vertexBytes->data());
    for (auto x : dots)
        *pos++ = x;

    vertexBuffer->setData(*vertexBytes);
}
