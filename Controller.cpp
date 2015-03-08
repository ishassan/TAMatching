#include "Controller.h"

Controller::Controller(QString excelfile, int numchoice, int taload, int tacourses, QObject *parent) :
    QObject(parent)
{
    this->excelfile_ = excelfile;
    this->numchoice_ = numchoice;
    this->taload_ = taload;
    this->ta_uniq_courses_ = tacourses; // maximum number of unique courses TA can teach

    int parFolder;
    for (parFolder = excelfile.size()-1; parFolder >= 0; --parFolder) {
        if(excelfile[parFolder]=='/' || excelfile[parFolder]=='\\') break;
    }
    outputfile_ = excelfile.mid(0,parFolder+1).append("output.xlsx");
}

void Controller::sortCourses(vector<string>& courses, vector<int>& courseload, vector<vector< pair<int,int> > >& courseToTAs){
    vector<int> indeces(courses.size());
    for (int i = 0; i < (int)indeces.size(); ++i) {
        indeces[i] = i;
    }

    //sorting courses according to number of TA who choose it
    sort(indeces.begin(), indeces.end(), [&](int idx1, int idx2){
        return courseToTAs[idx1].size() < courseToTAs[idx2].size();
    });
    sort(courseToTAs.begin(), courseToTAs.end(), [&](const vector< pair<int,int> >& v1, const vector< pair<int,int> >& v2){
        return v1.size() < v2.size();
    });

    //sorting TAs per course
    for (int i = 0; i < (int)courseToTAs.size(); ++i) {
        sort(courseToTAs[i].begin(),courseToTAs[i].end());
    }

    vector<string> sorted_courses(courses.size());
    vector<int> sorted_courseload(courses.size());
    for (int i = 0; i < (int)courses.size(); ++i) {
        sorted_courses[i] = courses[indeces[i]];
        sorted_courseload[i] = courseload[indeces[i]];
    }
    courses = sorted_courses;
    courseload = sorted_courseload;

}

void Controller::run(){
    ParseExcel parseExcel(excelfile_,numchoice_);
    parseExcel.run();

    vector<string>& ta = parseExcel.getTA();
    vector<string>& courses = parseExcel.getCourses();
    vector<int>& courseload = parseExcel.getCourseLoad();// minimum number of TAs per course
    vector<vector< pair<int,int> > >& courseToTAs = parseExcel.getCourseToTAs(); //given course, get TAs who selected this course
    sortCourses(courses, courseload, courseToTAs);

    //----
    for (int i = 0; i < (int)courseToTAs.size(); ++i) {
        cerr << i << " - " << courses[i] << "\n";
    }
    for (int i = 0; i < (int)courseToTAs.size(); ++i) {
        cerr << courses[i]  << " ( " << courseToTAs[i].size() << " ) "<< " : ";
        for (int j = 0; j < (int)courseToTAs[i].size(); ++j) {
            cerr << ta[courseToTAs[i][j].second] << ","<<courseToTAs[i][j].first << " | ";
        }
        cerr << "\n******\n";
    }
    //----

    Matching matching(ta, courses, courseToTAs, taload_, ta_uniq_courses_, courseload, outputfile_);
    vector<vector<int> >& mat = matching.match();
}

QString Controller::getOutputFile(){
    return outputfile_;
}
