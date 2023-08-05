#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

// Struct definition for Point
typedef struct{
    int id_point; // Point id
    int id_cluster; // Cluster id of the point
    double* values; // Point attributes
    int num_values; // Number of attributes
    char name[128]; // Point label
} Point;

// Initialize Point struct object
void initPoint(Point* point, int id_point, int num_values, double* values, char* name){
    point->id_point = id_point;
    // Initially, the point is not assigned to any cluster
    point->id_cluster = -1;
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

// Struct definition for Cluster
typedef struct{
    int id_cluster; // Cluster id
    double* centroid; // Cluster centroid's atrributes
    int num_centroid; // Number of attributes
    Point** points; // Points in the cluster
    int num_points; // Number of points in the cluster
} Cluster;

// Initialize Cluster struct object
void initCluster(Cluster* cluster, int id_cluster, Point* point){
    cluster->id_cluster = id_cluster;
    cluster->num_centroid = point->num_values;
    cluster->centroid = (double*)malloc(cluster->num_centroid * sizeof(double));
    // Error handling
    if(cluster->centroid == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    for(int i=0; i<cluster->num_centroid; i++){
        cluster->centroid[i] = point->values[i];
    }
    cluster->num_points = 1;
    cluster->points = (Point**)malloc(cluster->num_points * sizeof(Point*));
    // Error handling
    if(cluster->points == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    cluster->points[0] = point;
}

// Add a point to a cluster
void addPoint(Cluster* cluster, Point* point){
    cluster->points = (Point**)realloc(cluster->points, (cluster->num_points + 1) * sizeof(Point*));
    // Error handling
    if(cluster->points == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    cluster->points[cluster->num_points] = point;
    cluster->num_points++;
}

// Remove a point from a cluster
int removePoint(Cluster* cluster, int id_point){
    for(int i=0; i<cluster->num_points; i++){
        // Find the point with the given id
        if(cluster->points[i]->id_point == id_point){
            for(int j=i; j<cluster->num_points-1; j++){
                cluster->points[j] = cluster->points[j+1];
            }
            cluster->num_points--;
            cluster->points = (Point**)realloc(cluster->points, cluster->num_points * sizeof(Point*));
            // Error handling
            if(cluster->points == NULL){
                printf("Error: Memory allocation failed!\n");
                exit(1);
            }
            return 1;
        }
    }
    return 0;
}

// Free memory allocated for a cluster
void freeCluster(Cluster* cluster){
    free(cluster->centroid);
    for(int i=0; i<cluster->num_points; i++){
        freePoint(cluster->points[i]);
    }
    free(cluster->points);
}

// Calculate the euclidean distance between two points
double euclidean_distance(Point* point1, Point* point2, int num_values){
    double distance = 0.0;
    for(int i=0; i<num_values; i++){
        distance += pow(point1->values[i] - point2->values[i], 2);
    }
    return sqrt(distance);
}
// Calculate the euclidean distance point and centroid
double euclidean_distance(Point* point1, double* point2, int num_values){
    double distance = 0.0;
    for(int i=0; i<num_values; i++){
        distance += pow(point1->values[i] - point2[i], 2);
    }
    return sqrt(distance);
}

// Struct definition for KMeans
typedef struct{
    int num_values; // Number of attributes in a data point
    int num_points; // Number of data points
    int max_iter; // Maximum number of iterations
    Cluster** clusters; // Clusters
    int num_clusters; // Number of clusters
} KMeans;

// Initialize KMeans struct object
void initKmeans(KMeans* kmeans, int num_values, int num_points, int num_clusters, int max_iter){
    kmeans->num_values = num_values;
    kmeans->num_points = num_points;
    kmeans->num_clusters = num_clusters;
    kmeans->max_iter = max_iter;
    kmeans->clusters = (Cluster**)malloc(num_clusters * sizeof(Cluster*));
    // Error handling
    if(kmeans->clusters == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
}

// To get the nearest cluster centeroid for a data point
int getNearestCenter(KMeans* kmeans, Point* point){
    double dist = 0.0;
    int id_cluster_center = -1;
    double min_dist = INFINITY;
    
    // Calculate the distance between the data point and the cluster centeroids and find the nearest one
    for(int i=0; i<kmeans->num_clusters; i++){
        dist = euclidean_distance(point, kmeans->clusters[i]->centroid, kmeans->num_values);
        // If the distance is less than the minimum distance, then update the minimum distance and the nearest cluster centeroid
        if(dist < min_dist){
            min_dist = dist;
            id_cluster_center = i;
        }
    }

    // Return the nearest cluster centeroid ID
    return id_cluster_center;
}

// Calculate distortion of a KMeans object
double findDistortion(KMeans* kmeans){
    double dist = 0.0;
    for(int i=0; i<kmeans->num_clusters; i++){
        for(int j=0; j<kmeans->clusters[i]->num_points; j++){
            dist += euclidean_distance(kmeans->clusters[i]->points[j], kmeans->clusters[i]->centroid, kmeans->num_values);
        }
    }
    dist /= kmeans->num_points;
    return dist;
}

// K-Means algorithm
void run(KMeans* kmeans, Point** points){
    // Select initial cluster centroids randomly
    int* prohibited_indexes = (int*)calloc(kmeans->num_points, sizeof(int));
    // Error handling
    if(prohibited_indexes == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    for(int i=0; i<kmeans->num_clusters; i++){
        while(1){
            int index = rand() % kmeans->num_points;
            // If already selected, then continue
            if(prohibited_indexes[index] == 1) continue;
            prohibited_indexes[index] = 1;
            points[index]->id_cluster = i;
            Cluster* cluster = (Cluster*)malloc(sizeof(Cluster));
            // Error handling
            if(cluster == NULL){
                printf("Error: Memory allocation failed!\n");
                exit(1);
            }
            initCluster(cluster, i, points[index]);
            kmeans->clusters[i] = cluster;
            break;
        }
    }
    // Free the memory
    free(prohibited_indexes);
    printf("Initial Centroids Selected!\nStarting Iterations...\n");
    
    // Run the algorithm for a maximum of max_iter iterations
    int iter = 1;
    while(1){
        int done = 1;
        // For every data point, find the nearest cluster centeroid and assign it to that cluster
        for(int i=0; i<kmeans->num_points; i++){
            int id_old_cluster = points[i]->id_cluster;
            int id_nearest_center = getNearestCenter(kmeans, points[i]);
            // If the nearest cluster centeroid is different from the cluster to which the data point was assigned, then update the cluster
            if(id_old_cluster != id_nearest_center){
                if(id_old_cluster != -1) removePoint(kmeans->clusters[id_old_cluster], points[i]->id_point);
                points[i]->id_cluster = id_nearest_center;
                // Add the data point to the cluster
                addPoint(kmeans->clusters[id_nearest_center], points[i]);
                // Done = 0 means that the algorithm has not converged yet
                done = 0;
            }
        }
        // Recalculate the cluster centeroids
        for(int i=0; i<kmeans->num_clusters; i++){
            // If the cluster has no points, discard it
            if(kmeans->clusters[i]->num_points == 0){
                for(int j=i; j<kmeans->num_clusters-1; j++){
                    kmeans->clusters[j] = kmeans->clusters[j+1];
                }
                kmeans->num_clusters--;
                kmeans->clusters = (Cluster**)realloc(kmeans->clusters, kmeans->num_clusters * sizeof(Cluster*));
                // Error handling
                if(kmeans->clusters == NULL){
                    printf("Error: Memory allocation failed!\n");
                    exit(1);
                }
                i--;
                continue;
            }
            // Else recalculate the cluster centeroid
            for(int j=0; j<kmeans->num_values; j++){
                int total_points_cluster = kmeans->clusters[i]->num_points;
                double sum = 0.0;
                if(total_points_cluster > 0){
                    for(int p=0; p<total_points_cluster; p++){
                        sum += kmeans->clusters[i]->points[p]->values[j];
                    }
                    kmeans->clusters[i]->centroid[j] = sum / total_points_cluster;
                }
            }
        }

        double distortion = findDistortion(kmeans);
        printf("Distortion: %lf\n", distortion);
        
        // If the algorithm has converged, then break
        if(done){
            printf("Stopping due to convergence!\n");
            break;
        }
        // If the algorithm has not converged and the maximum number of iterations have been reached, then break
        if(iter >= kmeans->max_iter){
            printf("Stopping due to max iterations!\n");
            break;
        }
        // Else continue to next iteration
        iter++;
    }
}

// Print the clusters
void showClusters(KMeans* kmeans, FILE* fp_out){
    // For every cluster formed:
    for(int i=0; i<kmeans->num_clusters; i++){
        int total_points_cluster = kmeans->clusters[i]->num_points;
        // Print the cluster ID
        fprintf(fp_out, "Cluster %d: Number of data points: %d\n", kmeans->clusters[i]->id_cluster + 1, kmeans->clusters[i]->num_points);
        // Print the centroid attributes
        fprintf(fp_out, "Cluster Centroid: ");
        for(int j=0; j<kmeans->num_values; j++){
            fprintf(fp_out, "%lf ", kmeans->clusters[i]->centroid[j]);
        }
        fprintf(fp_out, "\n");

        // Print the points in this cluster
        for(int j=0; j<total_points_cluster; j++){
            fprintf(fp_out, "Point %d: ", kmeans->clusters[i]->points[j]->id_point + 1);
            for(int p=0; p<kmeans->num_values; p++){
                fprintf(fp_out, "%lf ", kmeans->clusters[i]->points[j]->values[p]);
            }
            // Print the point label if it exists
            char* point_name = kmeans->clusters[i]->points[j]->name;
            if(strcmp(point_name, "\0") != 0){
                fprintf(fp_out, "- %s", point_name);
            }
            fprintf(fp_out, "\n");
        }
        fprintf(fp_out, "===================================================================================================\n\n");
    }
}

// Free the allocated memory
void freeKmeans(KMeans* kmeans){
    for(int i=0; i<kmeans->num_clusters; i++){
        freeCluster(kmeans->clusters[i]);
    }
    free(kmeans->clusters);
}

// Calculate the silhouette score of a KMeans object
double silhouette_score(KMeans* kmeans){
    double silhouette_score = 0.0;
    for(int i=0; i<kmeans->num_clusters; i++){
        for(int j=0; j<kmeans->clusters[i]->num_points; j++){
            double a = 0.0;
            for(int k=0; k<kmeans->clusters[i]->num_points; k++){
                if(k != j){
                    a += euclidean_distance(kmeans->clusters[i]->points[j], kmeans->clusters[i]->points[k], kmeans->num_values);
                }
            }
            a /= kmeans->clusters[i]->num_points - 1;
            double b = 0;
            int count = 0;
            for(int k=0; k<kmeans->num_clusters; k++){
                if(k != i){
                    for(int l=0; l<kmeans->clusters[k]->num_points; l++){
                        b += euclidean_distance(kmeans->clusters[i]->points[j], kmeans->clusters[k]->points[l], kmeans->num_values);
                    }
                    count += kmeans->clusters[k]->num_points;
                }
            }
            b /= count;
            silhouette_score += (b - a) / fmax(a, b);
        }
    }
    silhouette_score /= kmeans->num_points;
    return silhouette_score;
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
    int num_points, num_values, num_clusters, num_iterations, has_name;
    fscanf(fp_in, "%d %d %d %d %d", &num_points, &num_values, &num_clusters, &num_iterations, &has_name);

    // Error handling
    if(num_points < num_clusters){
        printf("Error: Number of clusters more than number of data points!\n");
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
            initPoint(points[i], i, num_values, values, name);
        }
        else{
            initPoint(points[i], i, num_values, values, NULL);
        }
    }
    free(values);
    free(name);

    // Initialize KMeans object
    KMeans* kmeans = (KMeans*)malloc(sizeof(KMeans));
    // Error handling
    if(kmeans == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    printf("Initializing...\n");
    initKmeans(kmeans, num_values, num_points, num_clusters, num_iterations);
    
    // Run KMeans algorithm
    printf("Running...\n");
    run(kmeans, points);
    
    printf("Printing Reults...\n");
    // Print resulting clusters
    showClusters(kmeans, fp_out);
    printf("Done!\n");

    // Calculate Silhouette Score
    // printf("Calculating Silhouette Score...\n");
    // double silhouette = silhouette_score(kmeans);
    // printf("Silhouette Score: %.5lf\n", silhouette);

    // Calculate Distortion
    printf("Calculating Distortion...\n");
    double distortion = findDistortion(kmeans);
    printf("Final Distortion: %lf\n", distortion);
    
    // Free allocated memory
    freeKmeans(kmeans);
    free(kmeans);
    free(points);
    printf("Exiting...\n");

    // Close input and output files
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}