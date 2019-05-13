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
    //b related to a
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
typedef point<double> pt;
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
        sort(points.begin(),points.end(),[&](pt x,pt y){
            double cro = points[0].cross(x,y);
            if (cro != 0)return cro > 0;
            return points[0].sqrDis(x) < points[0].sqrDis(y);
        });

        res.push_back(points[0]);
        res.push_back(points[1]);
        for (int i=2;i<points.size();i++){
            pt now = points[i];
            while (res.size() > 2){
                double cro = res[res.size()-2].cross(now,res.back());
                if (cro >= 0)res.pop_back();
                else break;
            }
            res.push_back(now);
        }
        return res;
    }

};
using namespace Geometry;
int main(){
    int n;
    cin>>n;
    vector<pt> points(0);
    for (int i=0;i<n;i++){
        double x,y;
        cin>>x>>y;
        points.push_back(pt(x,y));
    }
    if (n <= 1){
        return puts("0.00"),0;
    }
    if (n == 2){
        printf("%.2f\n",sqrt(1.0 * points[0].sqrDis(points[1])));
        return 0;
    }
    vector<pt> ch = Convex_Hull(points);
    double ans = 0.0;
    for (int i=0;i<ch.size();i++){
        ans += sqrt(ch[i].sqrDis(ch[(i+1)%ch.size()]));
    }
    printf("%.2f\n",ans);
    return 0;

}
