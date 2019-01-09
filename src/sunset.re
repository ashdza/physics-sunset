module H = Tea.Html;

/* ***** Model : the math or science problem **** */
type model = {
  personHeight: float,
  planetRadius: float,
  planetRotationPeriod: int,
  currentTime: int,
  sunDistance: float
};

/* ****** Messages and UPDATE ****** */
type msg =
  | IncRadius
  | DecRadius
  | SetRadius int
  | SetTime int
  | SetHeight int
  | SetSunDistance int
[@@bs.deriving {accessors: accessors}];

let update (model: model) (msg: msg) : model => {
  Js.log {j| Model: $model   Message: $msg |j};
  switch msg {
  | IncRadius => {...model, planetRadius: model.planetRadius +. 20.}
  | DecRadius => {...model, planetRadius: model.planetRadius -. 20.}
  | SetRadius r => {...model, planetRadius: float_of_int r}
  | SetTime t => {...model, currentTime: t}
  | SetHeight h => {...model, personHeight: float_of_int h}
  | SetSunDistance d => {...model, sunDistance: float_of_int d}
  }
};

/* ****** VIEW ****** */
let angleAtTime ::t ::rot => (t |> float_of_int) /. (rot |> float_of_int) *. 2.0 *. 3.14159;

let locationAtAngle ::rad ::angle center::(center: (int, int)) => (
  rad *. cos angle +. (fst center |> float_of_int) |> int_of_float,
  rad *. sin angle +. (snd center |> float_of_int) |> int_of_float
);

let personPos ::t ::rot ::rad ::height ::center => {
  let angle = angleAtTime ::t ::rot;
  let footPos = locationAtAngle ::rad ::angle ::center;
  let headPos = locationAtAngle rad::(rad +. height) ::angle ::center;
  (footPos, headPos)
};

let view (m: model) : Vdom.t msg => {
  let title = H.h1 [H.class' "box title"] [H.text "Interactive Sunset"];
  let text = H.div [H.class' "box"] [H.text "The green circle is earth viewed from a pole, the black stick figure is a person at the equator, and the pink dot is the sun.  
  The person would see the sun setting at different times if lying down vs. standing up. 
  The orange and red lines are rays from the sun to the person's feet (person lying down) and head (person standing) respectively. 
  Many variables affect absolute sunset time, some of them affect the difference in sunset times.
  This interactive app lets you explore these variables."];
  let {personHeight, planetRadius, planetRotationPeriod, currentTime} = m;
  let (planetX0, planetY0) = (250, 280);
  let radius = int_of_float planetRadius;
  let planetCircle = Picture.Circle (planetX0, planetY0) radius Picture.Green;
  let sunCenter = (planetX0 + int_of_float(m.sunDistance *. planetRadius /. 100.), planetY0);
  let sunCircle = Picture.Circle sunCenter 8 Picture.Pink;
  let (personFoot, personHead) =
    personPos
      t::currentTime
      rot::planetRotationPeriod
      rad::planetRadius
      height::personHeight
      center::(planetX0, planetY0);
  let personLine = Picture.Line personFoot personHead 4 Picture.Black;
  let topRay = Picture.Line personHead sunCenter 2 Picture.Red;
  let bottomRay = Picture.Line personFoot sunCenter 2 Picture.Orange;
  let btnInc = H.button [H.onClick incRadius, H.class' "button"] [H.text "Radius + 20"];
  let btnDec = H.button [H.onClick decRadius, H.class' "button"] [H.text "Radius - 20"];
  let radSlider =
    Interaction.slider
      label'::"Earth Radius" min::50 max::200 init::(int_of_float m.planetRadius) action::setRadius;
  let sunDistanceSlider =
    Interaction.slider
      label'::"Sun's Distance" min::150 max::500 init::(int_of_float m.sunDistance) action::setSunDistance;
  let timeSlider =
    Interaction.slider
      label'::"Earth Rotation"
      min::0
      max::m.planetRotationPeriod
      init::m.currentTime
      action::setTime;
  let heightSlider =
    Interaction.slider
      label'::"Person's Height" min::0 max::60 init::(int_of_float m.personHeight) action::setHeight;
  let pic = Picture.picture (1100, 1000) [planetCircle, sunCircle, personLine, topRay, bottomRay];
  H.div
    []
    [ title
    , text
    , H.div [H.class' "box"]
        [ H.div [] [H.text {j| Current Time (secs from MidDay): $currentTime|j}]
        , H.div [] [btnInc, btnDec]
        , radSlider
        , timeSlider
        , sunDistanceSlider
        , heightSlider
        ]
    , H.div [] [pic]
    ]
};

/* ******* Initial Model & Main ****** */
let deltaT model => {
  let {planetRadius: r, planetRotationPeriod: rp, personHeight: h} = model;
  let theta = acos (r /. (r +. h));
  let dt = theta *. float_of_int rp /. (2. *. 3.14);
  dt
};

let initialModel = {
  planetRadius: 150.,
  planetRotationPeriod: 24 * 60 * 60,
  personHeight: 20.,
  currentTime: 10000,
  sunDistance: 200.
};

let main: Picture.interactiveDisplay msg = Interaction.interact initialModel view update;
