let height = 950;
let width = 950;

function setup() {
  createCanvas(width, height);
  background("#BE9E9E");
  strokeWeight(0.6);
  angleMode(DEGREES);
  noLoop();
}

function draw() {
  let roseSize = 200;
  let base = 210;
  drawRose(base, base, roseSize, 6, 31);
  drawRose(base + 2.5 * roseSize, base, roseSize, 8, 67);
  drawRose(base, base + 2.5 * roseSize, roseSize, 4, 119);
  drawRose(base + 2.5 * roseSize, base + 2.5 * roseSize, roseSize, 10, 119);
}

function drawRose(xOffset, yOffset, a, n, d) {
  stroke("#9A0D0D");
  noFill();
  beginShape();
  for (var i = 0; i < 361; i++) {
    let k = i * d;
    let x = a * sin(k * n) * cos(k);
    let y = a * sin(k * n) * sin(k);
    vertex(x + xOffset, y + yOffset);
  }
  endShape(CLOSE);
}
