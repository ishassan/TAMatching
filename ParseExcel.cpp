#include "ParseExcel.h"
#include "Matching.h"

ParseExcel::ParseExcel(QString excelfile, int numchoice)
{
    excel = new QXlsx::Document(excelfile);
    choice_num = numchoice;
}

void ParseExcel::run(){
    ta.clear();
    courses.clear();
    taToIdx.clear();
    courseToIdx.clear();
    courseLoad.clear();
    
    const QStringList& sheets = excel->sheetNames();
    extractMetaData(sheets[kMetadataSheet]);
    extractPreferences(sheets[kPreferencesSheet]);
}

void ParseExcel::extractMetaData(const QString& sheetname){
    excel->selectSheet(sheetname);

    //TODO: loop on exactly rowCount
    bool data = true;
    for (int i = 2; data; ++i) {
        data = false;
        QVariant tacell = excel->read(i,kListOfTACol);
        QVariant coursecell = excel->read(i,kListOfCoursesCol);
        QVariant cloadcell = excel->read(i, kListOfCourseLoadCol);

        if(!tacell.isNull()){
            data = true;
            string taname = tacell.toString().toStdString();
            taToIdx[taname] = ta.size();
            ta.push_back(taname);
        }
        if(!coursecell.isNull()){
            data = true;
            string coursename = coursecell.toString().toStdString();
            courseToIdx[coursename] = courses.size();
            courses.push_back(coursename);

            int courseload = cloadcell.toInt();
            courseLoad.push_back(courseload);
        }
    }
}

void ParseExcel::extractPreferences(const QString &sheetname){
    excel->selectSheet(sheetname);
    courseToTAs.clear();
    courseToTAs.resize(courses.size());
    //TODO: loop on exactly rowCount
    //TODO: catch exception for wrong input formats
    //TODO: be flexible to file input format

    bool visCourse[1000];
    for (int i = 2; ; ++i) {
        QVariant tacell = excel->read(i,kTANameCol);
        if(tacell.isNull()) break;
        string taname = tacell.toString().toStdString();
        if(taToIdx.count(taname) == 0) continue;
        int taIdx = taToIdx[taname];
        memset(visCourse,0,sizeof visCourse);
        for (int j = kChoiceStartCol; j < kChoiceStartCol+choice_num; ++j) {
            QVariant coursecell = excel->read(i,j);
            if(coursecell.isNull()) continue;
            string coursename = coursecell.toString().toStdString();
            if(courseToIdx.count(coursename) == 0) continue;
            int courseIdx = courseToIdx[coursename];
            if(!visCourse[courseIdx]){
                visCourse[courseIdx] = 1;
                courseToTAs[courseIdx].push_back(make_pair(kCostLowerBound+j, taIdx));
            }

        }
    }

}

vector<string>& ParseExcel::getTA(){
    return ta;
}
vector<string>& ParseExcel::getCourses(){
    return courses;
}
vector<vector<pair<int, int> > > &ParseExcel::getCourseToTAs(){
    return courseToTAs;
}

vector<int>& ParseExcel::getCourseLoad(){
    return courseLoad;
}
