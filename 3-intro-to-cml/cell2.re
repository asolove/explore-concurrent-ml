type t 'a = {
  getCh: Event.channel 'a,
  putCh: Event.channel 'a
};

let get {getCh} => Event.sync (Event.receive getCh);
let put {putCh} v => Event.sync (Event.send putCh v);

let create v => {
  let getCh = Event.new_channel ();
  let putCh = Event.new_channel ();

  let rec loop v => Event.select [
    Event.wrap (Event.send getCh v) (fun unit => { loop v; }),
    Event.wrap (Event.receive putCh) loop
  ];

  let _ = Thread.create loop v;
  {getCh, putCh}
};
