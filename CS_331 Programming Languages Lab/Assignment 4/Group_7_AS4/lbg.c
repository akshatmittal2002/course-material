#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define alpha 0.001
#define epsilon 0.1

// Struct definition for Point
typedef struct{
    int id_cluster; // Cluster id of the point
    double* values; // Point attributes
    int num_values; // Number of attributes
    char name[128]; // Point label
} Point;

// Initialize Point struct object
void initPoint(Point* point, int num_values, double* values, char* name){
    // Initially, the point is not assigned to any cluster
    point->id_cluster = 0;
    point->num_values = num_values;
    point->values = (double*)malloc(num_values * sizeof(double));
    // Error handling
    if(point->values == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    for(int i = 0; i < num_values; i++){
        point->values[i] = values[i];
    }
    if(name != NULL) strcpy(point->name, name);
    else strcpy(point->name, "\0");
}

// Free memory allocated for a point
void freePoint(Point* point){
    free(point->values);
}

typedef struct{
    double* values; // Centroid attributes
    int num_values; // Number of attributes
    int num_points; // Number of points in the codebook
} Codebook;

void initCodebook(Codebook* codebook, int num_values){
    codebook->num_values = num_values;
    codebook->num_points = 0;
    codebook->values = (double*)calloc(num_values, sizeof(double));
    // Error handling
    if(codebook->values == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
}

void addValues(Codebook* codebook, double* values){
    for(int i=0; i<codebook->num_values; i++){
        codebook->values[i] = values[i];
    }
}

void freeCodebook(Codebook* codebook){
    free(codebook->values);
}

typedef struct{
    int num_points; // Number of data points
    int num_values; // Number of attributes of the points
    Codebook** codebook; // Codebooks
    int num_codebooks; // Number of codebooks
    int max_codebooks; // Maximum number of codebooks
    int max_iter; // Maximum number of iterations
} Lbg;

void initLbg(Lbg* lbg, int num_points, int num_values, int max_codebooks, int max_iter){
    lbg->num_points = num_points;
    lbg->num_values = num_values;
    lbg->num_codebooks = 1;
    lbg->max_codebooks = max_codebooks;
    lbg->codebook = (Codebook**)malloc(2*max_codebooks*sizeof(Codebook*));
    // Error handling
    if(lbg->codebook == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    for(int i=0; i<2*max_codebooks; i++){
        lbg->codebook[i] = (Codebook*)malloc(sizeof(Codebook));
        if(lbg->codebook[i] == NULL){
            printf("Error: Memory allocation failed!\n");
            exit(1);
        }
        initCodebook(lbg->codebook[i], num_values);
    }
    lbg->max_iter = max_iter;
}

void freeLbg(Lbg* lbg){
    for(int i=0; i<2*lbg->max_codebooks; i++){
        freeCodebook(lbg->codebook[i]);
        free(lbg->codebook[i]);
    }
    free(lbg->codebook);
}

// Calculate the euclidean distance between point and centroid
double euclidean_distance(double* point1, double* point2, int num_values){
    double distance = 0.0;
    for(int i=0; i<num_values; i++){
        distance += pow(point1[i] - point2[i], 2);
    }
    return sqrt(distance);
}

// Calculate centroid of given data points
void findCentroid(double* centroid, Point** points, Lbg* lbg, int id){
    for(int i=0; i<lbg->num_values; i++){
        centroid[i] = 0;
    }
    for(int i=0; i<lbg->num_points; i++){
        for(int j=0; j<lbg->num_values; j++){
            if(id == points[i]->id_cluster){
                centroid[j] += points[i]->values[j];
            }
        }
    }
    for(int i=0; i<lbg->num_values; i++){
        centroid[i] /= lbg->codebook[id]->num_points;
    }
}

void splitCodebook(Lbg* lbg){
    int m = lbg->num_codebooks;
    for(int i=0; i<m; i++){
        for(int j=0; j<lbg->num_values; j++){
            int x = (rand() > RAND_MAX/2) ? 1 : -1;
            lbg->codebook[i+m]->values[j] = lbg->codebook[i]->values[j] + x*epsilon;
            lbg->codebook[i]->values[j] = lbg->codebook[i]->values[j] - x*epsilon;
        }
    }
    lbg->num_codebooks *= 2;
}

// To get the nearest centeroid for a data point
int getNearestCenter(Lbg* lbg, Point* point){
    double dist = 0.0;
    int codebook_id = -1;
    double min_dist = INFINITY;
    // Calculate the distance between the data point and the centeroids and find the nearest one
    for(int i=0; i<lbg->num_codebooks; i++){
        dist = euclidean_distance(point->values, lbg->codebook[i]->values, lbg->num_values);
        // If the distance is less than the minimum distance, then update the minimum distance and the nearest codebook id
        if(dist < min_dist){
            min_dist = dist;
            codebook_id = i;
        }
    }
    // Return the nearest cluster centeroid ID
    return codebook_id;
}

double findDistortion(Lbg* lbg, Point** points){
    double dist = 0;
    for(int i=0; i<lbg->num_codebooks; i++){
        for(int j=0; j<lbg->num_points; j++){
            if(points[j]->id_cluster == i){
                dist += euclidean_distance(lbg->codebook[i]->values, points[j]->values, lbg->num_values);
            }
        }
    }
    dist /= lbg->num_points;
    return dist;
}

void run(Lbg* lbg, Point** points){
    double* centroid = (double*)malloc(lbg->num_values*sizeof(double));
    initCodebook(lbg->codebook[0], lbg->num_values);
    lbg->codebook[0]->num_points = lbg->num_points;
    findCentroid(centroid, points, lbg, 0);
    addValues(lbg->codebook[0], centroid);
    double distortion = findDistortion(lbg,points);
    printf("Distortion: %lf\n", distortion);
    while(lbg->num_codebooks < lbg->max_codebooks){
        splitCodebook(lbg);
        printf("Splitted!\n");
        // KMeans on given centroids
        int iter = 1;
        while(1){
            // For every data point, find the nearest centeroid and assign it to that codebook
            for(int i=0; i<lbg->num_points; i++){
                int old_codebook = points[i]->id_cluster;
                int new_codebook = getNearestCenter(lbg,points[i]);
                points[i]->id_cluster = new_codebook;
                lbg->codebook[old_codebook]->num_points--;
                lbg->codebook[new_codebook]->num_points++;
            }
            // Update centroids
            for(int i=0; i<lbg->num_codebooks; i++){
                findCentroid(centroid, points, lbg, i);
                addValues(lbg->codebook[i], centroid);
            }
            // If the algorithm has converged or iterations limit reached, then break
            double new_distortion = findDistortion(lbg,points);
            int converge = 0;
            if((distortion - new_distortion)/new_distortion <= alpha) converge = 1;
            if(converge || iter >= lbg->max_iter){
                break;
            }
            // Else continue to next iteration
            iter++;
            distortion = new_distortion;
        }
        printf("Distortion: %lf\n", distortion);
    }
    free(centroid);
}

void show(Lbg* lbg, Point** points, FILE* fp_out){
    for(int i=0; i<lbg->num_codebooks; i++){
        fprintf(fp_out, "Codebook %d: Number of data points: %d\n", i + 1, lbg->codebook[i]->num_points);
        // Print the centroid
        fprintf(fp_out, "Centroid: ");
        for(int j=0; j<lbg->num_values; j++){
            fprintf(fp_out, "%lf ", lbg->codebook[i]->values[j]);
        }
        fprintf(fp_out, "\n");

        // Print the points in this cluster
        for(int j=0; j<lbg->num_points; j++){
            if(points[j]->id_cluster != i) continue;
            fprintf(fp_out, "Point %d: ", j + 1);
            for(int p=0; p<lbg->num_values; p++){
                fprintf(fp_out, "%lf ", points[j]->values[p]);
            }
            // Print the point label if it exists
            char* point_name = points[j]->name;
            if(strcmp(point_name, "\0") != 0){
                fprintf(fp_out, "- %s", point_name);
            }
            fprintf(fp_out, "\n");
        }
        fprintf(fp_out, "===================================================================================================\n\n");
    }
}

int main(int argc, char** argv){
    srand(time(NULL));

    // Open input and output files
    FILE* fp_in = fopen(argv[1], "r");
    FILE* fp_out = fopen(argv[2], "w");

    // Error handling
    if(fp_in == NULL || fp_out == NULL){
        printf("Error: File can not be opened!\n");
        exit(1);
    }

    // Scan input file
    int num_points, num_values, max_codebooks, max_iter, has_name;
    fscanf(fp_in, "%d %d %d %d %d", &num_points, &num_values, &max_codebooks, &max_iter, &has_name);

    // Error handling
    if(num_points < max_codebooks){
        printf("Error: Number of codebooks more than number of data points!\n");
        exit(1);
    }

    // Allocate memory for data points
    Point** points = (Point**)malloc(num_points * sizeof(Point*));
    char* name = (char*)malloc(128 * sizeof(char));
    double* values = (double*)malloc(num_values * sizeof(double));

    // Error handling
    if(points == NULL || name == NULL || values == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }

    // Scan data points
    for(int i=0; i<num_points; i++){
        for(int j=0; j<num_values; j++){
            fscanf(fp_in, "%lf", &values[j]);
        }
        points[i] = (Point*)malloc(sizeof(Point));
        // Error handling
        if(points[i] == NULL){
            printf("Error: Memory allocation failed!\n");
            exit(1);
        }
        if(has_name){
            fscanf(fp_in, "%s", name);
            initPoint(points[i], num_values, values, name);
        }
        else{
            initPoint(points[i], num_values, values, NULL);
        }
    }
    free(values);
    free(name);

    Lbg* lbg = (Lbg*)malloc(sizeof(Lbg));
    // Error handling
    if(lbg == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    printf("Initializing...\n");
    initLbg(lbg, num_points, num_values, max_codebooks, max_iter);
    
    // Run LBG algorithm
    printf("Running...\n");
    run(lbg, points);

    printf("Printing Reults...\n");
    // Print resulting codebooks
    show(lbg, points, fp_out);
    printf("Done!\n");
    
    // Free allocated memory
    freeLbg(lbg);
    free(lbg);
    for(int i=0; i<num_points; i++){
        freePoint(points[i]);
        free(points[i]);
    }
    free(points);

    printf("Exiting...\n");
    // Close input and output files
    fclose(fp_in);
    fclose(fp_out);
    return 0;
    
}