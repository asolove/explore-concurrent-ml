
let ch = Event.new_channel ();
let ch2 = Event.new_channel ();

let receiver ch => {
  print_string "Ready to receive\n";
  let value = Event.sync (Event.receive ch);
  print_string ("Did receive: " ^ value ^ "\n");
};

let sender ch => {
  print_string("Ready to send\n");

  let send_ev = Event.send ch "Hello, Reason!";
  let wont_send_ev = Event.send ch2 "This won't succeed";
  let wont_send_ev_wrapped = Event.wrap_abort wont_send_ev (fun () => { print_string "Didn't send 2!\n"; });

  let choose_ev = Event.choose [send_ev, wont_send_ev_wrapped];
  Event.sync choose_ev;

  print_string "Did send!\n";
};

let t1 = Thread.create receiver ch;
let t2 = Thread.create sender ch;

print_string "Threads created\n";

Thread.join t2;
Thread.join t1;
