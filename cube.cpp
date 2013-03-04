

#include <qmath.h>
#include <QtAlgorithms>
#include <QDebug>
#include "cube.h"



cube::cube()
{
    init();
    m_cubeImage = QImage(QSize(m_cubeW,m_cubeH),QImage::Format_RGB32);
    m_cubePainter = new QPainter(&m_cubeImage);
    m_cubePainter->setBackground(Qt::black);
  // evaluateCube();

}

void cube::init()
{

    PointDDD tmp0 = PointDDD( 1, 1, 1);
    PointDDD tmp1 = PointDDD( 1,-1, 1);
    PointDDD tmp2 = PointDDD( 1, 1,-1);
    PointDDD tmp3 = PointDDD( 1,-1,-1);

    m_faces[0] = Face(tmp0,tmp1,tmp2,tmp3);

    tmp0 = PointDDD( 1,-1, 1);
    tmp1 = PointDDD(-1,-1, 1);
    tmp2 = PointDDD( 1,-1,-1);
    tmp3 = PointDDD(-1,-1,-1);

    m_faces[1] = Face(tmp0,tmp1,tmp2,tmp3);

    tmp0 = PointDDD(-1,-1, 1);
    tmp1 = PointDDD(-1, 1, 1);
    tmp2 = PointDDD(-1,-1,-1);
    tmp3 = PointDDD(-1, 1,-1);

    m_faces[2] = Face(tmp0,tmp1,tmp2,tmp3);

    tmp0 = PointDDD(-1, 1, 1);
    tmp1 = PointDDD( 1, 1, 1);
    tmp2 = PointDDD(-1, 1,-1);
    tmp3 = PointDDD( 1, 1,-1);


    m_faces[3] = Face(tmp0,tmp1,tmp2,tmp3);



    tmp0 = PointDDD( 1, 1, 1);
    tmp1 = PointDDD( 1,-1, 1);
    tmp2 = PointDDD(-1, 1, 1);
    tmp3 = PointDDD(-1,-1, 1);


    m_faces[4] = Face(tmp0,tmp1,tmp2,tmp3);



    tmp0 = PointDDD(-1,-1,-1);
    tmp1 = PointDDD(-1, 1,-1);
    tmp2 = PointDDD( 1,-1,-1);
    tmp3 = PointDDD( 1, 1,-1);
    m_faces[5] = Face(tmp0,tmp1,tmp2,tmp3);


    m_phi = 0;
    m_omega = 0;
    m_cubeW = 800;
    m_cubeH = 600;


    //lights

    m_lights.clear();
    lightSourceData lsd;  // =)
    lsd.amp = 1;
    lsd.color = QColor(255,0,0,255);
    lsd.pos = PointDDD(2,2,2);
    m_lights.append(lsd);
    lsd.amp = 0.3;
    lsd.color = QColor(Qt::blue);
    lsd.pos = PointDDD(-2,-2,-2);
    m_lights.append(lsd);
    lsd.amp = 0.7;
    lsd.color = QColor(Qt::blue);
    lsd.pos = PointDDD(2,-2,3);
    m_lights.append(lsd);
    lsd.amp = 1;
    lsd.color = QColor(0,255,0,50);
    lsd.pos = PointDDD(2,-2,-2);
    m_lights.append(lsd);

    m_cubeCenter.setX(0);
    m_cubeCenter.setY(0);
    m_cubeCenter.setZ(0);

    m_screenLighsPos.clear();
    m_visLightPos.clear();
    a = b = c = d = 0;

    m_amb = 0.3f;
    m_spec = 0.5f;
    m_diff = 0.97f;


}



QVector3D& cube::createVectorByPoint(PointDDD& a,PointDDD& b)
{
    QVector3D *tmp = new QVector3D();
    tmp->setX(b.getX() - a.getX());
    tmp->setY(b.getY() - a.getY());
    tmp->setZ(b.getZ() - a.getZ());
    return *tmp;
}





void cube::evaluatePolygonsNormals()
{

}


void cube::evaluateCube()
{
    a = cos(m_phi/180);
    b = sin(m_phi/180);

    c = cos(m_omega/180);
    d = sin(m_omega/180);
    QPen pen;
    pen.setColor(Qt::cyan);
    pen.setStyle(Qt::SolidLine);
    m_cubePainter->setPen(pen);
    clearCubeImage();
    QVector< Polygon > tmpScreenCoords;
   // tmpScreenCoords.clear();
    for (int i=0;i<6;i++)
    {
        m_faces[i].calculate(a,b,c,d);
    }
    m_visLightPos.clear();
    m_screenLighsPos.clear();
    for (int i = 0; i<m_lights.count();i++)
    {        
            lightSourceData tmp = m_lights[i];
            PointDDD newPos;
            newPos.setX((-d)*tmp.pos.getX()+c*tmp.pos.getY());
            newPos.setY((-a)*c*tmp.pos.getX()+(-a)*d*tmp.pos.getY()+b*tmp.pos.getZ());
            newPos.setZ((-b)*c*tmp.pos.getX()+(-b)*d*tmp.pos.getY()+(-a)*tmp.pos.getZ() + 5);
            m_visLightPos.append(newPos);

            QPoint newScreenCoord = QPoint(300*(m_visLightPos[i].getX()/
                                                m_visLightPos[i].getZ())+800/2,
                                           300*(m_visLightPos[i].getY()/
                                                m_visLightPos[i].getZ())+600/2);
            m_screenLighsPos.append(newScreenCoord);
    }




    for (int i=0;i<m_lights.count();i++)
    {
        QColor colorr(m_lights[i].color);
        pen.setColor(Qt::white);
        QBrush br(colorr);
        m_cubePainter->setBrush(br);
        pen.setStyle(Qt::SolidLine);
        m_cubePainter->setPen(pen);
        m_cubePainter->drawEllipse(m_screenLighsPos[i].x(),m_screenLighsPos[i].y(),10,10);
    }



    m_faceArr.clear();
    for (int j=0;j<6;j++)
    {
        m_faceArr.append(m_faces[j]);
    }

    qSort(m_faceArr.begin(), m_faceArr.end(),order);

    QColor col(Qt::red);
    evaluateSimpleInt();
    for (int t=2;t>-1;t--)
    {
//        drawFaceColor(m_faceArr[t],col);
        pen.setColor(Qt::cyan);
        pen.setStyle(Qt::SolidLine);
        m_cubePainter->setPen(pen);
        //drawFace(m_faceArr[t]);
    }
    emit(repCube(m_cubeImage));
}








