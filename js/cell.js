class Cell {
  constructor(i, j, size) {
    this.i = i;
    this.j = j;
    this.size = size;
    this.notVisited = true;
    this.walls = ['N', 'E', 'S', 'W'];
    this.color = color(255);
  }

  removeWall(wall) {
    this.walls.splice(this.walls.indexOf(wall), 1);
  }

  draw() {
    const x = this.i * this.size;
    const y = this.j * this.size;

    push();
    noStroke();
    fill(this.color);
    rect(x, y, this.size, this.size);
    stroke(0);
    if (this.walls.includes('N', 0)) {
      line(x, y, x + this.size, y);
    }
    if (this.walls.includes('E', 0)) {
      line(x + this.size, y, x + this.size, y + this.size);
    }
    if (this.walls.includes('S', 0)) {
      line(x, y + this.size, x + this.size, y + this.size);
    }
    if (this.walls.includes('W', 0)) {
      line(x, y, x, y + this.size);
    }
    pop();
  }
}
