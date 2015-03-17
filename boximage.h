#ifndef BOXIMAGE
#define BOXIMAGE

#include <QGridLayout>
#include <QScrollArea>
#include "mainwindow.h"

class BoxImage : public QWidget
{
    Q_OBJECT
public:
    BoxImage(QWidget* parent = 0);
    ~BoxImage();
    QGridLayout* getLayout();

private slots:
    void slotAddCollection();
    void slotAddImage();
    void slotDeleteAllImages();

private:
    QGridLayout* layout;
    int imageNum;
    bool openImage(QString filename);
    bool invalidImage(QString filename);
};
#endif // BOXIMAGE

