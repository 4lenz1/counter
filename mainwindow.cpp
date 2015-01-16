#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
vector<string> v;
QString filePath;
QString writeFilePath;
int totalRow;

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

    int index = 0 ;
    QTextStream in(&file);
    //    QString line ;
    

    ifstream inFile(filePath.toStdString());
    totalRow =  std::count(istreambuf_iterator<char> (inFile),
                           istreambuf_iterator<char>() , '\n');
    qDebug () <<  "output c  : " << totalRow ;


    ui->Progess->setText("Row: " + QString::number( totalRow ) + "\t\t\t File Size: " +
                         QString::number( file.size() ) + " bytes" );

    /* if(!fopen(filePath.toUtf8().constData(),"rw")){
        exit(1);
    }*/
    if(!file.open(QIODevice::ReadOnly)){
        exit(1);
    }
    // dict Vector
    vector<string> dictV ;



    int pos = 0 ;
    while (!in.atEnd()) {
        // create dict vector
        istringstream iss(in.readLine().toStdString());

        //after dict string
        string newstr ;

        //left side and right side
        for(int index = 0 ; index < 2 ; index ++){
            string substr ;
            iss >>substr ;

            auto findout =  std::find(dictV.begin() , dictV.end(),substr);
            if(findout == dictV.end()){
                pos++;
                dictV.push_back(substr);

                // use pos to improve performance instead of dictV.size()
                newstr +=  to_string( pos -1 ) + " ";

            }else{
                auto i = distance(dictV.begin() , findout);
                newstr  +=  to_string( i )+ " "  ;
            }

        } // split for end

        v.push_back(newstr);

        //reset string
        newstr = "" ;
        ui->progressBar->setValue(( ++index *100) / totalRow );
        ui->status->setText("Reading " + QString::number(index) +
                            "  of " +QString::number( totalRow));
    }  // while
    ui->status->setText("Read Completed.  "  + QString::number(index) +
                        " of " +QString::number( totalRow));
    file.close();


    filePath = QFileDialog::getSaveFileName(this, tr("Save File to"),
                                            "",
                                            tr("txt (*txt*)"));
    ui->lineOut->setText(filePath);

    //sort the vector
    ui->status->setText("sorting plz wait");
    qSort(v);
    ui->status->setText("sorted");

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

    for (int nextIndex = 1; nextIndex  < totalRow ; nextIndex  ++){
        if(v.at(OIndex) == v.at(nextIndex)){
            count ++;
        }else{
            countVector.push_back( v.at(OIndex)+ to_string( count ) );
            // next time is 1
            count = 1;
            OIndex  =  nextIndex;
            //nextIndex ++;
        }
    }

    // create scv file
    int max =  countVector.size() - 1;
    // qDebug() << max ;

//    vector<string> v2(max , 0);
//    vector<vector<string> > v2d2(max,v2);




//    std::ofstream out(filePath.toUtf8());
//       out << "[Map]" << std::endl;
//       v2d2.resize(max);

//       for(int i = 0; i < max; i++)
//       {
//           v2d2[i].resize(max);
//           for(int j = 0; j < max; j++)
//           {
//               char str[20];
//               sprintf(str, "%d ", v2d2[i][j]);
//               out << str;
//           }
//           out << '\n';
//       }




    ofstream outputFile(filePath.toStdString());
    ostream_iterator<string> output_iterator(outputFile, "\n");
   //copy( v2d2.begin() , v2d2.end(), output_iterator);
    copy(  countVector.begin() , countVector.end(), output_iterator);
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
