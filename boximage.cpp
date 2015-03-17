#include "boximage.h"
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>
#include <QLayoutItem>
#include <iostream>

using namespace std;

BoxImage::BoxImage(QWidget* parent) : QWidget(parent)
{
    BoxImage::layout = new QGridLayout();
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    BoxImage::imageNum = 0;
    this->setLayout(layout);
}

BoxImage::~BoxImage()
{}

QGridLayout* BoxImage::getLayout()
{
    return layout;
}

bool BoxImage::openImage(QString filename)
{
    QPixmap image(filename, 0, Qt::AutoColor);
    if(image.isNull())
        return false;
    QLabel *label = new QLabel;
    label->setPixmap(image.scaled(150,150,Qt::KeepAspectRatio));
    label->setMaximumHeight(150);
    label->setMaximumWidth(150);
    label->setMinimumHeight(150);
    label->setMidLineWidth(150);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background-color: grey; border: 1px solid black ;");
    int row = imageNum/5;
    int column = imageNum%5;
    BoxImage::imageNum++;
    BoxImage::layout->addWidget(label, row, column);
    if(column == 0){
        for(int i=1; i<5; i++){
            layout->addWidget(new QWidget(), row, i);
        }
        layout->addWidget(new QWidget(), row+1, column);
    }
    return true;
}
bool BoxImage::invalidImage(QString filename)
{
    QMessageBox *msgBox = new QMessageBox;
    msgBox->setText("Image "+filename+" cannot be read. Continue or exit the application?");
    msgBox->addButton(tr("Continue"), QMessageBox::AcceptRole);
    msgBox->addButton(tr("Exit"), QMessageBox::RejectRole);
    int reply;
    reply = msgBox->exec();
    if(reply == QMessageBox::AcceptRole){
        return true;
    }else
        return false;
}
void BoxImage::slotAddImage()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::homePath());
    if(filename.isEmpty())
        return;
    bool suc = BoxImage::openImage(filename);
    if(!suc)
       BoxImage::invalidImage(filename);
}
void BoxImage::slotAddCollection()
{
    QString dirname = QFileDialog::getExistingDirectory(this, tr("Add Images from Directory"), QDir::homePath(), QFileDialog::ShowDirsOnly);
    if(dirname.isEmpty())
        return;
    QDir directory(dirname);
    foreach (QString filename, directory.entryList(QDir::Files))
    {
        filename = dirname + "/" + filename;
        bool suc = !filename.isEmpty() && BoxImage::openImage(filename);
        if(!suc){
            if(BoxImage::invalidImage(filename) == false)
                break;
        }
    }
}
void BoxImage::slotDeleteAllImages()
{
    QLayoutItem *child;
    while ((child = BoxImage::layout->takeAt(0)) != 0) {
        if (child->widget()) {
            delete child->widget();
            delete child;
        } else {
            delete child;
        }
    }
    BoxImage::imageNum = 0;
}
