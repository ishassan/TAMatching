#ifndef PARSEEXCEL_H
#define PARSEEXCEL_H
#include <bits/stdc++.h>
#include <unordered_map>

#include <QString>
#include "qtxlsx/src/xlsx/xlsxdocument.h"
#include "qtxlsx/src/xlsx/xlsxworksheet.h"
#include "qtxlsx/src/xlsx/xlsxworkbook.h"
#include "Controller.h"
#include "Matching.h"

using namespace std;

class ParseExcel : public QObject
{
    QXlsx::Document* excel;
    vector<string> ta;
    vector<string> courses;
    vector<vector<pair<int,int> > > courseToTAs; //courseToTAs[courseidx] =  { pair(cost, taIdx) }
    unordered_map<string,int> taToIdx, courseToIdx;
    vector<int> courseLoad;

    int choice_num;

    void extractMetaData(const QString& sheetname);
    void extractPreferences(const QString& sheetname);

public:
    ParseExcel(QString excelfile, int numchoice);
    void run();
    vector<string>& getTA();
    vector<string>& getCourses();
    vector<vector<pair<int,int> > >& getCourseToTAs();
    vector<int>& getCourseLoad();

};

#endif // PARSEEXCEL_H
