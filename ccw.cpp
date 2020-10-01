template<typename T>
inline T vec(T a, T b){
    return make_pair(b.first-a.first,b.second-a.second);
}
template<typename T>
inline ll cross(T a, T b){
    return a.first*b.second-a.second*b.first;
}
template<typename T>
inline bool ccw(T a, T b, T c){
    return cross(vec(b,a),vec(b,c))<0;
}
