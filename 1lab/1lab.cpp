#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

#define NUM_SAMPLES 10
#define NUM_FEATURES 3
#define NUM_CENTROIDS 2
using namespace std;
struct FEATURE {
    double* features = new double[NUM_FEATURES] {0};
};
double distance(FEATURE feature1, FEATURE feature2) {
    double sum = 0.0;
    for (int i = 0; i < NUM_FEATURES; i++) {
        sum += abs(feature1.features[i] - feature2.features[i]);
    }
    return sum;
}
bool findNewCentroids(FEATURE* dataset, FEATURE* centoid, int* clusterID) {
    for (int i = 0; i < NUM_SAMPLES; i++) {
        double minDistance = 999999;
        int centroidID = -1;

        for (int j = 0; j < NUM_CENTROIDS; j++) {
            double d = distance(dataset[i], centoid[j]);
            if (d < minDistance) {
                minDistance = d;
                centroidID = j;
            }
        }
        clusterID[i] = centroidID;
    }

    FEATURE* newCentroid = new FEATURE[NUM_CENTROIDS];
    for (int i = 0; i < NUM_CENTROIDS; i++) {
        int cnt = 0;
        double* sum = new double[NUM_FEATURES] {0};

        for (int j = 0; j < NUM_SAMPLES; j++) {
            if (clusterID[j] == i) {
                cnt++;
                for (int f = 0; f < NUM_FEATURES; f++) {
                    sum[f] += dataset[j].features[f];
                }
            }
        }

        if (cnt == 0) {
            newCentroid[i] = centoid[i];
        }
        else {
            for (int f = 0; f < NUM_FEATURES; f++) {
                newCentroid[i].features[f] = sum[f] / cnt;
            }
        }
    }

    bool finishFlag = true;
    for (int i = 0; i < NUM_CENTROIDS; i++) {
        for (int j = 0; j < NUM_FEATURES; j++) {
            if (abs(centoid[i].features[j] - newCentroid[i].features[j]) > 0.001) {
                finishFlag = false;
            }
        }
    }

    for (int i = 0; i < NUM_CENTROIDS; i++) {
        for (int j = 0; j < NUM_FEATURES; j++) {
            centoid[i].features[j] = newCentroid[i].features[j];
        }
    }

    return finishFlag;
}

int main() {
    setlocale(LC_ALL, "Russian");

    FEATURE* dataset = new FEATURE[NUM_SAMPLES];
    dataset[0].features = new double[NUM_FEATURES] {1.0, 2.0, 1.0};
    dataset[1].features = new double[NUM_FEATURES] {2.0, 1.0, 1.0};
    dataset[2].features = new double[NUM_FEATURES] {2.0, 3.0, 2.0};
    dataset[3].features = new double[NUM_FEATURES] {1.0, 1.0, 2.0};
    dataset[4].features = new double[NUM_FEATURES] {1.5, 2.0, 1.5};
    dataset[5].features = new double[NUM_FEATURES] {10.0, 11.0, 10.0};
    dataset[6].features = new double[NUM_FEATURES] {11.0, 10.0, 11.0};
    dataset[7].features = new double[NUM_FEATURES] {10.0, 10.0, 10.0};
    dataset[8].features = new double[NUM_FEATURES] {9.0, 11.0, 9.0};
    dataset[9].features = new double[NUM_FEATURES] {10.5, 10.5, 10.5};

    FEATURE* centoid = new FEATURE[NUM_CENTROIDS];
    centoid[0].features = new double[NUM_FEATURES] {10.0, 10.0, 10.0};
    centoid[1].features = new double[NUM_FEATURES] {3.0, 3.0, 3.0};

    int* clusterID = new int[NUM_SAMPLES];


    cout << fixed << setprecision(2);

    int iteration = 0;

    while (true) {
        iteration = iteration + 1;
        cout << "Итерация " << iteration << ":" << endl;

        for (int i = 0; i < NUM_CENTROIDS; i++) {
            cout << "  Центроид " << i << ": [";


            for (int j = 0; j < NUM_FEATURES; j++) {
                cout << centoid[i].features[j];
                if (j < NUM_FEATURES - 1) {
                    cout << ", ";
                }
            }

            cout << "]" << endl;
        }


        bool exitFlag = findNewCentroids(dataset, centoid, clusterID);
        if (exitFlag == true) {
            break;
        }
    }

    cout << "Кластеризация завершена!" << endl;
    return 0;
}