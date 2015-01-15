#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QArrayData>

#include <fstream>
#include <iterator>
#include <string>

using namespace std;
vector<string> v;
QString filePath;
QString writeFilePath;
int totalData ;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Progess->setText("Plz select a data");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                            "",
                                            tr("txt (*txt*)"));
    
    ui->lineLoad->setText(filePath);
    
    ui->Progess->setText("counting row....");
    
    
    
    
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0, "error", file.errorString());
    }
    int index = 0 ;
    QTextStream in(&file);
    QString line ;
    
    
    while (!in.atEnd()) {
        line = in.readLine();
        index ++;
        // qDebug() << line;
    }
    // qDebug() << index;
    totalData = index ;
    qDebug() << "total data : " << totalData;
    QString row = QString::number(index);
    ui->Progess->setText("Row: " + row + "\t\t\t File Size: " +
                         QString::number( file.size() ) + " bytes" );
    
    

    //reset index
    index = 0 ;
    
    file.close();
    
    if(!file.open(QIODevice::ReadOnly)){
        exit(1);
    }
    
    
    //QVector<QString> vector;
    
    //QVector<QString> Qv;
    while (!in.atEnd()) {
        //line = in.readLine();
        //v.push_back( in.readLine().toStdString());
        v.push_back(in.readLine().toStdString());
        //qDebug() << v;
        
        ui->progressBar->setValue(( ++index *100) / totalData );
        ui->status->setText("Reading " + QString::number(index) +
                            "  of " +QString::number( totalData));
    }
    
    ui->status->setText("Read Completed.  "  + QString::number(index) +
                        " of " +QString::number( totalData));
    
    
    
    //Nv = v ;
    //Qv = QVector::fromStdVector(v) ;
    //    qDebug() << "vector sort result: ";
    file.close();
    
    
    filePath = QFileDialog::getSaveFileName(this, tr("Save File to"),
                                            "",
                                            tr("txt (*txt*)"));
    ui->lineOut->setText(filePath);
    
    
    //sort the vector
    ui->status->setText("sorting plz wait");
    qSort(v);
    ui->status->setText("sorted");
//    ofstream outputFile(filePath.toStdString());
//    ostream_iterator<string> output_iterator(outputFile, "\n");
//    copy(  v.begin() , v.end(), output_iterator);
//    // qCopy(Qv.begin() , Qv.empty() , output_iterator);
//    QMessageBox::information(this , "saved" , "File Saved !");
}


// start
// add  column
void MainWindow::on_pushButton_2_clicked()
{
    //check if not select file to count
    if(ui->lineOut->text() == ""){
        on_pushButton_clicked();
    }
    ui->status->setText("counting....");
    
    // if equal  , thats 2  not 1
    int count =  1;
    
    // count index
    int OIndex = 0;

    //create a new vector to record node & count
    vector<string> countVector;

    for (int nextIndex = 1; nextIndex  < totalData ; nextIndex  ++){
        if(v.at(OIndex) == v.at(nextIndex)){
            count ++;
        }else{

            countVector.push_back( v.at(OIndex) + " "+ to_string( count ) );

            //qDebug() << QString::fromStdString( countVector.at(OIndex)) ;
            // next time is 1
            count = 1;
            OIndex  =  nextIndex;
            //nextIndex ++;
        }
        
    }

    ofstream outputFile(filePath.toStdString());
    ostream_iterator<string> output_iterator(outputFile, "\n");
    copy(  countVector.begin() , countVector.end(), output_iterator);
    // qCopy(Qv.begin() , Qv.empty() , output_iterator);
      ui->status->setText("Done !");
    QMessageBox::information(this , "saved" , "File Saved !");

}

void MainWindow::on_pushButton_3_clicked()
{
    writeFilePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "",
                                                 tr("txt (*txt*)"));
    ui->lineOut->setText(writeFilePath);
}

void MainWindow::on_actionQt_triggered()
{
    QMessageBox::aboutQt(this , "About Qt");
}

void MainWindow::on_actionAbout_4lenz1_triggered()
{
    QMessageBox::about(this , "About this application"
                       ,"pingfallenzone@gmail.com \n"
                       "only use for the home work for BIG DATA .");
}
