let height = 900;
let width = 700;

function setup() {
  createCanvas(width, height);
  background("#BE9E9E");
  strokeWeight(0.8);
  noLoop();
}

function draw() {
  let roseSize = 40;

  // drawing roses
  let yOffset = 0;
  for (var d = 1; d <= 9; d++) {
    let xOffset = 0;
    for (var n = 1; n <= 7; n++) {
      drawRose(50 + xOffset, 50 + yOffset, roseSize, n, d);
      xOffset += 2.5 * roseSize;
    }
    yOffset += 2.5 * roseSize;
  }
}

function drawRose(xOffset, yOffset, a, n, d) {
  // A rose is the set of points in polar coordinates        specified by the polar equation r = a * cos(k*theta)
  let k = n / d;
  stroke("#9A0D0D");
  for (var theta = 0; theta <= d * TWO_PI; theta += 0.001) {
    let x = a * cos(k * theta) * cos(theta);
    let y = a * cos(k * theta) * sin(theta);
    point(x + xOffset, y + yOffset);
  }
}
