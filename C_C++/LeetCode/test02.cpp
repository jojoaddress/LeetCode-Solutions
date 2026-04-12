#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

double distSquared(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

double distance(const Point& p1, const Point& p2) {
    return sqrt(distSquared(p1, p2));
}

bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

double bruteForce(const vector<Point>& points, int left, int right) {
    double minDist = numeric_limits<double>::max();
    for (int i = left; i <= right; i++) {
        for (int j = i + 1; j <= right; j++) {
            minDist = min(minDist, distSquared(points[i], points[j]));
        }
    }
    return sqrt(minDist);
}

double closestUtil(vector<Point>& points, int left, int right) {
    if (right - left + 1 <= 3) {
        return bruteForce(points, left, right);
    }
    
    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];
    
    double leftMin = closestUtil(points, left, mid);
    double rightMin = closestUtil(points, mid + 1, right);
    double minDist = min(leftMin, rightMin);
    
    vector<Point> strip;
    for (int i = left; i <= right; i++) {
        if (fabs(points[i].x - midPoint.x) < minDist) {
            strip.push_back(points[i]);
        }
    }
    
    sort(strip.begin(), strip.end(), compareY);
    
    for (size_t i = 0; i < strip.size(); i++) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; j++) {
            minDist = min(minDist, distance(strip[i], strip[j]));
        }
    }
    
    return minDist;
}

double closestPair(vector<Point>& points) {
    if (points.size() < 2) {
        return 0.0;
    }
    
    sort(points.begin(), points.end(), compareX);
    
    return closestUtil(points, 0, points.size() - 1);
}

int main() {
    int n;
    cin >> n;
    
    vector<Point> points;
    points.reserve(n);
    
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    
    double minDistance = closestPair(points);
    
    cout << fixed << setprecision(4) << minDistance << endl;
    
    return 0;
}
