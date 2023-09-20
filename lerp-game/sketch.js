let from, to, f, playerPosition;
var clicks = 0;
let height = 450;
let width = 550;
let gameOver = false;

// enemies
let e_a = [],
  e_b = [],
  e_p = [];
let e_f = [],
  e_m = [];
let num_enemies = 10;

function setup() {
    createCanvas(width, height);
    textSize(20);
    font = loadFont('PressStart2P-Regular.ttf');

    // initialize player vectors 
    from = createVector(0,0);
    to = createVector(0,0);
    f = 0;

    // initialize the enemies
    for (let i = 0; i < num_enemies; i++) { // for each enemy
        // random route:
        e_a[i] = createVector(random(20, width-20), random(20, height-20));
        e_b[i] = createVector(random(20, width-20), random(20, height-20));
        // random start and movement speed:
        e_f[i] = random(0, 1);
        e_m[i] = random(0.005, 0.025);
        }
}

function draw() {
    background(0);
    stroke(255);

    // update player position, movement
    stroke("#DC9639");
    fill("#DC9639");
    playerPosition = p5.Vector.add(p5.Vector.mult(from, 1 - ease(f)), p5.Vector.mult(to, ease(f)));
    ellipse(playerPosition.x, playerPosition.y, 10, 10);
    if (f < 1) {
    f = f + 0.01;
    }

    // update number of clicks
    text('clicks: ' + clicks, 50, height-50);

    // move and paint the enemy:
    stroke("#702626");
    fill("#702626");
    for (let i = 0; i < num_enemies; i++) {
      e_p[i] = p5.Vector.add(p5.Vector.mult(e_a[i], 1 - ease(e_f[i])), p5.Vector.mult(e_b[i], ease(e_f[i])));
      ellipse(e_p[i].x, e_p[i].y, 20, 20);
      // move per frame:
      e_f[i] = e_f[i] + e_m[i];
      // turn around after reaching end point:
      if (e_f[i] >= 1 || e_f[i] <= 0)
        e_m[i] = -e_m[i];
      // check for collisions
      if (checkCollision(playerPosition.x, playerPosition.y, 10, e_p[i].x, e_p[i].y, 20)){
        gameOver = true;
      }
    }
  
  if (gameOver){
    push();
    textSize(36);
    textFont(font);
    stroke("#FFFAFA");
    fill("#FFFFFF");
    textAlign(CENTER);
    text('GAME OVER', width/2, height/2);
    pop();
  }
    

}

function mousePressed() {
  clicks ++;
}

function mouseReleased() {
  from = createVector(playerPosition.x, playerPosition.y);
  to = createVector(mouseX, mouseY);
  f = 0;
}

function ease(f) {
  //return f*f*f; // smooth start
  return 1 - (1 - f) * (1 - f) * (1 - f); // smooth stop
  // return (1-f)*(f*f) + (f)*(1-(1-f)*(1-f)); // blend both ...
}

function checkCollision(Px, Py, Pr, Ex, Ey, Er){
 	if(dist(Px, Py, Ex, Ey) < Pr + Er ) {
    return true;
  } else {
   	return false; 
  }
}