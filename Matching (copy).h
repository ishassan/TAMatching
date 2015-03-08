#ifndef MATCHING_H
#define MATCHING_H

#include <bits/stdc++.h>
#include <ctime>

using namespace std;

const int inf = 1e8;

class Matching{
    vector<string> ta,courses;
    vector<vector<pair<int,int> > > preferences;
    int taLoad, courseLoad;
    vector<int> visCourse;
    vector<vector<bool> > assigns,bestAssigns;

    void calc(int taIdx, int lstTaken, int remCoursesForTA, int unitMatch, multiset<int,greater<int> >& allMatch){
        if(taIdx == (int)ta.size()){
            for (int i = 0; i < visCourse.size(); ++i) {
                if(visCourse[i] < courseLoad) return;
            }
            if(bestMatch < allMatch) return;

            bestMatch = allMatch;
            bestAssigns = assigns;
            return;
        }
        if(remCoursesForTA == 0){
            calc(taIdx+1,0,taLoad, 0,allMatch);
            return;
        }

        for (int i = lstTaken; i < (int)preferences[taIdx].size(); ++i) {
            dum++;
            if(preferences[taIdx][i].first >= inf) break;
            int course = preferences[taIdx][i].second;
            if(visCourse[course] < courseLoad){
                visCourse[course]++;
                assigns[taIdx][course]=1;
                if(remCoursesForTA == 1){
                    unitMatch+=preferences[taIdx][i].first;
                    allMatch.insert(unitMatch);
                    calc(taIdx+1,0,taLoad, 0,allMatch);
                    allMatch.erase(allMatch.find(unitMatch));
                    unitMatch-=preferences[taIdx][i].first;
                }
                else
                    calc(taIdx, i, remCoursesForTA-1, unitMatch+preferences[taIdx][i].first, allMatch);
                assigns[taIdx][course]=0;
                visCourse[course]--;
            }
        }

        if(remCoursesForTA < taLoad){
            allMatch.insert(unitMatch);
            calc(taIdx+1,0,taLoad, 0,allMatch);
            allMatch.erase(allMatch.find(unitMatch));
        }

    }

public:
    int dum;
    multiset<int,greater<int> > bestMatch;
    Matching(const vector<string>& ta, const vector<string>& courses, const vector<vector<pair<int,int> > >& preferences, int taLoad, int courseLoad){
        dum = 0;
        this->ta = ta;
        this->courses = courses;
        this->preferences = preferences;
        this->taLoad = taLoad;
        this->courseLoad = courseLoad;
        visCourse = vector<int>(courses.size(), 0);
        assigns = bestAssigns= vector<vector<bool> >(ta.size(), vector<bool>(courses.size(),0));
        for (int i = 0; i < (int)ta.size(); ++i)
            bestMatch.insert(inf);

    }

    vector<vector<bool> > match(){
        for (int i = 0; i < (int)preferences.size(); ++i) {
            sort(preferences[i].begin(), preferences[i].end());
        }
        multiset<int, greater<int> > a;
        calc(0,-1,taLoad,0,a);
        return bestAssigns;
    }
};

#endif // MATCHING_H
