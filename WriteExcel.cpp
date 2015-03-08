#include "WriteExcel.h"

WriteExcel::WriteExcel(QString outputfile, QObject *parent) :
    QObject(parent)
{
    this->outputfile = outputfile;
}

void WriteExcel::run(const vector<string>& ta, const vector<string>& courses, const vector<vector< pair<int,int> > >& courseToTAs, const vector<vector< int > >& match){
    QXlsx::Document excel;
    vector<vector<bool> > isCourseToTa(courses.size(), vector<bool>(ta.size()));
    for (int i = 0; i < (int)courseToTAs.size(); ++i)
        for (int j = 0; j < (int)courseToTAs[i].size(); ++j)
            isCourseToTa[i][ courseToTAs[i][j].second ] = 1;
    int i;
    for (i = 0; i < (int)match.size(); ++i) {
        int col=1;
        excel.write(i+1,col++,ta[i].c_str());
        for (int j = 0; j < (int)match[i].size(); ++j) {
            int ntimes = match[i][j];
            QXlsx::Format format;
            if(!isCourseToTa[j][i])
                format.setPatternBackgroundColor(Qt::red);
            while(ntimes--)
                excel.write(i+1,col++,courses[j].c_str(),format);
        }
    }
    i+=3;
    excel.write(i,1,"Cells marked with red (if any) are not within TA choices.");
    excel.saveAs(outputfile);
}
