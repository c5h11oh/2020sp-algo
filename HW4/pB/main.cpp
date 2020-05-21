#include <iostream>
#include <list>
using namespace std;
const int DAYS = 1e9;
//enum Status{ NONE = 0, ONCE = 1, FINISH = 2};
struct Visitor{
    short seenTimes = 0;
    int start = 0, finish = 0;
};
int main(){
    list<int>* s = new list<int>[DAYS];
    list<int>* f = new list<int>[DAYS];
    int N = 0, li, ri;
    cin >> N;
    struct Visitor visitor[N];
    for(int i=0; i<N; ++i){
        visitor[N].seenTimes = 0;
        cin >> li >> ri;
        visitor[i].start = li-1;
        visitor[i].finish = ri-1;
        s[li-1].push_back(i);
        f[ri-1].push_back(i);
    }

    int unfinishedVisitors = N, maxDay = 0;
    list<int> currentVisitorsID, maxVisitorsID, exertedDays;
    while(unfinishedVisitors){
        maxDay = -1;
        currentVisitorsID.clear();
        maxVisitorsID.clear();
        // Find the day with the maximum visitor
        for(int i=0; i<DAYS; ++i){
            bool exerted = false;
            for (auto it = exertedDays.begin(); it != exertedDays.end(); ++it){
                if(i == *it) {
                    exerted = true;
                    break;
                }
            }
            currentVisitorsID.insert(currentVisitorsID.end(), s[i].begin(), s[i].end());
            if(!exerted && currentVisitorsID.size()>maxVisitorsID.size()){
                maxVisitorsID.assign(currentVisitorsID.begin(), currentVisitorsID.end());
                maxDay = i;
            }
            for (auto it = f[i].begin(); it != f[i].end(); ++it){
                currentVisitorsID.remove(*it);
            }
        }
        if (maxDay == -1) cout<< "ERROR! LINE 48";
        //exert the firework on that maxDay
        for (auto it = maxVisitorsID.begin(); it != maxVisitorsID.end(); ++it){
            ++visitor[*it].seenTimes;
            if(visitor[*it].seenTimes == 2){
                --unfinishedVisitors;
                s[visitor[*it].start].remove((*it));
                f[visitor[*it].finish].remove((*it));
            }
            else if (visitor[*it].seenTimes > 2){ cout << "ERROR! LINE 57"; }
        }
        exertedDays.push_back(maxDay);

    }
    cout << exertedDays.size();
    delete[] s;
    delete[] f;
    return 0;
}