void cube::rotate(double omega, double phi)
{
    m_omega += omega;
    m_phi += phi;
    evaluateCube();
}


void cube::link(QPoint& p1,QPoint& p2)
{    
    m_cubePainter->drawLine(p1.x(),p1.y(),p2.x(),p2.y());
}

void cube::clearCubeImage()
{
    m_cubePainter->eraseRect(0,0,m_cubeW,m_cubeH);
    m_cubePainter->setBackground(Qt::black);
}


void cube::evaluateSimpleInt()
{

    int ax,r,g,b;
    double NandL;

    for (int i=2;i>-1;i--)
    {
        for (int k = 0;k<2;k++)
        {
            r=g=b=1;
            Polygon poly = m_faceArr[i].getNPolygon(k);
            for (int j=0;j<m_lights.count();j++)
            {
//                QVector3D L = this->createVectorByPoint(m_cubeCenter,m_lights[j].pos);
                QVector3D L(m_lights[j].pos.getX(),m_lights[j].pos.getY(),m_lights[j].pos.getZ());
                double distance = createVectorByPoint(poly.getMid(),m_lights[j].pos).length();
                L.normalize();
                QVector3D n = poly.getNormal();
                NandL = QVector3D::dotProduct(n,L);
                float angle = getDegree(NandL);
                double lightPart;
                if (angle >= 0 && angle<=90)
                {
                    lightPart = (m_diff*m_lights[j].amp*NandL)/(distance+0.2);
                }
                else
                {
                     lightPart = 0;
                }

                a =  0.3*0.3+lightPart;

                r+= m_lights[j].color.red()*a;
                g+= m_lights[j].color.green()*a;
                b+= m_lights[j].color.blue()*a;

                if (r>255) r = 255;if (r<0) r = 0;
                if (g>255) g = 255;if (g<0) g = 0;
                if (b>255) b = 255;if (b<0) b = 0;
                QColor clr(r,g,b);
                drawPolyColor(poly,clr);
            }
        }
    }
}



double cube::getDegree(double cosin)
{
    return (acos(cosin)*180)/3.1415;
}


bool cube::order(  Face & p1,  Face & p2 )
{
    return p1.getFaceLayer() < p2.getFaceLayer();
}

bool cube::pointCompare(QPoint& pnt1, QPoint& pnt2)
{
    return pnt1.y() > pnt2.y();
}


void cube::drawFace(Face& fce)
{
    for (int i =0;i<2;i++)
    {
        Polygon tmp = fce.getNPolygon(i);
        ScreenPolygonCoordsStruct poly =  tmp.getScreenCords();
        m_cubePainter->drawLine(poly.v0.x(),poly.v0.y(),poly.v1.x(),poly.v1.y());
        m_cubePainter->drawLine(poly.v0.x(),poly.v0.y(),poly.v2.x(),poly.v2.y());
        m_cubePainter->drawLine(poly.v1.x(),poly.v1.y(),poly.v2.x(),poly.v2.y());

    }
}


void cube::drawPolyColor(Polygon & poly, QColor& color)
{
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    m_cubePainter->setPen(pen);
    ScreenPolygonCoordsStruct tmpSCoords = poly.getScreenCords();
    QVector <QPoint> pointArr;
    pointArr.clear();
    pointArr.append(tmpSCoords.v0);
    pointArr.append(tmpSCoords.v1);
    pointArr.append(tmpSCoords.v2);

    qSort(pointArr.begin(),pointArr.end(),pointCompare);
    QPoint A = pointArr[0];
    QPoint B = pointArr[1];
    QPoint C = pointArr[2];


    int sy = A.y();
    int x1,x2;
    for (sy = A.y(); sy >= C.y(); sy--) {
        if (A.y() == C.y())
        {
            x1 = A.x();
        }
        else
        {
            x1 = (int)(A.x() + (sy - A.y()) * (C.x() - A.x()) / (C.y() - A.y()));
        }
        if (sy > B.y())
            if (A.y() == B.y())
            {
                x2 = A.x();
            }
        else
            {
                x2 = (int)(A.x() + (sy - A.y()) * (B.x() - A.x()) / (B.y() - A.y()));
            }
      else {
            if (C.y() == B.y())
            {
                x2 = B.x();
            }
        else
            {
                x2 = (int)(B.x() + (sy - B.y()) * (C.x() - B.x()) / (C.y() - B.y()));
            }
      }
        m_cubePainter->drawLine(x1,sy,x2,sy);
    }
}


void cube::drawFaceColor(Face& fce, QColor& color)
{
    for (int i=0;i<2;i++)
    {
        Polygon tmpPoly = fce.getNPolygon(i);
        drawPolyColor(tmpPoly,color);
    }
}





