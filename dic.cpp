#include <dic.h>


void swap(vector<string> v , int totalRow){

    int No = 0 ;
    vector<string> newV ;
    QString str ;
    QStringList list ;
    for(int index = 0 ; index < totalRow  ; index++){
        str = QString::fromStdString( v.at(index));
        list =  str.split(" ");
    }

}
