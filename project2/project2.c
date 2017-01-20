/*
 * project2.c
 * This program approximately calculates area of any polygon.
 * Fatih Yılmaz
 * 151202046
 */
#include <stdio.h>
#include <stdlib.h>
#define XMAX 50
#define YMAX 50
#define N 1000      /* the total number of points */

/* gets a point from user */
int getPoint(double *point)
{
    /* TODO
     * read an x value from user
     * read a y value from user
     * assign them to point[0] and point[1]
     */
    printf("x value:");
    scanf("%lf",&point[0]);
    printf("y value:");
    scanf("%lf",&point[1]);
    return 0;
}

/* gets points and assigns them to the edges*/
int getEdges(double **edges, int n)
{
    /* TODO
     * for each of the n edges,
     * --call function getpoint to read an x and a y value from user
     * assign them to edges[i][0] and edges[i][1]
     * --call function getpoint to read an x and a y value from user
     * assign them to edges[i][2] and edges[i][3]
     */
    for (int i=0; i<n; i++)
    {
        getPoint(edges[i]);
        getPoint(edges[i]+2);
    }
    return 0;
}


/* generates a random point */
int generatePoint(double *point)
{
    /* TODO:
     * generate random double x in [0, XMAX]
     * generate random double y in [0, YMAX]
     * assign x and y to the elements of point[0] and point[1]
     */

    double x = rand()/RAND_MAX;
    double y = rand()/RAND_MAX;
    /*need to add 1 to the XMAX and YMAX because program need a x and y value between closed interval 0 to 50 */

    /*(rand()/(double)RAND_MAX)*YMAX; (rand()/(double)RAND_MAX)*YMAX;*/
    /*
      There can be used above formula too. However these two formulas gives different values.
      I prefered to used other formula because it gives more accurate results in my computer.
    */

    point[0] = x;
    point[1] = y;

    return 0;
}


/* determines if a point is inside the polygon */
int isInside(double **edges, int n, double *point){
     /* TODO
     * for each of the n edges,
     * --if the x coordinates of both ends of the edge are less than
     * the x coordinate of point then continue
     * --if the x coordinates of both ends of the edge are greater than
     * the x coordinate of point then continue.
     * --if the y coordinates of both ends of the edge are below
     * the y coordinate of the point, then continue.
     * --If none of the above true, then compute the vertical
     * crossing point:
     *  ycrossing =  yleft + (yright -yleft)/(xright -xleft) * (point[0]-xleft)
     * --If ycrossing is greater than the y coordinate of the point,
     * then a crossing is found: add one to number of crossing.
     */
    int noc = 0; /*Number of crossing*/
    for (int i = 0; i<n; i++)
    {
        if (edges[i][0] < point[0] && edges[i][2] < point[0])
        {
            continue;
        }
        if (edges[i][0] > point[0] && edges[i][2] > point[0])
        {
            continue;
        }
        if (edges[i][1] < point[1] && edges[i][3] < point[1])
        {
            continue;
        }

        double ycrossing =  edges[i][1] + (edges[i][3]-edges[i][1])/(edges[i][2]-edges[i][0]) * (point[0]-edges[i][0]);
        if ( ycrossing>point[1] )
        {
            noc++;
        }
    }

     /* TODO: After all edges have been evaluated,
      * if the number of crossing is odd, the point lies inside the polygon:
      * the function returns 1.
      * Otherwise,
      *  it is not inside the polygon:
      *  the function returns 0.
      */
    if ((noc%2)==1)
    {
      return 1;
    }
    else
    {
      return 0;
    }

}

int main()
{
    int k = 0;  /* the number of points inside the polygon      */
    int ne = 0; /* the number of edges                          */


    /* pointer to the edges: each edge has x1, y1 and x2, y2
     * For example,
     * edges[3][0] is the x1 of the 3rd edges
     * edges[3][1] is the y1 of the 3rd edges
     * edges[3][2] is the x2 of the 3rd edges
     * edges[3][3] is the y2 of the 3rd edges
     */
    double **edges;

    /* read number of edges from user */
    printf("Number of Edges for Polygon:");
    scanf("%d", &ne);

    /* allocate memory for the edges */
    edges = (double **) malloc(ne * sizeof(double *));
    for (int i = 0; i< ne; i++){
        edges[i] = (double *)malloc(4 * sizeof(double));
    }
    /* NO CHANGE ABOVE THIS POINT */


    /* TODO:
     * call getEdges to get points of the edges from user
    */
    getEdges(edges, ne);

    /* TODO:
     * N times (inside a loop)
     * -- call generatePoint to generate a random point
     * -- call isInside with the arguments edges, n, and point
     * to determine if the point lies inside the polygon or not.
     * -- if it is inside, then increment k by 1.
     */
    double *point;
    point = (double *) malloc(N * sizeof(double));
    for (int i=0; i<N; i++)
    {
        generatePoint(point);
        if (isInside(edges,ne,point))
        {
            k++;
        }
    }

    /* NO CHANGE BELOW THIS POINT */
    printf("\n\nThe area of the polygon is: %lf", XMAX*YMAX*(double)k/N);
    /* free the allocated memory for the edges */
    for (int i = 0; i< ne; i++){
        free(edges[i]);
    }
    free(edges);
    return 0;
}
