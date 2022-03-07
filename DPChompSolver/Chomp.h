#pragma once
#include <array>
#include <iostream>
#include <vector>
using namespace std;

const int M = 5;

class Chomp {
private:
    enum Status { True, False, Invalid };
    template <typename T> using vec5D = vector<vector<vector<vector<vector<T>>>>>;
    template <typename T> using vec4D = vector<vector<vector<vector<T>>>>;
    template <typename T> using vec3D = vector<vector<vector<T>>>;
    template <typename T> using vec2D = vector<vector<T>>;
    vec5D<Status> WIN = vec5D<Status>(
        11, vec4D<Status>(11, vec3D<Status>(11, vec2D<Status>(11, vector<Status>(11, Invalid)))));;
    int N = 12;
    int n;
public:
    Chomp(int n);
    bool isValid(int a, int b, int c, int d, int e);
    bool setTrue(int a, int b, int c, int d, int e);
    bool setFalse(int a, int b, int c, int d, int e);
    bool report(int a, int b, int c, int d, int e);
    bool validmove(int a, int b, int c, int d, int e,
        int f, int g, int h, int i, int j);
    void create();
    void print();
};





