## Overview

An interactive graphical simulation of a physics problem. A person views the sunset at two different times depending on whether she is lying down or standing up. Identify and understand the relevant variables in the problem: the time difference, diameter of the earth, height of person, rate of planet rotation, etc. (The actual textbook problem gave the person's height and time difference, and asked for an estimate of the earth's diameter.)

## Demo

There is an online live demo here: https://physics.7insights.com/public/index.html

Here's an animated gif showing an old version of the app.

![recording](./recording.gif "Recording")

## App Structure

The app is built in `ReasonML`, using `Bucklescript-TEA` which support The Elm Architecture. The code is in a single file `src/sunset.re`. At its core it boils down to just 4 things.

#### Model = State of the App

```
type model = {
  record with fields for all changeable app state
};
```

#### Message = Set of Messages from the UI that the App will handle

```
type msg =
  | variant or 
  | union of 
  | each possible incoming message
```

#### Update = state transition function from current state to next state

```
let update (model: model) (msg: msg) : model => {
    for each model, msg combination, compute next model
};
```

#### View = function from current state to Html (Vdom.t) parameterized by msg

```
let view (m: model) : Vdom.t msg => {
  build html structure from model
  embed callbacks to generate msgs when triggered by the user
};
```

## Misc

Why the interactivity? Well, just because ... it was fun, and I got to learn ReasonML.

What is the file `physics02.re`? It is not related in any way to the project, just a separate side experiment. The file has explanatory comments.

## To Run

Clone this repository, `npm install`, then run `npm run start` and in another shell `npm run webpack`.