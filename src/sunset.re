module H = Tea.Html;

/* ***** Model : the math or science problem **** */
type model = {
  personHeight: float,
  planetRadius: float,
  planetRotationPeriod: int,
  currentTime: int
};

/* ****** Messages and UPDATE ****** */
type msg =
  | IncRadius
  | DecRadius
  | SetRadius int
  | SetTime int
  | SetHeight int
[@@bs.deriving {accessors: accessors}];

let update (model: model) (msg: msg) => {
  Js.log {j| Model: $model   Message: $msg |j};
  switch msg {
  | IncRadius => {...model, planetRadius: model.planetRadius +. 20.}
  | DecRadius => {...model, planetRadius: model.planetRadius -. 20.}
  | SetRadius i => {...model, planetRadius: float_of_int i}
  | SetTime i => {...model, currentTime: i}
  | SetHeight i => {...model, personHeight: float_of_int i}
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

let view (m: model) => {
  let title = H.h1 [] [H.text "Interactive Sunset"];
  let {personHeight, planetRadius, planetRotationPeriod, currentTime} = m;
  let (planetX0, planetY0) = (200, 200);
  let radius = int_of_float planetRadius;
  let planetCircle = Picture.Circle (planetX0, planetY0) radius Picture.Green;
  let sunCenter = (planetX0 + 3 * radius, planetY0);
  let sunCircle = Picture.Circle sunCenter 3 Picture.Orange;
  let (personFoot, personHead) =
    personPos
      t::currentTime
      rot::planetRotationPeriod
      rad::planetRadius
      height::personHeight
      center::(planetX0, planetY0);
  let personLine = Picture.Line personFoot personHead 4 Picture.Black;
  let topRay = Picture.Line personHead sunCenter 3 Picture.Red;
  let bottomRay = Picture.Line personFoot sunCenter 3 Picture.Orange;
  let btnInc = H.button [H.onClick incRadius] [H.text "Increase radius"];
  let btnDec = H.button [H.onClick decRadius] [H.text "Decrease radius"];
  let radSlider =
    Interaction.slider
      label'::"Radius" min::50 max::200 init::(int_of_float m.planetRadius) action::setRadius;
  let timeSlider =
    Interaction.slider
      label'::"Current Time"
      min::0
      max::m.planetRotationPeriod
      init::m.currentTime
      action::setTime;
  let heightSlider =
    Interaction.slider
      label'::"Height" min::0 max::60 init::(int_of_float m.personHeight) action::setHeight;
  let pic = Picture.picture (1000, 1000) [planetCircle, sunCircle, personLine, topRay, bottomRay];
  H.div
    []
    [
      Picture.stylesheet "https://cdn.rawgit.com/yegor256/tacit/gh-pages/tacit-0.8.1.min.css",
      title,
      H.text {j| Current Time: $currentTime|j},
      btnInc,
      btnDec,
      radSlider,
      timeSlider,
      heightSlider,
      H.div [] [pic]
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
  currentTime: 10000
};

let main: Picture.interactiveDisplay msg = Interaction.interact initialModel view update;
