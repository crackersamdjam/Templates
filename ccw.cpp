template<typename T>
inline pair<T,T> vec(pair<T,T> a, pair<T,T> b){
    return make_pair(b.first-a.first,b.second-a.second);
}
template<typename T>
inline T cross(pair<T,T> a, pair<T,T> b){
    return a.first*b.second-a.second*b.first;
}
template<typename T>
inline bool ccw(pair<T,T> a, pair<T,T> b, pair<T,T> c){
    return cross(vec(b,a),vec(b,c))<0;
}
