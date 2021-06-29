# graph-process-C++

## Parsed Image into Blocks

- A Linked List is a dynamic linear structure designed to hold any type of data. In this exercise, we develop and use a doubly-linked list to manipulate blocks of pixels from an image.
  ![alt text](./img/block1.png "Logo Title Text 1")

- Each Block is placed into a GridNode of a GridList, as shown here:
  ![alt text](./img/block2.png "Logo Title Text 1")

---

## Automated Imae with Flood Fill

1.  With Border Color Picker

- Using BFS Algorithm

  ![alt text](./img/bfs_border.gif "Logo Title Text 1")

- Using DFS Algorithm

  ![alt text](./img/dfs_border.gif "Logo Title Text 1")

2.  With Solid Color Picker

- Using BFS Algorithm

  ![alt text](./img/bfs_solid.gif "Logo Title Text 1")

- Using DFS Algorithm

  ![alt text](./img/dfs_solid.gif "Logo Title Text 1")

3.  With Fade Color Picker

- Using BFS Algorithm

  ![alt text](./img/bfs_fade.gif "Logo Title Text 1")

- Using DFS Algorithm

  ![alt text](./img/dfs_fade.gif "Logo Title Text 1")

---

## Graph Compression

- The inspiration for this assignment came from an article about an artist whose work recreates classic portraits with a blocky effect. The exact algorithm he used is not given in the article, but we will create similar images using a strategy for image representation that underlies common lossy image compression algorithms.

- The two images below illustrate the result of this assignment. Note that the second image sacrifices color detail in rectangles that do not contain much color variability in the original image, but maintains detail by using smaller rectangles in areas of the original image containing lots of variability.

- Before

  ![alt text](./img/PA3pic1.png "Logo Title Text 1")
- After

  ![alt text](./img/PA3pic2.png "Logo Title Text 1")
