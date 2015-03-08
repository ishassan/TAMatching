#ifndef MATCHING_H
#define MATCHING_H

#include <bits/stdc++.h>
#include <ctime>
#include "global.h"
#include "Controller.h"
#include "WriteExcel.h"

using namespace std;

class Matching : public QObject{
    vector<string> ta_,courses_; //Names of TAs and courses.
    vector<vector<pair<int,int> > > course_to_tas_; //Given a course id, get a vector of TAs who selected it. A TA is represented by a pair of (cost of selecting this course, TA ID).
    int ta_load_; //Maxmum number of teaching slots a TA can teach.
    int ta_uniq_courses_; //Maximum number of unique courses a TA can teach per semester.
    vector<int> course_load_; //Given a course id, get the number of teaching slots needed for this course.

    multiset<int, greater<int> > best_ta_costs_; //Holds the costs of all TAs in descending order.
    vector<int> vis_ta_; // Counts the number of slots a TA teaches in the current assignment.
    vector<int> bad_courses_; // Holds the courses that no TA desires to teach.
    vector<int> cnt_uniq_; // Counts the number of unique courses a TA teaches in the current assignment.
    vector<vector<int> > assigns_; // assigns[TA ID][Course ID] = number of teaching slots a TA teaches for this course.
    vector<vector<int> > best_assigns_; // Holds the most optimal copy of "assigns" data structure so far.
    int bad_course_cost_; // Cost of assigning a bad course to a TA. A bad course for a TA is a course that the TA doesn't want to teach it.
    QString outputfile_; //path of output file.

    void AssignBadCourses(vector<int>& ta_costs, vector<vector<int> >& assigns){
        //Insert all TAs in a priority queue. The TAs are sorted from lowest to highest costs.
        priority_queue<pair<int,int> , vector<pair<int,int> >, greater<pair<int,int> > > q;
        for (int i = 0; i < (int)ta_costs.size(); ++i)
            q.push(make_pair(ta_costs[i], i));

        // Distribute bad courses to TAs in order.
        for(int i = 0; i < (int)bad_courses_.size(); i++){
            int bad = bad_courses_[i];
            while(bad--){
                pair<int,int> pair_ta = q.top();
                q.pop();
                ta_costs[pair_ta.second] += bad_course_cost_;
                assigns[pair_ta.second][i]++;
                pair_ta.first += bad_course_cost_;
                q.push(pair_ta);
            }
        }
    }
    inline bool CanTakeCourse(int ta_idx, int course_idx){
        if(vis_ta_[ta_idx] == ta_load_) return 0;
        bool add = !assigns_[ta_idx][course_idx];
        if(cnt_uniq_[ta_idx] + add > ta_uniq_courses_) return 0;
        return 1;
    }

    void Log(){
        cerr << "LOG\n";
        for (int i = 0; i < (int)ta_.size(); ++i) {
            cerr << ta_[i] << ":\n";
            for (int j = 0; j < (int)best_assigns_[i].size(); ++j) {
                cerr << best_assigns_[i][j] << " ";
            }
            cerr << "\n";
        }
        cerr << flush;
    }

    bool CalcBestAssign(int course_idx, int lst_taken_ta, int rem_ta_for_course, bool is_bad_course, vector<int>& ta_costs, multiset<int, greater<int> >& set_ta_costs){
        if(best_ta_costs_ < set_ta_costs){
            return 1;
        }

        if(course_idx == (int)courses_.size()){
            vector<int> curTACosts = ta_costs;
            vector<vector<int> > curAssigns = assigns_;
            multiset<int, greater<int> > compTACosts;
            if(is_bad_course){
                AssignBadCourses(curTACosts, curAssigns);
                compTACosts = multiset<int, greater<int> >(curTACosts.begin(), curTACosts.end());
            }
            else
                compTACosts = set_ta_costs;

            if(compTACosts < best_ta_costs_){
                best_ta_costs_ = compTACosts;
                best_assigns_ = curAssigns;
                cerr << "*****Yes*****\n";
                Log();
                WriteExcel writeExcel(outputfile_, this);
                writeExcel.run(ta_,courses_, course_to_tas_,best_assigns_);
                return 1;
            }

            return 1;
        }

        bool valid=0;
        for (int i = lst_taken_ta; i < (int)course_to_tas_[course_idx].size(); ++i) {
            int taIdx = course_to_tas_[course_idx][i].second;
            if(CanTakeCourse(taIdx, course_idx)){
                vis_ta_[taIdx]++;
                bool add = !assigns_[taIdx][course_idx];
                cnt_uniq_[taIdx] += add;
                assigns_[taIdx][course_idx]++;

                //update costs
                set_ta_costs.erase(set_ta_costs.find(ta_costs[taIdx]));
                ta_costs[taIdx] += course_to_tas_[course_idx][i].first;
                set_ta_costs.insert(ta_costs[taIdx]);

                if(rem_ta_for_course == 1)
                    valid |= CalcBestAssign(course_idx+1,0,course_load_[course_idx+1],is_bad_course,ta_costs,set_ta_costs);
                else
                    valid |= CalcBestAssign(course_idx,i,rem_ta_for_course-1,is_bad_course,ta_costs,set_ta_costs);

                //get old cost
                set_ta_costs.erase(set_ta_costs.find(ta_costs[taIdx]));
                ta_costs[taIdx] -= course_to_tas_[course_idx][i].first;
                set_ta_costs.insert(ta_costs[taIdx]);

                assigns_[taIdx][course_idx]--;
                cnt_uniq_[taIdx] -= add;
                vis_ta_[taIdx]--;
            }
        }

        if(!valid){
            bad_courses_[course_idx] = rem_ta_for_course;
            valid = CalcBestAssign(course_idx+1,0,course_load_[course_idx+1],1,ta_costs,set_ta_costs);
            bad_courses_[course_idx] = 0;
        }
        return valid;
    }

public:

    Matching(const vector<string>& ta, const vector<string>& courses, const vector<vector<pair<int,int> > >& courseToTAs, int taLoad, int taUniqCourses, const vector<int>& courseLoad, const QString& outputfile){
        this->ta_ = ta;
        this->courses_ = courses;
        this->course_to_tas_ = courseToTAs;
        this->ta_load_ = taLoad;
        this->ta_uniq_courses_ = taUniqCourses;
        this->course_load_ = courseLoad;

        this->course_load_.resize(courseLoad.size()+1);
        this->outputfile_ = outputfile;

        best_ta_costs_.clear();
        for(int i = 0; i < (int)ta.size(); i++) best_ta_costs_.insert(INF);

        vis_ta_ = vector<int>(ta.size(), 0);
        bad_courses_ = vector<int>(courses.size(), 0);
        assigns_ = best_assigns_= vector<vector<int> >(ta.size(), vector<int>(courses.size(),0));
        cnt_uniq_ = vector<int> (ta.size(),0);

        int startCost = kCostLowerBound+kChoiceStartCol;
        bad_course_cost_ = startCost*2-2; //taking 1 slot of unwanted course is better than taking 2 slots of the most wanted course
    }

    vector<vector<int> >& match(){
        vector<int> taCosts(ta_.size(),0);
        multiset<int, greater<int> > setTACosts(taCosts.begin(), taCosts.end());
        CalcBestAssign(0,0,course_load_[0],0,taCosts,setTACosts);

        return best_assigns_;

    }

};

#endif // MATCHING_H
