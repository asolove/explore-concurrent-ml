open Event;

type t 'a;

let create: unit => t 'a;
let swap: t 'a => 'a => event 'a;

