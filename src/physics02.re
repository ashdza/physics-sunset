/* *****************  Ch 2: Motion in a Straight Line *********** */
type time = float;

type iDistance = float;

type iDisplacement = float;

type iVelocity = float;

type iAcceleration = float;

type tDisplacement = time => iDisplacement;

type tVelocity = time => iVelocity;

type tAcceleration = time => iAcceleration;

let pass () => raise (Failure "pass");

let ashDisplacement: tDisplacement = fun t => 2. *. sin t;

/* *********** Derivatives ***** */
let derivative (f: time => float) :(time => float) => pass ();

let velocityFromDisp (d: time => iDisplacement) :tVelocity => derivative d;

let accelFromVeloc (v: time => iVelocity) :tAcceleration => derivative v;

/* *********** Integrals ***** */
let integral (f: time => float) (c: float) :(time => float) => pass ();

let defIntegral (f: time => float) (t1: time) (t2: time) :float => pass ();

let dispFromVelocity (v: time => iVelocity) (d0: iDisplacement) :tDisplacement => integral v d0;

let velocityFromAccel (a: time => iAcceleration) (v0: iVelocity) :tVelocity => integral a v0;

/* deltas and average displacement, distance, velocity, speed, acceleration */
/* instantaneous as limit of delta */
/* net displacement, total distance, average speed, average velocity, average accelaration */
let netDisplacement (d1: iDisplacement) (d2: iDisplacement) :iDisplacement => d2 -. d1;

let netDisplacementFromVelocity (v: time => iVelocity) (t1: time) (t2: time) :iDisplacement =>
  defIntegral v t1 t2;

let absF (f: float => float) :(float => float) => fun (x: float) => abs_float (f x);

let totalDistance (v: time => iVelocity) (t1: time) (t2: time) :iDistance =>
  defIntegral (absF v) t1 t2;

let totalDistanceFromDisp (d: time => iDisplacement) (t1: time) (t2: time) :iDistance => {
  let vt = derivative d;
  totalDistance vt t1 t2
};

let averageVelocity (d: time => iDisplacement) (t1: time) (t2: time) :iVelocity => {
  let disp = totalDistanceFromDisp d t1 t2;
  disp /. (t2 -. t1)
};
/*let totalDistance ()*/
/* particle */
/* system of particles */
/* auto-diff */
