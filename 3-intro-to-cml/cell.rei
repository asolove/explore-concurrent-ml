type t 'a;

let create: 'a => t 'a;
let get: t 'a => 'a;
let put: (t 'a) => 'a => unit;

