open Event;

let makeUIdServer = fun () => {
  let ch = new_channel ();
  let rec loop = fun i => { sync(send ch i); loop (i+1) };
  let _ = Thread.create loop 0;
  fun () => receive ch;
}

