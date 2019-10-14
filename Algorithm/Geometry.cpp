#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000 + 50;
template<class type> 
struct point{
    type x,y;
    point(){};
    point(type x_,type y_):x(x_),y(y_){}
    point operator +(const point &p)const {return point(x + p.x,y + p.y);}
    point operator -(const point &p)const {return point(x - p.x,y - p.y);}
    //a related to b
    //clockwise : positive
    //anti-clockwise : negative
    //share a line : zero
    type cross(const point &p)const {return x * p.y - y * p.x;}
    type dot(const point &p)const {return x * p.x + y * p.y;}
    type cross(const point &a,const point &b)const {return (a - *this).cross(b - *this);}
    type dot(const point &a,const point &b)const {return (a - *this).dot(b - *this);}
    type sqrLen()const{return this->dot(*this);}
    type sqrDis(const point &p)const {return (p - *this).sqrLen();}
};
typedef point<long long> pt;
namespace Geometry{
    const double PI = acos(-1.0);
    //res[0]: left most and bottom most
    //anti-clockwise
    //no three points share one line
    //WARN: this function modifies points
    vector<pt> Convex_Hull(vector<pt> &points){
        vector<pt> res(0);
        assert(points.size() >= 3);
        int idx = 0;
        for (int i=1;i<points.size();i++){
            pt temp = points[i];
            pt now = points[idx];
            if (temp.x < now.x || temp.x == now.x && temp.y < now.y)idx = i;
        }
        swap(points[idx],points[0]);
        sort(points.begin()+1,points.end(),[&](pt x,pt y){
            double cro = points[0].cross(x,y);
            if (cro != 0)return cro > 0;
            return points[0].sqrDis(x) < points[0].sqrDis(y);
        });
        res.push_back(points[0]);
        res.push_back(points[1]);
        for (int i=2;i<points.size();i++){
            pt now = points[i];
            while (res.size() >= 2){
                double cro = res[res.size()-2].cross(now,res.back());
                auto p = res[res.size()-2];
                auto pp = res.back();
                if (cro >= 0)res.pop_back();
                else break;
            }
            res.push_back(now);
        }
        return res;
    }
    //calc the Minkowski Sum of two Convex Hull
    vector<pt> Minkowski(const vector<pt> &ch1,const vector<pt> &ch2){
        assert(ch1.size() >= 3);
        assert(ch2.size() >= 3);
        stack<pt> vec1;
        stack<pt> vec2;
        for (int i = ch1.size() - 1;i >=0;i--){
            vec1.push(ch1[(i+1)%ch1.size()] - ch1[i]);
        }
        for (int i = ch2.size() - 1;i >= 0;i--){
            vec2.push(ch2[(i+1)%ch2.size()] - ch2[i]);
        }
        vector<pt> res(0);
        res.push_back(ch1.front() + ch2.front());
        while (!vec1.empty() && !vec2.empty()){
            auto v1 = vec1.top();
            auto v2 = vec2.top();
            long long cro = v1.cross(v2);
            if (cro > 0){
                res.push_back(res.back() + v1);
                vec1.pop();
            }else{
                res.push_back(res.back() + v2);
                vec2.pop();
            }
        }
        while (!vec1.empty())res.push_back(res.back() + vec1.top()),vec1.pop();
        while (!vec2.empty())res.push_back(res.back() + vec2.top()),vec2.pop();
        return Convex_Hull(res);
    }
    //logn
    //wether point in or on convex hull
    bool within(pt p,const vector<pt> &ch){
        assert(ch.size() >= 3);
        auto base = ch.front();
        if (base.cross(p,ch[1]) > 0 || base.cross(p,ch.back()) < 0)return false;
        if (base.cross(p,ch[1]) == 0 && (p - base).sqrLen() <= (ch[1] - base).sqrLen())return true;
        auto cmp = [&](const pt x,const pt y){
            long long cro = base.cross(x,y);
            return cro>0;
        };
        int i = lower_bound(ch.begin(),ch.end(),p,cmp) - ch.begin() - 1;
        int j = i+1;
        assert(j < ch.size());
        return ch[i].cross(ch[j],p) >= 0;
    }
};

