// Generated by BUCKLESCRIPT VERSION 1.10.3, PLEASE EDIT WITH CARE
'use strict';

var Interaction           = require("interactive-pictures/src/interaction.js");
var Draw_ex$PhysicsSunset = require("./draw_ex.bs.js");

function showPersonAt(t) {
  var delta = 120 * Math.sin(t / 250) | 0;
  return Draw_ex$PhysicsSunset.view(/* record */[
              /* base_mood */Draw_ex$PhysicsSunset.initialPerson[/* base_mood */0],
              /* mood_swing */Draw_ex$PhysicsSunset.initialPerson[/* mood_swing */1],
              /* shift */delta
            ]);
}

var main = Interaction.animate(showPersonAt, /* Some */[5.0]);

var Draw = 0;

exports.Draw         = Draw;
exports.showPersonAt = showPersonAt;
exports.main         = main;
/* main Not a pure module */