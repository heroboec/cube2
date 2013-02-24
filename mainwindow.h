#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QPainter>
#include <QImage>

class cube;
class QVBoxLayout;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void repCube(QImage& img);
signals:
    void rotate(double, double);
    void resizeImg(int,int);
    
private:
    Ui::MainWindow *ui;
    QImage cubeImage;
    cube *myCube;
    QVBoxLayout *layout;



    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);


};

#endif // MAINWINDOW_H
