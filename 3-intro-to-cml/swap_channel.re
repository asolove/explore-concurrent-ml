open Event;

/*
 * A swap channel allows two threads to atomically trade values.
 * Phase 1: one thread sends its value and a reply channel, the other receives.
 * Phase 2: the receiving thread sends its value over the reply channel, the other receives.
 * The new channel is private to the transaction, preventing the second phase
 * of the protocol from syncing with any other threads.
 */
type t 'a = channel ('a, channel 'a);

let create => new_channel ();

let swap ch v => {
  guard(fun () => {
    let swapCh = new_channel ();
    choose [
      wrap (receive ch)
        (fun (msgIn, outCh) => { sync(send outCh v); msgIn; }),
      wrap (send ch (v, swapCh))
        (fun () => { sync(receive(swapCh)) })
    ]
  });
};

