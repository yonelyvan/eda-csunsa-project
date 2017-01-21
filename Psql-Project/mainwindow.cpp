 #include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QImage>
#include <iostream>
#include <QFile>
#include <qfiledialog.h>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
string filename_img;
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName1 = QFileDialog::getOpenFileName(
                            this,
                            "Select one or more files to open",
                            "/home",
                            "Images (*.ppm *.pgm *.bmp *jpg *png)");
    QFile file1(fileName1);
     if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

     QTextStream in(&file1);
     while(!in.atEnd())
     {
        QString line = in.readLine();
     }
    //ui->lineEdit_1->setText(QFileInfo(file1).filePath());
    /* aqui carga la dirreccion y manda levantar*/

    QString filename = QFileInfo(file1).filePath();
    filename_img = filename.toStdString();
    cout<<"IMG:    |"<<filename_img<<"|"<<endl;
    QImage image( filename );
    if( image.isNull() )
    {
        cout<<"error , no se pudo cargar la imagen"<<endl;
    }
     ui->label_mainimage->setPixmap(QPixmap::fromImage( image ));

     // Para mostrar el tamaño de la imagen en bits
//    tam=file1.size();
  //  ui->label_propiedades->setText("Tamaño original : \n"+QString::number(tam) + " bytes");
}
