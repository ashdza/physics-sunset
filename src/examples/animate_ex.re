module Draw = Draw_ex;

let showPersonAt (t: float) => {
  let delta = 120. *. sin (t /. 250.) |> int_of_float;
  let p' = {...Draw.initialPerson, Draw.shift: delta};
  Draw.view p'
};

let main: Picture.simpleDisplay = Interaction.animate showPersonAt delta_ms::5.0;
