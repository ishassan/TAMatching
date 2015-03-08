#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <bits/stdc++.h>
#include "ParseExcel.h"
#include "Matching.h"
#include <WriteExcel.h>

using namespace std;

class Controller : public QObject
{
    QString excelfile_,outputfile_;
    Q_OBJECT
    int courseload_;
    int taload_;
    int ta_uniq_courses_;
    int numchoice_;
    void sortCourses(vector<string>& courses, vector<int>& courseload_, vector<vector< pair<int,int> > >& courseToTAs);

public:
    explicit Controller(QString excelfile, int numchoice, int taload, int tacourses, QObject *parent = 0);
    void run();
    QString getOutputFile();
};

#endif // CONTROLLER_H
