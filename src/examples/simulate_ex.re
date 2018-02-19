module Draw = Draw_ex;

type person = Draw_ex.person;

let initialPerson = Draw_ex.initialPerson;

let view = Draw_ex.view;

let updatePerson t (p: person) => {
  let delta = 100. *. sin (t /. 250.) |> int_of_float;
  {...p, Draw.mood_swing: delta}
};

let main: Picture.simpleDisplay =
  Interaction.simulate initialPerson view updatePerson delta_ms::10.0;
