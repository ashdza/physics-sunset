module H = Tea.Html;

/* *********** Model ******* */
type person = {
  base_mood: int,
  mood_swing: int,
  shift: int
};

type model = {
  person,
  simRate: int
};

/* *********** Messages ******* */
type msg =
  | Inc
  | Dec
  | SetShift int
  | Tick float
  | SetSimRate int
[@@bs.deriving {accessors: accessors}];

/* *********** View ******* */
let viewPerson (p: person) => {
  let {base_mood, mood_swing, shift} = p;
  let mood = base_mood + mood_swing;
  let color = mood < 100 ? Picture.Orange : mood < 150 ? Picture.Pink : Picture.Red;
  /*let color = Picture.Rgb mood 50 100;*/
  let r = max (10 + mood) 10;
  let (headX, headY) = (250 + shift, 260);
  let head = Picture.Circle (headX, headY) r color;
  /*let (bodyLen, bodyThick) = (30, 5);*/
  /*let (bodyTop, bodyBot) = ((headX, headY + r), (headX, headY + r + bodyLen));*/
  /*let torso = Picture.Line bodyTop bodyBot bodyThick Brown;*/
  /*let arms =
    Picture.Line (headX - 15, headY + r + 15) (headX + 15, headY + r + 15) bodyThick Black;*/
  /*let legL = Picture.line bodyBot bodyLen 120 bodyThick Black;*/
  /*let legR = Picture.line bodyBot bodyLen 60 bodyThick Black;*/
  /*Js.log {j|Head: $head Body: $body|j};*/
  Picture.picture (1000, 600) [head] /* , torso, arms, legL, legR] */
};

let view {person, simRate} =>
  H.div
    []
    [
      /* "Model: " ^ toString person ^ " :: Simulation Rate:: " ^ toString simRate */
      H.div [] [H.text {j| Model: $person  :: Simulation Rate:: $simRate |j}],
      H.button [H.onClick Inc] [H.text "Inc Base_Mood"],
      H.button [H.onClick Dec] [H.text "Dec Base_Mood"],
      Interaction.selector
        label'::"Model Shift" choices::[0, 20, 50, 100, 200] init::person.shift action::setShift,
      Interaction.slider label'::"Simulation Rate" min::1 max::10 init::simRate action::setSimRate,
      viewPerson person
    ];

/* *********** Update ******* */
let tickPerson t (p: person) => {
  let delta = 120. *. sin (t /. 250.) |> int_of_float;
  {...p, mood_swing: delta}
};

let update (model: model) (msg: msg) :model =>
  switch msg {
  | Inc => {...model, person: {...model.person, base_mood: model.person.base_mood + 40}}
  | Dec => {...model, person: {...model.person, base_mood: model.person.base_mood - 40}}
  | SetShift i =>
    Js.log ("SetShift : " ^ string_of_int i);
    {...model, person: {...model.person, shift: i}}
  | Tick t => {...model, person: tickPerson (t *. float_of_int model.simRate /. 10.) model.person}
  | SetSimRate i => {...model, simRate: i}
  };

/* *********** Initialize ******** */
let initialModel = {person: {base_mood: 75, mood_swing: 100, shift: 20}, simRate: 1};

let main: Picture.interactiveDisplay msg =
  Interaction.interact initialModel view update every::(20., tick);
