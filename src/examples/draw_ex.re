type person = {
  base_mood: int,
  mood_swing: int,
  shift: int
};

let initialPerson = {base_mood: 75, mood_swing: 100, shift: 20};

let view (p: person) => {
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

let main: Picture.simpleDisplay = Interaction.draw (view initialPerson);

type shape =
  | Square int
  | Circle int
  | Rect int int
[@@bs.deriving {accessors: accessors}];

let r4 = rect 4;

let area s =>
  switch s {
  | Square x => x * x
  | Circle r' =>
    let r = float_of_int r';
    2. *. 3.142 |> ( *. ) r |> ( *. ) r |> int_of_float
  | Rect x y => x * y
  };
