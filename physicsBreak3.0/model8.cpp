#include "models.h"
#include "plot.h"

Model8::Model8()
{
    ent = new Qt3DCore::QEntity();
    inf =  new QVBoxLayout();
    set =  new QVBoxLayout();
    LoadModel();


}



void Model8::Transform()
{
    gtr->setRotationX(35.f);//angle

}

void Model8::LoadModel()
{
    addObject(ent, ":/Res/Room.obj", ":/Res/Room.png");
    addObject(ent, ":/Res/ceiling.obj", ":/Res/ceiling.jpg");
    addObject(ent, ":/Res/tablemetal.obj", ":/Res/tablemetal.png");

    addObject(ent, ":/Stands/Math8/stand.obj", ":/Stands/Math8/stand.jpg");
    addObject(ent, ":/Stands/Math8/tab.obj", ":/Stands/Math8/tab.jpg");
    Qt3DCore::QEntity *p1 = addObject(ent, ":/Stands/Math8/plas.obj", ":/Stands/Math8/plas.jpg");
    Qt3DCore::QEntity *p2 = addObject(ent, ":/Stands/Math8/plas.obj", ":/Stands/Math8/plas.jpg");
    Qt3DCore::QEntity *gp1 = addObject(ent, ":/Stands/Math8/shar.obj", ":/Stands/Math8/plas.jpg");
    Qt3DCore::QEntity *gp2 = addObject(ent, ":/Stands/Math8/rope.obj", ":/Stands/Math8/rope.jpg");




    tr1 = new Qt3DCore::QTransform();
    tr2 = new Qt3DCore::QTransform();
    gtr = new Qt3DCore::QTransform();
    p1->addComponent(tr1);
    p2->addComponent(tr2);
    gp1->addComponent(gtr);
    gp2->addComponent(gtr);
    tr1->setTranslation({0. , 0., -.5f});
    tr2->setTranslation({0. , 0., .5f});
    gtr->setTranslation({0., 0.8042f, 0.});



    Transform();
   /* tr1->setTranslation(QVector3D(0., 0.681, 0.));
    g1->setTranslation(QVector3D(0., 1.443, 0.));
    g2->setTranslation(QVector3D(0., 1.443, 0.));
    gq->setTranslation(QVector3D(0., 1.443, 0.));*/

}


void Model8::Init()
{

}

void Model8::Compute(double dt)
{

}

void Model8::Update(double dt)
{
    Compute(dt);
    Transform();
}

void Model8::CreatePlot(int)
{

}

