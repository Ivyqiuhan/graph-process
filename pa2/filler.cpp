/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */

/**
 * Performs a multi-point flood fill using breadth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillBFS(FillerConfig &config){
    return fill<Queue>(config);
}

/**
 * Performs a multi-point flood fill using depth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillDFS(FillerConfig &config){
     return fill<Stack>(config);
}


bool filler::IsWithinBoundary(int xBound, int yBound, int x, int y, bool visited){
    if(x < xBound && y < yBound && !visited){
        return true;
    }
    return false;
}
/**
 * Run a multi-point flood fill on an image
 *
 * @param  config     FillerConfig struct with data for flood fill of image
 * @return animation  object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure> animation filler::fill(FillerConfig &config){
    OrderingStructure<point> orderingStructure;
    animation animation;
    animation.addFrame(config.img);


    int width = config.img.width();
    int height= config.img.height();
    bool visited[width][height];
    int direction[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

    //Initialize all the points to unvisited
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < height; ++j){
            visited[i][j] = false;
        }
    }

    //For each point in the center set
    int totalPoints = config.centers.size();
    int counter = 0;
    for(int i = 0; i < totalPoints; ++i){
        center localCenter = config.centers[i];
        point thePoint = point(localCenter);

        //Add the point to the ordering structure
        if(IsWithinBoundary(width, height, localCenter.x, localCenter.y, visited[localCenter.x][localCenter.y])){
        //if(localCenter.x < width && localCenter.y < height && !visited[localCenter.x][localCenter.y]){
            orderingStructure.add(thePoint);
            visited[localCenter.x][localCenter.y] = true;
            counter++;
            *(config.img.getPixel(thePoint.x, thePoint.y)) = (*config.pickers[i])(thePoint);

            //If the number of frames reache the frame frequency, add to the frame
            if(counter % config.frameFreq == 0) animation.addFrame(config.img);

            //Add the 4 neighbors of the points
            while(!orderingStructure.isEmpty()) {
                point curr = orderingStructure.remove();
                for (int j=0; j< 4; j++) {
                    point temp = curr;
                    temp.x= curr.x + direction[j][0];
                    temp.y= curr.y + direction[j][1];
                    if (temp.x < ((unsigned int) width) && temp.y < ((unsigned int) height) && !visited[temp.x][temp.y]) {
                        if (config.img.getPixel(temp.x, temp.y)->dist(localCenter.color) <= config.tolerance) {
                            orderingStructure.add(temp);
                            counter++;
                            visited[temp.x][temp.y] = true;
                            *(config.img.getPixel(temp.x, temp.y)) = (*config.pickers[i])(temp);
                            if(counter % config.frameFreq == 0) animation.addFrame(config.img);
                        }
                    }
                }
            }
        }
    }
    animation.addFrame(config.img);
    return animation;
}