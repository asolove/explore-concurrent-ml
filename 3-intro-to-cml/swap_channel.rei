open Event;

type t 'a;

let create: unit => t 'a;
let swap: t 'a => 'a => event 'a;

/* Naive version does not guarantee atomicity */
let faulty_swap: channel 'a => 'a => event 'a;
