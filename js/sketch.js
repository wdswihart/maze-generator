const canvasWidth = 801;
const canvasHeight = 601;
const cellRatio = 0.05;
const cellSize = Math.floor(
  canvasWidth > canvasHeight ? canvasWidth * cellRatio : canvasHeight * cellRatio
);
let grid;

function create2DArray(rows, cols) {
  let array = new Array(cols);
  for (let i = 0; i < cols; i++) {
    array[i] = new Array(rows);
  }
  return array;
}

function pickRandomNeighbor(i, j) {
  let pool = [];
  if (i > 0 && grid[i - 1][j].notVisited) {
    pool.push(grid[i - 1][j]);
  }
  if (i < grid.length - 1 && grid[i + 1][j].notVisited) {
    pool.push(grid[i + 1][j]);
  }
  if (j > 0 && grid[i][j - 1].notVisited) {
    pool.push(grid[i][j - 1]);
  }
  if (j < grid[i].length - 1 && grid[i][j + 1].notVisited) {
    pool.push(grid[i][j + 1]);
  }
  if (pool.length > 0) {
    return pool[Math.floor(Math.random() * pool.length)];
  } else {
    return null;
  }
}

function removeWalls(cell, neighbor) {
  let cellWall = '';
  let neighborWall = '';
  if (neighbor.i < cell.i) {
    cellWall = 'W';
    neighborWall = 'E';
  } else if (neighbor.i > cell.i) {
    cellWall = 'E';
    neighborWall = 'W';
  } else if (neighbor.j < cell.j) {
    cellWall = 'N';
    neighborWall = 'S';
  } else {
    cellWall = 'S';
    neighborWall = 'N';
  }
  grid[cell.i][cell.j].removeWall(cellWall);
  grid[neighbor.i][neighbor.j].removeWall(neighborWall);
}

function generate() {
  const start = Math.round(Math.random() * (grid.length - 1));
  grid[start][0].removeWall('N');

  const end = Math.round(Math.random() * (grid.length - 1));
  grid[end][grid[end].length - 1].removeWall('S');

  let stack = [];
  stack.push(grid[start][0]);
  while (stack.length > 0) {
    const current = stack[stack.length - 1];
    if (current) {
      grid[current.i][current.j].notVisited = false;
      const neighbor = pickRandomNeighbor(current.i, current.j);
      if (neighbor) {
        stack.push(neighbor);
        removeWalls(current, neighbor);
      } else {
        stack.pop();
      }
    }
  }
}

function setup() {
  createCanvas(canvasWidth, canvasHeight);
  frameRate(10);

  grid = create2DArray(
    Math.floor(canvasHeight / cellSize),
    Math.floor(canvasWidth / cellSize)
  );
  for (let i = 0; i < grid.length; i++) {
    for (let j = 0; j < grid[i].length; j++) {
      grid[i][j] = new Cell(i, j, cellSize);
    }
  }

  generate();
}

function draw() {
  for (let col of grid) {
    for (let cell of col) {
      cell.draw();
    }
  }
}
