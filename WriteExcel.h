#ifndef WRITEEXCEL_H
#define WRITEEXCEL_H

#include <QObject>
#include "xlsxdocument.h"
#include <bits/stdc++.h>
using namespace std;

class WriteExcel : public QObject
{
    QString outputfile;
    Q_OBJECT
public:
    explicit WriteExcel(QString outputfile, QObject *parent = 0);
    void run(const vector<string>& ta, const vector<string>& courses, const vector<vector< pair<int,int> > >& courseToTAs, const vector<vector< int > >& match);

signals:

public slots:

};

#endif // WRITEEXCEL_H
