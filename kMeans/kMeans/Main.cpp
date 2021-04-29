#include<iostream>
#include<vector>
#include<string>
#include<math.h>
#include<fstream>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <float.h>
using namespace std;

struct Point2D {
	double x;
	double y;
	Point2D(double xaxis, double yaxis) {
		x = xaxis;
		y = yaxis;
	}

	Point2D& operator=(const Point2D& p2d) {
		if (this != &p2d) {
			x = p2d.x;
			y = p2d.y;
		}
		return *this;
	}
	void print() {
		cout << x << " " << y << endl;
	}
};

double distance(Point2D a, Point2D b) {
	return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
}

double withinClusterScatter(Point2D centroid, vector<Point2D> cluster) {
	double sum = 0.0;
	for (int i = 0; i < cluster.size(); i++) {
		double dist = distance(cluster[i], centroid);
		sum = sum + dist;
	}
	return sum / cluster.size();
}

vector<vector<Point2D>> clusterize(vector<Point2D>& centroids, int k, vector<Point2D> points, double& WCS) {
	bool equal = false;
	vector<vector<Point2D>> clusters_final;

	while (equal == false) {
		vector<vector<Point2D>> clusters(k);
		for (int i = 0; i < points.size(); i++) {
			double min = 570000.0;
			int clusterIndex;
			for (int j = 0; j < k; j++) {
				double dist = distance(points[i], centroids[j]);
				if (dist < min) {
					min = dist;
					clusterIndex = j;
				}
			}
			clusters[clusterIndex].push_back(points[i]);
		}

		vector<Point2D> newcentroids;
		for (int i = 0; i < k; i++) {
			double sumX = 0.0;
			double sumY = 0.0;
			for (int a = 0; a < clusters[i].size(); a++) {
				sumX = sumX + clusters[i][a].x;
				sumY = sumY + clusters[i][a].y;
			}
			double newX = sumX / clusters[i].size();
			double newY = sumY / clusters[i].size();
			Point2D newCentroid(newX, newY);
			//clusters[i][0] = newCentroid;
			newcentroids.push_back(newCentroid);
		}

		bool eq = true;
		for (int i = 0; i < k; i++) {
			if (newcentroids[i].x != centroids[i].x || newcentroids[i].y != centroids[i].y) {
				eq = false;
			}
		}
		equal = eq;

		for (int i = 0; i < k; i++) {
			centroids[i] = newcentroids[i];
		}

		if (eq == true) {
			double wcs = 0.0;
			for (int i = 0; i < k; i++) {
				wcs += withinClusterScatter(centroids[i], clusters[i]);
			}
			wcs = wcs / k;
			WCS = wcs;

			clusters_final = clusters;
		}
	}

	return clusters_final;
}

bool member(Point2D p, vector<Point2D> points) {
	for (int i = 0; i < points.size(); i++) {
		if (p.x == points[i].x && p.y == points[i].y) {
			return true;
		}
	}
	return false;
}

vector<Point2D> getRandomClusters(int k, vector<Point2D> points) {
	vector<Point2D> centroids;
	for (int i = 0; i < k; i++) {
		srand(time(0));
		int randIndex = rand() % points.size();
		while (member(points[randIndex], centroids)) {
			srand(time(0));
			randIndex = rand() % points.size();
		}
		centroids.push_back(points[randIndex]);
	}
	return centroids;
}



int main() {
	ifstream file;
	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	file.open(filename, ios::in);
	if (file.is_open()) {
		cout << "file is open" << endl;
	}
	else {
		cout << "file is NOT open" << endl;
	}
	vector<Point2D> points;
	while (!file.eof()) {
		double x, y;
		file >> x >> y;
		Point2D p2d(x, y);
		points.push_back(p2d);
	}

	/*double checkDataX = points[1].x;
	double checkDataY = points[1].y;
	int scale;
	if (checkDataX < 10 && checkDataY < 10) {
		scale = 1;
	}
	else if (checkDataX < 100 && checkDataY < 100) {
		scale = 2;
	}
	else if (checkDataX < 10000 && checkDataY < 10000) {
		scale = 3;
	}
	else if (checkDataX < 1000000 && checkDataY < 1000000) {
		scale = 4;
	}
	else if (checkDataX >= 1000000 && checkDataY >= 1000000) {
		scale = 5;
	}*/

	cout << "Enter number of clusters: ";
	int k;
	cin >> k;
	vector<Point2D> centroids = getRandomClusters(k, points);
	/*for (int i = 0; i < k; i++) {
		centroids[i].print();
	}*/


	//vector<double> WCSs;
	//vector<vector<Point2D>> vectorWithCentroids;
	double wcs = 0.0;

	double minWCS = 1000000.0;
	int index;
	vector<vector<Point2D>> bestClusters;

	//Random Restart
	for (int i = 0; i < 5; i++) {
		vector<vector<Point2D>> clusters = clusterize(centroids, k, points, wcs);
		//WCSs.push_back(wcs);
		//vectorWithCentroids.push_back(centroids);

		if (minWCS > wcs) {
			minWCS = wcs;
			index = i;
			bestClusters = clusters;
		}

		srand(time(0));
		centroids.clear();
		centroids = getRandomClusters(k, points);
	}

	/*for (int i = 0; i < bestClusters.size(); i++) {
		for (int j = 0; j < bestClusters[i].size(); j++) {
			bestClusters[i][j].print();
		}
		cout << endl << endl;
	}*/

	//create a file with best clusters
	for (int i = 0; i < k; i++) {
		string filename;
		cout << "Enter filename: ";
		cin >> filename;
		ofstream f;
		f.open(filename, ios::out);
		for (int j = 0; j < bestClusters[i].size(); j++) {
			if (j == bestClusters[i].size() - 1) {
				f << bestClusters[i][j].x << " " << bestClusters[i][j].y;
			}
			else {
				f << bestClusters[i][j].x << " " << bestClusters[i][j].y << endl;
			}
		}
	}
	return 0;
}